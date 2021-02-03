#include <cs50.h>
#include <stdio.h>

bool isEven(int number);

int main(void)
{
    // Card number
    long card = -1;
    // Even and odd numbers
    int digits1 = 0;
    int digits2 = 0;
    // Number of digits in card
    int count = 0;
    // First two digits in a number, if applicable
    int firstTwo = 0;
    // Output to be returned
    string output = "";

    // Ask for the card number
    while (card < 0)
    {
        card = get_long("Number:");
    }

    // Reads each digit and proccesses it accordingly
    while (card)
    {
        // If it's even adds it sums it directly
        if (isEven(count))
        {
            digits1 += card % 10;
        }
        else
        {
            // If it's odd multiplies the digit by 2
            int tempMul = (card % 10) * 2;

            // And then either adds it directly if it's single, or adds both digits if it's bigger than 10
            if (tempMul >= 0 && tempMul <= 9)
            {
                digits2 += tempMul;
            }
            else
            {
                digits2 += tempMul % 10;
                digits2 += tempMul / 10;
            }
        }

        if (card >= 10)
        {
            firstTwo = card;
        }
        // Removes last digit and adds the digit counter
        card /= 10;
        count++;
    }

    // Sums the digits and check if the last digit is a 0
    if ((digits1 + digits2) % 10 == 0)
    {
        if ((firstTwo == 34 || firstTwo == 37) && (count == 15))
        {
            output = "AMEX\n";
        }
        else if ((firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || firstTwo == 54 || firstTwo == 55) && (count == 16))
        {
            output = "MASTERCARD\n";
        }
        else if ((firstTwo / 10 == 4) && (count == 13 || count  == 16))
        {
            output = "VISA\n";
        }
        else
        {
            output = "INVALID\n";
        }
    }
    else
    {
        output = "INVALID\n";
    }

    printf("%s", output);
}

bool isEven(int number)
{
    bool even = false;

    if (number == 0 || number % 2 == 0)
    {
        even = true;
    }

    return even;
}
