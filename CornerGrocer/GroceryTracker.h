#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
    //read purchased items from the text file and count each occurrence
    bool loadItems(const std::string& fileName);

    //write the counts to a backup file before displaying the menu
    bool saveFrequencyData(const std::string& fileName) const;

    //return how many times one item was purchased (zero if not found)
    int getItemFrequency(const std::string& itemName) const;

    //show either numbered counts or a text based histogram
    void printAllFrequencies() const;
    void printHistogram() const;

private:
    //map stores each distinct item and its purchase count
    std::map<std::string, int> itemCounts;

    //standardize spelling case so Apples and apples are counted together
    static std::string normalizeItem(const std::string& itemName);
    static std::string displayItem(const std::string& itemName);
};

#endif
