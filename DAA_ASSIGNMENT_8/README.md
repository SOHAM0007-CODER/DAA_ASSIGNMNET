# DAA Assignment 8: SwiftShip LC Branch and Bound TSP

## Description
Find a minimum **fuel-cost Hamiltonian tour** that visits every city exactly
once, returns to the starting city, and meets a total travel-time limit.
The program implements **Least-Cost Branch and Bound**, using a min-priority
queue of partial routes ordered by admissible cost bounds.

The C++ source is separate from the PDF report. The objective is fuel cost;
distance and time are reported, with time treated as a hard constraint.
This is not simultaneous minimization of cost, distance and time.

## Features
- Exact LC Branch and Bound, with no heuristic early-stop rule.
- Directed roads with varying distances, fuel-consumption rates and times.
- Lower bounds from outgoing and incoming edge minima.
- Separate time lower bound to prune deadline-infeasible routes.
- Two greedy seed tours provide upper bounds only; they are not the solver.
- Exact integer milli-INR costs avoid floating-point pruning errors.
- Complete route, fuel cost, distance, litres, duration and search statistics.
- Clear no-feasible-tour output when no route meets all requirements.

## Files
- `SwiftShipTSP.cpp`: C++ source.
- `DAA_Assignment_No_8_Soham_Kulkarni.pdf`: report without C++ source.
- `Demo_Guide.md`: exact input and output explanations.
- `input.txt`, `Output.txt`: 90-minute sample and captured output.


## Compile and Run
From this folder in Windows PowerShell:

```powershell
g++ -std=c++11 SwiftShipTSP.cpp -o SwiftShipTSP.exe
.\SwiftShipTSP.exe
```

For file-based input:

```powershell
Get-Content input.txt | .\SwiftShipTSP.exe
```

Linux/WSL:

```sh
g++ -std=c++11 SwiftShipTSP.cpp -o SwiftShipTSP
./SwiftShipTSP
```

## Input Order
1. Number of cities, 2-25. City IDs start at 1.
2. Positive whole-number fuel price, in INR per litre.
3. Number of directed roads.
4. Each road: `from to distanceKm fuelMlPerKm travelMinutes`.
5. Starting city and total travel-time limit in minutes.

Example: `1 2 10 100 30` means city 1 to city 2, distance 10 km,
consumption 100 mL/km, and duration 30 minutes. It consumes 1000 mL
(1 litre), costing 100 INR at a fuel price of 100 INR/litre.

Roads are directed: enter both directions for an undirected connection.
Omit a road to represent an unavailable connection. Self-loops and duplicate
ordered city pairs are rejected. Rates can differ across roads to model
conditions. All weights are static during a solve; edit and rerun for a
different road-condition snapshot. No live traffic feed is connected.

All inputs are integers. Limits: distance 1-1000000 km, rate 1-10000 mL/km,
road time 1-1000000 minutes, fuel price 1-100000 INR/litre, total time limit
0-25000000 minutes. These bounds keep sums inside 64-bit integers.
Invalid input terminates with an error.

## Expected Demo Results
| Time limit | Minimum fuel cost | Route | Travel time |
| --- | --- | --- | --- |
| 90 minutes | 550 INR | 1 -> 3 -> 2 -> 4 -> 1 | 75 minutes |
| 130 minutes | 400 INR | 1 -> 2 -> 3 -> 4 -> 1 | 120 minutes |
| 70 minutes | No feasible tour | â€” | â€” |

Every complete result includes the return trip. Equal-cost tours may return
any optimum; there is no secondary distance/time tie objective.

## Exactness and Performance
For a partial route, every remaining completion needs one outgoing edge
from its last city and each unvisited city, and one incoming edge into
each unvisited city and the start. The larger of the outgoing-minimum sum
and incoming-minimum sum is a valid remaining-cost lower bound. Add the
already incurred cost. Do not add the two minimum sums to each other.
The same calculation on time weights gives a separate admissible time bound.

Prune a node when it cannot beat the best feasible cost, cannot meet the
deadline, or lacks a necessary remaining edge. The priority queue expands
the least cost-bound node first. When no live node can improve the feasible
incumbent, its optimality is proven. If no feasible incumbent exists when
search ends, no feasible tour exists for the input.

Bounding takes O(N squared) per generated partial route. If G prefixes are
generated and Q is the maximum live frontier, search costs roughly
O(G*(N squared + log(Q+1))). G can be factorial; memory is O(N squared + Q*N).
There is no polynomial-time guarantee or promise that arbitrary 20+ city
instances finish quickly. A separate 22-city test was deliberately structured so
the initial feasible tour matches the root lower bound; zero expanded nodes
is a valid proof for that case, not a general runtime claim.

Only road travel time is modeled. Service times, individual delivery windows,
driver breaks, payload-dependent fuel use and vehicle routing across several
trucks would need additional constraints. All demo data are illustrative.
