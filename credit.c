// Description below taken from CS50's problem 1 set "Credit":

// "A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services.
// Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, the creditor knows whom to bill.
// There are a lot of people with credit cards in this world, so those numbers are pretty long:
// American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
// And [they use] decimal numbers (0 through 9)...
//
// All American Express numbers start with 34 or 37;
// most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem);
// and all Visa numbers start with 4. But credit card numbers also have a “checksum” built into them, a mathematical relationship between at least one number and others.
// That checksum enables computers to detect typos (e.g., transpositions), if not fraudulent numbers, without having to query a database, which can be slow."

// Checksum formula: Luhn's Algorithm

// "most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a credit card number is (syntactically) valid as follows:
//
// (1) Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
// (2) Add the sum to the sum of the digits that weren’t multiplied by 2.
// (3) If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!"

// Calling libraries supplied by the CS50 staff, as well as the C library
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    char *credit = get_string("Enter your credit card number: "); // 'get_string' is a part of the CS50 library that allows ease of use for those learning C for the first time
    int end = strlen(credit); //obstains length of the user inputted data in 'credit'
    unsigned char card_numbers[end]; // placeholder variable that has the same number of characters as 'credit'

    for (int i = 0; i < end; i++)
    {
        if (!isdigit(credit[i])) // checks if user input is a digit
        {
            printf("I didn't get a number\n");
            return 1; // terminates the program
        }
        card_numbers[i] = credit[i] - '0';
    }

    int half = end / 2, checkSum = 0;
    unsigned char manip = 0, hold = 0;

    for (int up = 0, odd = 0, even = 1; up < half; up++, odd += 2, even += 2) // for loop that executes luhn's algorithm
    {
        manip = card_numbers[odd] * 2; // checks the digit in location [odd], multiplies by 2, stores in 'manip'
        // (debugging method commented out below)
        //printf("%i - ", manip);
        hold = card_numbers[even]; // stores digit in location [even] in 'hold'
        // (debugging method commented out below)
        //printf("%i - ", hold);
        //printf("\n");
        checkSum += hold + (manip % 10) + ((manip / 10) % 10); // performs checksum on the values of the credit card number entered
    }

    // (debugging method commented out below)
    //printf("%i", checkSum);
    //printf("\n");

    int checkZero = checkSum % 10; // checks if the remainder of 'checkSum' is 0 (step in checking for a real credit card number)

    if (card_numbers[0] == 3 && (card_numbers[1] == 4 || card_numbers[1] == 7) && checkZero == 0) // checks if credit card number entered is American Express
    {
        printf("AMEX\n");
    }
    else if (card_numbers[0] == 5 && (card_numbers[1] == 1 || card_numbers[1] == 2 || card_numbers[1] == 3
    || card_numbers[1] == 4 || card_numbers[1] == 5) && checkZero == 0) // checks if credit card number entered is Mastercard
    {
        printf("MASTERCARD\n");
    }
    else if (card_numbers[0] == 4 && checkZero == 0) // checks if credit card number entered is Visa
    {
        printf("VISA\n");
    }
    else // if credit card number entered isn't any of the above options, then it's fake
    {
        printf("INVALID\n");
    }
}