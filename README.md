# demogame
STRING DRIVEN SNAKE GAME(similqar to nokia phone snake game)
This program implements a Snake Game in C using the ncurses library.
the game i created is purely luckbased as we dont know were the food was i.e randomised
The snake is represented using a linked list, where each node stores the coordinates of a snake segment.(like #-----)
 The snake moves according to an input ( U WILL GIVE n,m FOR GRID SIZE 1ST) then for movement  a string is given string ( user will give a string using U- MOVING UP,L- MOVING LEFT,R MOVING RIGHT,D-MOVING DOWN,P-PAUSE) and after giving n,m it goes to graphics mode and scho what iput ur giving then after clicking enter we will get movement snakehead(#)
When the snake eats food (+), its length increases ('-' this symbol is added for it to increase length) , and new food is generated randomly.
if the snake touches the rightmost coordinsate then after that if its movent is R then it goes to left most and starts again(toroidal wrap).
 It takes input string using getchar function and for every character in string the movement of it is shown on the screen.
 The program checks several game conditions, such as:
snake touching its own body,
blocked rows/columns based on the score( it happens if count is >=3 when it continuesly eats food).
Based on input vales n,m the speed of movement will change.
If this not eat food succesively then i will cut tail( decrese the length).
border restrictions when the score is prime (it happens if count is >=3 when it continuesly eats food)
 A pause feature (P) allows the game to temporarily stop for a few seconds without moving the snake.
During gameplay, the program records the snake’s position, score, and time whenever food is eaten.
 After the game ends, an HTML file (game.html) is generated displaying a table with the snake's score history, coordinates, time, and date of each food event.
It gives GAMEOVER only if it doesnot folow the constrains in given in snakemove function and if inputstring completes i.e reaches null then it comeout of graphics mode back to terminal.
