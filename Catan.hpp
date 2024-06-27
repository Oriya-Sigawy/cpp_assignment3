// 214984932 Oriyas.07@gmail.com
#pragma once
#include <array>
#include <vector>
#include <utility>
#include <cstdlib>
#include "Board.hpp"
#include "Player.hpp"
using std::array;
using std::pair;
using std::vector;

#define COUNT_DCS 25
#define POINTS_TO_WIN 10

// enum for the type of the develop card
enum DCType
{
    KNIGHT,
    VICTORY_POINT,
    MONOPOLY,
    ROAD_BUILDING,
    YEAR_OF_PLENTY,
    TYPES_COUNT
};

// struct for develop card
typedef struct
{
    DCType type;
    Player *owner;
    bool used; // true if the card already used
} DevelopCard;

// This class represent the logic of catan's game
class Catan
{
    array<DevelopCard, COUNT_DCS> game_dcs;
    Board game_board = Board();
    pair<int, unsigned int> biggestArmy;

private:
    void createDCs();                // initialize the Catan's array of the develop cards.
    bool dcHasOwner(unsigned int i); // check if the develop card has owner.

public:
    /**
     * This is a constructor for the catan's game.
     *  The constructor calles to createDCs and initialize the biggestArmy field.
     */
    Catan();

    /**
     * This function returns a result of random rolling of two dices.
     * @returns the result of random rolling of two dices.
     */
    unsigned int rollDice();

    /**
     *This function calles to Board's resourcesAllocation.
     *@param:
     *diceRoll - if its 0, the function calles to Board's allocateResourcesForBeginning. Else, the function sends diceRoll to Board's allocateResources.
     */
    void allocateResources(unsigned int diceRoll);

    /**
     * This function is used to build a road.
     * The function checks that p has enough resources to build a road, and if p has, calls to Board's build_road.
     *  If the road building succeed, the function takes the road's price from p's resources.
     * @param:
     *  p: the player who wants to build a road.
     * i1, i2: the intersections of the road that p wants to build.
     *  start: true if this function is called on the beginning of the game, false otherwise.
     *         if its true, the function does not check if p has enough resources, and does not take the road's price from p's resources.
     * @returns: -2 if p does not have enough resources, or the result of the Board's build_road.
     */
    int buildRoad(Player *p, unsigned int i1, unsigned int i2, bool start);

    /**
     * This function is used to build a settlement.
     * The function checks that p has enough resources to build a settlement, and if p has, calls to Board's build_settlement.
     *  If the settlement building succeed, the function takes the settlement's price from p's resources.
     * @param:
     *  p: the player who wants to build a settlement.
     * s: the settlement p wants to build.
     *  start: true if this function is called on the beginning of the game, false otherwise.
     *         if its true, the function does not check if p has enough resources, and does not take the settlement's price from p's resources.
     * @returns: -2 if p does not have enough resources, or the result of the Board's build_settlement.
     */
    int buildSettlement(Player *p, unsigned int s, bool start);

    /**
     * This function is used to update a settlement to a city.
     * The function checks that p has enough resources to update a settlement to city, and if p has, calls to Board's updateToCity.
     *  If the update succeed, the function takes the updates's price from p's resources.
     * @param:
     *  p: the player who wants to update a settlement to a city.
     * s: the settlement p wants to update.
     * @returns: -1 if p does not have enough resources, or the result of the Board's updateToCity.
     */
    int updateToCity(Player *p, unsigned int s);

    /**
     * This function is used to buy a develop card. 
     * The function checks that p has enough resources, and if he has, takes the DC price from p's resources.
     * @param: 
     * p: the player who wants to buy a develop card.
     * dc: the type of the develop card p wants to buy.
     * @returns: -2 if there is no available DC of this type, -1 if p does not have enough resources, 0 if succeed.
     */
    int buyDevelopCard(Player *p, DCType dc);

    /**
     * This function is used to check if p can use a DC of a specific type.
     * the function checks on the Catan's DC list if there is an unused DC that p owns.
     * @param:
     * p: the player who wants to use the DC.
     * dc: the type of DC that p wants to use.
     * @returns: -1 if p does not have an unused DC of dc's type, and if p has, returns the i
     */
    int canUseDC(Player *p, DCType dc);
    int useKnight(Player *p, Player *p2, int index);
    int useVictoryPoint(Player *p, int index);
    int useYearOfPlenty(Player *p, resourceType r1, resourceType r2, int index);
    int useMonopoly(Player *p, resourceType rt, array<Player *, COUNT_PLAYERS> players, int index);
    int useRoadBuilding(Player *p, pair<unsigned int, unsigned int> r1, pair<unsigned int, unsigned int> r2, int index);
    void trade(vector<pair<resourceType, unsigned int>> resourcesToTrade, Player *p1, Player *p2);
    bool check_winner(Player *p);
    int getOwnerOfBiggestArmy();
};
