# DAA Assignment 3: Fractional Knapsack Problem

## Description
This assignment implements a solution to the **Fractional Knapsack Problem** using a **Greedy Approach** in C++. Given a set of items, each with a specific weight and profit, the goal is to determine the maximum profit that can be obtained by selecting items such that their total weight does not exceed the knapsack's capacity. 

In the fractional variant, items can be broken down into smaller fractions if the remaining capacity cannot accommodate the whole item.

## Features
- **Greedy Strategy:** Sorts items based on their Profit-to-Weight ratio in descending order.
- **Tabular Display:** Beautifully formats the item details (Profit, Weight, P/W Ratio) and the selection process using `std::setw` and `std::setprecision`.
- **Dynamic Calculation:** Accurately calculates the exact fraction of the item taken and its corresponding profit contribution.

## How to Run
1. Compile the C++ program:
   ```bash
   g++ knapsack.cpp -o knapsack
   ```
2. Run the executable:
   ```bash
   ./knapsack
   ```
3. Enter the number of items and the knapsack capacity.
4. Input the weight and profit for each item as prompted.
