#pragma once
#include <array>
#include <utility>
#include "Player.hpp"
using std::array;
using std::pair;

#define COUNT_INERS_ON_LAND 6
#define COUNT_INTERSECTIONS 54
#define COUNT_LANDS 19
#define COUNT_ROADS 72
typedef struct
{
    bool isCity;
    Player *owner;
} Settlement;

typedef struct
{
    unsigned int ID;
    Settlement s;
} Intersection;
typedef struct
{
    unsigned int diceNum;
    resourceType resource;
    int ID;
    array<Intersection *, COUNT_INERS_ON_LAND> myIntersections; // using std::array for elina and for style
} Hexagon;

typedef struct
{
    Player *owner;
    pair<unsigned int, unsigned int> intersections; // IDs of intersections
} Road;

class Board
{
    array<Hexagon, COUNT_LANDS> lands;
    array<Road, COUNT_ROADS> roads;
    array<Intersection, COUNT_INTERSECTIONS> intersections;
    unsigned int roads_offset; // global for initialize the roads's array

public:
    Board();
    int build_road(Player *p, unsigned int i1, unsigned int i2, bool start);
    int build_settlement(Player *p, unsigned int s, bool start);
    void resourcesAllocationForBeginnig();
    void resourcesAllocation(unsigned int num);
    int updateToCity(Player *p, unsigned int s);

private:
    bool roadHasOwner(unsigned int x);
    bool interHasOwner(unsigned int x);
    bool myinterHasOwner(unsigned int l, unsigned int x);
    void createHexagon(unsigned int dn, resourceType rt, int id, int i1, int i2, int i3, int i4, int i5, int i6);
    void createIntersections();
    void createRoad(unsigned int i1, unsigned int i2);
};