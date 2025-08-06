// Daniel Henrique da Silva, Gabriel Henrique da Silva, Jorge Luiz Siemann Pereira, Lucas dos Santos Luckow

#include <iostream>
#include <locale.h>
#include <time.h>
#define SIZE 9
using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul"); // To support accents in Windows terminal
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    int menu, i, j, random, won;
    int counter = 0, ri; // Move counter // Row index of game matrix
    int value, inputRow, inputCol; // Variables used to play

    int solution[SIZE][SIZE] = { 4, 9, 5, 2, 8, 7, 3, 6, 1, 
                                 7, 2, 8, 6, 1, 3, 4, 9, 5, 
                                 3, 6, 1, 9, 5, 4, 7, 2, 8, 
                                 6, 5, 3, 8, 4, 9, 2, 1, 7, 
                                 9, 8, 4, 1, 7, 2, 6, 5, 3, 
                                 2, 1, 7, 5, 3, 6, 9, 8, 4, 
                                 1, 3, 2, 4, 6, 5, 8, 7, 9, 
                                 5, 4, 6, 7, 9, 8, 1, 3, 2, 
                                 8, 7, 9, 3, 2, 1, 5, 4, 6}; // Main matrix
    int key[SIZE][SIZE]; // Key matrix
    int game[SIZE][SIZE]; // Game matrix
    
    do {
        cout << endl;
        cout << "                                                          ███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗\n"
                "                                                          ██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║\n"
                "                                                          ███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║\n"
                "                                                          ╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║\n"
                "                                                          ███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝\n"
                "                                                          ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ \n\n\n\n";
        cout << "                                                                            1.  PLAY\n\n\n"
                "                                                                            2.  ABOUT\n\n\n"
                "                                                                            3.  EXIT\n\n\n\n";
        cin >> menu;

        switch (menu) {
        case 1: // Play
            system(CLEAR);
            random = rand() % 4 + 1; // Generates a pseudo-random number from 1 to 4 to define the template matrix
            
            if (random == 1) { // Generate key matriz (without changes)
                for (i = 0; i < SIZE; i++) {
                    for (j = 0; j < SIZE; j++) {
                        key[i][j] = solution[i][j];
                    }
                }
            } else if (random == 2) { // Generate key matriz (transposed)
                for (i = 0; i < SIZE; i++) {
                    for (j = 0; j < SIZE; j++) {
                        key[i][j] = solution[j][i];
                    }
                }
            } else if (random == 3) { // Generate key matriz (inverted by rows)
                for (i = 0; i < SIZE; i++) {
                    for (j = 0; j < SIZE; j++) {
                        key[8 - i][j] = solution[i][j];
                    }
                }
            } else if (random == 4) { // Generate key matriz (inverted by columns)
                for (i = 0; i < SIZE; i++) {
                    for (j = 0; j < SIZE; j++) {
                        key[i][8 - j] = solution[i][j];
                    }
                }
            }
    
            for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++) {
                    game[i][j] = key [i][j]; // Copy key matrix to game matrix
                }
            }
    
            for (value  = 0; value  < 40;) {
                inputRow = rand() % 9; // Generates a pseudo-random number from 0 to 8 to define row coordinate
                inputCol = rand() % 9; // Generates a pseudo-random number from 0 to 8 to define column coordinate
                if (game[inputRow][inputCol] > 0) { // Check if the value has already been reset
                    value ++;
                }
                game[inputRow][inputCol] = 0; // Reset value
            }
    
            won = 40;
            do { // Game starts
                ri = 1;
                cout << "Move counter: " << counter << endl << endl;
                cout << " 1 2 3  4 5 6  7 8 9  \n"; // Prints the column index before the loop that prints the game matrix
                cout << "╔══════╦══════╦═════╗\n"; // Print this edge before the loop that prints the game matrix
                for (i = 0; i < SIZE; i++) {
                    if (i == 3 || i == 6 ) // Print this row after the 3rd and 6th lines of the matrix
                        cout << "╠══════╬══════╬═════╣\n";
                    for (j = 0; j < SIZE; j++) {
                        if (j % 3 == 0) { // Print this row after the 3rd and 6th row of the matrix
                            cout << "║"; 
                        }
                        if (game[i][j] == 0 && j != 8) { // If the value is 0, print empty with space after
                            cout << "  ";
                        } else if (game[i][j] == 0 && j == 8) { // If the value is 0 in the last column, print empty with no space after it
                            cout << " ";
                        } else if (game[i][j] != 0 && j < 8) { // If it has a value and it is not the last column, print the value with a space after it
                            cout << game[i][j] << " ";
                        } else { // Print the value without the space after it (last column)
                            cout << game[i][j]; 
                        }
                    }
                    cout << "║ " << ri << endl; // After each end of row, print a ║ as border and skip the row
                    ri++;
                }
                cout << "╚══════╩══════╩═════╝\n\n"; // After the loop that prints the game matrix, print this row at the end
                
                cout << "Enter the row you want to fill...";
                cin >> inputRow;
                cout << "Enter the column you want to fill...";
                cin >> inputCol;
                cout << "Enter the value you want to fill...";
                cin >> value;
                system(CLEAR);
            
                if (value == key[inputRow - 1][inputCol - 1] && game[inputRow - 1][inputCol - 1] == 0) { // Check if the value is valid in an unfilled position
                    game[inputRow - 1][inputCol - 1] = value;
                    won--; // This value starts at 40, which is the number of values left to discover, it decreases, and when it reaches zero, you win.
                    cout << "You got a value right!\n\n";
                } else if ((inputRow < 1 || inputRow > 9 || inputCol < 1 || inputCol > 9) && (value < 1 || value > 9)) { // Check if the position is invalid && the value is invalid
                    cout << "You entered an invalid position and an invalid value! Enter only natural numbers from 1 to 9.\n\n";
                } else if (inputRow < 1 || inputRow > 9 || inputCol < 1 || inputCol > 9) { // Check if the position is invalid
                    cout << "You entered an invalid position! Enter a natural number from 1 to 9.\n\n";
                } else if (game[inputRow - 1][inputCol - 1] > 0) { // Check if the position has already been filled
                    cout << "This position has already been filled!\n\n";
                } else if (value < 1 || value > 9) { // Check if the value is invalid
                    cout << "You entered an invalid value! Please enter a natural number from 1 to 9.\n\n";
                } else if (value != key[inputRow - 1][inputCol - 1] && game[inputRow - 1][inputCol - 1] == 0) { // Check if the value is incorrect
                    cout << "You entered an incorrect value!\n\n";
                }
            
                counter++; // Increase the counter variable with each attempt
            
            } while (won > 0);
    
            system(CLEAR);
            cout << "                                                 ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗  ██╗██╗██╗\n"
                    "                                                 ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║  ██║██║██║\n"
                    "                                                  ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║  ██║██║██║\n"
                    "                                                   ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║  ╚═╝╚═╝╚═╝\n"
                    "                                                    ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║  ██╗██╗██╗\n"
                    "                                                    ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝  ╚═╝╚═╝╚═╝\n\n\n\n";
    
            cout << "You needed " << counter << " moves to complete the sudoku.\n";
            cout << "Type any character to return to the menu...";
            counter = 0; // Reset move counter
            cin.ignore();
            cin.get();
            system(CLEAR);
            break;
        
        case 2: // About
            system(CLEAR);
            cout << "\nDevelopers:    Daniel Henrique da Silva\n"
                    "               Gabriel Henrique da Silva\n"
                    "               Jorge Luiz Siemann Pereira\n"
                    "               Lucas dos Santos Luckow\n"
                    "Professor:     Prof. Rafael Ballotin Martins\n"
                    "Course:        Algorithms and Programming I\n"
                    "June/2023\n\n";
            cout << "Type any character to return to the menu...";
            cin.ignore();
            cin.get();
            system(CLEAR);
            break;

        case 3: // Exit
            break;
        }

        system(CLEAR);
    } while (menu != 3);
    return 0;
}
