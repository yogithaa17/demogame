#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"

// creating global variable
// count is used to know the size of snake
static int count = 0;
 
// for storing html values
typedef struct
{
    int count;

    // at which cordinates snake at food

// x co ordinate    
int x;

// y coordinate
    int y;
    
// time at which snake ate  food
    time_t T;
} storage;

// storing things for generating html file
storage arr[1000];
static int i = 0;

// creating node
linkedlist *createnode(int x, int y)
{
    linkedlist *newnode = malloc(sizeof(linkedlist));
    if (newnode == NULL)
    {
        return NULL;
    }
    newnode->x = x;
    newnode->y = y;
    newnode->next = NULL;
    return newnode;
}

// inserting
linkedlist *insert(linkedlist *head, int x, int y)
{
// inserting at head
    linkedlist *newnode = createnode(x, y);
    if (head == NULL)
    {
        return newnode;
    }
    newnode->next=head;
    return newnode;
}

// check whether snake touches its body or not
int selftouch(linkedlist *head, int x, int y)
{
    if (head == NULL)
        return 0;
    linkedlist *temp = head;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// in whole process if doesnot eat food delete tail
linkedlist *deletetail(linkedlist *head)
{
    if (head == NULL || head->next == NULL)
    {
        free(head);
        return NULL;
    }

    linkedlist *ptr = head;

    while (ptr->next->next != NULL)
        ptr = ptr->next;

    free(ptr->next);
    ptr->next = NULL;

    return head;
}

// leveling up the game
int constraint(int hx, int hy, int n, int m)
{ 
// if it ate food for more than 3rd time and it is not prime number time 
    if (count >= 3 && !isPrime(count))
    {
        if (count % 2 == 0)
        {
            // block row = count % n
            if (hx == (count % n) && (hy != 0 && hy != m - 1))
                return 1;
        }
        else
        {
            // block column = count % m
            if (hy == (count % m) && (hx != 0 && hx != n - 1))
                return 1;
        }
    }

// count is >3 and is prime
    if (count >= 3 && isPrime(count))
    {
        // block 0th row OR (m-1)th column OR 0th column OR (n-1)th row
        if (hx == 0 || hx == n - 1 || hy == 0 || hy == m - 1)
            return 1;
    }

    return 0;
}

// game play
int snakemove(linkedlist **head, int n, int m, int *fx, int *fy, char move)
{
    if (*head == NULL)
    {
        return 0;
    }
    int hx = (*head)->x;
    int hy = (*head)->y;

// calling poschange function to change coords position
    poschange(&hx, &hy, n, m, move);

    // toridal wrap
//if it is at left most coord
    if (hx < 0){
        hx = n - 1;
}
// if it at right most coord
    else if (hx >= n){
        hx = 0;
}

// if  it is at top most coord
    if (hy < 0)
{
        hy = m - 1;
}
// if it is at down most coord 
    else if (hy >= m)
{
        hy = 0;
}
    // blocking the snake path if count>=3
    if (constraint(hx, hy, n, m))
    {
        printf("Game Over\n");
        return 0;
    }

    //  it touches its body parts
    if (selftouch(*head, hx, hy))
    {
        printf("Game Over: Snake touched its body\n");
        return 0;
    }

    *head = insert(*head, hx, hy);
    
//if  it ate food
    if (hx == *fx && hy == *fy)
    {  
        count++;
        generatefood(fx, fy, n, m, *head);
    }
    else
    {
// if it did not eat food then node is removed

//its size length is to be reduced i.e count shoud be decreased 
      if(count>0)
     {
      count--;
     }
       *head = deletetail(*head);
    }
    
// storing data to get html table
    if (i < 1000)
    { 

// storing count
        arr[i].count = count;

// storing hx
        arr[i].x = hx;

// storing hy
        arr[i].y = hy;

// storing time
        arr[i].T = time(NULL);
        i++;
    }
    return 1;
}

// printing  states of snake movement
void printgrid(linkedlist *head, int n, int m, int fx, int fy)
{
    char grid[n][m];

// initialising grid with .
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            grid[i][j] = '.';
        }
    }

// giving symbol for food                                                                                               
grid[fx][fy]='+';  

    linkedlist *temp = head;
    int shead = 1;
    
while (temp)
    {
// giving symbol for head of snake  
      if (shead)
        {
            grid[temp->x][temp->y] = '#';
            shead = 0;
        }
// giving symbol for snake body
        else
            grid[temp->x][temp->y] = '-';
        temp = temp->next;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mvprintw(i,j,"%c", grid[i][j]);
        }
    }
}

void snakegame(linkedlist *head, int n, int m, char str[])
{
    int fx;
    int fy;

// generating food for 1st time
    generatefood(&fx, &fy, n, m, head);

    for (int i = 0; str[i] != '\0'; i++)
    {
// making the screen pause for a movement
 if (str[i] == 'P')
    {
        mvprintw(0,0," Game Paused");
        refresh();
// paused for 3sec
        sleep(3);
// skip  the movement 
        continue;   // skip movement
    }

//clears the screen
 clear();

        if (!snakemove(&head, n, m, &fx, &fy, str[i]))
        {
            mvprintw(0,0,"Game Over\n");
            refresh();
            sleep(3);
            return;
        }

 // printing grid for every 15sec   
    printgrid(head, n, m, fx, fy);

//after .5sec the screen has to refresh and be ready for next move
   refresh();
                                                
// 1. If n and m are same (0.5 sec)
if (n == m) {
    usleep(500000);
}
// 2. If n+m is even (0.1 sec)
else if ((n + m) % 2 == 0) {
    usleep(100000);
}
// 3. If n+m is odd (0.9 sec)
else {
    usleep(900000);
}

}

}

// function to generate html file
void gen_html()
{
    FILE *fptr;
    fptr = fopen("game.html", "w");
    if (fptr == NULL)
    {
        printf("error in creating file");
        return;
    }
    
// start of html file
    fprintf(fptr, "<html>\n");
    
// printing webpagename
    fprintf(fptr, "<head>\n");
    fprintf(fptr, "\t<title>myscore</title>\n");
    fprintf(fptr, "</head>\n");
    
// start of body  of html table
    fprintf(fptr, "<body>\n");
    
// heading
    fprintf(fptr, "\t<h1>Snake Game</h1>\n");
    
// table coloring
    fprintf(fptr, "<table border=\"1\" width=\"50%%\" style=\"border-color:blue; text-align:left;\">\n");
    
// row coloring
    fprintf(fptr, "<tr style=\"background-color:lightgray;\"><th>count</th><th>x</th><th>y</th><th>time</th><th>date</th></tr>\n");
    
for (int k = 0; k < i; k++)
    {
        char timeStr[50];
        char dateStr[50];
        struct tm *t = localtime(&(arr[k].T));
        
// printing all things related to time in one string
        sprintf(timeStr, "%02d:%02d:%02d",
                t->tm_hour,
                t->tm_min,
                t->tm_sec);
        
// printing all things related to date in one string
        sprintf(dateStr, "%d-%02d-%02d",
                t->tm_year + 1900,
                t->tm_mon + 1,
                t->tm_mday);
        
// printing rows
        if (k % 2 == 0)
{
            fprintf(fptr, "<tr style=\"background-color:#f2f2f2;\">");
}       
          else
            fprintf(fptr, "<tr>");

        // printing count
        fprintf(fptr, "<td>%d</td>", arr[k].count);
        
// printing at which coordinate it ate food
        //  x coordinate
        fprintf(fptr, "<td>%d</td>", arr[k].x);
        // y coordinate
        fprintf(fptr, "<td>%d</td>", arr[k].y);
        
// printing time at which snake ate food
        fprintf(fptr, "<td>%s</td>", timeStr);
        
// printing date at which snake ate food
        fprintf(fptr, "<td>%s</td>", dateStr);
        fprintf(fptr, "</tr>\n");
    }
    fprintf(fptr, "</table>\n</body>\n</html>");

    if (fclose(fptr) != 0) 
{
        printf("error in closing file\n");
}

}

int main()
{
    // n is no of rows in grid and m is no of columns in grid
    int n;
    int m;

// taking input of n and m
    scanf("%d %d", &n, &m);
int c;
while((c=getchar()!='\n' && c!=EOF));

    linkedlist *head = NULL;

// if no of rows and columns are equal 
   if (n == m)
{
        head = insert(head, n/2, m/2);
}

//if n and m are not equal but sum of them is odd 
    else if (n != m && (n + m) % 2 == 0 && !isPrime(n) && !isPrime(m))
{
        head = insert(head, 0, 0);
}

//if n and m are not equal and n+m is odd
    else if (n != m && (n + m) % 2 != 0 && !isPrime(n) && !isPrime(m))
{
        head = insert(head, n - 1, m - 1);
}
// if any number nis prime or m is prime and n is not equal to m
    else if (n!=m && (isPrime(n) || isPrime(m) ))
{
int x=rand()%n;
int y=rand()%m;
head= insert(head,x,y);
}

// for changing rand everytime    
srand(time(NULL));

    char str[100000];

// initializing screen
    initscr();

// calling to take inpathfun input string                                                                               
inpath(str);                                                                                                            

//disables  line buffering       
cbreak();

// to print what string we are given with
echo();

// removing cursor
curs_set(0);

// to refresh the screen after every move
refresh();

// caling the function to start game    
snakegame(head, n, m, str);
  
//closing the screen after game play is done                                                                                                    
    endwin();   

//generate html file
 gen_html();
 
   return 0;
}