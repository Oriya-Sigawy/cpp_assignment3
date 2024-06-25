
#include <iostream>
#include "Player.hpp"

Player::Player(int id)
{
    if (id < 0 || id >= COUNT_PLAYERS)
    {
        throw std::out_of_range("Too many / too few players");
    }
    this->ID = id;
    this->victory_points = 0;
    this->knightsCount = 0;
    player_rb = resourcesBank{
        0,
        0,
        0,
        0,
        0,
    };
}

// setters
void Player::updateVictoryPoints(int num)
{
    this->victory_points += num;
}
void Player::updateKnightsCount(int num)
{
    this->knightsCount += num;
}
void Player::updateResource(resourceType rt, int amount)
{
    switch (rt)
    {
    case WOOL:
        player_rb.wool += amount;
        break;
    case GRAIN:
        player_rb.grain += amount;
        break;
    case LUMBER:
        player_rb.lumber += amount;
        break;
    case BRICK:
        player_rb.brick += amount;
        break;
    case ORE:
        player_rb.ore += amount;
        break;
    case DESERT:
        return;
    default:
        throw std::invalid_argument("this is not a resource!");
        break;
    }
}

// getters
int Player::getID()
{
    return this->ID;
}
unsigned int Player::getResourcesCount()
{
    unsigned int resourcesCount = 0;
    resourcesCount += player_rb.wool;
    resourcesCount += player_rb.grain;
    resourcesCount += player_rb.lumber;
    resourcesCount += player_rb.brick;
    resourcesCount += player_rb.ore;
    return resourcesCount;
}
unsigned int Player::getResourceCount(resourceType rt)
{
    switch (rt)
    {
    case WOOL:
        return player_rb.wool;
    case GRAIN:
        return player_rb.grain;
    case LUMBER:
        return player_rb.lumber;
    case BRICK:
        return player_rb.brick;
    case ORE:
        return player_rb.ore;
    default:
        throw std::invalid_argument("this is not a resource!");
        break;
    }
}
unsigned int Player::getVictoryPoints()
{
    return this->victory_points;
}
unsigned int Player::getKnightsCount()
{
    return knightsCount;
}