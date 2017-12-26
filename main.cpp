//
//  main.cpp
//  BullsAndCowsGame
//
//  Created by Nitin Katyal on 12/21/17.
//  Copyright © 2017 Nitin Katyal. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// use Ftext as an alias to std::string in this file. We do this to later migrate to Ftext type
// used by the unreal engine, which is to support cross platform manipulation of strings / integers etc.
using Ftext = std::string;
using int32 = int;

// Declarations
void printIntro();
void printGameSummary();
void playGame();
Ftext getValidGuess();
bool askToPlayAgain();

// Before playing the game, lets get an instance of it
// Since onlt 1 user will be playing the game, we instantiate the game at the global level
// It is not a good practise to do so.
FBullCowGame BCGame;

int main()
{
    // Print the Introduction
    printIntro();
    
    // Play the game
    bool play_again = false;
    do {
        playGame();
        play_again = askToPlayAgain();
    }
    while(play_again);
    return 0;
}

// This method is used to play the game for some number of turns
void playGame()
{
    // reset the game before it is played
    BCGame.reset();
    int32 max_tries = BCGame.getMaxRetries();
    
    // Keep going while the game is NOT WON and number of tries has not been exhausted
    while(!BCGame.isGameWon() && (BCGame.getCurrentTry() <= max_tries)){
        Ftext guess = getValidGuess();
        BCGame.checkGuessValidity(guess);
        FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);
        std::cout << "Bulls = " << bullCowCount.bulls << ". Cows = " << bullCowCount.cows << "\n\n";
    }
    
    printGameSummary();
    
    return;
}

// prints the game summary when the game has been played
void printGameSummary()
{
    if (BCGame.isGameWon()){
        std::cout<<"YOU WON..."<<std::endl;
    }
    else {
        std::cout<<"BAD LUCK... MAYBE NEXT TIME."<<std::endl;
    }
    
    // end a new line
    std::cout<<std::endl;
    
    return;
}

// This method introduces the game
void printIntro()
{
    
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
}

// This method retreives the guessed word and ensures that the word is valid..
Ftext getValidGuess()
{
    Ftext guess = "";
    Estatus status = Estatus::INVALID;
    do {
        int32 current_guess_count = BCGame.getCurrentTry();
        
        std::cout << "Enter your " << current_guess_count << " guess" << " of " << BCGame.getMaxRetries() <<" : ";
        getline(std::cin, guess);
        
        std::cout<<"Your guess was: " << guess << std::endl;
        
        status = BCGame.checkGuessValidity(guess);
        
        switch (status) {
            case Estatus::NOT_LOWERCASE:
                std::cout<<"Not all letters are in lower case." << std::endl;
                break;
            case Estatus::LENGTH_MISMATCH:
                std::cout<<"Length of the guess does not match with the actual word."<<std::endl;
                break;
            case Estatus::NO_INPUT:
                std::cout<<"Empty String added."<<std::endl;
                break;
            case Estatus::NOT_ISOGRAM:
                std::cout<<"Word is not an Isogram. Repeating characters found."<<std::endl;
                break;
            default:
                return guess;
                break;
        }
    // Enter a new line for the next iteration
        std::cout<< std::endl;
    } while (status != Estatus::OK);
    
    return guess;
}

// This methods ask the user if he wants to play again
bool askToPlayAgain()
{
    Ftext play_again = "";
    std::cout<<"Do you want to play again (y/n): ";
    getline(std::cin, play_again);
    if ((play_again[0] == 'y') || (play_again[0] == 'Y')) {
        return true;
    }
    else{
        return false;
    }
}
