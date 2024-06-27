// 214984932 Oriyas.07@gmail.com
#include <utility>
#include "Board.hpp"
#include "Player.hpp"
using std::pair;

Board::Board()
{
    // initialize
    createIntersections();
    createHexagon(10, ORE, 0, 1, 4, 5, 8, 9, 13);
    createHexagon(2, WOOL, 1, 2, 5, 9, 14, 10, 6);
    createHexagon(9, LUMBER, 2, 3, 6, 10, 15, 11, 7);
    createHexagon(12, GRAIN, 3, 8, 12, 13, 17, 18, 23);
    createHexagon(6, BRICK, 4, 9, 13, 14, 18, 19, 24);
    createHexagon(4, WOOL, 5, 10, 14, 15, 19, 20, 25);
    createHexagon(10, BRICK, 6, 11, 15, 16, 20, 21, 26);
    createHexagon(9, GRAIN, 7, 17, 22, 23, 28, 29, 34);
    createHexagon(11, LUMBER, 8, 18, 23, 24, 29, 30, 35);
    createHexagon(0, DESERT, 9, 19, 24, 25, 30, 31, 36);
    createHexagon(3, LUMBER, 10, 20, 25, 26, 31, 32, 37);
    createHexagon(8, ORE, 11, 21, 26, 27, 32, 33, 38);
    createHexagon(8, LUMBER, 12, 29, 34, 35, 39, 40, 44);
    createHexagon(3, ORE, 13, 30, 35, 36, 40, 41, 45);
    createHexagon(4, GRAIN, 14, 31, 36, 37, 41, 42, 46);
    createHexagon(5, WOOL, 15, 32, 37, 38, 42, 43, 47);
    createHexagon(5, BRICK, 16, 40, 44, 45, 48, 49, 52);
    createHexagon(6, GRAIN, 17, 41, 45, 46, 49, 50, 53);
    createHexagon(11, WOOL, 18, 42, 46, 47, 50, 51, 54);

    roads_offset = 0;
    for (unsigned int i = 1, j = 54; i < 4; i++, j--)
    {
        createRoad(i, i + 3);
        createRoad(i, i + 4);
        createRoad(i + 3, i + 7);
        createRoad(j, j - 3);
        createRoad(j - 3, j - 7);
        createRoad(j, j - 4);
    }

    for (unsigned int i = 8, j = 47; i < 12; i++, j--)
    {
        createRoad(i, i + 4);
        createRoad(i, i + 5);
        createRoad(j, j - 4);
        createRoad(j, j - 5);
        createRoad(i + 4, i + 9);
        createRoad(j - 4, j - 9);
    }

    for (unsigned int i = 17, j = 38; i < 22; i++, j--)
    {

        createRoad(i, i + 5);
        createRoad(i, i + 6);
        createRoad(j, j - 5);
        createRoad(j, j - 6);
        createRoad(i + 5, i + 11);
    }
    createRoad(7, 11);
    createRoad(16, 21);
    createRoad(27, 33);
    createRoad(34, 39);
    createRoad(44, 48);
}
void Board::createHexagon(unsigned int dn, resourceType rt, int id, int i1, int i2, int i3, int i4, int i5, int i6)
{

    Hexagon h = {
        dn, // dice-number
        rt, // resource
        id, // ID of the land
        // list of the intersections on the land
        {&this->intersections[i1 - 1], &this->intersections[i2 - 1], &this->intersections[i3 - 1], &this->intersections[i4 - 1], &this->intersections[i5 - 1], &this->intersections[i6 - 1]},
    };
    lands[id] = h;
}
void Board::createIntersections()
{
    for (unsigned int i = 0; i < COUNT_INTERSECTIONS; i++)
    {
        Settlement s = {
            false,
            nullptr,
        };
        Intersection inter = {
            i,
            s,
        };
        this->intersections[i] = inter;
    }
}
void Board::createRoad(unsigned int i1, unsigned int i2)
{
    pair<unsigned int, unsigned int> p(i1, i2);
    Road r = {
        .owner = nullptr,
        .intersections = p,
    };

    this->roads[roads_offset] = r;
    roads_offset++;
}

bool Board::roadHasOwner(unsigned int x)
{
    return this->roads[x].owner != nullptr;
}
bool Board::interHasOwner(unsigned int x)
{
    return this->intersections[x].s.owner != nullptr;
}
bool Board::myinterHasOwner(unsigned int l, unsigned int x)
{
    return lands[l].myIntersections[x]->s.owner != nullptr;
}

int Board::build_road(Player *p, unsigned int i1, unsigned int i2, bool start)
{
    if (i1 >= COUNT_ROADS || i2 >= COUNT_ROADS)
    {
        return -3; // out of bounds
    }
    bool canBuild = false;
    if (!start) // means that the road needs to be connected to another of p's roads
    {
        for (unsigned int i = 0; i < COUNT_ROADS; i++)
        {
            unsigned int f = this->roads[i].intersections.first;
            unsigned int s = this->roads[i].intersections.second;
            // checks that the road is connected to another of p's roads
            if (((f == i1 && s != i2) || (f == i2 && s != i1) || (f != i1 && s == i2) || (f != i2 && s == i1)))
            {
                if (roadHasOwner(i) && (this->roads[i].owner->getID() == p->getID()))
                {
                    canBuild = true;
                    break;
                }
            }
        }
        // checks that the road is connected to one of p's settlements
        if ((interHasOwner(i1 - 1) && this->intersections[i1 - 1].s.owner->getID() == p->getID()) || (interHasOwner(i2 - 1) && this->intersections[i2 - 1].s.owner->getID() == p->getID()))
        {
            canBuild = true;
        }
        if (!canBuild)
        {
            return -1; // there is no road or settlement of p connect to the road
        }
    }
    if (start || canBuild)
    {
        for (unsigned int i = 0; i < COUNT_ROADS; i++)
        {
            unsigned int f = this->roads[i].intersections.first;
            unsigned int s = this->roads[i].intersections.second;
            if ((f == i1 && s == i2) || (f == i2 && s == i1))
            {
                if (!roadHasOwner(i))
                {
                    this->roads[i].owner = p;
                    return 0; // success
                }
                else
                {
                    return -1; // the road belongs to someone else
                }
            }
        }
    }
    return -3; // there is no road between i1 to i2
}
int Board::build_settlement(Player *p, unsigned int s, bool start)
{
    if (s >= COUNT_INTERSECTIONS)
    {
        return -3; // out of bounds
    }
    for (unsigned int i = 0; i < COUNT_ROADS; i++)
    {
        // if the settlement is in the edge of one of p's roads
        if (start || (roadHasOwner(i) && this->roads[i].owner->getID() == p->getID() && (this->roads[i].intersections.first == (s) || this->roads[i].intersections.second == (s))))
        {
            for (unsigned int j = 0; j < COUNT_INTERSECTIONS; j++)
            {
                if (this->intersections[j].ID == (s - 1))
                {
                    if (!(interHasOwner(j)))
                    {
                        this->intersections[j].s.owner = p;
                        p->updateVictoryPoints(1);
                        return 0; // success
                    }
                    else
                    {
                        return -1; // the settlement belongs to someone else
                    }
                    break;
                }
            }
        }
    }
    return -3; // there is no road near this settlement that belongs to p
}
void Board::resourcesAllocation(unsigned int num)
{
    for (unsigned int i = 0; i < COUNT_LANDS; i++)
    {
        if (this->lands[i].diceNum == num)
        {
            for (unsigned int j = 0; j < COUNT_INERS_ON_LAND; j++)
            {
                if (myinterHasOwner(i, j))
                {
                    unsigned int x = 1;
                    if (this->lands[i].myIntersections[j]->s.isCity) // city gives 2 of the resource instead of 1
                    {
                        x++;
                    }
                    this->lands[i].myIntersections[j]->s.owner->updateResource(this->lands[i].resource, x);
                }
            }
        }
    }
}

void Board::resourcesAllocationForBeginnig()
{
    for (unsigned int i = 0; i < COUNT_LANDS; i++)
    {
        for (unsigned int j = 0; j < COUNT_INERS_ON_LAND; j++)
        {
            if (myinterHasOwner(i, j))
            {
                this->lands[i].myIntersections[j]->s.owner->updateResource(this->lands[i].resource, 1);
            }
        }
    }
}

int Board::updateToCity(Player *p, unsigned int s)
{
    if (s >= COUNT_INTERSECTIONS)
    {
        return -4; // out of bounds
    }
    if (interHasOwner(s - 1))
    {
        if (this->intersections[s - 1].s.owner->getID() != p->getID())
        {
            return -2; // the city belongs to someone else
        }
        else
            (!this->intersections[s - 1].s.isCity)
            {
                this->intersections[s - 1].s.isCity = true;
                return 0; // success
            }
    }
    return -3; // the city does not belong to anyone or if s is already a city
}