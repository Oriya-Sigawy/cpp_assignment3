
#pragma once
// 214984932 Oriyas.07@gmail.com
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
}

// tests for board.cpp:
TEST_CASE("check buildRoad in start")
{
    Player p = Player(1);
    Board board = Board();
    CHECK(board.build_road(&p, 1, 5, true) == 0);
    CHECK(board.build_road(&p, 1, 75, true) == -3);
    CHECK(board.build_road(&p, 1, 25, true) == -3);
}

TEST_CASE("check buildRoad not in start")
{
    Player p = Player(1);
    Board board = Board();
    CHECK(board.build_road(&p, 1, 5, false) == -1);
    Player p2 = Player(2);
    CHECK(board.build_road(&p2, 1, 5, true) == 0);
    CHECK(board.build_road(&p, 1, 5, true) == -1);
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

TEST_CASE("check buyDC, useVP, canUseDC")
{
    Catan game = Catan();
    Player player0 = Player(0);
    Player player1 = Player(1);
    Player player2 = Player(2);
    std::array<Player, COUNT_PLAYERS> players = {player0, player1, player2};
    CHECK(game.buyDevelopCard(&player2, VICTORY_POINT) == -1); // player2 does not have enough resources
    player0.updateResource(GRAIN, TYPES_COUNT + 2);            // will buy 3 knights
    player0.updateResource(ORE, TYPES_COUNT + 2);
    player0.updateResource(WOOL, TYPES_COUNT + 2);

    CHECK(game.buyDevelopCard(&player0, TYPES_COUNT) == -2); // there is no DC with the type "TYPES_COUNT"

    // check victory point
    CHECK(game.buyDevelopCard(&player0, VICTORY_POINT) == 0);
    int index = game.canUseDC(&player0, VICTORY_POINT);
    CHECK(index >= 0);
    CHECK(game.useVictoryPoint(&player0, index) == 0);
    CHECK(player0.getVictoryPoints() == 1);
    int x = game.canUseDC(&player0, VICTORY_POINT);
    CHECK(x == -1);

    // check knight
    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(game.useKnight(&player0, players, index) == 0);
    CHECK(player0.getKnightsCount() == 1);

    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(game.useKnight(&player0, players, index) == 0);
    CHECK(player0.getKnightsCount() == 2);

    CHECK(game.buyDevelopCard(&player0, KNIGHT) == 0);
    index = game.canUseDC(&player0, KNIGHT);
    CHECK(index >= 0);
    CHECK(player0.getVictoryPoints() == 1);
    CHECK(game.useKnight(&player0, players, index) == 0);
    CHECK(player0.getKnightsCount() == 3);
    CHECK(player0.getVictoryPoints() == 3);
    
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
