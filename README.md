DODGY BIRD INTRUCTIONS


PREPARATION 

In VScode or other desired IDE, open the folder called group_416 found in courses -> ence260 -> ence260-ucfk4 -> assignment. Ensure the terminal leads to the correct directory by using bash commands. Next, connect a USB mini cable to both funkits. A yellow led should light up to indicate it is connected. Once completed, you are now ready to compile the program and begin the game. In the terminal, enter 'make' followed by 'make program'. If the program has been previously uploaded then you can press the button S3 for a few seconds followed by the S2 button as well.

Ensure you and your partner are holding the funkits near to each other in the correct orientation, so that the infrared sensor of your funkit board directly faces the recieving component of the other player's funkit board. These boards should be relatively close to one another, away from other funkits and out of direct light sources to reduce interference.


IN-GAME

After the program is compiled correctly, the screen should read "CHOOSE CHARACTER" which may be exited by pushing down on the navigational switch. Both players will be shown a character select screen to which each player will be given a choice to pick a character: Bird or Cannon. Selection of character is done by pushing the navigational switch in the direction of the character of your choice. Both players must select different characters, otherwise the program must be recompiled again to restart. 

Once a character is selected the players will be shown the starting position of their selected character followed by 'PUSH TO START'. Either player can move the navigational switch in the North, East, South, West directions which will allow players to enter a countdown and begin the game. 


CANNON GAMEPLAY

The goal of the Cannon is to try to hit the Bird until its healthline runs out. The cannon character is restricted to the right-hand side of the board and can only move in the vertical direction by using the North and South directions of the navigational switch. It also cannot move into the bottom row as this row is reseved for the healthline of the bird. To fire cannon balls, position the cannon to the desired row and push down on the navigational switch. the cannon ball should be transmitted from one funkit to the other. If the Bird remains alive after time runs out, the Cannon player loses and the game will end and a game over screen will be shown.


BIRD GAMEPLAY

The goal of the Bird is to avoid getting hit by the projectiles of the Cannon and to survive until the timer runs out. The Bird can move freely both vertically and horizontally within the screen of the LED matrix using the North, East, South, West directions. The three dots displayed above the bird represents its lives, and its lives decrement accordingly when they have been hit by a cannon ball which is indicated by a flash. Once the Bird has used all its lives the Bird loses and the game will end with the cannon as the Winner. 




