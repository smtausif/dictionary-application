# 📖 Dictionary Application (C++ Project)

A C++17 command-line application that loads dictionary data from CSV files, searches for words, and displays definitions with multiple senses and parts of speech.  
This project demonstrates **Object-Oriented Programming principles**, including the **Rule of 5** (copy/move constructors, copy/move assignment, destructor), and includes performance benchmarking.

---

## 🚀 Features
- Load dictionary data from large/small CSV files.  
- Search words and display multiple definitions.  
- Handle "word not found" gracefully.  
- Implements **Rule of 5** for safe dynamic memory management.  
- Performance timing (nanoseconds, microseconds, milliseconds).  
- Modular structure (`settings`, `event`, `logger`, `timeMonitor`, `dictionary`).  

---

## 📂 Usage
Compile:
```bash
g++ -Wall -std=c++17 -g -o asgn tester_1.cpp settings.cpp event.cpp logger.cpp timeMonitor.cpp dictionary.cpp
