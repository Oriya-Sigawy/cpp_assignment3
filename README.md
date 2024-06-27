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
* `allocaateResourcesForBeginning()` : allocate resources to every settlement that has an owner.
* `allocateResources()` : allocate resources by the result of the random dice roll.
The class has more private functions that help the public functions.

`The Catan class` - this class deals with the game's logic. The class receives the user's choices from the frontend, and pass them to Board when needed.   Catan mainly deal with the develop cards.  
Catan's methods:
* `Catan()` : constructor.
* `rollDice()` : returns the result of a random roll of 2 dice.
* `allocateResources()` : calls Board's allocateResources.
* `buildRoad()` : checks that p has enough resources to build a road, and if p has, calls to Board's build_road.
* 'buildSettlement()` : checks that p has enough resources to build a settlement, and if p has, calls to Board's build_settlement.
* `updateToCity()` : checks that p has enough resources to update a settlement to city, and if p has, calls to Board's updateToCity.
* `buyDevelopCard()`
* `canUseDC()` : checks if p can use a DC of a specific type.
* `useKnight()`
* `useVictoryPoint()`
* `useYearOfPlenty()`
* `useMonopoly()`
* `useRoadBuilding()`
* `trade()` : receives 2 player to switch resources between and vector of pairs of <RESOURCE_TYPE, AMOUNT> and switch the resources.
* `check_winner()` : receives a player and check if he won.
* `getOwnerOfBiggestArmy()`
The class has more private functions that help the public functions.

`The Frontend class` - this class deals with communication with the user. The class receives the user's choices and bring them to Catan.  This class is the manager class.  
Frontend's methods:
* `Frontend()` : constructor.
* `updateToCityF()`
* `seven in dice()` : in case when seven is the dice result, the user needs to decide which resources he gives up on.
* `tradeF()`
* `chooseRoadF()`
* `chooseSettlementF()`
* `buyDC_F()`
* `useDC_F()`
* `getPlayer()` : receives an index and return the players in this index in the player's array.
* `getTurn()` :returns the player who owns the current turn.
* `next()` : pass the turn to the next player.
* `initialeBuild()` : receives from the user which roads and settlements he wants to build on the beginning of the game.
* `finish()` : check if one of the players won.
* `rollDice_F` : presents to the user what number was rolled on the dice.
* `allocateFB` : used for the initial resources allocation in the beginning of the game.
The class has more private functions that help the public functions.

HOW TO RUN THIS CODE?
* To run the frontend, use `make frontend` or just `make` and than `./frontend` .
* To run the test, use `make test` and than `./test` .
* To run the main, use `make main` and than `./main` .  
GOOD LUCK!
