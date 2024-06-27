//214984932 oriyas.07@gmail.com
#include <iostream>
#include <string>
#include <utility>
#include "Frontend.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;

int player_offset = 0;

Frontend::Frontend() : players{0, 0, 0}
{
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        Player p(i);
        this->players[i] = p;
    }
    this->turn = &this->players[0];
    player_offset++;
}

bool Frontend::chooseRoadF(Player *p, bool start)
{
    unsigned int i1;
    unsigned int i2;
    cout << "Player " << p->getID() << ", please choose a road." << endl;
    cout << "Usage: <INTERSECTION1_NUM> <INTERSECTION2_NUM>" << endl;
    cin >> i1 >> i2;
    int result = this->game.buildRoad(p, i1, i2, start);
    if (result == -2)
    {
        cout << "You do not have enough resources!" << endl;
    }
    if (result == -1)
    {
        cout << "You can not choose this road!" << endl;
    }
    if (result == -3)
    {
        cout << "This road does not exist!" << endl;
    }
    return result == 0;
}

bool Frontend::chooseSettlementF(Player *p, bool start)
{
    unsigned int s;
    cout << "Player " << p->getID() << ", please choose a settlement." << endl;
    cout << "Usage: <INTERSECTION_NUM>" << endl;
    cin >> s;
    int result = this->game.buildSettlement(p, s, start);
    if (result == -2)
    {
        cout << "You do not have enough resources!" << endl;
    }
    if (result == -1)
    {
        cout << "You can not choose this settlement!" << endl;
    }
    if (result == -3)
    {
        cout << "This settlement does not exist!" << endl;
    }
    return result == 0;
}

bool Frontend::updateToCityF()
{
    unsigned int s;
    cout << "Player " << this->turn->getID() << ", which settlement do you want to update?" << endl;
    cin >> s;
    int result = this->game.updateToCity(this->turn, s);
    if (result == -1)
    {
        cout << "You do not have enough resources!" << endl;
    }
    if (result == -2)
    {
        cout << "You can not choose this settlement!" << endl;
    }
    if (result == -3)
    {
        cout << "This is already a city" << endl;
    }
    if (result == -4)
    {
        cout << "This is not a settlement!" << endl;
    }
    return result == 0;
}
void Frontend::seven_in_dice()
{
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        unsigned int resourcesCount = this->players[i].getResourcesCount();
        if (resourcesCount <= 7)
        {
            break;
        }
        while (resourcesCount > 7)
        {
            cout << "Please choose a resource to give up on" << endl;
            char r;
            cin >> r;
            cout << "Please choose amount" << endl;
            int x;
            cin >> x;
            resourceType rt;
            try
            {
                rt = convertToRT(r);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            try
            {
                this->players[i].updateResource(rt, -1 * x);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                continue;
            }
            resourcesCount -= x;
        }
    }
}

bool Frontend::tradeF()
{
    unsigned int tradeWith;
    cout << "Please enter the number of the player you want to trade with" << endl;
    cin >> tradeWith;
    if (tradeWith >= COUNT_PLAYERS)
    {
        cout << "This is not a player number." << endl;
        return false;
    }
    if (tradeWith == (unsigned int)this->turn->getID())
    {
        cout << "You can not trade with yourself" << endl;
        return false;
    }
    Player *playerToTradeWith;
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        if ((unsigned int)this->players[i].getID() == tradeWith)
        {
            playerToTradeWith = &(this->players[i]);
        }
    }
    cout << "Please enter the resources you want to accept and amount for each one of them. To finish, press enter." << endl;
    cout << "Usage: <RESOURCE_TYPE> <AMOUNT>.... <ENTER>" << endl;
    vector<pair<resourceType, unsigned int>> wanted;
    try
    {
        wanted = makeVectorOfResources(this->turn);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    cout << "Please enter the resources you want to give up on and amount for each one of them. To finish, press enter." << endl;
    cout << "Usage: <RESOURCE_TYPE> <AMOUNT>.... <ENTER>" << endl;
    vector<pair<resourceType, unsigned int>> willingToGive;
    try
    {
        willingToGive = makeVectorOfResources(this->turn);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    cout << "Player " << playerToTradeWith->getID() << ", player " << this->turn->getID() << "wants:" << endl;
    for (unsigned int i = 0; i < wanted.size(); i++)
    {
        cout << wanted[i].second << " " << convertResourceToString(wanted[i].first) << endl;
    }
    cout << "In exchange to:" << endl;
    for (unsigned int i = 0; i < willingToGive.size(); i++)
    {
        cout << willingToGive[i].second << " " << convertResourceToString(willingToGive[i].first) << endl;
    }
    cout << "Player " << playerToTradeWith->getID() << ", do you agree?" << endl;
    cout << "Press y for yes, n for no" << endl;
    char choice;
    cin >> choice;
    switch (choice)
    {
    case 'y':
        this->game.trade(wanted, this->turn, playerToTradeWith);
        this->game.trade(willingToGive, playerToTradeWith, this->turn);
        return true;
    case 'n':
        cout << "Player " << this->turn->getID() << ", you can not make this trade." << endl;
        return false;
    default:
        cout << "Invalid argument. Trade failed" << endl;
        break;
    }
    return false;
}
vector<pair<resourceType, unsigned int>> Frontend::makeVectorOfResources(Player *p)
{
    vector<pair<resourceType, unsigned int>> result;
    char resource;
    unsigned int amount;
    cin >> resource;
    while (resource != '\n')
    {
        cin >> amount;
        resourceType rt;
        try
        {
            rt = convertToRT(resource);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        if (p->getResourceCount(rt) < amount)
        {
            throw std::invalid_argument("You can not make this trade!");
        }
        pair<resourceType, unsigned int> toStack(rt, amount);
        result.push_back(toStack);
        cin >> resource;
    }
    return result;
}

resourceType Frontend::convertToRT(char c)
{
    switch (c)
    {
    case 'o':
        return ORE;
    case 'g':
        return GRAIN;
    case 'w':
        return WOOL;
    case 'l':
        return LUMBER;
    case 'b':
        return BRICK;
    default:
        throw std::invalid_argument("This is not a resource!");
        break;
    }
}
DCType Frontend::convertToDCType(char t)
{
    switch (t)
    {
    case 'k':
        return KNIGHT;
    case 'm':
        return MONOPOLY;
    case 'r':
        return ROAD_BUILDING;
    case 'p':
        return YEAR_OF_PLENTY;
    case 'v':
        return VICTORY_POINT;
    default:
        throw std::invalid_argument("this is not a dc type!");
    }
}
bool Frontend::buyDC_F()
{
    char c;
    cout << "Please enter the type of the DC you want to buy" << endl;
    cin >> c;
    DCType dc;
    try
    {
        dc = convertToDCType(c);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    int result = this->game.buyDevelopCard(this->turn, dc);
    if (result == -1)
    {
        cout << "You do not have enough resources!" << endl;
    }
    if (result == -2)
    {
        cout << "There is no avaliable card of this kind" << endl;
    }
    return result == 0 ? true : false;
}
bool Frontend::useDC_F()
{
    char c;
    cout << "Please choose the type of the develop card you want to use" << endl;
    cin >> c;
    DCType dc = convertToDCType(c);
    int index = this->game.canUseDC(this->turn, dc); // return the index on the DCs array
    if (index == -1)
    {
        cout << "You do not have this develop card!" << endl;
        return false;
    }
    switch (dc)
    {
    case KNIGHT:
        if (this->game.getOwnerOfBiggestArmy() == -1)
        {
            this->game.useKnight(this->turn, this->turn, index);
        }
        else
        {
            for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
            {
                if (this->players[i].getID() == this->game.getOwnerOfBiggestArmy())
                    this->game.useKnight(this->turn, &this->players[i], index);
            }
        }
        break;
    case VICTORY_POINT:
        this->game.useVictoryPoint(this->turn, index);
        break;
    case MONOPOLY:
        useMDC_F(index);
        break;
    case ROAD_BUILDING:
        this->useRB_F(index);
        break;
    case YEAR_OF_PLENTY:
        return useYOP_F(index);
    default:
        cout << "This is not a type!" << endl;
        return false;
    }
    return true;
}

bool Frontend::useRB_F(int index)
{
    unsigned int r1, r2;
    cout << "Player " << this->turn->getID() << ", please choose the first road you want to buy" << endl;
    cin >> r1 >> r2;
    unsigned int r3, r4;
    cout << "Player " << this->turn->getID() << ", please choose the second road you want to buy" << endl;
    cin >> r3 >> r4;
    pair<unsigned int, unsigned int> p1(r1, r2);
    pair<unsigned int, unsigned int> p2(r3, r4);
    return (this->game.useRoadBuilding(this->turn, p1, p2, index)) == 0 ? true : false;
}
bool Frontend::useYOP_F(int index)
{
    char r1, r2;
    cout << "Player " << this->turn->getID() << ", which resources do you want?" << endl;
    cout << "Usage: <RESOURCE> <RESOURCE>" << endl;
    cin >> r1 >> r2;
    resourceType rt1;
    try
    {
        rt1 = convertToRT(r1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    resourceType rt2;
    try
    {
        rt2 = convertToRT(r2);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return this->game.useYearOfPlenty(this->turn, rt1, rt2, index) == 0 ? true : false;
}

bool Frontend::useMDC_F(int index)
{
    cout << "Player " << this->turn->getID() << ", please choose a resource" << endl;
    char r;
    cin >> r;
    resourceType rt;
    try
    {
        rt = convertToRT(r);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    array<Player *, COUNT_PLAYERS> temp_players;
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        temp_players[i] = &this->players[i];
    }

    return this->game.useMonopoly(this->turn, rt, temp_players, index);
}
string Frontend::convertResourceToString(resourceType rt)
{
    switch (rt)
    {
    case WOOL:
        return "wool";
    case GRAIN:
        return "grain";
    case BRICK:
        return "brick";
    case ORE:
        return "ore";
    case DESERT:
        return "";
    case LUMBER:
        return "lumber";

    default:
        break;
    }
    return "";
}

Player Frontend::getPlayer(unsigned int i)
{
    return this->players[i];
}

Player *Frontend::getTurn()
{
    return this->turn;
}

void Frontend::next()
{
    player_offset++;
    this->turn = &(this->players[player_offset % COUNT_PLAYERS]);
}
void Frontend::initialBuild()
{
    for (unsigned int i = 0; i < COUNT_PLAYERS; i++)
    {
        bool success = false;
        while (!success)
        {
            success = chooseRoadF(&(this->players[i]), true);
        }
        success = false;
        while (!success)
        {
            success = chooseSettlementF(&(this->players[i]), true);
        }
    }
    for (unsigned int i = COUNT_PLAYERS; i > 0; i--)
    {
        bool success = false;
        while (!success)
        {
            success = chooseRoadF(&(this->players[i]), true);
        }
        success = false;
        while (!success)
        {
            chooseSettlementF(&(this->players[i]), true);
        }
    }
}
bool Frontend::finish()
{
    return this->game.check_winner(this->turn);
}

void Frontend::rollDice_F(unsigned int num)
{
    unsigned int dice_roll;
    if (num == 0)
    {
        dice_roll = game.rollDice();
    }
    cout << "dice_roll is " << dice_roll << endl;
    if (dice_roll == 7)
    {
        seven_in_dice();
    }
    game.allocateResources(dice_roll);
}

void Frontend::allocateFB()
{
    this->game.allocateResources(0);
}

int main()
{
    srand(time(NULL));
    Frontend frontend;
    frontend.initialBuild();
    frontend.allocateFB();
    while (!(frontend.finish()))
    {
        frontend.rollDice_F(0);
        Player *turn = frontend.getTurn();
        bool madeSomething = false;
        while (!madeSomething)
        {
            char user_ans;
            cout << "Player " << turn->getID() << " , what to you want to do?" << endl;
            cout << "Press N for nothing, T for trade, R for build a road, S for build a settlement, C to update settlement to city, D to buy develop card or U to use develop card" << endl;
            cin >> user_ans;
            switch (user_ans)
            {
            case 'N':
                break;
            case 'T':
                madeSomething = frontend.tradeF();
                break;
            case 'R':
                madeSomething = frontend.chooseRoadF(turn, false);
                break;
            case 'S':
                madeSomething = frontend.chooseSettlementF(turn, false);
                break;
            case 'C':
                madeSomething = frontend.updateToCityF();
                break;
            case 'D':
                madeSomething = frontend.buyDC_F();
                break;
            case 'U':
                try
                {
                    madeSomething = frontend.useDC_F();
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                    continue;
                }
                break;
            default:
                cout << "This was not one of the options!" << endl;
                break;
            }
        }
        frontend.next();
    }
    cout << "Player" << frontend.getTurn()->getID() << "is the winner!" << endl;
    return 0;
}