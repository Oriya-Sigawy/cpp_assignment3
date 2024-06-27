//214984932 Oriyas.07@gmail.com
#include <iostream>
#include "Player.hpp"

Player::Player(int id)
{
    if (id < 0 || id >= COUNT_PLAYERS)
    {
        throw std::out_of_range("Too many / too few players");
    }
    // initialize
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
    if (num < (-1 * (int)this->victory_points)) // means that I was requested to reduse more than what this Player really have.
    {
        this->victory_points = 0;
        return;
    }
    this->victory_points += num;
}
void Player::updateKnightsCount(int num)
{
    if (num < (-1 * (int)this->knightsCount)) // means that I was requested to reduse more than what this Player really have.
    {
        this->knightsCount = 0;
        return;
    }
    this->knightsCount += num;
}
void Player::updateResource(resourceType rt, int amount)
{
    switch (rt)
    {
    case WOOL:
        if (amount < (-1 * (int)this->player_rb.wool)) // means that I was requested to reduse more than what this Player really have.
        {
            this->player_rb.wool = 0;
            break;
        }
        player_rb.wool += amount;
        break;
    case GRAIN:
        if (amount < (-1 * (int)this->player_rb.grain)) // means that I was requested to reduse more than what this Player really have.
        {
            this->player_rb.grain = 0;
            break;
        }
        player_rb.grain += amount;
        break;
    case LUMBER:
        if (amount < (-1 * (int)this->player_rb.lumber)) // means that I was requested to reduse more than what this Player really have.
        {
            this->player_rb.lumber = 0;
            break;
        }
        player_rb.lumber += amount;
        break;
    case BRICK:
        if (amount < (-1 * (int)this->player_rb.brick)) // means that I was requested to reduse more than what this Player really have.
        {
            this->player_rb.brick = 0;
            break;
        }
        player_rb.brick += amount;
        break;
    case ORE:
        if (amount < (-1 * (int)this->player_rb.ore)) // means that I was requested to reduse more than what this Player really have.
        {
            this->player_rb.ore = 0;
            break;
        }
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
