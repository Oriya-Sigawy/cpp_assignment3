
// 214984932 Oriyas.07@gmail.com
#include <array>
#include <vector>
#include <utility>
#include <iostream>
#include "Catan.hpp"
#include "Board.hpp"
using std::array;
using std::pair;
using std::vector;
Catan::Catan()
{
    biggestArmy = std::make_pair(-1, 3);
    createDCs(); //  create develop cards
}
void Catan::createDCs()
{
    int offset = 0;
    DCType types[] = {KNIGHT, VICTORY_POINT, MONOPOLY, YEAR_OF_PLENTY, ROAD_BUILDING};
    unsigned int counts[] = {14, 5, 2, 2, 2};
    for (int i = 0; i < TYPES_COUNT; i++)
    {
        for (unsigned int j = 0; j < counts[i]; j++)
        {
            DevelopCard dc =
                {
                    types[i],
                    nullptr,
                    false,
                };
            this->game_dcs[offset] = dc;
            offset++;
        }
    }
}

unsigned int Catan::rollDice()
{
    unsigned int roll = 0;
    roll += rand() % 6 + 1;
    roll += rand() % 6 + 1;
    return roll;
}

void Catan::allocateResources(unsigned int diceRoll)
{
    if (diceRoll == 0)
    {
        this->game_board.resourcesAllocationForBeginnig();
    }
    else
    {
        this->game_board.resourcesAllocation(diceRoll);
    }
}

int Catan::buildRoad(Player *p, unsigned int i1, unsigned int i2, bool start)
{
    if (!start)
    {
        if (p->getResourceCount(BRICK) < 1 || p->getResourceCount(LUMBER) < 1)
        {
            return -2; // not enough resources
        }
    }
    int x = this->game_board.build_road(p, i1, i2, start);
    if (x == 0 && !start)
    {
        p->updateResource(BRICK, -1);
        p->updateResource(LUMBER, -1);
    }
    return x;
}
int Catan::buildSettlement(Player *p, unsigned int s, bool start)
{
    if (!start)
    {
        if (p->getResourceCount(BRICK) < 1 || p->getResourceCount(LUMBER) < 1 || p->getResourceCount(WOOL) < 1 || p->getResourceCount(GRAIN) < 1)
        {
            return -2; // not enough resources
        }
    }
    int x = this->game_board.build_settlement(p, s, start);
    if (x == 0 && !start)
    {
        p->updateResource(BRICK, -1);
        p->updateResource(LUMBER, -1);
        p->updateResource(WOOL, -1);
        p->updateResource(GRAIN, -1);
    }
    return x;
}

int Catan::updateToCity(Player *p, unsigned int s)
{
    if (p->getResourceCount(ORE) < 3 || p->getResourceCount(GRAIN) < 2)
    {
        return -1; // not enough resources
    }
    int result = this->game_board.updateToCity(p, s);
    if (result == 0)
    {
        p->updateResource(ORE, -3);
        p->updateResource(GRAIN, -2);
        p->updateVictoryPoints(1);
    }
    return result;
}

int Catan::buyDevelopCard(Player *p, DCType dc)
{
    if (p->getResourceCount(WOOL) < 1 || p->getResourceCount(GRAIN) < 1 || p->getResourceCount(ORE) < 1)
    {
        return -1; // not enough resources
    }
    for (unsigned int i = 0; i < COUNT_DCS; i++)
    {
        if (this->game_dcs[i].type == dc && this->game_dcs[i].owner == nullptr)
        {
            this->game_dcs[i].owner = p;
            p->updateResource(WOOL, -1);
            p->updateResource(GRAIN, -1);
            p->updateResource(ORE, -1);
            return 0;
        }
    }
    return -2; // there is no available DC from type dc
}

bool Catan::dcHasOwner(unsigned int i)
{
    return this->game_dcs[i].owner != nullptr;
}

int Catan::canUseDC(Player *p, DCType dc)
{
    for (int i = 0; i < COUNT_DCS; i++)
    {
        if (this->game_dcs[i].type == dc && dcHasOwner((unsigned int)i) && this->game_dcs[i].owner->getID() == p->getID() && !this->game_dcs[i].used)
        {
            return i;
        }
    }
    return -1; // can not use this DC (p do not have unused DC of dc type)
}
int Catan::getOwnerOfBiggestArmy()
{
    return this->biggestArmy.first;
}
int Catan::useKnight(Player *p, Player *p2, int index)
{
    p->updateKnightsCount(1);
    if (p->getKnightsCount() >= biggestArmy.second)
    {
        if (p->getID() != p2->getID())
        {
            p2->updateVictoryPoints(-2);
        }
        p->updateVictoryPoints(2);
        biggestArmy.first = p->getID();
    }
    this->game_dcs[index].used = true;
    return 0;
}
int Catan::useVictoryPoint(Player *p, int index)
{
    p->updateVictoryPoints(1);
    this->game_dcs[index].used = true;
    return 0;
}
int Catan::useYearOfPlenty(Player *p, resourceType r1, resourceType r2, int index)
{
    try
    {
        p->updateResource(r1, 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    try
    {
        p->updateResource(r2, 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    this->game_dcs[index].used = true;
    return 0;
}
int Catan::useMonopoly(Player *p, resourceType rt, array<Player *, COUNT_PLAYERS> players, int index)
{
    unsigned int sum = 0;
    unsigned int resourceCount = 0;
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        if (players[i]->getID() != p->getID())
        {
            try
            {
                resourceCount = players[i]->getResourceCount(rt);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                return -1;
            }
            sum += resourceCount;
            try
            {
                players[i]->updateResource(rt, -1 * resourceCount);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                return -1;
            }
        }
    }
    try
    {
        p->updateResource(rt, sum);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    this->game_dcs[index].used = true;
    return 0;
}
int Catan::useRoadBuilding(Player *p, pair<unsigned int, unsigned int> r1, pair<unsigned int, unsigned int> r2, int index)
{
    int result = this->game_board.build_road(p, r1.first, r1.second, false);
    if (result != 0) // failed
    {
        return result;
    }
    result = this->game_board.build_road(p, r2.first, r2.second, false);
    if (result == 0) // succeed
    {
        this->game_dcs[index].used = true;
    }
    return result;
}

void Catan::trade(vector<pair<resourceType, unsigned int>> resourcesToTrade, Player *giveTo, Player *takeFrom)
{
    for (unsigned int i = 0; i < resourcesToTrade.size(); i++)
    {
        giveTo->updateResource(resourcesToTrade[i].first, resourcesToTrade[i].second);
        takeFrom->updateResource(resourcesToTrade[i].first, (-1 * resourcesToTrade[i].second));
    }
}
bool Catan::check_winner(Player *p)
{
    if (p->getVictoryPoints() >= POINTS_TO_WIN)
    {
        return true;
    }
    return false;
}
