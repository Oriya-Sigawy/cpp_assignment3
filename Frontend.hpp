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
class Frontend
{
    Catan game = Catan();                 // has dcs
    array<Player, COUNT_PLAYERS> players; // for elina and for style
    Player *turn;

public:
    Frontend();
    bool chooseRoadF(Player *p, bool start);
    bool chooseSettlementF(Player *p, bool start);
    bool updateToCityF();
    void seven_in_dice();
    bool tradeF();
    bool buildF();
    bool buyDC_F();
    bool useDC_F();
    Player getPlayer(unsigned int i);
    Player *getTurn();
    void next();
    void initialBuild();
    bool finish();
    void rollDice_F(unsigned int num);
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
