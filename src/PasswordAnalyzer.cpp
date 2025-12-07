#include "PasswordAnalyzer.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>

// ---------- Constructor & Dictionary Loading ----------

PasswordAnalyzer::PasswordAnalyzer(const std::string& dictionaryFile)
    : dictionaryLoaded(false) {

    std::ifstream in(dictionaryFile);
    if (!in) {
        // Not going to throw an error here so the program can still be used without a dictionary file.
        std::cerr << "[Warning] Could not open dictionary file: "
                  << dictionaryFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            // Store passwords in lowercase for case-insensitive comparison
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            commonPasswords.insert(line);
        }
    }

    if (!commonPasswords.empty()) {
        dictionaryLoaded = true;
    }
}

bool PasswordAnalyzer::isDictionaryLoaded() const {
    return dictionaryLoaded;
}

// ---------- Helper Checks ----------

bool PasswordAnalyzer::hasLower(const std::string& password) const {
    for (char c : password) {
        if (std::islower(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordAnalyzer::hasUpper(const std::string& password) const {
    for (char c : password) {
        if (std::isupper(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordAnalyzer::hasDigit(const std::string& password) const {
    for (char c : password) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordAnalyzer::hasSymbol(const std::string& password) const {
    for (char c : password) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordAnalyzer::hasRepeatedSequences(const std::string& password) const {
    // Simple heuristic: look for immediate repeated pairs.
    // Example: "abab", "123123", "aaaa" -> considered as repeated sequence.
    const int n = static_cast<int>(password.size());
    if (n < 4) return false;

    for (int len = 2; len <= n / 2; ++len) {
        for (int i = 0; i + 2 * len <= n; ++i) {
            std::string first = password.substr(i, len);
            std::string second = password.substr(i + len, len);
            if (first == second) {
                return true;
            }
        }
    }
    return false;
}

// ---------- Common Password Check ----------

bool PasswordAnalyzer::isCommonPassword(const std::string& password) const {
    if (!dictionaryLoaded) return false;

    std::string lowered = password;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return commonPasswords.find(lowered) != commonPasswords.end();
}

// ---------- Scoring & Classification ----------

int PasswordAnalyzer::calculateScore(const std::string& password) const {
    if (password.empty()) return 0;

    int score = 0;

    // Length contribution: up to 40 points.
    int length = static_cast<int>(password.size());
    score += std::min(40, length * 4);

    // Character variety: up to 40 points.
    bool lower = hasLower(password);
    bool upper = hasUpper(password);
    bool digit = hasDigit(password);
    bool symbol = hasSymbol(password);

    int varietyCount = 0;
    if (lower) varietyCount++;
    if (upper) varietyCount++;
    if (digit) varietyCount++;
    if (symbol) varietyCount++;

    score += varietyCount * 10; // max +40

    // Penalties for simplicity.
    if (varietyCount <= 1) {
        score -= 15; // only one type of character
    }

    // Repeated pattern penalty.
    if (hasRepeatedSequences(password)) {
        score -= 10;
    }

    // Common password penalty.
    if (isCommonPassword(password)) {
        score -= 40;
    }

    // Clamp to [0, 100]
    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return score;
}

std::string PasswordAnalyzer::classifyScore(int score) const {
    if (score < 25) return "Very weak";
    if (score < 50) return "Weak";
    if (score < 70) return "Moderate";
    if (score < 85) return "Strong";
    return "Very strong";
}

// ---------- Feedback & Suggestions ----------

std::string PasswordAnalyzer::getFeedback(const std::string& password) const {
    std::string feedback;

    if (password.empty()) {
        return "Your password is empty. You should definitely set a password!";
    }

    int length = static_cast<int>(password.size());
    bool lower = hasLower(password);
    bool upper = hasUpper(password);
    bool digit = hasDigit(password);
    bool symbol = hasSymbol(password);

    if (length < 12) {
        feedback += "- Consider using at least 12 characters for better security.\n";
    } else {
        feedback += "- Good length! Longer passwords are harder to crack.\n";
    }

    if (!lower || !upper) {
        feedback += "- Mix UPPERCASE and lowercase letters to increase complexity.\n";
    }

    if (!digit) {
        feedback += "- Add some digits (0–9) to strengthen your password.\n";
    }

    if (!symbol) {
        feedback += "- Consider adding symbols (e.g. !, @, #, $, %) to make it harder to guess.\n";
    }

    if (hasRepeatedSequences(password)) {
        feedback += "- Try to avoid repeated patterns like 'abab' or '123123'.\n";
    }

    if (isCommonPassword(password)) {
        feedback += "- This password appears in a common password list. You should NOT use it.\n";
    }

    if (feedback.empty()) {
        feedback = "Nice! Your password already follows most best practices.";
    }

    return feedback;
}

// ---------- Password Generation ----------

std::string PasswordAnalyzer::generatePassword(int length, bool allowSymbols) const {
    if (length <= 0) {
        throw std::invalid_argument("Password length must be positive.");
    }

    const std::string lower = "abcdefghijklmnopqrstuvwxyz";
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()-_=+[]{};:,.<>?/";

    std::string charset = lower + upper + digits;
    if (allowSymbols) {
        charset += symbols;
    }

    // Use a random device to seed a Mersenne Twister engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(charset.size()) - 1);

    std::string result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        result.push_back(charset[dist(gen)]);
    }

    return result;
}