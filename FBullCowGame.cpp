#pragma once
#include "FBullCowGame.h"
#include <map>

//make syntax Unreal Friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (letterSeen[Letter]) {
			return false;
		} else {
			letterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	
	for (int32 HiddenWordIndex = 0; HiddenWordIndex < WordLength; HiddenWordIndex++)
	{
		for (int32 GuessWordIndex = 0; GuessWordIndex < WordLength; GuessWordIndex++)
		{
			if (MyHiddenWord[HiddenWordIndex] == Guess[GuessWordIndex]) 
			{
				if (HiddenWordIndex == GuessWordIndex) 
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		
	if (Guess == MyHiddenWord)
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}
