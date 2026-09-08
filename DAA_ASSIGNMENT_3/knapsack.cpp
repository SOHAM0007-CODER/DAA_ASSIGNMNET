#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Item {
    int id;
    double weight;
    double profit;
    double ratio;
    double fraction;
    double weightTaken;
    double profitTaken;
};


bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {

    int n;
    double capacity;


    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    Item items[n];

    cout << "Enter weight and profit of each item: "<<endl;

    for (int i = 0; i < n; i++) {

        items[i].id = i + 1;

        cout << "Item " << i + 1 << ":\n";

        cout << "  Weight: ";
        cin >> items[i].weight;

        cout << "  Profit: ";
        cin >> items[i].profit;

        items[i].ratio =
            items[i].profit / items[i].weight;

        items[i].fraction = 0;
        items[i].weightTaken = 0;
        items[i].profitTaken = 0;

        cout << endl;
    }

  
    sort(items, items + n, compare);

   cout<<"Item sorted by Weight/Profit Ratio"<<endl;

    cout << left
         << setw(8) << "Item"
         << setw(12) << "Weight"
         << setw(12) << "Profit"
         << setw(15) << "P/W Ratio"
         << endl;

    cout << "---------------------------------------------------\n";

    for (int i = 0; i < n; i++) {

        cout << left
             << setw(8) << items[i].id
             << setw(12) << fixed << setprecision(2)
             << items[i].weight
             << setw(12)
             << items[i].profit
             << setw(15)
             << items[i].ratio
             << endl;
    }

  
    double remainingCapacity = capacity;
    double totalProfit = 0;


    for (int i = 0; i < n; i++) {

        if (remainingCapacity <= 0)
            break;

       
        if (items[i].weight <= remainingCapacity) {

            items[i].fraction = 1.0;

            items[i].weightTaken = items[i].weight;

            items[i].profitTaken = items[i].profit;

            remainingCapacity -= items[i].weight;

            totalProfit += items[i].profit;

            
        }

       
        else {

            items[i].fraction =
                remainingCapacity / items[i].weight;

            items[i].weightTaken =
                remainingCapacity;

            items[i].profitTaken =
                items[i].profit * items[i].fraction;

            totalProfit += items[i].profitTaken;

            

            remainingCapacity = 0;

          
        }
    }

    
    cout << "-----------------------------------------------------\n";

    cout << left
         << setw(8) << "Item"
         << setw(12) << "Fraction"
         << setw(15) << "Weight Taken"
         << setw(15) << "Profit Taken"
         << endl;

    cout << "-----------------------------------------------------\n";

    for (int i = 0; i < n; i++) {

        if (items[i].fraction > 0) {

            cout << left
                 << setw(8) << items[i].id
                 << setw(12) << fixed << setprecision(2)
                 << items[i].fraction
                 << setw(15)
                 << items[i].weightTaken
                 << setw(15)
                 << items[i].profitTaken
                 << endl;
        }
    }

    cout << "\n---------------------------------------------\n";

    cout << "Knapsack Capacity : "
         << capacity << endl;

    cout << "Total Weight Used : "
         << capacity - remainingCapacity << endl;

    cout << "Remaining Capacity: "
         << remainingCapacity << endl;

    cout << "Maximum Profit    : "
         << fixed << setprecision(2)
         << totalProfit << endl;

    cout << "---------------------------------------------\n";

    return 0;
}