# DAA Assignment 2: Quick Sort on Movies Data

## Description
This assignment demonstrates the use of the **Quick Sort** algorithm in C++ to sort a dataset of movies loaded from a CSV file (`movies.csv`). The data contains the movie's title, rating, release year, and popularity. The application is interactive, allowing the user to select which criterion (rating, year, or popularity) they wish to sort by.

The sorting is facilitated by custom comparators passed as function pointers to the `quickSort` function.

## Features
- **Customizable Sorting:** Sort movies by Rating, Release Year, or Popularity based on user input.
- **Quick Sort Algorithm:** Employs a custom Quick Sort implementation utilizing function pointers for modular comparison logic.
- **Performance Measurement:** Uses the `chrono` library to measure the exact time taken by the sorting algorithm in seconds.
- **File Parsing:** Reads and parses movie data robustly from a CSV format.

## How to Run
1. Ensure you have the `movies.csv` file in the same directory.
2. Compile the source file:
   ```bash
   g++ DAA_ASSIGNMNET_2.cpp -o Assignment2
   ```
3. Run the program:
   ```bash
   ./Assignment2
   ```
4. Enter your sorting preference when prompted (`rating`, `year`, or `popularity`).

## Input file
`input.txt` contains `rating`, the sorting choice identified by the saved
output. `movies.csv` reconstructs the 50 movie records visible in that output;
it is a sample, not the unavailable original full dataset. Keep the CSV beside
the program and run from this folder.

The saved Output.txt comes from a different program version: it shows an
ascending table of 50 movies, whereas the current C++ code prints the top
10 in descending order. The source and saved output are preserved unchanged;
these input files cannot make the current program reproduce that old format.
