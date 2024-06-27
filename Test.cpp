
#pragma once
// 214984932 Oriyas.07@gmail.com
#include <utility>
#include "doctest.h"
#include "Catan.hpp"
#include "Board.hpp"
#include "Player.hpp"

// tests for Player
TEST_CASE("check p.getID()")
{
    Player p = Player(1);
    CHECK(p.getID() == 1);
}

TEST_CASE("check invalid id")
{
    CHECK_THROWS(new Player(COUNT_PLAYERS + 1));
    CHECK_THROWS(new Player(-1));
}

TEST_CASE("check victoryPoints")
{
    Player p = Player(2);
    p.updateVictoryPoints(5);
    CHECK(p.getVictoryPoints() == 5);
}

TEST_CASE("check knightsCount")
{
    Player p = Player(2);
    p.updateKnightsCount(3);
    CHECK(p.getKnightsCount() == 3);
}

TEST_CASE("check resources")
{
    Player p = Player(2);
    p.updateResource(WOOL, 1);
    p.updateResource(GRAIN, 3);
    CHECK(p.getResourceCount(WOOL) == 1);
    CHECK(p.getResourceCount(LUMBER) == 0);
    CHECK(p.getResourcesCount() == 4);
    p.updateResource(ORE, -2);
    CHECK(p.getResourceCount(ORE) == 0);
    p.updateResource(BRICK, -50);
    CHECK(p.getResourceCount(BRICK) == 0);
    CHECK(p.getResourceCount(GRAIN) == 3);
}

// tests for board.cpp:
TEST_CASE("check buildRoad in start")
{
    Player p = Player(1);
    Board board = Board();
    Player p2 = Player(2);
    CHECK(board.build_road(&p, 1, 5, true) == 0);
    CHECK(board.build_road(&p, 1, 75, true) == -3); // 75 is out of bound
    CHECK(board.build_road(&p, 1, 25, true) == -3); // 1-25 is not an existing road
    CHECK(board.build_road(&p2, 1, 5, true) == -1); // this road is already belong to p
}

TEST_CASE("check buildRoad not in start")
{
    Player p = Player(1);
    Board board = Board();
    CHECK(board.build_road(&p, 1, 5, false) == -1);
    Player p2 = Player(2);
    CHECK(board.build_road(&p2, 1, 5, true) == 0);
    CHECK(board.build_road(&p, 1, 5, true) == -1);
    p2.updateResource(BRICK, 1);
    p2.updateResource(LUMBER, 1);
    int x = board.build_road(&p2, 1, 4, false);
    CHECK(x == 0);
}

TEST_CASE("check buildSettlement")
{
    Player p = Player(1);
    Board board = Board();
    int result = board.build_settlement(&p, 5, true);
    CHECK(result == 0);
    result = board.build_settlement(&p, 100, true);
    CHECK(result == -3);
    Player p2 = Player(2);
    result = board.build_settlement(&p2, 5, true);
    CHECK(result == -1);
}

TEST_CASE("check buildSettlement")
{
    Player p = Player(1);
    Board board = Board();
    board.build_road(&p, 1, 4, true);
    int result = board.build_settlement(&p, 4, false);
    CHECK(result == 0);
    result = board.build_settlement(&p, 7, false);
    CHECK(result == -3);
    Player p2 = Player(2);
    result = board.build_settlement(&p2, 4, true);
    CHECK(result == -1);
}

TEST_CASE("check resourceAllocation && updateToCity")
{
    Player p = Player(0);
    Board board = Board();
    board.build_settlement(&p, 36, true);
    board.resourcesAllocation(3); // should give p LUMBER, WOOL AND GRAIN
    CHECK(p.getResourceCount(resourceType::ORE) == 1);
    board.resourcesAllocation(3);
    CHECK(p.getResourceCount(resourceType::ORE) == 2);
    board.resourcesAllocation(3);
    CHECK(p.getResourceCount(resourceType::ORE) == 3);
    board.resourcesAllocation(4); // should give p GRAIN
    CHECK(p.getResourceCount(resourceType::GRAIN) == 1);
    board.resourcesAllocation(4);
    CHECK(p.getResourceCount(resourceType::GRAIN) == 2);
    CHECK(board.updateToCity(&p, 36) == 0); // update succeeded
    board.resourcesAllocation(3);
    CHECK(p.getResourceCount(resourceType::ORE) == 5);
    CHECK(board.updateToCity(&p, 100) == -4); // no such intersection
    CHECK(board.updateToCity(&p, 36) == -3);  // already a city
    Player p2 = Player(1);
    CHECK(board.build_settlement(&p2, 45, true) == 0);
    CHECK(board.updateToCity(&p, 45) == -2); // the settlement does not belong to p
}

// tests for Catan

TEST_CASE("check rollDice()")
{
    Catan game = Catan();
    int x = game.rollDice(0);
    bool check = (x > 0) && (x <= 12);
    CHECK(check);
    x = game.rollDice(5);
    CHECK(x == 5);
    x = game.rollDice(0);
    check = (x > 0) && (x <= 12);
    CHECK(check);
}

TEST_CASE("check allocateResources")
{
    Catan game = Catan();
    Player p = Player(0);
    game.buildSettlement(&p, 36, true);
    game.buildSettlement(&p, 13, true);
    game.allocateResources(0);
    unsigned int x = p.getResourceCount(ORE);
    CHECK(x == 2);
    x = p.getResourceCount(GRAIN);
    CHECK(x == 2);
    x = p.getResourceCount(BRICK);
    CHECK(x == 1);
    game.allocateResources(10);
    CHECK(p.getResourceCount(ORE) == 3);
    game.updateToCity(&p, 13);
    game.allocateResources(6);
    CHECK(p.getResourceCount(BRICK) == 3);
}

TEST_CASE("check buildRoad()")
{
    Catan game = Catan();
    Player p = Player(0);
    CHECK(game.buildRoad(&p, 1, 4, true) == 0);
    p.updateResource(LUMBER, 1);
    CHECK(game.buildRoad(&p, 1, 5, false) == -2);
    p.updateResource(BRICK, 1);
    int x = game.buildRoad(&p, 1, 5, false);
    CHECK(x == 0);
    CHECK(p.getResourceCount(LUMBER) == 0);
    CHECK(p.getResourceCount(BRICK) == 0);
}

TEST_CASE("check buildSettlement() && updateToCity")
{
    Catan game = Catan();
    Player p = Player(0);
    CHECK(game.buildSettlement(&p, 46, false) == -2);
    CHECK(game.buildSettlement(&p, 46, true) == 0);
    p.updateResource(BRICK, 1);
    p.updateResource(LUMBER, 1);
    p.updateResource(WOOL, 1);
    p.updateResource(GRAIN, 3);
    CHECK(game.buildRoad(&p, 41, 45, true) == 0);
    CHECK(game.buildSettlement(&p, 45, false) == 0);
    CHECK(p.getResourceCount(BRICK) == 0);
    CHECK(p.getResourceCount(LUMBER) == 0);
    CHECK(p.getResourceCount(WOOL) == 0);
    CHECK(p.getResourceCount(GRAIN) == 2);
}

TEST_CASE("check buyDC, useVP")
{
    Catan game = Catan();
    Player player0 = Player(0);
    Player player2 = Player(2);
    CHECK(game.buyDevelopCard(&player2, VICTORY_POINT) == -1); // player2 does not have enough resources
    player0.updateResource(GRAIN, 2);
    player0.updateResource(ORE, 2);
    player0.updateResource(WOOL, 2);
    CHECK(game.buyDevelopCard(&player0, TYPES_COUNT) == -2); // there is no DC with the type "TYPES_COUNT"

    // check victory point
    CHECK(game.buyDevelopCard(&player0, VICTORY_POINT) == 0);
    int index = game.canUseDC(&player0, VICTORY_POINT);
    CHECK(index >= 0);
    CHECK(game.useVictoryPoint(&player0, index) == 0);
    CHECK(player0.getVictoryPoints() == 1);
    int x = game.canUseDC(&player0, VICTORY_POINT);
    CHECK(x == -1);
}
TEST_CASE("check useKnight")
{
    // check knight
    Catan game = Catan();
    Player player0 = Player(0);
    Player player1 = Player(1);
    player0.updateResource(GRAIN, 2); // will buy 3 knights
    player0.updateResource(ORE, 2);
    player0.updateResource(WOOL, 2);
    CHECK(game.getOwnerOfBiggestArmy() == -1);
    
    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    int index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(game.useKnight(&player0, &player0, index) == 0);
    CHECK(player0.getKnightsCount() == 1);

    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(game.useKnight(&player0, &player0, index) == 0);
    CHECK(player0.getKnightsCount() == 2);

    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(player0.getVictoryPoints() == 1);
    CHECK(game.useKnight(&player0, &player0, index) == 0);
    CHECK(player0.getKnightsCount() == 3);
    CHECK(player0.getVictoryPoints() == 3);

    player1.updateKnightsCount(3);
    player1.updateResource(GRAIN, 1); // will buy 3 knights
    player1.updateResource(ORE, 1);
    player1.updateResource(WOOL, 1);
    game.buyDevelopCard(&player1, KNIGHT);
    index = game.canUseDC(&player1, KNIGHT);
    CHECK(index >= 0);
    int x = game.useKnight(&player1, &player0, index);
    CHECK(x == 0);
    CHECK(player1.getKnightsCount() == 4);
    CHECK(player1.getVictoryPoints() == 2);
    CHECK(player0.getVictoryPoints() == 1);
}

TEST_CASE("check useYearOfPlenty")
{
    Catan game = Catan();
    Player p = Player(0);
    p.updateResource(GRAIN, 2);
    p.updateResource(ORE, 2);
    p.updateResource(WOOL, 2);
    CHECK(p.getResourceCount(BRICK) == 0);
    CHECK(p.getResourceCount(LUMBER) == 0);
    CHECK(game.buyDevelopCard(&p, YEAR_OF_PLENTY) == 0);
    int index = game.canUseDC(&p, YEAR_OF_PLENTY);
    CHECK(index >= 0);
    CHECK(game.useYearOfPlenty(&p, BRICK, LUMBER, index) == 0);
    CHECK(p.getResourceCount(BRICK) == 1);
    CHECK(p.getResourceCount(LUMBER) == 1);
}

TEST_CASE("check useMonopoly")
{
    Catan game = Catan();
    Player p = Player(0);
    Player p1 = Player(1);
    Player p2 = Player(2);
    array<Player *, 3> players = {&p, &p1, &p2};
    p.updateResource(GRAIN, 1);
    p.updateResource(ORE, 1);
    p.updateResource(WOOL, 1);
    p1.updateResource(LUMBER, 2);
    p2.updateResource(LUMBER, 3);
    CHECK(p.getResourceCount(LUMBER) == 0);
    CHECK(game.buyDevelopCard(&p, MONOPOLY) == 0);
    int index = game.canUseDC(&p, MONOPOLY);
    CHECK(index >= 0);
    int x = game.useMonopoly(&p, LUMBER, players, index);
    CHECK(x == 0);
    CHECK(p.getResourceCount(LUMBER) == 5);
    CHECK(p1.getResourceCount(LUMBER) == 0);
    CHECK(p2.getResourceCount(LUMBER) == 0);
}

TEST_CASE("check useRoadBuilding()")
{
    Catan game = Catan();
    Player p = Player(0);
    // build roads to be connected to the road p will build with the DC
    p.updateResource(BRICK, 2);
    p.updateResource(LUMBER, 2);
    game.buildRoad(&p, 1, 4, true);
    game.buildRoad(&p, 2, 6, true);

    // resources to buy the DC
    p.updateResource(GRAIN, 1);
    p.updateResource(ORE, 1);
    p.updateResource(WOOL, 1);
    CHECK(game.buyDevelopCard(&p, ROAD_BUILDING) == 0);
    int index = game.canUseDC(&p, ROAD_BUILDING);
    CHECK(index >= 0);
    std::pair<unsigned int, unsigned int> r1 = std::make_pair(1, 5);
    std::pair<unsigned int, unsigned int> r2 = std::make_pair(6, 10);
    int x = game.useRoadBuilding(&p, r1, r2, index);
    CHECK(x == 0);

    // check that p's road is not valid to build on
    Player p1 = Player(1);
    x = game.buildRoad(&p1, 1, 5, true);
    CHECK(x == -1);
}

TEST_CASE("check trade()")
{
    Catan game = Catan();
    Player p0 = Player(0);
    Player p1 = Player(1);
    p0.updateResource(LUMBER, 3);
    std::vector<std::pair<resourceType, unsigned int>> trade = {std::make_pair(LUMBER, 2)};
    game.trade(trade, &p1, &p0);
    CHECK(p0.getResourceCount(LUMBER) == 1);
    CHECK(p1.getResourceCount(LUMBER) == 2);
}

TEST_CASE("check check_winner()")
{
    Catan game = Catan();
    Player p = Player(1);
    p.updateVictoryPoints(10);
    CHECK(game.check_winner(&p));
    p.updateVictoryPoints(15);
    CHECK(game.check_winner(&p));
    p.updateVictoryPoints(-25);
    CHECK(!game.check_winner(&p));
}
