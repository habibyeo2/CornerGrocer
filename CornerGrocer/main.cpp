#include "GroceryTracker.h"

#include <iostream>
#include <sstream>
#include <string>

//read a single menu number. Other text is rejected instead of crashing.
int readMenuChoice(const std::string& input) {
    std::istringstream inputStream(input);
    int choice = 0;
    std::string extraText;

    if (!(inputStream >> choice) || (inputStream >> extraText)) {
        return 0;
    }
    return choice;
}

int main() {
    const std::string inputFileName = "CS210_Project_Three_Input_File.txt";
    const std::string backupFileName = "frequency.dat";
    GroceryTracker groceryTracker;

    //read the purchases and create the backup before the menu is shown.
    if (!groceryTracker.loadItems(inputFileName)) {
        std::cerr << "Error: Could not read " << inputFileName << ".\n"
                  << "Put the file in the program's working folder.\n";
        return 1;
    }
    if (!groceryTracker.saveFrequencyData(backupFileName)) {
        std::cerr << "Error: Could not create " << backupFileName << ".\n";
        return 1;
    }

    std::cout << "Corner Grocer Item Tracker\n"
              << "Backup created: " << backupFileName << "\n";

    std::string input;
    while (true) {
        std::cout << "\n1. Find the frequency of an item\n"
                  << "2. Display all item frequencies\n"
                  << "3. Display a histogram\n"
                  << "4. Exit\n"
                  << "Choose an option (1-4): ";

        if (!std::getline(std::cin, input)) {
            std::cout << "\nInput ended. Closing program.\n";
            break;
        }

        const int choice = readMenuChoice(input);
        if (choice == 1) {
            std::string itemName;
            std::cout << "Enter an item name: ";
            if (!std::getline(std::cin, itemName)) {
                std::cout << "\nInput ended. Closing program.\n";
                break;
            }
            std::cout << itemName << " was purchased "
                      << groceryTracker.getItemFrequency(itemName)
                      << " time(s).\n";
        }
        else if (choice == 2) {
            groceryTracker.printAllFrequencies();
        }
        else if (choice == 3) {
            groceryTracker.printHistogram();
        }
        else if (choice == 4) {
            std::cout << "Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid option. Please enter 1, 2, 3, or 4.\n";
        }
    }

    return 0;
}
