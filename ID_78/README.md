Flow Diagram:

Initialization:

Import necessary libraries
Initialize variables
Obstacle Generation:

Generate new obstacles using random numbers
Update current obstacles
Obstacle Painting:

Clear the screen
Draw obstacles on the screen using bitmap images
Update the score
Ball Painting:

Clear the previous position of the ball
If the ball is not in contact with an obstacle, clear the space below the ball
If the ball has lost the game, draw a deflated ball image
Otherwise, draw a ball image
Game Over:

Check if the ball has lost the game
If so, print the score and "GAME OVER" on the screen
Wait for the player to move their device
Main Loop:

Read accelerometer data
If the button is pressed, change the direction of the ball
If enough time has passed, update the position of the ball
If enough time has passed, update the obstacles
Paint the ball and obstacles on the screen
Utility Functions:

isInAir() checks if the ball is in the air
hasLost() checks if the ball has hit an obstacle and has not bounced back up yet
generateObstacles() generates new obstacles using random numbers
Note that this flow diagram is not exhaustive and some details may have been left out.

Video Link:-
https://drive.google.com/drive/folders/1UQbCsvmyZ_9rPUOOeIkuRKExUdJ3RHAL?usp=share_link
