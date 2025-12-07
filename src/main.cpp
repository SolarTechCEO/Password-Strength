#include <iostream>
#include <string>
#include "PasswordAnalyzer.h"

void showMenu() {
    std::cout << "=========================================\n";
    std::cout << "   Password Strength Analyzer\n";
    std::cout << "=========================================\n";
    std::cout << "1) Analyze a password\n";
    std::cout << "2) Generate a strong password\n";
    std::cout << "3) Quit\n";
    std::cout << "Choose an option: ";
}

int main() {
    PasswordAnalyzer analyzer("common_passwords.txt"); // Short for demo

    if (!analyzer.isDictionaryLoaded()) {
        std::cout << "[Info] Running without a common password dictionary.\n"
                  << "       (Place 'common_passwords.txt' in the same folder\n"
                  << "        to enable common-password detection.)\n\n";
    }

    bool running = true;
    while (running) {
        showMenu();

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }

        std::cin.ignore(10000, '\n'); // clear leftover newline

        if (choice == 1) {
            std::string password;
            std::cout << "\nEnter a password to analyze: ";
            std::getline(std::cin, password);

            int score = analyzer.calculateScore(password);
            std::string label = analyzer.classifyScore(score);

            std::cout << "\n=== Analysis Result ===\n";
            std::cout << "Score: " << score << " / 100\n";
            std::cout << "Rating: " << label << "\n\n";

            std::cout << "Feedback:\n";
            std::cout << analyzer.getFeedback(password) << "\n";

            if (analyzer.isCommonPassword(password)) {
                std::cout << "\n[Warning] This password appears in a common password list.\n"
                          << "          You should choose a different one.\n";
            }

            std::cout << "\n";

        } else if (choice == 2) {
            int length;
            char useSymbolsChar;

            std::cout << "\nDesired password length: ";
            std::cin >> length;
            std::cin.ignore(10000, '\n');

            std::cout << "Include symbols? (y/n): ";
            std::cin >> useSymbolsChar;
            std::cin.ignore(10000, '\n');

            bool useSymbols = (useSymbolsChar == 'y' || useSymbolsChar == 'Y');

            try {
                std::string generated = analyzer.generatePassword(length, useSymbols);
                std::cout << "\nGenerated password: " << generated << "\n\n";
            } catch (const std::exception& ex) {
                std::cout << "Error: " << ex.what() << "\n\n";
            }

        } else if (choice == 3) {
            running = false;
        } else {
            std::cout << "Please choose 1, 2, or 3.\n\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}