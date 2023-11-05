//
//  picture.cpp
//  picture
//
//  Created by Layah Vigneaud on 10/20/23.
//
//
//  picture.cpp
//  picture
//
//  Created by Layah Vigneaud on 10/20/23.
//
#include "grid.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// constant variables and other variables.
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;
int r = 1;
int c = 1;
bool syntaxError(string commandString, int& pos);
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg); //function to plot line
void plotHorizontalLine(int r, int c, int distance, char plotChar, int fgbg); //function to plot horizontal line
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg); //function to plot vertical line
int performCommands(string commandString, char& plotChar, int& mode, int& badPos); //function to perform commands
bool getDistance(string x, int& startingPos, int& distance); //function to find distance
//Main function provided by Smallberg
int main()
{
    
    for (;;)
    {
        cout << "Enter the number of grid rows and columns (max 30 each): ";
        int nRows;
        int nCols;
        cin >> nRows >> nCols;
        cin.ignore(10000, '\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string (empty line to quit): ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
            cout << "Syntax error at position " << position << endl;
            break;
          case 2:
            if (!isprint(currentChar))
                cout << "Current character is not printable" << endl;
            if (currentMode != FG  &&  currentMode != BG)
                cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
            break;
          case 3:
            cout << "Cannot perform command at position " << position << endl;
            break;
          default:
              // It should be impossible to get here.
            cout << "performCommands returned " << status << "!" << endl;
        }
    }
}
// Horizontal line function, with (x,y) coordinates (r,c), distance, the character plotted, and foreground/background information.
void plotHorizontalLine(int r, int c, int distance, char plotChar, int fgbg)
{
    for(int i = 0; i <= abs(distance); i++) //loop runs until reaching the absalout value of distance.
    {
        if (fgbg == FG || (fgbg == BG && getChar(r, c) == ' ')) { // if in the foreground or background with a space, call set char.
            setChar(r, c, plotChar);
        }
        if (distance < 0) { // if distance is less then zero subtract from c.
            c--;
                }
        else if (distance > 0) { // if distance is greater then zero add to c.
            c++;
        }
        
        
    }
    
        
}
// Vertical line function, with (x,y) coordinates (r,c), distance, the character plotted, and foreground/background information.
void plotVerticalLine(int r, int c, int distance, char plotChar, int fgbg)
{
    
    for(int i = 0; i <= abs(distance); i++) //loop runs until reaching the absalout value of distance.
    {
        if (fgbg == FG || (fgbg == BG && getChar(r, c) == ' ')) { // if in the foreground or back ground with a space, call set char.
            setChar(r, c, plotChar);
        }
        if (distance < 0) { // if distance is less then zero subtract from r.
            r--;
        
        }
       else if (distance > 0) { // if distance is greater then zero add to r.
            r++;
        }
    }
}
// plot line function with (x,y) coordinates (r,c), distance, direction, the character plotted, and foreground/background information.
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
    if (!(isprint(plotChar))) //if character can not be printed return.
    {
        return false;
    }
    if(dir != HORIZ && dir != VERT) // if the direction is not horizontal or vertical return.
     {
         return false;
     }
    if(fgbg != FG && fgbg != BG) // if not in foreground or backround return.
        {
            return false;
        }
    if(dir == HORIZ) // if direction is horizontal
    {
        
        if(c + distance <= 0 || c + distance > getCols() || r  <= 0 || r > getRows()) // check the distance and (c,r) values against 0 and the number of columns and rows. Return false if conditions aren't met, else plot line.
        {
            return false;
        }
        else
        {
            plotHorizontalLine(r, c, distance, plotChar, fgbg);
        }
    }
    if(dir == VERT) // if direction is vertical.
    {
        if(r + distance <= 0 || r + distance > getRows() || c <= 0 || c > getCols()) // check the distance and (c,r) values against 0 and the number of columns and rows. Return false if conditions aren't met, else plot line.
        {
            return false;
        }
        else
        {
            plotVerticalLine(r, c, distance, plotChar, fgbg);
        }
        
    }
    
    return true;
}
// function performCommands, with the string, character, mode and bad position information.
int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    //declare variables
    int pos = 0;
    int r = 1;
    int c = 1;
    int x;
    if(!isprint(plotChar)){
        return 2;
    }
    if(mode != BG && mode != FG){
        return 2;
    }
    
    if(!syntaxError(commandString,pos)){
        badPos = pos;
        return 1;
    }
    pos = 0;
    while(pos != commandString.size()) // Runs until the position equals the string size
    {
        x = pos;
        int distance = 0;
//        string s = toupper(commandString[pos]);
        if (toupper(commandString[pos]) == 'H') { //Check for character h/H.
        
            if(!getDistance(commandString, pos, distance)) //Check distance and returns 1 and badPos if false, else calls plotLine function.
            {
                badPos = pos;
                return 3;
            }
            if(plotLine(r, c, distance, HORIZ, plotChar, mode))
            {
                c = c + distance;
    
            }
            else{
                badPos = x;
                return 3;
            }
        }
        else if (toupper(commandString[pos]) == 'V') { // Checks for character v/V
            if(!getDistance(commandString, pos, distance)) //Check distance and returns 1 and badPos if false, else calls plotLine function.
            {
                badPos = pos;
                return 3;
            }
            if(plotLine(r, c, distance, VERT, plotChar, mode))
            {
                r = r + distance;
            }
            else{
                badPos = x;
                return 3;
            }
        }
            // Checks for b or B and plots characters int in the backeground if true.
        else if (toupper(commandString[pos]) == 'B') { // Checks for b/B.
            pos++;
            if(pos == commandString.size() && !isprint(commandString[pos])) // if the position equals the string size and is not a printable character returns 1, else changes mode to BG and plotChar to position.
            {
                badPos = pos;
                return 3;
            }
            else{
                mode = BG;
                plotChar = commandString[pos];
                pos++;
                }
                }
        else if (toupper(commandString[pos]) == 'F') // Checks for f/F.
        {
            pos++;
            if(pos == commandString.size() && !isprint(commandString[pos])) // if the position equals the string size and is not a printable character returns 1, else changes mode to FG and plotChar to position.
            {
                badPos = pos;
                return 3;
            }
            else{
                mode = FG;
                plotChar = commandString[pos];
                pos++;
                }
            }
            
        else if (toupper(commandString[pos]) == 'C') //Checks for c/C, and if found clears the grid and sets all values back to starting mode, character and position.
        {
            clearGrid();
            r = 1;
            c = 1;
            plotChar = '*';
            mode = FG;
            pos++;
            }
        else
        {
            badPos = x;
            return 3;
        }
    }
return 0; //if no conditions are met the function returns.
}
                
// Get Distance function with the string, and references to the position and distance values.
bool getDistance(string commandString, int& pos, int& distance){
    pos++;
    bool negative = false; // creates a boolean to check for negative numbers.
    if(!isdigit(commandString[pos]) && commandString[pos] != '-') // if the value of pos is not a digit or dash returns false.
    {
        return false;
    }
    if(commandString[pos] == '-') //if dash is present the distance is negative.
    {
        pos++;
        negative = true;
    }
    int start = pos;
    for(int j = 0; j <2; j++){ // checks for the two number values.
        if(isdigit(commandString[pos]))
        {
            pos++;
        }
        else if(pos - start == 0) //checks if starting position and current position are the same.
        {
            return false;
        }
        else{
            break;
            }
        }
        string original = commandString.substr(start, pos-start); //gets substring value
        if(negative){ // if negative is true, makes original variable a negative number.
            original = '-' + original;
        }
        distance = stoi(original); // changes string values to integers.
        return true;
}
//syntax error checks all code for syntax issues and returns.
bool syntaxError(string commandString, int& pos){
    while(pos != commandString.size()){
        if(toupper(commandString[pos]) == 'H' || toupper(commandString[pos]) == 'V'){
            pos++;
            if(commandString[pos] == '-')
            {
                if(pos == commandString.size())
                    return false;
                pos++;
            }
            if(!isdigit(commandString[pos]))
                return false;
            pos++;
            if(pos != commandString.size() && isdigit(commandString[pos]))
                pos++;
            if(pos == commandString.size())
            {
                pos++;
                return true;
            }
        
        }
        else if(toupper(commandString[pos]) == 'B' || toupper(commandString[pos]) == 'F'){
            pos++;
            if(!isprint(commandString[pos]))
                return false;
            if(pos == commandString.size())
                break;
            pos++;
            
        }
        else if(toupper(commandString[pos]) == 'C'){
            pos++;
            break;
        }

      else{
            return false;
        }
    }
    return true;
}

