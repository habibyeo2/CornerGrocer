#include "GroceryTracker.h"

#include <cctype>
#include <fstream>
#include <iostream>

std::string GroceryTracker::normalizeItem(const std::string& itemName) {
    std::string normalized = itemName;
    for (char& letter : normalized) {
        letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
    }
    return normalized;
}

std::string GroceryTracker::displayItem(const std::string& itemName) {
    std::string displayName = itemName;
    if (!displayName.empty()) {
        displayName[0] = static_cast<char>(
            std::toupper(static_cast<unsigned char>(displayName[0])));
    }
    return displayName;
}

bool GroceryTracker::loadItems(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        return false;
    }

    itemCounts.clear();
    std::string item;

    //the input file lists one purchased item (one word) per record.
    while (inputFile >> item) {
        ++itemCounts[normalizeItem(item)];
    }

    return !inputFile.bad();
}

bool GroceryTracker::saveFrequencyData(const std::string& fileName) const {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        return false;
    }

    //each line of frequency.dat contains an item and its count.
    for (const auto& entry : itemCounts) {
        outputFile << displayItem(entry.first) << " " << entry.second << '\n';
    }

    outputFile.close();
    return outputFile.good();
}

int GroceryTracker::getItemFrequency(const std::string& itemName) const {
    const auto result = itemCounts.find(normalizeItem(itemName));
    if (result == itemCounts.end()) {
        return 0;
    }
    return result->second;
}

void GroceryTracker::printAllFrequencies() const {
    std::cout << "\nItem Purchase Frequencies\n";
    for (const auto& entry : itemCounts) {
        std::cout << displayItem(entry.first) << " " << entry.second << '\n';
    }
}

void GroceryTracker::printHistogram() const {
    std::cout << "\nItem Purchase Histogram\n";
    for (const auto& entry : itemCounts) {
        //one asterisk represents one purchase of the item.
        std::cout << displayItem(entry.first) << " "
                  << std::string(entry.second, '*') << '\n';
    }
}
