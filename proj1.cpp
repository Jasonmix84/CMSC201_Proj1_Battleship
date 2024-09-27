/*
 File: Proj1.cpp
 Author: Jason Rojas
 Section: 12
 Email: jasonr2@umbc.edu
 Date: 2/17/23
 Description: A guess the positon game where you try to find where the position of a ballon is on a 2D grid (array) Similar to battleship
*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

//CONSTANTS

const int rows = 16; //change the number of rows(y-axis)
const int columns = 20; //change the number of columns (x-axis)
const char NOT_GUESSED = '$'; //Represets spots not guessed
const char GUESSED = 'G'; //Represents spots guessed

// PROTOTYPES

void printMap(char grid[rows][columns]);
//Name: PrintMap
//PreCondition: An array named grid is passed to function
//PostCondition: Couts the grid to viewer so they can see where they have guessed and where they haven't

int setBallon(int bounds);
//Name: setBallon
//PreCondition: takes in the limit i.e the number or rows or columns
//PostCondition: returns a random number that is less than or equal to the number of rows or columns which is used as the ballon's position

void resetMap(char grid[rows][columns]);
//Name: resetMap
//PreCondition: passes a grid with some locations already guessed
//PostCondition: the grid positions that have been guessed are now set back to unguessed

bool isHit(int xPos, int yPos, int bPosX, int bPosY);
//Name: isHit 
//PreCondition: take in the ballon positon and the guess
//PostCondition: returns true or false on whether the ballon was hit

void checkDirection(int guessX , int guessY, int ballonPosX, int ballonPosY);
//Name: checkDirection
//PreCondition: takes the ballon position and the guess
//PostCondition: couts if the guess was north south of the ballon or east west of the ballon

// MAIN

int main (){
    //variables
    int choiceNum = 0;
    srand(time(NULL));
    int ballonYPos = 0;
    int ballonXPos = 0;
    int xGuess = 0;
    int yGuess = 0;
    char playAgain = ' ';

    //get a random number for ballon X and Y positions 
    ballonYPos = setBallon(rows);
    ballonXPos = setBallon(columns);

    //cout << ballonXPos << endl; for testing
    //cout << ballonYPos << endl; for testing

    //create the grid 
    char grid[rows][columns] = {};
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            grid[i][j] = NOT_GUESSED;
        }
    }
    
    //start of what the user sees
    cout << "Welcome to the Surveillance Ballon Traker\nYou are searching for the surveillance ballon" << endl;

    //game ends when user enters 3 when asked what they want to do
    while (choiceNum != 3)
    {
        cout << "What would you like to do?: " << endl;
        cout << "1. Dispay Map\n2. Guess Location of Ballon\n3. Exit" << endl;
        cin >> choiceNum;
        
        if (choiceNum == 1){
            //Display Map
            printMap(grid);
        }
        else if (choiceNum == 2){
            //Guess location of ballon
            cout << "Where would you like to look for the balloon?" << endl;
            do {
            //validate users response only allow answers within the bounds
            cout << "Enter the X coordinate (" << (columns - columns) << " - " << (columns-1) << "): " <<endl;
            cin >> xGuess;
            }
            while ((xGuess < 0) or (xGuess > columns-1));
            do {
            //validate users response only allow answers within the bounds
            cout << "Enter the Y coordinate (" << (rows - rows) << " - " << (rows-1) << "): " <<endl;
            cin >> yGuess;
            }
            while ((yGuess < 0) or (yGuess > rows-1));

            //sets the grid positon to G
            grid[yGuess][xGuess] = GUESSED;

            if (isHit(xGuess, yGuess, ballonXPos, ballonYPos)){
                //Won Game
                cout <<"You found the ballon!" << endl;
                cout << "Would you like to play again? (y/n)" << endl;
                //play again?
                cin >> playAgain;
                switch (playAgain)
                {
                    case 'y':
                    case 'Y':
                        //play again
                        resetMap(grid);
                        ballonYPos = setBallon(rows);
                        ballonXPos = setBallon(columns);
                        cout << "Welcome to the Surveillance Ballon Traker\nYou are searching for the surveillance ballon" << endl;
                        break;
                    case 'N':
                    case 'n':
                        //end game
                        choiceNum = 3;
                        break;
                    default:
                        //validate answers only takes 4 options
                        cout << "Invalid Input\nWould you like to play again? (y/n)" << endl;
                }
            }
            else{
                cout << "You didn't find the ballon"<< endl;
                //Tell user if ballon is north south east or west
                checkDirection(xGuess, yGuess, ballonXPos, ballonYPos);
            }

        }
        else if (choiceNum == 3){
            // exit
            cout <<"GoodBye" << endl;
        }
        else{
            // inpuut validation
            cout << "Invalid input please enter 1, 2, or 3" << endl;
        }
    } 
    cout << "Thank you for using the Surveillance Balloon Tracker" << endl;


    return 0;
}

//Functions

//print map func
void printMap(char grid[rows][columns]){
    cout << "     ";
    for (int i = 0; i < columns; i++){
        //shows the columns (x-coordinates) on map
        cout << setw(5) << i;
        }
    cout << endl;

    for (int i = 0; i < rows; i++){
        // couts the row numbers (y-coordinate)
         cout << setw(5) << (i);
        for (int j = 0; j < columns; j++){
            // cout the actual grid
            cout << setw(5) << grid[i][j];
        }
        // new row
        cout << endl; 
}
}

// set ballon func
int setBallon(int bounds){
    //generates a random number 
    //bounds is the maximum possible number for rows or columns
    int randomPos = 0;
    randomPos = (rand() %  (bounds + (1 - 0)));

    return randomPos;
    //returns the random number
}

// reset map func
void resetMap(char grid[rows][columns]){
    //resets the map
    //iterates through grid and evertime there is a G set it to $ to represent them as unguessed
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if (grid[i][j] == GUESSED){
                grid[i][j] = NOT_GUESSED;
            }

        }
    }
}

//Is Hit func
bool isHit(int xPos, int yPos, int bPosX, int bPosY){
    //boolean expression is returned into a while loop in main
        return ((bPosX == xPos) and (bPosY == yPos));
    }

// check direction func
void checkDirection(int guessX , int guessY, int ballonPosX, int ballonPosY){
    // will check if hit and give a dirrection of where ballon is
    // check north or south first then east or west
        if (guessY < ballonPosY){
            cout << "The ballon is south of your guess" << endl; 
        }
        else if (guessY > ballonPosY){
            cout << "The ballon is north of your guess" << endl;
        }
        else if (guessX > ballonPosX){
            cout << "The ballon is west of your guess" << endl;
        }
        else{
            cout << "the ballon is east of your guess" << endl;
        }
    }

