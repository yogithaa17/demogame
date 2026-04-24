# demogame
STRING-DRIVEN SNAKE GAME (Similar to the Nokia Snake Game)
This program implements a Snake Game in C using the ncurses library. The game is primarily luck-based because the position of the food is randomized.
The user first inputs the grid dimensions (n, m). Then, the snake’s movement is controlled through a string (maximum length: 100,000 characters). Each character in the string represents a move:
U – move up,
D – move down,
L – move left,
R – move right,
P – pause the game,
After entering n and m, the program switches to graphics mode and displays the input. When the user presses Enter, the snake begins moving step by step according to the input string.
The snake is represented using a linked list, where each node stores the coordinates of a segment. The head of the snake is shown using #, and the body using -.
Food is represented by +. When the snake eats food:
Its length increases (a new - segment is added).
New food is generated randomly.
The game uses toroidal wrapping: if the snake moves beyond one edge of the grid, it reappears on the opposite side (for example, moving right from the rightmost column brings it to the leftmost column).
If the snake does not eat food for a while, its tail is shortened (length decreases).
Game Conditions and Rules
The program checks several conditions during gameplay:
Collision with its own body results in Game Over.
Special constraints are applied when the score reaches certain conditions:
If the snake eats food continuously (count ≥ 3), rows or columns may become blocked.
If the score is a prime number (and count ≥ 3), border restrictions are applied.
The speed of the snake depends on the grid size (n, m).
The Pause (P) command temporarily stops the snake for a few seconds without movement.
The game ends when:
The snake violates movement constraints defined in the snakemove function, or
The input string is fully processed (i.e., reaches the null character)
After termination, the program exits graphics mode and returns to the terminal.
Data Logging and Output
During gameplay, each time the snake eats food, the program records:
Snake’s position,
Score,
Time and date.
After the game ends, an HTML file named game.html is generated. This file displays a table containing:
Score history,
Coordinates,
Time and date of each food event.
The HTML file contains data only for the current game session and does not store previous game data.
