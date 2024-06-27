# cpp_assignment3
In this assignment I implemented a catan game (with the rules I understood, I do not know this game.
I wrote a Player class, a Board class, a Catan class and a Frontend class.  
I will explain them one by one.  
`The Player class` - This class represent a player in the game. The class has a resources bank that saves how much the player has of every resource.  
Player's methods:  
* `Player()` : a constructor.
* `updateVictoryPoints()`
* `updateResource()`
* `updateKnightCount()`
* `getVictoryPoints()`
* 'getResorceCount()`
* `getResourcesCount()` : returns the sum of the resources the player has.
* `getKnightCount()`
* `getID()`

`The Board class` - this class deals with everything that connects to the game's board (roads, intersections, settlements, citys, lands).  
Board's methods:
* `Board()` : a constructor.
* `build_road()`
* `build_settlement()`
* `updateToCity()`
* `allocaateResourcesForBeginning` : allocate resources to every settlement that has an owner.
* `allocateResources` : allocate resources by the result of the random dice roll.
The class has more private functions that help the public functions.

`The Catan class` - this class deals with the game's logic. The class receives the user's choices from the frontend, and pass them to Board when needed.   Catan mainly deal with the develop cards.  
Catan's methods:
* `rollDice()` : returns the result of a random roll of 2 dice.
* `allocateResources` : calls Board's allocateResources.
* `buildRoad` : checks that p has enough resources to build a road, and if p has, calls to Board's build_road.
* 'buildSettlement` : checks that p has enough resources to build a settlement, and if p has, calls to Board's build_settlement.
* `updateToCity` : checks that p has enough resources to update a settlement to city, and if p has, calls to Board's updateToCity.
* 
