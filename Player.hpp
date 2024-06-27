//214984932 Oriyas.07@gmail.com
#pragma once

#define COUNT_PLAYERS 3
// this enum stores all the resources types
enum resourceType
{
    DESERT,
    WOOL,
    GRAIN,
    BRICK,
    LUMBER,
    ORE
};
// struct to hold how much the player has of every resource.
typedef struct
{
    unsigned int wool;
    unsigned int grain;
    unsigned int lumber;
    unsigned int brick;
    unsigned int ore;
} resourcesBank;

// this class represent a player in the game
class Player
{
private:
    int ID;
    unsigned int victory_points;
    resourcesBank player_rb;
    unsigned int knightsCount;

public:
    /*
        This is a constructor for the player. The constructor gets the Player's ID, check if its a llegal id and initialize the ID field.
    */
    Player(int id);

    // getters

    /**
     * This function returns the player's ID.
     * @returns: the player's ID.
     */
    int getID();

    /**
     * This function sums the total amount of the resources that the player have by summing the values of the Player's player_rb.
     * @returns: total amount of resources.
     */
    unsigned int getResourcesCount();

    /**
     * Returns the amount of the specific resource that the player have by returning the right value from player_rb.
     * @param: 
     * rt: the requested resourceType.
     * @returns: the amount of the specific resourceType.
     */
    unsigned int getResourceCount(resourceType rt);

    /**
     * Returns the number of victory points this player have.
     * @returns: the number of victory points.
     */
    unsigned int getVictoryPoints();

    /**
     *Returns the number of knights this player have.
     * @returns: the number of knights.
     */
    unsigned int getKnightsCount();

    // setters

    /**
     * This funcion adds num amount of the existing victory points.
     * @param: 
     * num: the amount of the victory points to add.
     */
    void updateVictoryPoints(int num);

    /**
     * This funcion adds num to the amount of the existing knights.
     * @param: 
     * num: the amount of the knights to add.
     */
    void updateKnightsCount(int num);

    /**
     * This funcion adds num to the existing amount of the specific resourceType..
     * @param: 
     * num: the amount of the amount of the specific resourceType. rt is the specific resource to add to.
     * */
    void updateResource(resourceType rt, int amount);
};
