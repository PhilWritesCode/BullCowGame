/*
	This is the console executable that makes use of the BullCowGame Class.

	This acts as the view in an MVC pattern, and is responsible 
	for all user interaction.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

//prototype methods, because we're not in a class (and have no .h file)
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
void RepeatGuess(FText);
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() 
{
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		
	} while (AskToPlayAgain());

	return 0;
}

void PlayGame() 
{
	BCGame.Reset();
	int32 MAX_GUESSES = BCGame.GetMaxTries();

	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MAX_GUESSES)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	return;
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,----|              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.isGameWon()) {
		std::cout << "Congratulations, you've won!\n\n";
	}
	else {
		std::cout << "Better luck next time!\n\n";
	}

	return;
}

FText GetValidGuess()
{
	EGuessStatus Status;
	FText Guess = "";
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please be sure your guess has no repeated letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guesses must be lower case.\n\n";
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

void RepeatGuess(FText Guess)
{
	std::cout << "Your guess was: '" << Guess << "'" << std::endl;
	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n) ";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << std::endl << std::endl;

	return response[0] == 'y' || response[0] == 'Y';
}
