#include <iostream>
#include <string>
#include <vector>
// Print a triangle to the screen with asterisks
int main() {

    int lines;
    std::cout << "How many lines for the triangle?" << std::endl;
    std::cin >> lines;

    // calculate how many characters needed for the base of the triangle
    int total_chars = lines + (lines - 1);
    
    // the peak of the triangle needs one fewer spaces than the number of lines
    int starting_spaces = lines -1;
    
    // Peak of the triangle is always a single star
    int peak_of_triangle = 1;

    for(int i = 1; i <= lines; i++){

        // Use the string constructor function to set up the triangle print starting from the top
        std::string spaces(starting_spaces, ' ');
        std::string asterisks(peak_of_triangle, '*');
        std::cout << spaces << asterisks << std::endl;
        
        // Update our variables for the next pass
        peak_of_triangle = peak_of_triangle + 2;
        starting_spaces--;
    }

    return 0;
}