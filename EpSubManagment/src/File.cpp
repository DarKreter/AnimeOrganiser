#include "File.hpp"
#include "Entertainment.hpp"
#include "FilesManagment.hpp"
#include "StringManagment.hpp"
#include <algorithm>

using namespace std;
using file::File;
using namespace ent;

Format_t errorColor = Format_t(Format_t::Color(Format_t::Color::rgb, {255, 0, 0})),
         SIColor = Format_t(Format_t::Color(Format_t::Color::rgb, {0, 255, 255})),
         userColor = Format_t(Format_t::Color(Format_t::Color::rgb, {128, 255, 0})),
         userMenuColor = Format_t(Format_t::Color(Format_t::Color::rgb, {128, 255, 0}),
                                  Format_t::Mode::fastBlinking | Format_t::Mode::underline),
         dataColor = Format_t(Format_t::Color(Format_t::Color::rgb, {0, 0, 255})),
         successColor = Format_t(Format_t::Color(Format_t::Color::rgb, {128, 255, 0}));

namespace file {
string File::animeName = "";
string File::animeDirectory = "";
int File::seasonNumber = 0;
int File::maxEpisodeNumber = 0;

std::string File::GetFileExtension() { return originalName.substr(originalName.find_last_of('.')); }

std::string File::NewNameWithoutExt()
{
    ostringstream s;
    s << animeName << " - s" << std::setw(2) << setfill('0') << seasonNumber << "e" << setw(2)
      << setfill('0') << episodeNumber;
    return s.str();
}

std::string File::NewName()
{
    ostringstream s;
    s << animeName << " - s" << std::setw(2) << setfill('0') << seasonNumber << "e" << setw(2)
      << setfill('0') << episodeNumber << GetFileExtension();
    return s.str();
}

std::string File::NewNameWithPath() { return fm::GetExecutablePath() + NewName(); }

void File::Configure(std::string aN, std::string aD, int sN)
{
    animeName = aN;
    animeDirectory = aD;
    seasonNumber = sN;
}

void File::FindEpNumber(int offset)
{
    try {
        string::size_type begPos = 0;
        string::size_type endPos = 0;

        for(int i = 0; i <= offset; i++) {
            // cout << i << "\t";
            begPos = originalName.find_first_of("1234567890", endPos);
            // cout << begPos << "\t";
            endPos = originalName.find_first_not_of("1234567890", begPos);
            // cout << endPos << "\n";
        }

        auto temp = stoi(originalName.substr(begPos, endPos - begPos));

        // tutaj mozesz se zmienic numerek jakbys chcial
        temp += EPISODE_DELAY;

        // cout << originalName.substr(begPos, endPos - begPos) << "\n";
        episodeNumber = temp;
        maxEpisodeNumber = max(episodeNumber, maxEpisodeNumber);
    }
    catch(...) {
        episodeNumber = -1;
    }
}

string File::GetAnimeName(string path)
{
    string name;
    cout << errorColor;

    try {
        path.erase(path.length() - 1, 1);
        path = path.substr(path.find_last_of('/') + 1, string::npos);
        string::size_type beg = path.find('[');
        string::size_type end = path.find(']');

        if(beg != string::npos && end != string::npos)
            path.erase(beg, end + 1);

        vector<string> maybeErase = {" - HQ", " -HQ", " - LQ", " -LQ"};

        for(auto& mE : maybeErase) {
            auto find = std::search(begin(path), std::end(path), begin(mE), std::end(mE));
            if(find != std::end(path))
                path.erase(find, std::end(path));
        }

        path = sm::RemoveDoubleWS(sm::RemoveWSBeginEnd(path));

        string animeName;
        cout << SIColor << "Suggesting name of anime:" << endl
             << "\t\'" << path << "\'" << endl
             << "If the name is correct press ENTER, if not write your \"better\" name: "
             << userColor;
        getline(cin, animeName);

        if(animeName.empty())
            return path;
        else
            return animeName;
    }
    catch(...) {
        string animeName;

        cout << SIColor << "Enter the name of Anime to transmutation: " << userColor;
        getline(cin, animeName);

        return animeName;
    }
}

int File::GetSeasonNumber(string path)
{
    int sN;
    cout << errorColor; // cout << endl;

    try {
        path.erase(path.length() - 1, 1);
        path = path.substr(path.find_last_of('\\') + 1, string::npos);
        string::size_type beg = path.find('[');
        string::size_type end = path.find(']');

        if(beg == string::npos)
            throw Error_t{"Could not find ["};

        if(end == string::npos)
            throw Error_t{"Could not find ]"};

        sN = std::stoi(path.substr(beg + 1, end));

        return sN;
    }
    catch(std::invalid_argument& e) {
        cout << "Extracting the number of season ended with error." << endl;
        cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
             << "\tCatched exception: invalid_Argument." << endl
             << "\texception.what \"" << e.what() << "\"" << endl
             << endl;
    }
    catch(std::out_of_range& e) {
        cout << "Extracting the number of season ended with error." << endl;
        cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
             << "\tCatched exception: out_of_range." << endl
             << "\texception.what \"" << e.what() << "\"" << endl
             << endl;
    }
    catch(file::Error_t& e) {
        cout << "Extracting the number of season ended with error." << endl;
        cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
             << "\tCatched exception: file::Error_t." << endl
             << "\texception.what \"" << e.what << "\"" << endl
             << endl;
    }
    catch(...) {
        cout << "Extracting the number of season ended with error." << endl;
        cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
             << "\tCatched unknown exception." << endl
             << endl;
    }

    cout << SIColor;
    cout << endl;

    cout << "Please check if the number of season is in square brackets \"[]\"" << endl;
    cout << "You can also enter this data manually: ";
    string line;

back:
    cout << userColor;
    getline(cin, line);

    try {
        sN = stoi(line);
    }
    catch(...) {
        cout << errorColor << "Error! Please enter the CORRECT number of season: ";
        goto back;
    }

    return sN;
}

} // namespace file