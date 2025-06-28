#ifndef PRODUCETRACKER_H
#define PRODUCETRACKER_H

#include <map>
#include <string>

class ProduceTracker {
private:
    std::map<std::string, int> originalFrequencyMap;
    std::map<std::string, std::string> normalizedToOriginalMap;

    void loadData(const std::string& filename);
    void saveBackup(const std::string& filename);
    std::string normalizeWord(const std::string& word) const;

public:
    ProduceTracker(const std::string& filename);

    bool findFrequency(const std::string& item) const;
    void displayAllFrequencies() const;
    void displayHistogram() const;
};

#endif // PRODUCETRACKER_H

