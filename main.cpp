#include "ProduceTracker.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\nCorner Grocer Menu\n";
    cout << "1. Look up item frequency\n";
    cout << "2. Print all frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ProduceTracker tracker("CS210_Project_Three_Input_File.txt");  // Change to your data file

    int choice;
    do {
        displayMenu();
        cin >> choice;

        // Input validation
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: {
            cout << "Enter item name: ";
            string item;
            cin >> item;
            if (!tracker.findFrequency(item)) {
                cout << item << " was not found.\n";
            }
            break;
        }
        case 2:
            tracker.displayAllFrequencies();
            break;
        case 3:
            tracker.displayHistogram();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
