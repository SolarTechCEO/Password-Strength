# Password Strength Analyzer 🔐
A C++ command-line security tool that evaluates password strength, detects weak or commonly used passwords, and generates strong alternatives. Built as an enhanced portfolio project demonstrating real-world cybersecurity concepts, object-oriented programming, file processing, and algorithmic analysis.

## 📘 Overview
Modern systems rely heavily on password security, yet weak or compromised passwords remain one of the most common causes of data breaches.
This project provides a **local, offline password strength analyzer** that evaluates password security using multiple heuristics including:
- Length  
- Character diversity  
- Repetitive patterns  
- Dictionary-based weak password detection  

The analyzer outputs a **numeric score (0–100)**, a **strength classification**, and **human-readable feedback**.

It also includes a **strong password generator**, allowing users to instantly create secure passwords.

## ✨ Features
### 🔍 Password Analysis
- Strength scoring (0–100)
- Classification (Very Weak → Very Strong)
- Pattern detection (repetition, low diversity)
- Common-password dictionary checking

### 🧠 Intelligent Feedback
Provides suggestions on:
- Improving length  
- Adding digits/symbols  
- Removing repetitive structures  
- Avoiding known weak passwords  

### 🔑 Password Generator
- Custom length  
- Optional symbols  
- Cryptographically strong randomness (Mersenne Twister)

### 🗂 Dictionary Support
Loads `common_passwords.txt` for offline weak-password detection.

## 🏗 Project Structure
```
├── include/
│   ├── PasswordAnalyzer.h
├── src/
│   ├── PasswordAnalyzer.cpp
│   ├── main.cpp
├── common_passwords.txt
├── Makefile
├── README.md
```

## 🔧 Installation & Compilation

### Requirements
- A C++11 (or newer) compatible compiler  
- `make` installed (macOS/Linux by default; MSYS2/MinGW on Windows)

### Build (Linux/macOS/Windows)
```
make
```

### Clean the build
```
make clean
```

### Run the program
```
make run
```

Or manually:
```
./PasswordAnalyzer
```
(Windows: `PasswordAnalyzer.exe`)

## ▶️ Usage Example

```
=========================================
   Password Strength Analyzer
=========================================
1) Analyze a password
2) Generate a strong password
3) Quit
Choose an option:
```

Example analysis:
```
Score: 82/100
Rating: Strong
Feedback:
- Good length! Longer passwords are harder to crack.
```

Generated password:
```
Fg9@hZ7m!vLp3&Ds
```

## 🧩 What Was Created/Improved
This project was designed from scratch as a portfolio-quality cybersecurity tool demonstrating:
- Object-oriented design
- Real security heuristics
- Pattern detection
- Dictionary-based password checks
- File I/O handling
- Strong random password generation
- Modular architecture using separate headers/source files
- Professional Makefile-based build system

## 🚀 Planned Enhancements
- Entropy calculation  
- GUI front-end (Qt/ImGui)  
- Breach dataset importer  
- Policy templates (NIST, PCI-DSS)

## 📝 License
This project is licensed under the MIT License.  
You are free to use, modify, and distribute this software with proper attribution.
See the accompanying LICENSE file for full details.

## ❤️ Author
Nick C. (SolarTechCEO)
Lead Developer
