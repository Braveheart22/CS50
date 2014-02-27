#include <stdio.h>
#include <cs50.h>
/*
 * Provide quick validation of credit card number.
 */
int main (void)
{
    long long ccNumber, tempCcNumber;
    int sumDigit, sumEven, sumOdd;
    
    printf ("Number: ");
    ccNumber = GetLongLong ();

// If credit card number is less than 13 digits, it is not a vailid number
    if (ccNumber < 1000000000000)
    {
        printf ("INVALID\n");
        return 0;
    }

    tempCcNumber = ccNumber;
    sumEven = 0;

// Take every other number (starting with the 2nd to last digit),
// multiply by 2, then add all of the digits
    do
    {
        tempCcNumber = tempCcNumber / 10;
        sumDigit = 2 * (tempCcNumber % 10);
        if (sumDigit > 9)
            sumEven += sumDigit % 10 + (sumDigit / 10) % 10;
        else
            sumEven += sumDigit;
        tempCcNumber = tempCcNumber / 10;
    }   
    while (tempCcNumber > 1);
    
    tempCcNumber = ccNumber;
    sumOdd = 0;
    
// Take every other number (starting with the last digit),
// and add the digits together
    do
    {
        sumOdd += tempCcNumber % 10;
        tempCcNumber = tempCcNumber / 10;
        tempCcNumber = tempCcNumber / 10;
    }   
    while (tempCcNumber > 1);

// If the sum of the previous 2 equations is divisible by 10,
// it is a valid credit card number
    if ((sumOdd + sumEven) % 10 == 0)
        if (ccNumber >= 5000000000000000 && ccNumber <= 5999999999999999)
            printf ("MASTERCARD\n");
        else 
            if (ccNumber >= 4000000000000000 && ccNumber <= 4999999999999999)
                printf ("VISA\n");
            else
                if (ccNumber >= 340000000000000 && ccNumber <= 3799999999999999)
                    printf ("AMEX\n");
                else
                    printf ("INVALID\n");
       
    else
        printf ("INVALID\n");

    return 0;
}
