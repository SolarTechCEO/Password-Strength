#ifndef PASSWORD_ANALYZER_H
#define PASSWORD_ANALYZER_H

#include <string>
#include <unordered_set>

/**
 * PasswordAnalyzer
 *
 * A class that can:
 *  - Load a list of common passwords from a file
 *  - Calculate a numeric strength score for a password
 *  - Classify the score into categories (Very Weak, Weak, etc.)
 *  - Check if a password is in the "common" password list
 *  - Produce human-readable feedback for improving a password
 *  - Generate strong random passwords
 *
 * This is designed as a portfolio-style class with clear responsibilities.
 */
class PasswordAnalyzer {
private:
    std::unordered_set<std::string> commonPasswords;
    bool dictionaryLoaded;

    bool hasLower(const std::string& password) const;
    bool hasUpper(const std::string& password) const;
    bool hasDigit(const std::string& password) const;
    bool hasSymbol(const std::string& password) const;
    bool hasRepeatedSequences(const std::string& password) const;

public:
    // Constructor: attempts to load a dictionary file of common passwords.
    explicit PasswordAnalyzer(const std::string& dictionaryFile);

    // Returns true if dictionary file was successfully loaded.
    bool isDictionaryLoaded() const;

    // Returns true if password is present in the common password list.
    bool isCommonPassword(const std::string& password) const;

    // Calculate a score between 0 and 100 based on composition and risks.
    int calculateScore(const std::string& password) const;

    // Convert a numeric score into a text label.
    std::string classifyScore(int score) const;

    // Generate human-readable feedback about how to improve the password.
    std::string getFeedback(const std::string& password) const;

    // Generate a strong random password.
    std::string generatePassword(int length, bool allowSymbols = true) const;
};

#endif