// 214984932 Oriyas.07@gmail.com
#pragma once
#include <array>
#include <utility>
#include "Player.hpp"
using std::array;
using std::pair;

#define COUNT_INERS_ON_LAND 6 // each land have 6 intersection on it
#define COUNT_INTERSECTIONS 54
#define COUNT_LANDS 19
#define COUNT_ROADS 72

// struct for settlement
typedef struct
{
    bool isCity; // true if this settlement was updated to city, false otherwise.
    Player *owner;
} Settlement;

// struct for intersection
typedef struct
{
    unsigned int ID;
    Settlement s;
} Intersection;

// struct for hexagon
typedef struct
{
    unsigned int diceNum;
    resourceType resource;
    int ID;
    // array of the intersections on the land
    array<Intersection *, COUNT_INERS_ON_LAND> myIntersections; // using std::array for elina and for style
} Hexagon;

// struct for road
typedef struct
{
    Player *owner;
    pair<unsigned int, unsigned int> intersections; // pair of the 2 adjacent intersection (IDs of intersections)
} Road;

class Board
{
    array<Hexagon, COUNT_LANDS> lands;
    array<Road, COUNT_ROADS> roads;
    array<Intersection, COUNT_INTERSECTIONS> intersections;
    unsigned int roads_offset; // to initialize the roads's array

public:
    /**
     * This is the constructor of the Board.
     * The constructor calls to createIntersections, createHexagon, createrRoad and initialize roads_offset to 0.
     */
    Board();

    /**
     * This function is used to build a road on the board.
     * @param:
     * p: the player who want to build the road.
     * i1, i2: the edges of the road.
     * start: boolean to if the function was called in the start of the game or not.
              if not, p can only build a road if the new road is connected to another p's road or to one of p's settlements.
     * @returns: 0 in success,
                -1 if start is false and the new road is not connected to any of p's road or if the road between i1 to i2 belongs to someone else,
                -3 if i1 or i2 is out of bound or if there is no road between i1 to i2.
     */
    int build_road(Player *p, unsigned int i1, unsigned int i2, bool start);

    /**
     * This function is used to build a settlement on the board.
     * @param:
     * p: the player who want to build the settlement.
     * s: the ID of the settlement.
     * start: boolean to if the function was called in the start of the game or not.
              if not, p can only build a settlement in the edge of one of its roads.
    * @returns: 0 in success,
               -1 if the settlement belongs someone else,
               -3 if s is out of bound or if start is false and non of p's roads is connected to the settlement.
     */
    int build_settlement(Player *p, unsigned int s, bool start);

    /**
     * This function is used to allocate resources in the beginning of the game.
     * The function goes over all the intersections in the board, and if the intersection has an owner,
        the owner gets 1 of every resource of the lands the intersection is on.
     */
    void resourcesAllocationForBeginnig(); // TODO tests for that

    /**
     * This function allocate resources to every player that have a settlement on a land that its dice-number is equal to num.
     * @param:
     *  num: the dice-num to check which land has.
     */
    void resourcesAllocation(unsigned int num);

    /**
     * This function is used to update settlement to city.
     * @param:
     *  p: the owner of the settlement.
     *  s: the settlement to update.
     * @returns: 0 in success, -2 if s does not belong to p, -3 if s is already a city or does not belong to anyone, -4 if s is out of bound.
     */
    int updateToCity(Player *p, unsigned int s);

private:
    bool roadHasOwner(unsigned int x);                                                                            // checks if road x has an owner.
    bool interHasOwner(unsigned int x);                                                                           // checks if settlement x has an owner.
    bool myinterHasOwner(unsigned int l, unsigned int x);                                                         // checks if the x's settlement on l's intersections array has an owner.
    void createHexagon(unsigned int dn, resourceType rt, int id, int i1, int i2, int i3, int i4, int i5, int i6); // helper for constructor
    void createIntersections();                                                                                   // helper for constructor
    void createRoad(unsigned int i1, unsigned int i2);                                                            // helper for constructor
};