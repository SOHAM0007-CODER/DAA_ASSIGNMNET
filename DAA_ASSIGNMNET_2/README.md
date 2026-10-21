# DAA Assignment 2: Quick Sort - all movie ratings

Reads all 4,803 TMDB movies and prints every record by the selected numeric key, descending. The sample chooses rating. Decimal popularity and quoted titles containing commas are supported. Output includes comparisons, swaps, extrema and sorting-only time.

## Compile and run (PowerShell)

```powershell
g++ -std=c++11 "DAA_ASSIGNMNET_2.cpp" -o Assignment2.exe
.\Assignment2.exe
```

Use the saved input:

```powershell
Get-Content input.txt | .\Assignment2.exe
```

## Input

CSV columns: title,rating,release_year,popularity. Keyboard choice: rating, year or popularity. Rating is vote_average (0-10); year 0 means missing release date.

## Output

`Output.txt` is the actual captured output of the current program and saved input. The PDF includes theory, pseudocode, input details and the full output; C++ source stays separate. Sorting runtimes vary by machine and run.

## Complexity

Average O(N log N), worst O(N^2); O(log N) stack by recursing on the smaller partition and looping over the larger.

## Viva notes and scope

Quick Sort is not stable. Equal ratings may appear in any order. This is attribute-based ranking, not personalized recommendation. Zero-rated records remain in the dataset.

See [DATASET_SOURCE.md](DATASET_SOURCE.md) for the Kaggle source, exact preparation and archive checksum. Every CSV record is displayed; there is no top-ten cutoff.
