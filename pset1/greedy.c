#include <stdio.h>
#include <cs50.h>
#include <math.h>
/*
 * Time for Change: Compute the minimum amount of coins
 * needed to create the necessary change
 * 1/24/14 JS
 *
 */
int main (void)
{
    float   change;
    int     changeInt, quarters, dimes;
    int     nickles, pennies;
    
    do
    {
        printf ("How much change is owed? \n");
        change = GetFloat ();
    }
    while (change < 0);
    
//  convert the change to a max number of coins.
    changeInt = (int) round (change * 100);

//  compute number of quarters
    quarters = changeInt / 25;
    changeInt-= (quarters * 25);
//  compute number of dimes
    dimes = changeInt / 10;
    changeInt -= (dimes * 10);
//  compute number of nickles
    nickles = changeInt / 5;
    changeInt -= (nickles * 5);
//  compute number of pennies
    pennies = changeInt / 1;
    changeInt -= (pennies * 1);
    
    printf ("%d\n", (quarters + dimes + nickles + pennies));
}
