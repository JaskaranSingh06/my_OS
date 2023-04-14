#include "stdlib.h"

//This method will swap the pointers of char1 and char2
void swap(char* ch1, char* ch2)
{
    char temp = *ch1;
    *ch1 = *ch2;
    *ch2 = temp;
}

//This function will reverse the string using the helper method swap.
char* reverse(char* str, int start, int end)
{
    while (start < end)
    {
        swap(&str[start++], &str[end--]);
    }
    return str;
}


// This function will take in a integer and a string as an arguments and return the int in string format.
char* itoa(char* str, int toPrint)
{
    int base = 10;
    int i = 0;
    _Bool negative = 0;

    if(toPrint == 0)
    {
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str;
    }
    //if the value is negative make sure we account for it. set num to its absolute number.
    if(toPrint < 0)
    {
        negative = 1;
        toPrint = -toPrint;
    }

    //Loop through each digit
    while(toPrint)
    {
        int rem = toPrint % base;

        if(rem >= 10)
        {
            str[i++] = 'a' + (rem - 10);
        }
        else
        {
            str[i++] = '0' + rem;
        }

        toPrint = toPrint/base;
    }


    //if negative we need to add the -.
    if(negative == 1)
    {
        str[i++] = '-';
    }

    //add null terminator
    str[i] = '\0';

    //reverse the string and return
    return reverse(str, 0, i - 1);

}
