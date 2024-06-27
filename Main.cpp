//214984932 oriyas.07@gmail.com
#include <utility>
#include <vector>
#include <iostream>
#include "Catan.hpp"
using std::cout;
using std::endl;
using std::pair;
using std::vector;
int main()
{
    cout << "Game begin!" << endl;
    Catan game = Catan();
    Player p0 = Player(0);
    Player p1 = Player(1);
    Player p2 = Player(2);

    cout << "Created all the players!" << endl;

    // initial road building
    int result;
    result = game.buildRoad(&p0, 32, 26, true);
    if (result == 0)
    {
        cout << "p0 build road from 26 to 32!" << endl;
    }
    result = game.buildRoad(&p1, 35, 40, true);
    if (result == 0)
    {
        cout << "p1 build road from 35 to 40!" << endl;
    }
    result = game.buildRoad(&p2, 8, 13, true);
    if (result == 0)
    {
        cout << "p2 build road from 8 to 13!" << endl;
    }
    result = game.buildRoad(&p2, 9, 14, true);
    if (result == 0)
    {
        cout << "p2 build road from 9 to 14!" << endl;
    }
    result = game.buildRoad(&p1, 23, 29, true);
    if (result == 0)
    {
        cout << "p1 build road from 23 to 29!" << endl;
    }
    result = game.buildRoad(&p0, 41, 36, true);
    if (result == 0)
    {
        cout << "p0 build road from 41 to 36!" << endl;
    }

    // initial settlements building
    result = game.buildSettlement(&p0, 32, true);
    if (result == 0)
    {
        cout << "player 0 build a settlement in 32" << endl;
    }
    result = game.buildSettlement(&p1, 40, true);
    if (result == 0)
    {
        cout << "player 1 build a settlement in 40" << endl;
    }
    result = game.buildSettlement(&p2, 13, true);
    if (result == 0)
    {
        cout << "player 2 build a settlement in 13" << endl;
    }
    result = game.buildSettlement(&p2, 14, true);
    if (result == 0)
    {
        cout << "player 2 build a settlement in 14" << endl;
    }
    result = game.buildSettlement(&p1, 29, true);
    if (result == 0)
    {
        cout << "player 1 build a settlement in 29" << endl;
    }
    result = game.buildSettlement(&p0, 41, true);
    if (result == 0)
    {
        cout << "player 0 build a settlement in 41" << endl;
    }

    game.allocateResources(0);

    std::cout << "player 0 resources: " << std::endl;
    std::cout << "brick: " << p0.getResourceCount(BRICK) << std::endl;
    std::cout << "wool: " << p0.getResourceCount(WOOL) << std::endl;
    std::cout << "grain: " << p0.getResourceCount(GRAIN) << std::endl;
    std::cout << "ore: " << p0.getResourceCount(ORE) << std::endl;
    std::cout << "lumber: " << p0.getResourceCount(LUMBER) << std::endl;
    std::cout << "player 1 resources: " << std::endl;
    std::cout << "brick: " << p1.getResourceCount(BRICK) << std::endl;
    std::cout << "wool: " << p1.getResourceCount(WOOL) << std::endl;
    std::cout << "grain: " << p1.getResourceCount(GRAIN) << std::endl;
    std::cout << "ore: " << p1.getResourceCount(ORE) << std::endl;
    std::cout << "lumber: " << p1.getResourceCount(LUMBER) << std::endl;
    std::cout << "player 2 resources: " << std::endl;
    std::cout << "brick: " << p2.getResourceCount(BRICK) << std::endl;
    std::cout << "wool: " << p2.getResourceCount(WOOL) << std::endl;
    std::cout << "grain: " << p2.getResourceCount(GRAIN) << std::endl;
    std::cout << "ore: " << p2.getResourceCount(ORE) << std::endl;
    std::cout << "lumber: " << p2.getResourceCount(LUMBER) << std::endl;

    // p0's turn
    game.allocateResources(8);
    cout << "The result of the dice roll is 8!" << endl;
    result = game.buyDevelopCard(&p0, VICTORY_POINT);
    if (result == 0)
    {
        cout << "p0 successfuly bought a victory_point DC!" << endl;
    }
    if (game.check_winner(&p0))
    {
        cout << "p0 is the winner!" << endl;
        return 0;
    }

    // p1's turn
    game.allocateResources(2);
    cout << "The result of the dice roll is 2!" << endl;
    result = game.buildRoad(&p1, 35, 30, false);
    if (result == 0)
    {
        cout << "p1 built a road between 30 to 35!" << endl;
    }
    if (game.check_winner(&p1))
    {
        cout << "p1 is the winner!" << endl;
        return 0;
    }

    // p2's turn
    game.allocateResources(3);
    cout << "The result of the dice roll is 3!" << endl;
    pair<resourceType, unsigned int> wanted = std::make_pair(LUMBER, 2);
    pair<resourceType, unsigned int> given1 = std::make_pair(ORE, 1);
    pair<resourceType, unsigned int> given2 = std::make_pair(GRAIN, 1);
    vector<pair<resourceType, unsigned int>> wantedResources;
    wantedResources.push_back(wanted);
    vector<pair<resourceType, unsigned int>> givenResources;
    givenResources.push_back(given1);
    givenResources.push_back(given2);
    game.trade(wantedResources, &p2, &p0);
    game.trade(givenResources, &p0, &p2);
    cout << "p0 and p2 made a trade!" << endl;
    cout << "p2 gave p0 1 ore and one grain in exchange to 2 lumber!" << endl;
    if (game.check_winner(&p2))
    {
        cout << "p2 is the winner!" << endl;
        return 0;
    }

    // p0's turn
    game.allocateResources(4);
    cout << "The result of the dice roll is 4!" << endl;
    result = game.updateToCity(&p0, 41);
    if (result == 0)
    {
        cout << "p0 updated 41 to city!" << endl;
    }
    if (game.check_winner(&p0))
    {
        cout << "p0 is the winner!" << endl;
        return 0;
    }

    // p1's turn
    game.allocateResources(4);
    cout << "The result of the dice roll is 4!" << endl;
    pair<resourceType, unsigned int> wanted2 = std::make_pair(BRICK, 2);
    pair<resourceType, unsigned int> given21 = std::make_pair(LUMBER, 2);
    vector<pair<resourceType, unsigned int>> wantedResources2;
    wantedResources2.push_back(wanted2);
    vector<pair<resourceType, unsigned int>> givenResources2;
    givenResources2.push_back(given21);
    game.trade(wantedResources2, &p1, &p2);
    game.trade(givenResources2, &p2, &p1);
    cout << "p1 and p2 made a trade!" << endl;
    cout << "p1 gave p2 2 lumber in exchange to 2 brick!" << endl;
    if (game.check_winner(&p1))
    {
        cout << "p1 is the winner!" << endl;
        return 0;
    }

    // p2's turn
    game.allocateResources(5);
    cout << "The result of the dice roll is 5!" << endl;
    cout << "p2 decided to do nothing on this turn :(" << endl;
    // p2 decided to do nothing
    if (game.check_winner(&p2))
    {
        cout << "p2 is the winner!" << endl;
        return 0;
    }

    // p0's turn
    game.allocateResources(3);
    cout << "The result of the dice roll is 3!" << endl;
    int index = game.canUseDC(&p0, VICTORY_POINT);
    if (index >= 0)
    {
        result = game.useVictoryPoint(&p0, index);
    }
    if (result == 0)
    {
        cout << "p0 successfuly used the victory_point DC!" << endl;
    }
    if (game.check_winner(&p0))
    {
        cout << "p0 is the winner!" << endl;
        return 0;
    }

    // p1's turn
    game.allocateResources(6);
    cout << "The result of the dice roll is 6!" << endl;
    result = game.buildRoad(&p1, 40, 44, false);
    if (result == 0)
    {
        cout << "p1 successfuly built a road between 40 to 44" << endl;
    }
    if (game.check_winner(&p1))
    {
        cout << "p1 is the winner!" << endl;
        return 0;
    }

    // p2's turn
    game.allocateResources(8);
    cout << "The result of the dice roll is 8!" << endl;
    result = game.buildRoad(&p2, 9, 5, false);
    if (result == 0)
    {
        cout << "p2 successfuly built a road between 5 to 9" << endl;
    }
    if (game.check_winner(&p2))
    {
        cout << "p2 is the winner!" << endl;
        return 0;
    }

    // p0's turn
    game.allocateResources(9);
    cout << "The result of the dice roll is 9!" << endl;
    result = game.updateToCity(&p0, 32);
    if (result == 0)
    {
        cout << "p0 updated 41 to city!" << endl;
    }
    if (game.check_winner(&p0))
    {
        cout << "p0 is the winner!" << endl;
        return 0;
    }
}