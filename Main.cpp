#include <iostream>
#include "Catan.hpp"
using std::cout;
int main()
{
    Catan game = Catan();
    game.begin();
    while (!game.check_winner())
    {
        game.move(0);
    }
}