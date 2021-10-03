#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main() {
    // Seed random number generator
    srand(time(0));
     printf("%i\n", rand()%2);

}