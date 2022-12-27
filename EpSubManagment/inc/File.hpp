#ifndef FILE_H
#define FILE_H

#include "Entertainment.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define EPISODE_DELAY 0
extern ent::Color errorColor, SIColor, userColor, dataColor;

namespace file {
struct Error_t {
    std::string what;
    std::string What() { return what; }
};

class File {
public:
    static std::string animeName;
    static std::string animeDirectory;
    static int seasonNumber;
    static int maxEpisodeNumber;
    std::string originalName;
    std::string originalNameWithPath;

public:
    int episodeNumber = 0;

    std::string GetFileExtension();
    std::string NewName();
    std::string NewNameWithoutExt();
    std::string NewNameWithPath();
    static int GetSeasonNumber(std::string path);
    static std::string GetAnimeName(std::string path);
    static void Configure(std::string aN, std::string aD, int sN);
    static std::string GetDirectory() { return animeDirectory; }
    int EpisodeNumber() { return episodeNumber; }
    std::string OriginalName() { return originalName; }
    std::string OriginalNameWithPath() { return originalNameWithPath; }
    static int MaxEpisodeNumber() { return maxEpisodeNumber; }

    bool operator==(const File& f2) const { return this->originalName == f2.originalName; }
    bool operator<(const File& f2) const { return this->originalName < f2.originalName; }
    void FindEpNumber(int offset);

    File(std::string n) : originalNameWithPath{n}, originalName{n.substr(n.find_last_of('/') + 1)}
    {
    }
};
} // namespace file

#endif // !FILE_H