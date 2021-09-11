#include <stdio.h>
#include <cs50.h>



int main (void)
{

    float x = get_float("x: ");
    float y = get_float("y: ");

    // Tell the formatter how many significant digits
    printf("%.50f\n", x / y);

    // We run into all kinds of issues when the computer can't store the values. It literally makes shit up.

    // Y2K will happen again in 2038


}




