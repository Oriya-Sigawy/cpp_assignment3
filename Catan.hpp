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

enum DCType
{
    KNIGHT,
    VICTORY_POINT,
    MONOPOLY,
    ROAD_BUILDING,
    YEAR_OF_PLENTY,
    TYPES_COUNT
};
typedef struct
{
    DCType type;
    Player *owner;
    bool used;
} DevelopCard;
class Catan
{
    array<DevelopCard, COUNT_DCS> game_dcs;
    Board game_board = Board();

private:
    void createDCs();
    bool dcHasOwner(unsigned int i);

public:
    Catan();
    unsigned int rollDice(unsigned int num);
    void allocateResources(unsigned int diceRoll);
    int buildRoad(Player *p, unsigned int i1, unsigned int i2, bool start);
    int buildSettlement(Player *p, unsigned int s, bool start);
    int updateToCity(Player *p, unsigned int s);
    int buyDevelopCard(Player *p, DCType dc);
    int canUseDC(Player *p, DCType dc);
    int useKnight(Player *p, array<Player, COUNT_PLAYERS> players, int index);
    int useVictoryPoint(Player *p, int index);
    int useYearOfPlenty(Player *p, resourceType r1, resourceType r2, int index);
    int useMonopoly(Player *p, resourceType rt, array<Player, COUNT_PLAYERS> players, int index);
    int useRoadBuilding(Player *p, pair<unsigned int, unsigned int> r1, pair<unsigned int, unsigned int> r2, int index);
    void trade(vector<pair<resourceType, unsigned int>> resourcesToTrade, Player *p1, Player *p2);
    bool check_winner(Player *p);
};
