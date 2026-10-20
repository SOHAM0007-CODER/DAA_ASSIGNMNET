# DAA Assignment 6: Simple 0/1 Knapsack

Choose whole relief packages that maximize total utility without exceeding
one truck's capacity. For each item, dynamic programming compares taking it
once with leaving it. The program prints the selected items and maximum utility.

## Files
- `ReliefKnapsack.cpp`: simplified C++ source.
- `input.txt`: sample values.
- `Output.txt`: captured result.
- `DAA_Assignment_No_6_Soham_Kulkarni.pdf`: report, without C++ code.
- `Greedy_Counterexample_Input.txt`: optional example where ratio greedy fails.

## Compile and Run

```powershell
g++ -std=c++11 ReliefKnapsack.cpp -o ReliefKnapsack.exe
.\ReliefKnapsack.exe
```

## Sample Input

```text
3 5
Medicine 2 30
Food 3 40
Blankets 4 50
```

`3 5` means three items and a 5 kg truck. Each row is `name weight utility`.
Medicine and Food weigh 5 kg and give maximum utility **70**. Names are single
words. Utility is an importance score, not a currency value.

## How It Works
`dp[i][w]` stores the best utility using the first i items and capacity w.
Compare leaving item i with its utility plus the best value for the remaining
capacity using earlier items. Trace the table backwards to recover the selection.
Each item is indivisible and used at most once. Ties keep the previous choice.

Time and space: O(N(W+1)), commonly O(NW) for positive W. The full table is
pseudo-polynomial in numeric capacity and keeps reconstruction simple.
Limits: 1-200 items, capacity 0-10000 kg, positive whole-number weights and
nonnegative integer utilities up to 1000000000. Invalid input terminates.

The PDF compares brute force, DP and greedy and discusses priority, changing
supplies and multiple trucks. This uploaded simple program handles the core
single-truck problem. Larger importance scores can encourage critical items
but do not force them to be selected. These example scores are illustrative.
