//
//  FBullCowGame.cpp
//  BullsAndCowsGame
//
//  Created by Nitin Katyal on 12/21/17.
//  Copyright © 2017 Nitin Katyal. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>

#define TMAP std::map

// use FString as an alias to std::string in this file. We do this to later migrate to FString type
// used by the unreal engine, which is to support cross platform manipulation of strings / integers etc.
using FString = std::string;
using int32 = int;

// Constructor function use reset to intialise the game..
FBullCowGame::FBullCowGame(){ reset(); };
    

// TODO: Make a more rich  return value
void FBullCowGame::reset()
{
    constexpr int32 MAXTRIES = 8;
    const FString HIDDEN_WORD = "plane";
    b_game_won = false;
    my_max_tries = MAXTRIES;
    my_hidden_string = HIDDEN_WORD;
    
    // This should not be constant
    my_current_tries = 1;
    return;
};

int32 FBullCowGame::getHiddenWordLength() const { return (int32) my_hidden_string.length(); };

// const doesnt allow the method to change any member variables (private / public)
int32 FBullCowGame::getMaxRetries() const { return my_max_tries; };

// const doesnt allow the method to change any member variables (private / public)
int32 FBullCowGame::getCurrentTry() const { return my_current_tries; };

bool FBullCowGame::isGameWon() const
{
    return b_game_won;
};

bool FBullCowGame::checkIfWordHasUppercase(FString guessWord) const
{
    for (int32 char_position=0;char_position < guessWord.length();char_position++)
    {
        if (!(islower(guessWord[char_position]))) {
            return true;
        }
    }
    
    return false;
};

bool FBullCowGame::isWordIsogram(FString guessWord) const
{
    TMAP<char, bool> letterSeen;
    bool isIsogram = true;
    
    for (auto letter: guessWord){
        letter = tolower(letter);
        
        if (letterSeen[letter]) {
            isIsogram = false;
        }
        else {
            letterSeen[letter] = true;
        }
    }
    return isIsogram;
};

Estatus FBullCowGame::checkGuessValidity(FString guess) const
{
    if (guess.length() == 0){
        return Estatus::NO_INPUT;
    }
    
    // Check if string lengths don't match
    if (my_hidden_string.length() != guess.length()) {
        return Estatus::LENGTH_MISMATCH;
    }
    
    // check if the word has uppercase
    if (checkIfWordHasUppercase(guess)) {
        return Estatus::NOT_LOWERCASE;
    }
    
    if (!isWordIsogram(guess)) {
        return Estatus::NOT_ISOGRAM;
    }
    
    return Estatus::OK;
};

// This function return struct of type BullCowCount and takes the guess of the user to evaluate
// the number of bulls and cows when the guess is submitted.
FBullCowCount FBullCowGame::submitValidGuess(FString guessWord)
{
    my_current_tries += 1;
    FBullCowCount bullCowCount;
    
    int32 word_length = (int32) my_hidden_string.length(); // assuming the same length for guess and hidden word
    
    // Not aiming to tackle efficiency / performance for now.
    for (int32 gchar=0;  gchar< word_length; gchar++)
    {
        for (int32 mhwchar=0; mhwchar< word_length; mhwchar++)
        {
            // If the character is found in the hidden string
            if (guessWord[gchar] == my_hidden_string[mhwchar])
            {
                // If they are the same position
                if (gchar == mhwchar)
                {
                    bullCowCount.bulls += 1;
                }
                else
                {
                    bullCowCount.cows += 1;
                }
            }
        }
    }
    
    // The game has been won if the length matches
    if (bullCowCount.bulls == word_length)
    {
       b_game_won = true;
    }
    return bullCowCount;
};

