//
//  FBullCowGame.hpp
//  BullsAndCowsGame
//
//  Created by Nitin Katyal on 12/21/17.
//  Copyright © 2017 Nitin Katyal. All rights reserved.
//

// If FBullCowGame_hpp not defined, define it
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp
#endif
/* FBullCowGame_hpp */

#include <string>

using FString = std::string;
using int32 = int;

// use Ftext as an alias to std::string in this file. We do this to later migrate to Ftext type
// used by the unreal engine, which is to support cross platform manipulation of strings / integers etc.
struct FBullCowCount {
    int32 bulls = 0;
    int32 cows = 0;
};

// As a practice enumerations variables should start with E
// We use class to allow strict enumeration other we wont be able to compile say OK under another
// enumerated variable.
enum class Estatus {
    OK,
    NOT_ISOGRAM,
    NO_INPUT,
    INVALID, // Initially value of the status of the word is invalid.
    LENGTH_MISMATCH,
    NOT_LOWERCASE
};

class FBullCowGame
{
public:
    FBullCowGame(); // Constructor
    void reset(); // TODO: Make a more rich  return value
    int32 getMaxRetries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    bool checkIfWordHasUppercase(FString) const;
    bool isGameWon() const;
    Estatus checkGuessValidity(std::string) const;
    
    // This function return struct of type BullCowCount and takes the guess of the user to evaluate
    // the number of bulls and cows when the guess is submitted.
    FBullCowCount submitValidGuess(FString);
    
private:
    int my_current_tries;
    int my_max_tries;
    bool b_game_won;
    FString my_hidden_string;
    bool isWordIsogram(FString) const;
};
