# cpp_assignment3
In this assignment I implemented a catan game (with the rules I understood, I do not know this game.
I wrote a Player class, a Board class, a Catan class and a frontend class.  
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
