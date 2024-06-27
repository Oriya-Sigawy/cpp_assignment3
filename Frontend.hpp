// 214984932 Oriyas.07@gmail.com
#include <iostream>
#include <string>
#include <utility>
#include "Catan.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
#define COUNT_PLAYERS 3
#define POINTS_TO_WIN 10

// This class represent the frontend - the communication between the user to the program
class Frontend
{
    Catan game = Catan();                 // has dcs
    array<Player, COUNT_PLAYERS> players; // for elina and for style
    Player *turn;

public:
    /**
     * This is a constructor to Frontend.
     * The constructor initialize the players.
     */
    Frontend();

    /**
     * This function receives from the user which settlement he want to update, and call Catan's updateToCity.
     * @returns: true if the update succeed, false otherwise.
     */
    bool updateToCityF();

    /**
     * This function is called when the dice's result is 7.
     * The function communicate with the user to know which cards he want to give up on.
     */
    void seven_in_dice();

    /**
     * This function is used to communicate with the trade's sides.
     * @returns: true if the trade succeed, false otherwise.
     */
    bool tradeF();

    /**
     * This function receives from the user which road he want to build, and call Catan's build_road.
     * @param:
     *  p: the player who wants to build a road
     *  start: boolean to know if the function was called on the beginning of the game.
     * @returns: true if the road building succeed, false otherwise.
     */
    bool chooseRoadF(Player *p, bool start);

    /**
     * This function receives from the user which settlement he want to build, and call Catan's build_settlement.
     * @param:
     *  p: the player who wants to build a settlement
     *  start: boolean to know if the function was called on the beginning of the game.
     * @returns: true if the settlement building succeed, false otherwise.
     */
    bool chooseSettlementF(Player *p, bool start);

    /**
     * This function receives from the user which DC he wants to buy, and calls to Catan's buyDevelopCard.
     * @returns: true if the DC bought successfuly, false otherwise.
     */
    bool buyDC_F();

    /**
     * This function communicate with the user about the DC he wants to use.
     * @returns: true if used the DC successfuly, false otherwise.
     */
    bool useDC_F();

    // getters
    /**
     * This function returns the ith player.
     * @params:
     * i: the player to return
     * @returns the ith player of the player's array.
     */
    Player getPlayer(unsigned int i);

    /**
     * This function returns the player that owns the turn currently.
     * @returns: reference to the player that owns the turn currently.
     */
    Player *getTurn();

    /**
     * This function moves the turn to the next player.
     */
    void next();

    /**
     * This function build the initial roads and settlements that every player build in the beginning of the game.
     */
    void initialBuild();

    /**
     * This function checks if the game is finished.
     * the function calles to Catan's check_winner.
     * @returns: true if the game is finished (there is a winner), false otherwise.
     */
    bool finish();

    /**
     * This function presents to the user what number was rolled on the dice.
     */
    void rollDice_F(unsigned int num);

    /**
     * This function is used for the initial resources allocation in the beginning of the game.
     */
    void allocateFB();

private:
    vector<pair<resourceType, unsigned int>> makeVectorOfResources(Player *p);
    resourceType convertToRT(char c);
    DCType convertToDCType(char t);
    bool useYOP_F(int index);
    bool useMDC_F(int index);
    bool useRB_F(int index);
    string convertResourceToString(resourceType rt);
};
