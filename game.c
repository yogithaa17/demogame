#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include "game.h"

// function for inputing string
void inpath(char str[])
{
    int i = 0;
    char p;

    while ((p= getch()) != '\n'  && i < 999)
    {
        str[i++] = p;
    }
    str[i] = '\0';
}

// function for generating food
void generatefood(int *fx, int *fy, int n, int m, linkedlist *head)
{
    int valid = 0;

    while (!valid)
    {
        *fx = rand() % n;
        *fy = rand() % m;

        valid = 1;
        linkedlist *temp = head;

        while (temp)
        {
            if (temp->x == *fx && temp->y == *fy)
            {
                valid = 0;
                break;
            }
            temp = temp->next;
        }
    }
}

// function for changing position
void poschange(int *hx, int *hy, int n, int m, char move)
{
    // moving up
    if (move == 'U')
        (*hx)--;

    // moving down
    else if (move == 'D')
        (*hx)++;

    // moving left
    else if (move == 'L')
        (*hy)--;

    // moving right
    else if (move == 'R')
        (*hy)++;

    // torodal wrap
    // if it touches left most boundary
    if (*hx < 0)
    {
        *hx = n - 1;
    }
    // it touches rightmost boundary
    if (*hx >= n)
    {
        *hx = 0;
    }
    // if it touches topmost boundary
    if (*hy < 0) 
    {
        *hy = m - 1;
    }

    // if it touches bottomost boundary
    if (*hy >= m)
    {
        *hy = 0;
    }

    }

// function for checking prime
int isPrime(int n)
{
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}