#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
// Rcheck if the character is present in the word being guessed
bool isCharPresent(const std::string& word, char guess) {
    return (word.find(guess) != std::string::npos);
}
// update the display after guessing
void updateDisplay(std::string& display, const std::string& word, char guess) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (word[i] == guess) {
            display[i] = guess;
        }
    }
}
// print the status of the game including how man guess is remaining
void printGameState(const std::string& display, int remainingAttempts, const std::vector<char>& guessedLetters) {
    std::cout << "Current word: " << display << std::endl;
    std::cout << "Remaining attempts: " << remainingAttempts << std::endl;
    std::cout << "Guessed letters: ";
    for (char c : guessedLetters) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int main() {
    // List of wposible words to guess
    std::vector<std::string> words = { "hangman", "apple", "computer", "programming", "elephant" };

    std::string playAgain;
    do {
        // Randomly select a word from the vector
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(words.begin(), words.end(), rng);
        std::string secretWord = words[0];

        std::string displayWord(secretWord.length(), '_');
        int remainingAttempts = 6;
        std::vector<char> guessedLetters;

        std::cout << "Welcome to Hangman!" << std::endl;
// code for guessing the word
        while (remainingAttempts > 0) {
            printGameState(displayWord, remainingAttempts, guessedLetters);

            char guess;
            std::cout << "Enter your guess: ";
            std::cin >> guess;

            if (std::find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                std::cout << "You already guessed that letter!" << std::endl;
                continue;
            }

            guessedLetters.push_back(guess);

            if (isCharPresent(secretWord, guess)) {
                updateDisplay(displayWord, secretWord, guess);
// if word is correct. ends the game but asks the player first if he wants to restart
                if (displayWord == secretWord) {
                    std::cout << "Congratulations! You guessed the word: " << secretWord << std::endl;
                    break;
                }
            } else {
                std::cout << "Incorrect guess!" << std::endl;
                --remainingAttempts;
            }
        }
// Code for game over. asks the user if he wants to restart the game, game restart when Y or y is entered.
        if (remainingAttempts == 0) {
            std::cout << "Game over! You ran out of attempts. The word was: " << secretWord << std::endl;
        }

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    } 
    // promt that asks the player if he wants to restart
    while (playAgain == "y" || playAgain == "Y");

    return 0;
}
