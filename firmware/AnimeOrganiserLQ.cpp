#include "Entertainment.hpp"
#include "Episode.hpp"
#include "File.hpp"
#include "FilesManagment.hpp"
#include "Menu.hpp"
#include "StringManagment.hpp"

using namespace std;
using namespace ent;
using file::Episode;
using file::File;

// #define LOG_VERSION

// argv[1] - Path
// argv[2] - AnimeName
// argv[3] - Episode offset

int main(int argc, char* argv[])
{

#ifdef LOG_VERSION
    wofstream log("log.k8d");
    struct L {
        wofstream* l;
        L(wofstream* s) { l = s; }
        ~L() { l->close(); }
    } ll(&log);
#endif

    if(argc == 4) /// Jesli nastapilo wywolanie odgorne przekazujemy dane klasie
    {
        File::Configure(argv[2], argv[1], File::GetSeasonNumber(argv[2]));
        Episode::Offset(stoi(argv[3]));
    }
    else /// Jesli musimy te dane sami pobrac
    {
        string animeName;

        // cout << errorColor << "Number of passed arguments is invalid! [" << dataColor << argc
        //      << errorColor << "]" << endl
        cout << SIColor << "Initialization of manual input of data [ ]\b\b" << dataColor;
        ent::Fan(11, 120);
        cout << dataColor << "SUCCESS!" << SIColor << "]" << endl << endl;

        animeName = File::GetAnimeName(fm::GetExecutablePath());
        // Mamy juz od uzytkownika nazwe anime
        string temp;

        cout << SIColor << "Enter the offset for episodes: ";
    back1:
        cout << userColor;

        getline(cin, temp);
        try {
            Episode::Offset(stoi(temp));
        }
        catch(...) {
            cout << errorColor << "Error! Please enter the CORRECT offset for episodes: ";
            goto back1;
        }

        // Bierzemy z GetExecutablePath sciezke oraz GetSeasonNumber razem z wylapywaniem bledow
        // pobiera numer sezonu
        File::Configure(animeName, fm::GetExecutablePath(),
                        File::GetSeasonNumber(fm::GetExecutablePath()));
        cout << endl;
        // cout << Episode::animeName << endl;
        // cout << Episode::animeDirectory << endl;
        // cout << Episode::seasonNumber << endl;
        // cout << Episode::offset << endl;
        // cout << Subtitle::offset << endl;
    }

    vector<Episode> episodes;
    fm::ReadDirectory(File::GetDirectory(), episodes, Episode::Extensions(), false, true);

    if(episodes.empty()) {
        cout << errorColor << "No episodes!" << endl;
        cin.get();
        exit(0);
    }

    // cout << "UWAGA:" << endl;
    // for (auto& x : subtitles)
    //	cout << x.originalName << endl;
    // cout << "UWAGA:" << endl;

    for(auto& ep : episodes)
        ep.FindEpNumber();

    for(auto& ep : episodes)
        if(ep.episodeNumber == -1)
            ep.episodeNumber = File::MaxEpisodeNumber() + 1;

    // cout << "maxEpisodeNumber = " << File::maxEpisodeNumber << endl;
    // for (auto& sub : subtitles)
    //         cout << sub.episodeNumber << " - " << sub.originalName << endl;
    // cout << "-----------------------" << endl;
    // for (auto& ep : episodes)
    //         cout << ep.episodeNumber << " - " << ep.originalName << endl;
    // wszystkie episode i subtitle maj� ju� w episodeNumber odpowiedni numer
    // Teraz trzeba je polaczyc w dwuwyymiarowej tablicy ktora ma pierwszy rozmiar maxEpisodeNumber
    // + 1 I potem przelecenie wszyystkiego zmieniajac nazwe albo robiac okienka wyboru (no ogolnie
    // sporo przypadkow)

    vector<vector<Episode>> episodesSorted;
    for(int i = 0; i < File::MaxEpisodeNumber() + 2; i++) {
        vector<Episode> x;
        episodesSorted.push_back(x);
    }

    for(auto& ep : episodes)
        episodesSorted[ep.episodeNumber].push_back(std::move(ep));

    // cout << "maxEpisodeNumber = " << File::maxEpisodeNumber << endl;
    // for (unsigned int i = 0; i < episodesSorted.size(); i++)
    //{
    //	cout << "\t\t\t" << i << endl;
    //	for (auto& sub : subtitlesSorted[i])
    //		cout << sub.episodeNumber << " - " << sub.originalName << endl;
    //	for (auto& ep : episodesSorted[i])
    //		cout << ep.episodeNumber << " - " << ep.originalName << endl;
    //	cout << endl;
    // }

    menu::Menu_t* meni;

    for(unsigned int i = 0; i < episodesSorted.size() - 1; i++) {
        if(episodesSorted[i].size() == 1) // TODO
        {
            // cout << "Zmieniam nazwe dla anime i dla napisow! [" << i << "]" << endl;
            // cout << subtitlesSorted[i][0].originalNameWithPath << endl;
            // cout << subtitlesSorted[i][0].NewName() << endl;
            // cout << episodesSorted[i][0].originalNameWithPath << endl;
            // cout << episodesSorted[i][0].NewName() << endl;

#ifdef LOG_VERSION
            fm::RenameFileLog(episodesSorted[i][0].OriginalNameWithPath(),
                              episodesSorted[i][0].NewName(), log);
#else
            fm::RenameFile(episodesSorted[i][0].OriginalNameWithPath(),
                           episodesSorted[i][0].NewName());
            cout << "\t" << SIColor << episodesSorted[i][0].NewName() << " - " << successColor
                 << "DONE!" << endl
                 << errorColor;
#endif

            // Zmiana nazwy odcinka anime i napisow plus przeniesienie napisow do lokalizacji
            // odcinka
        }
        else if(episodesSorted[i].size() == 0) // DONE
        {
            // cout << "Nic nie robie bo nie ma ani napisow ani odcinka [" << i << "]" << endl;
            continue; // Jesli nie ma ani odcinka ani napisow do tego numeru
        }
        else if(episodesSorted[i].size() > 1) // TODO
        {
            vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;

            int choosen = -1;

            for(unsigned int j = 0; j < episodesSorted[i].size(); j++) {
                auto lambda = [&meni, j, &choosen]() {
                    choosen = j;
                    menu::ClearScreen();
                    meni->Die();
                };
                x.push_back({episodesSorted[i][j].OriginalName(), lambda});
            }

            x.push_back({"Nani?! All of them are wrong?! MASAKA!", [&meni]() {
                             menu::ClearScreen();
                             meni->Die();
                         }});

            meni = menu::Menu_t::CreateMenu(2, 1, 55,
                                            "Found too much episodes with number " + to_string(i) +
                                                "!\nPlease choose which one is correct!",
                                            x, DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                                            DEFAULT_IN_KEYBOARD_KEYS, {},
                                            {SIColor, userMenuColor, dataColor});

            cout << "OH NOO! IMPOSSIBLE! (⊙_☉)\nI haven't been able to resolve occured "
                    "problem by myself (˃̣̣̥⌓˂̣̣̥⋆)\n"
                 << Format_t(errorColor.GetFColor(),
                             Format_t::Mode::fastBlinking | errorColor.GetMode(),
                             errorColor.GetBColor())
                 << "Press enter to resolve issue..." << errorColor << endl;
            cin.get();

            meni->StartMenu();
            meni->DeleteMenu();

            cout << SIColor;

            if(choosen != -1) // Jesli cos zostalo wybrane
            {
#ifdef LOG_VERSION
                fm::RenameFileLog(episodesSorted[i][choosen].OriginalNameWithPath(),
                                  episodesSorted[i][choosen].NewName(), log);
#else
                fm::RenameFile(episodesSorted[i][choosen].OriginalNameWithPath(),
                               episodesSorted[i][choosen].NewName());
                cout << "\t" << SIColor << episodesSorted[i][choosen].NewName() << " - "
                     << successColor << "DONE!" << endl
                     << errorColor;
#endif
            }
        }
    }

    cout << successColor << endl
         << "SUCCESS" << endl
         << Format_t(successColor.GetFColor(),
                     Format_t::Mode::fastBlinking | successColor.GetMode(),
                     successColor.GetBColor())
         << "Press enter to continue..." << successColor << endl;
    cin.get();

    return 0;
}
