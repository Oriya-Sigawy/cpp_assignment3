#pragma once

#define COUNT_PLAYERS 3
enum resourceType
{
    DESERT,
    WOOL,
    GRAIN,
    BRICK,
    LUMBER,
    ORE
};
typedef struct
{
    unsigned int wool;
    unsigned int grain;
    unsigned int lumber;
    unsigned int brick;
    unsigned int ore;
} resourcesBank;
class Player
{
private:
    int ID;
    unsigned int victory_points;
    resourcesBank player_rb;
    unsigned int knightsCount;

public:
    Player(int id);

    // getters
    int getID();
    unsigned int getResourcesCount();
    unsigned int getResourceCount(resourceType rt);
    unsigned int getVictoryPoints();
    unsigned int getKnightsCount();

    // setters
    void updateVictoryPoints(int num);
    void updateKnightsCount(int num);
    void updateResource(resourceType rt, int amount);
};
