#ifndef FILE_H
#define FILE_H

#include "Entertainment.h"
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
private:
    static std::wstring animeName;
    static std::wstring animeDirectory;
    static int seasonNumber;
    static int maxEpisodeNumber;
    std::wstring originalName;
    std::wstring originalNameWithPath;

public:
    int episodeNumber = 0;

    std::wstring GetFileExtension();
    std::wstring NewName();
    std::wstring NewNameWithoutExt();
    std::wstring NewNameWithPath();
    static int GetSeasonNumber(std::wstring path);
    static std::wstring GetAnimeName(std::wstring path);
    static void Configure(std::wstring aN, std::wstring aD, int sN);
    static std::wstring GetDirectory() { return animeDirectory; }
    int EpisodeNumber() { return episodeNumber; }
    std::wstring OriginalName() { return originalName; }
    std::wstring OriginalNameWithPath() { return originalNameWithPath; }
    static int MaxEpisodeNumber() { return maxEpisodeNumber; }

    bool operator==(const File& f2) const { return this->originalName == f2.originalName; }
    void FindEpNumber(int offset);

    File(std::wstring n) : originalNameWithPath{n}, originalName{n.substr(n.find_last_of('\\') + 1)}
    {
    }
};
} // namespace file

#endif // !FILE_H