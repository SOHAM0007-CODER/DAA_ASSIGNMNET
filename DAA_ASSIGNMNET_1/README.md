# DAA Assignment 1: Merge Sort on IPL 2025 Batters Data

## Description
This assignment involves implementing the **Merge Sort** algorithm in C++ to sort a dataset of IPL 2025 batters. The data is read from a CSV file (`IPL2025Batters.csv`), which contains the player's name, their team, and the number of runs scored. The program parses the file, populates a list of `Player` structures, and sorts them in descending order based on the runs scored. 

Finally, it displays the top 10 players and computes the execution time of the merge sort algorithm.

## Features
- **File I/O:** Parses data from a comma-separated values (CSV) file.
- **Merge Sort Algorithm:** Efficiently sorts the players with a time complexity of `O(N log N)`.
- **Execution Timing:** Measures the time taken to sort the dataset using `std::chrono`.
- **Data Structures:** Utilizes `std::vector` and custom `struct Player`.

## How to Run
1. Ensure the `IPL2025Batters.csv` file is present in the same directory.
2. Compile the code using a C++ compiler:
   ```bash
   g++ DAA_Assignment_1.cpp -o Assignment1
   ```
3. Run the executable:
   ```bash
   ./Assignment1
   ```
