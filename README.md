# demogame
STRING DRIVEN SNAKE GAME(similqar to nokia phone snake game)
This program implements a Snake Game in C using the ncurses library.
The snake is represented using a linked list, where each node stores the coordinates of a snake segment.
 The snake moves according to an input movement string, and the grid is displayed in the terminal.
When the snake eats food (+), its length increases, and new food is generated randomly.
 The program checks several game conditions, such as:
snake touching its own body
blocked rows/columns based on the score
border restrictions when the score is prime
 A pause feature (P) allows the game to temporarily stop for a few seconds without moving the snake.
During gameplay, the program records the snake’s position, score, and time whenever food is eaten.
 After the game ends, an HTML file (game.html) is generated displaying a table with the snake's score history, coordinates, time, and date of each food event.
