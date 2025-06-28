#include "ProduceTracker.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

ProduceTracker::ProduceTracker(const string& filename) {
    loadData(filename);
    saveBackup("frequency.dat");
}

void ProduceTracker::loadData(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string item;
    while (inputFile >> item) {
        originalFrequencyMap[item]++;
        string normalized = normalizeWord(item);

        if (normalizedToOriginalMap.find(normalized) == normalizedToOriginalMap.end()) {
            normalizedToOriginalMap[normalized] = item;
        } else {
            string current = normalizedToOriginalMap[normalized];
            if (originalFrequencyMap[item] > originalFrequencyMap[current]) {
                normalizedToOriginalMap[normalized] = item;
            }
        }
    }

    inputFile.close();
}

void ProduceTracker::saveBackup(const string& filename) {
    ofstream outFile(filename);
    for (const auto& pair : originalFrequencyMap) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();
}

string ProduceTracker::normalizeWord(const string& word) const {
    string result;
    for (char c : word) {
        result += static_cast<char>(tolower(c));
    }

    size_t len = result.length();
    if (len > 3) {
        if (result.substr(len - 3) == "ies") {
            result = result.substr(0, len - 3) + "y";
        } else if (result.substr(len - 3) == "oes") {
            result = result.substr(0, len - 2);
        } else if (result.substr(len - 4) == "ches" ||
                   result.substr(len - 4) == "shes" ||
                   result.substr(len - 3) == "xes") {
            result = result.substr(0, len - 2);
        } else if (result[len - 1] == 's') {
            result = result.substr(0, len - 1);
        }
    }

    return result;
}

bool ProduceTracker::findFrequency(const string& item) const {
    string normalized = normalizeWord(item);
    auto it = normalizedToOriginalMap.find(normalized);
    if (it != normalizedToOriginalMap.end()) {
        string original = it->second;
        int count = originalFrequencyMap.at(original);
        cout << original << " was purchased " << count << " time(s)." << endl;
        return true;
    }
    return false;
}

void ProduceTracker::displayAllFrequencies() const {
    cout << "\nItem Purchase Frequency:\n";
    for (const auto& pair : originalFrequencyMap) {
        cout << setw(15) << left << pair.first << pair.second << endl;
    }
}

void ProduceTracker::displayHistogram() const {
    cout << "\nItem Frequency Histogram:\n";
    const string colors[] = {
        "\033[31m",       // Red
        "\033[38;5;208m", // Orange
        "\033[33m",       // Yellow
        "\033[32m",       // Green
        "\033[34m",       // Blue
        "\033[38;5;54m",  // Indigo
        "\033[35m"        // Violet
    };
    const string reset = "\033[0m";

    int colorIndex = 0;
    for (const auto& pair : originalFrequencyMap) {
        cout << setw(15) << left << pair.first;
        cout << colors[colorIndex % 7];
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << reset << endl;
        ++colorIndex;
    }
}
