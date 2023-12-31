// Header Files
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <Windows.h>

using namespace std;

// Global Constants
const int WORD_LENGTH = 5;
const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;

// Wordle word to guess
string getWordleWord()
{
    return "words";
}

// Convert all letters to uppercase
void toUpperCase(string &input)
{
    transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
    { return toupper(c); });
}

// Diplay for wordle game
void printWordle(vector<string> tries, vector<vector<int>> matches, int currentTry)
{
    system("cls");
    cout << "=================================================================" << endl;
    cout << "|                                                               |" << endl;
    cout << "|   WW\\      WW\\                           DD\\ LL\\   |" << endl;
    cout << "|   WW | W\\  WW |                          DD |LL |             |" << endl;
    cout << "|   WW |WWW\\ WW | OOOOOO\\   RRRRRR\\   DDDDDDD |LL | EEEEEE\\     |" << endl;
    cout << "|   WW WW WW\\WW |OO  __OO\\ RR  __RR\\ DD  __DD |LL |EE  __EE\\    |" << endl;
    cout << "|   WWWW  _WWWW |OO /  OO |RR |  \\__|DD /  DD |LL |EEEEEEEE |   |" << endl;
    cout << "|   WWW  / \\WWW |OO |  OO |RR |      DD |  DD |LL |EE   ____|   |" << endl;
    cout << "|   WW  /   \\WW |\\OOOOOO  |RR |      \\DDDDDDD |LL |\\EEEEEEE\\    |" << endl;
    cout << "|   \\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|   |" << endl;
    cout << "|                                                               |" << endl;
    cout << "=================================================================" << endl;
    for (int i = 0; i <= currentTry && i < tries.size(); i++)
    {
        string separator = "-";
        string padding = "|";
        string text = "|";
        for (int j = 0; j < tries[i].length(); j++)
        {
            separator += "------";
            padding += "     |";
            char value = toupper(tries[i][j]);
            text += "  ";
            // Yellow color meaning correct letter but wrong position
            if (matches[i][j] == PARTIAL_MATCH)
            {
                text += "\033[33m";
            }
            // Green color meaning correct letter and correct position
            else if (matches[i][j] == MATCH)
            {
                text += "\033[32m";
            }
            text += value;
            if (matches[i][j] == PARTIAL_MATCH || matches[i][j] == MATCH)
            {
                text += "\033[0m";
            }
            text += "  |";
        }
        if (i == 0)
        { 
            cout << separator << endl;
        }
        cout << padding << endl;
        cout << text << endl;
        cout << padding << endl; 
        cout << separator << endl;
    }
}

// Checks if word inputted is a valid word
bool isValid(string word)
{
    return word.length() == WORD_LENGTH && word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

// Compares letters and checks for matches
void markMatch(vector<vector<int>> &matches, int tryIndex, string target, string guess)
{
    for (int i = 0; i < guess.length(); i++)
    {
        matches[tryIndex][i] = NOT_MATCH;
    }
    for (int j = 0; j < guess.length(); j++)
    {
        for (int i = 0; i < target.length(); i++)
        {
            if (guess[j] == target[i])
            {
                if (i == j)
                {
                    matches[tryIndex][j] = MATCH;
                   break;
                }
                else
                {
                    matches[tryIndex][j] = PARTIAL_MATCH;
                }
            }
        }
    }
}

// Checks if user guess word is the wordle word
bool isAllMatch(string target, string guess)
{
    for (int i = 0; i < guess.length(); i++)
    {
        if (guess[i] != target[i])
            return false;
    }
    return true;
}

int main(int, char**)
{
    // Set the maximum number of allowed tries
    int numberOfTries = 6;
    
    // Initialize vectors to store player's guesses and match information
    vector<string> tries(numberOfTries);
    vector<vector<int>> matches(numberOfTries, vector<int>(WORD_LENGTH));
    
    // Get the target word for the game and convert it to uppercase
    string targetWord = getWordleWord();
    toUpperCase(targetWord);
    
    // Declare variables for user input and current try count
    string input;
    int currentTry = 0;
    
    // Loop until the player exhausts the allowed number of tries
    while (currentTry < numberOfTries)
    {
        // Prompt the user to enter a guess, ensuring the input is valid
        do
        {
            cout << "Please enter your guess (word length must be " + to_string(WORD_LENGTH) + ") or type Q to quit: ";
            getline(cin, input);
            toUpperCase(input);
        } while (input != "Q" && !isValid(input));
        
        // If the user chooses to quit, display a message and exit the loop
        if (input == "Q")
        {
            cout << "Quit game" << endl;
            break;
        }

        // Store the current guess, mark the match, and display the game state
        tries[currentTry] = input;
        markMatch(matches, currentTry, targetWord, input);
        printWordle(tries, matches, currentTry);
        
        // If the guess is correct, display a victory message and exit the loop
        if (isAllMatch(targetWord, input))
        {
            cout << "You Guessed The Word!" << endl;
            break;
        }
        // If the player fails to guess within the allowed tries, display a message
        // (Note: There is a logical error here, the condition should be currentTry == numberOfTries - 1)
        else if (currentTry == numberOfTries)
        {
            cout << "You Did Not Guess The Word!" << endl;
        }

        // Move to the next try
        currentTry++;
    }

    // Exit the program
    return 0;
}
