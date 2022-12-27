#include "Entertainment.h"
#include "Episode.h"
#include "File.h"
#include "FilesManagment.h"
#include "Menu.h"
#include "StringManagment.h"
#include "Subtitle.h"


using namespace std;
using ent::ChangeColor;
using file::Episode;
using file::File;
using file::Subtitle;

//#define LOG_VERSION
// Jesli chcesz przesunac numery wszystkich odcinkow to pojdz na sam szczyt File.h i tam masz define
// ktory to obsluguje

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

    if(argc == 5) /// Jesli nastapilo wywolanie odgorne przekazujemy dane klasie
    {
        File::Configure(sm::STWS(argv[1]), sm::STWS(argv[2]),
                        File::GetSeasonNumber(sm::STWS(argv[2])));
        Episode::Offset(stoi(argv[3]));
        Subtitle::Offset(stoi(argv[4]));
    }
    else /// Jesli musimy te dane sami pobrac
    {
        wstring animeName;

        ChangeColor(errorColor);
        cout << "Number of passed arguments is invalid! [";
        ChangeColor(dataColor);
        cout << argc;
        ChangeColor(errorColor);
        cout << "]" << endl;
        ChangeColor(SIColor);
        cout << "Initialization of manual input of data [ ]\b\b";
        ChangeColor(dataColor);
        ent::Fan(11, 120);
        ChangeColor(dataColor);
        cout << "SUCCESS!";
        ChangeColor(SIColor);
        cout << "]" << endl << endl;

        animeName = File::GetAnimeName(fm::GetExecutablePathW());
        // Mamy juz od uzytkownika nazwe anime
        string temp;
        ChangeColor(SIColor);
        cout << "Enter the offset for episodes: ";
    back1:
        ChangeColor(userColor);
        getline(cin, temp);
        try {
            Episode::Offset(stoi(temp));
        }
        catch(...) {
            ChangeColor(errorColor);
            cout << "Error! Please enter the CORRECT offset for episodes: ";
            goto back1;
        }

        ChangeColor(SIColor);
        cout << "Enter the offset for subtitles: ";
    back2:
        ChangeColor(userColor);
        getline(cin, temp);
        try {
            file::Subtitle::Offset(stoi(temp));
        }
        catch(...) {
            ChangeColor(errorColor);
            cout << "Error! Please enter the CORRECT offset for subtitles: ";
            goto back2;
        }

        // Bierzemy z GetExecutablePath sciezke oraz GetSeasonNumber razem z wylapywaniem bledow
        // pobiera numer sezonu
        File::Configure(animeName, fm::GetExecutablePathW(),
                        File::GetSeasonNumber(fm::GetExecutablePathW()));

        // cout << Episode::animeName << endl;
        // cout << Episode::animeDirectory << endl;
        // cout << Episode::seasonNumber << endl;
        // cout << Episode::offset << endl;
        // cout << Subtitle::offset << endl;
    }

    vector<Episode> episodes;
    vector<Subtitle> subtitles;
    for(auto dir : Subtitle::folders)
        fm::ReadDirectoryWS(File::GetDirectory() + sm::STWS(dir) + L"\\", subtitles,
                            Subtitle::Extensions(), false, true);

    fm::ReadDirectoryWS(File::GetDirectory(), subtitles, Subtitle::Extensions(), false, true);
    fm::ReadDirectoryWS(File::GetDirectory(), episodes, Episode::Extensions(), false, true);

    if(episodes.empty()) {
        ChangeColor(errorColor);
        cout << "No episodes!" << endl;
        system("pause");
        exit(0);
    }
    if(subtitles.empty()) {
        ChangeColor(errorColor);
        cout << "No subtitles!" << endl;
        system("pause");
        exit(0);
    }

    // cout << "UWAGA:" << endl;
    // for (auto& x : subtitles)
    //	cout << sm::WSTS(x.OriginalName()) << endl;
    // cout << "UWAGA:" << endl;

    for(auto& ep : episodes)
        ep.FindEpNumber();
    for(auto& ep : subtitles)
        ep.FindEpNumber();

    for(auto& ep : episodes)
        if(ep.episodeNumber == -1)
            ep.episodeNumber = File::MaxEpisodeNumber() + 1;
    for(auto& ep : subtitles)
        if(ep.episodeNumber == -1)
            ep.episodeNumber = File::MaxEpisodeNumber() + 1;

    /*cout << "maxEpisodeNumber = " << File::maxEpisodeNumber << endl;
    for (auto& sub : subtitles)
            cout << sub.episodeNumber << " - " << sub.originalName << endl;
    cout << "-----------------------" << endl;
    for (auto& ep : episodes)
            cout << ep.episodeNumber << " - " << ep.originalName << endl;*/
    // wszystkie episode i subtitle mają już w episodeNumber odpowiedni numer
    // Teraz trzeba je polaczyc w dwuwyymiarowej tablicy ktora ma pierwszy rozmiar maxEpisodeNumber
    // + 1 I potem przelecenie wszyystkiego zmieniajac nazwe albo robiac okienka wyboru (no ogolnie
    // sporo przypadkow)

    vector<vector<Episode>> episodesSorted;
    vector<vector<Subtitle>> subtitlesSorted;
    for(int i = 0; i < File::MaxEpisodeNumber() + 2; i++) {
        vector<Episode> x;
        vector<Subtitle> y;
        episodesSorted.push_back(x);
        subtitlesSorted.push_back(y);
    }

    for(auto& ep : episodes)
        episodesSorted[ep.episodeNumber].push_back(std::move(ep));

    for(auto& sub : subtitles)
        subtitlesSorted[sub.episodeNumber].push_back(std::move(sub));

    // cout << "maxEpisodeNumber = " << File::MaxEpisodeNumber() << endl;
    // for (unsigned int i = 0; i < episodesSorted.size(); i++)
    //{
    //	cout << "\t\t\t" << i << endl;
    //	for (auto& sub : subtitlesSorted[i])
    //		cout << sub.EpisodeNumber() << " - " << sm::WSTS(sub.OriginalName()) << endl;
    //	for (auto& ep : episodesSorted[i])
    //		cout << ep.EpisodeNumber() << " - " << sm::WSTS(ep.OriginalName()) << endl;
    //	cout << endl;
    // }

    menu::Menu_t* meni;

    // cout << episodesSorted.size() << endl;

    for(unsigned int i = 0; i < episodesSorted.size() - 1; i++) {
        // cout << episodesSorted[i].size() << " - " << subtitlesSorted[i].size() << endl;

        if(episodesSorted[i].size() == subtitlesSorted[i].size() &&
           episodesSorted[i].size() == 1) // DONE
        {
            // cout << "Zmieniam nazwe dla anime i dla napisow! [" << i << "]" << endl;
            // cout << subtitlesSorted[i][0].originalNameWithPath << endl;
            // cout << subtitlesSorted[i][0].NewName() << endl;
            // cout << episodesSorted[i][0].originalNameWithPath << endl;
            // cout << episodesSorted[i][0].NewName() << endl;
#ifdef LOG_VERSION
            fm::MoveFileWLog(subtitlesSorted[i][0].OriginalNameWithPath(),
                             subtitlesSorted[i][0].NewName(), log);
            fm::RenameFileWLog(episodesSorted[i][0].OriginalNameWithPath(),
                               episodesSorted[i][0].NewName(), log);
#else
            fm::MoveFileW(subtitlesSorted[i][0].OriginalNameWithPath(),
                          subtitlesSorted[i][0].NewName());
            fm::RenameFileW(episodesSorted[i][0].OriginalNameWithPath(),
                            episodesSorted[i][0].NewName());
#endif
            // Zmiana nazwy odcinka anime i napisow plus przeniesienie napisow do lokalizacji
            // odcinka
        }
        else if(episodesSorted[i].size() == subtitlesSorted[i].size() &&
                subtitlesSorted[i].size() == 0) // DONE
        {
            // cout << "Nic nie robie bo nie ma ani napisow ani odcinka [" << i << "]" << endl;
            continue; // Jesli nie ma ani odcinka ani napisow do tego numeru
        }
        else if(episodesSorted[i].size() == 0) // DONE
        {
            cout << "Error! Couldn't find episode number " << i
                 << " even though there are subtitles!" << endl;

            // Przekopiowanie wszystkich napisow jakie byly bez pary do bazy napisow z ostatniego
            // odcinka
            move(begin(subtitlesSorted[i]), end(subtitlesSorted[i]),
                 inserter(subtitlesSorted[subtitlesSorted.size() - 1],
                          end(subtitlesSorted[subtitlesSorted.size() - 1])));

            _getch();
            continue;
        }
        else if(subtitlesSorted[i].size() == 0) // DONE
        {
            cout << "Error! Couldn't find subtitle number " << i << " even though there is episode!"
                 << endl;

            // Przekopiowanie wszystkich napisow jakie byly bez pary do bazy napisow z ostatniego
            // odcinka
            move(begin(episodesSorted[i]), end(episodesSorted[i]),
                 inserter(episodesSorted[episodesSorted.size() - 1],
                          end(episodesSorted[episodesSorted.size() - 1])));

            _getch();
            continue;
        }
        else if(subtitlesSorted[i].size() > 1 && episodesSorted[i].size() > 1) // DONE
        {
            int choosen1 = -1, choosen2 = -1;
            {
                vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;

                for(unsigned int j = 0; j < episodesSorted[i].size(); j++) {
                    auto lambda = [&meni, j, &choosen1]() {
                        choosen1 = j;
                        menu::ClearScreen();
                        meni->Die();
                    };
                    x.push_back({sm::WSTS(episodesSorted[i][j].OriginalName()), lambda});
                }

                x.push_back({"Nani?! All of them are wrong?! MASAKA!", [&meni]() {
                                 menu::ClearScreen();
                                 meni->Die();
                             }});

                meni = menu::Menu_t::CreateMenu(
                    2, 1, 55,
                    "Found too much episodes and subtitles with number " + to_string(i) +
                        "!\nFirstly please choose which episode is correct!",
                    x, DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                    DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

                meni->StartMenu();
                meni->DeleteMenu();
            }
            {
                vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;

                for(unsigned int j = 0; j < subtitlesSorted[i].size(); j++) {
                    auto lambda = [&meni, j, &choosen2]() {
                        choosen2 = j;
                        menu::ClearScreen();
                        meni->Die();
                    };
                    x.push_back({sm::WSTS(subtitlesSorted[i][j].OriginalName()), lambda});
                }

                x.push_back({"Who downloaded this subtitles?! SKIP!!!", [&meni]() {
                                 menu::ClearScreen();
                                 meni->Die();
                             }});

                meni = menu::Menu_t::CreateMenu(
                    2, 1, 55,
                    "Found too much episodes and subtitles with number " + to_string(i) +
                        "!\nNow please choose which subtitle is correct!",
                    x, DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                    DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

                meni->StartMenu();
                meni->DeleteMenu();

                ent::ChangeColor(SIColor);
            }

            if(choosen1 != -1 && choosen2 != -1) // Jesli cos zostalo wybrane
            {
#ifdef LOG_VERSION
                fm::MoveFileWLog(subtitlesSorted[i][choosen2].OriginalNameWithPath(),
                                 subtitlesSorted[i][choosen2].NewName(), log);
                fm::RenameFileWLog(episodesSorted[i][choosen1].OriginalNameWithPath(),
                                   episodesSorted[i][choosen1].NewName(), log);
#else
                fm::MoveFileW(subtitlesSorted[i][choosen2].OriginalNameWithPath(),
                              subtitlesSorted[i][choosen2].NewName());
                fm::RenameFileW(episodesSorted[i][choosen1].OriginalNameWithPath(),
                                episodesSorted[i][choosen1].NewName());
#endif

                auto newEnd1 = remove(begin(subtitlesSorted[i]), end(subtitlesSorted[i]),
                                      subtitlesSorted[i][choosen2]);
                subtitlesSorted[i].erase(newEnd1, end(subtitlesSorted[i]));

                auto newEnd2 = remove(begin(episodesSorted[i]), end(episodesSorted[i]),
                                      episodesSorted[i][choosen1]);
                episodesSorted[i].erase(newEnd2, end(episodesSorted[i]));
            }

            for(auto& x : subtitlesSorted[i])
                subtitlesSorted[subtitlesSorted.size() - 1].push_back(x);

            for(auto& x : episodesSorted[i])
                episodesSorted[episodesSorted.size() - 1].push_back(x);

            // cout << "Za duzo napisow i odcinkow dla " << i << endl;
        }
        else if(episodesSorted[i].size() > 1) // DONE
        {
            vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;

            int choosen = -1;

            for(unsigned int j = 0; j < episodesSorted[i].size(); j++) {
                auto lambda = [&meni, j, &choosen]() {
                    choosen = j;
                    menu::ClearScreen();
                    meni->Die();
                };
                x.push_back({sm::WSTS(episodesSorted[i][j].OriginalName()), lambda});
            }

            x.push_back({"Nani?! All of them are wrong?! MASAKA!", [&meni]() {
                             menu::ClearScreen();
                             meni->Die();
                         }});

            meni = menu::Menu_t::CreateMenu(2, 1, 55,
                                            "Found too much episodes with number " + to_string(i) +
                                                "!\nPlease choose which one is correct!",
                                            x, DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                                            DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

            meni->StartMenu();
            meni->DeleteMenu();

            ent::ChangeColor(SIColor);

            if(choosen != -1) // Jesli cos zostalo wybrane
            {
#ifdef LOG_VERSION
                fm::MoveFileWLog(subtitlesSorted[i][0].OriginalNameWithPath(),
                                 subtitlesSorted[i][0].NewName(), log);
                fm::RenameFileWLog(episodesSorted[i][choosen].OriginalNameWithPath(),
                                   episodesSorted[i][choosen].NewName(), log);
#else
                fm::MoveFileW(subtitlesSorted[i][0].OriginalNameWithPath(),
                              subtitlesSorted[i][0].NewName());
                fm::RenameFileW(episodesSorted[i][choosen].OriginalNameWithPath(),
                                episodesSorted[i][choosen].NewName());
#endif

                auto newEnd = remove(begin(episodesSorted[i]), end(episodesSorted[i]),
                                     episodesSorted[i][choosen]);
                episodesSorted[i].erase(newEnd, end(episodesSorted[i]));
            }

            for(auto& x : episodesSorted[i])
                episodesSorted[episodesSorted.size() - 1].push_back(x);
        }
        else if(subtitlesSorted[i].size() > 1) // DONE
        {
            vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;

            int choosen = -1;

            for(unsigned int j = 0; j < subtitlesSorted[i].size(); j++) {
                auto lambda = [&meni, j, &choosen]() {
                    choosen = j;
                    menu::ClearScreen();
                    meni->Die();
                };
                x.push_back({sm::WSTS(subtitlesSorted[i][j].OriginalName()), lambda});
            }

            x.push_back({"Who downloaded this subtitles?! SKIP!!!", [&meni]() {
                             menu::ClearScreen();
                             meni->Die();
                         }});

            meni = menu::Menu_t::CreateMenu(2, 1, 55,
                                            "Found too much subtitles for episode number " +
                                                to_string(i) +
                                                "!\nPlease choose which one is correct!",
                                            x, DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                                            DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

            meni->StartMenu();
            meni->DeleteMenu();

            ent::ChangeColor(SIColor);

            if(choosen != -1) // Jesli cos zostalo wybrane
            {
#ifdef LOG_VERSION
                fm::MoveFileWLog(subtitlesSorted[i][choosen].OriginalNameWithPath(),
                                 subtitlesSorted[i][choosen].NewName(), log);
                fm::RenameFileWLog(episodesSorted[i][0].OriginalNameWithPath(),
                                   episodesSorted[i][0].NewName(), log);
#else
                fm::MoveFileW(subtitlesSorted[i][choosen].OriginalNameWithPath(),
                              subtitlesSorted[i][choosen].NewName());
                fm::RenameFileW(episodesSorted[i][0].OriginalNameWithPath(),
                                episodesSorted[i][0].NewName());
#endif

                auto newEnd = remove(begin(subtitlesSorted[i]), end(subtitlesSorted[i]),
                                     subtitlesSorted[i][choosen]);
                subtitlesSorted[i].erase(newEnd, end(subtitlesSorted[i]));
            }

            for(auto& x : subtitlesSorted[i])
                subtitlesSorted[subtitlesSorted.size() - 1].push_back(x);
        }
    }

    for(auto& ep : episodesSorted[episodesSorted.size() - 1]) {
        vector<pair<string, menu::WskaznikNaFunkcjeMenu>> x;
        int i = subtitlesSorted.size() - 1;
        int choosen = -1;

        for(unsigned int j = 0; j < subtitlesSorted[i].size(); j++) {
            auto lambda = [&meni, j, &choosen]() {
                choosen = j;
                menu::ClearScreen();
                meni->Die();
            };
            x.push_back({sm::WSTS(subtitlesSorted[i][j].OriginalName()), lambda});
        }

        x.push_back({"Who downloaded this subtitles?! SKIP!!!", [&meni]() {
                         menu::ClearScreen();
                         meni->Die();
                     }});

        x.push_back({"I've seen Enough. I'm Satisfied.", [&meni]() {
                         menu::ClearScreen();
                         ent::ChangeColor(SIColor);
                         cout << "SUCCESS!" << endl;
                         _getch();
                         exit(0);
                     }});

        meni = menu::Menu_t::CreateMenu(
            2, 1, 55, "Choose subtitle file for this episode:\n" + sm::WSTS(ep.OriginalName()), x,
            DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS, DEFAULT_IN_KEYBOARD_KEYS, {},
            DEFAULT_MENU_COLOR_SET);

        meni->StartMenu();
        meni->DeleteMenu();

        ent::ChangeColor(SIColor);

        if(choosen != -1) // Jesli cos zostalo wybrane
        {

#ifdef LOG_VERSION
            fm::MoveFileWLog(subtitlesSorted[i][choosen].OriginalNameWithPath(),
                             ep.OriginalNameWithPath().replace(
                                 ep.OriginalNameWithPath().size() - 4, 4,
                                 subtitlesSorted[i][choosen].OriginalName().substr(
                                     subtitlesSorted[i][choosen].OriginalName().size() - 4)),
                             log);
#else
            fm::MoveFileW(subtitlesSorted[i][choosen].OriginalNameWithPath(),
                          ep.OriginalNameWithPath().replace(
                              ep.OriginalNameWithPath().size() - 4, 4,
                              subtitlesSorted[i][choosen].OriginalName().substr(
                                  subtitlesSorted[i][choosen].OriginalName().size() - 4)));
#endif
            remove(begin(subtitlesSorted[i]), end(subtitlesSorted[i]), subtitlesSorted[i][choosen]);
            // fm::ChangeName(ep.OriginalNameWithPath(), ep.NewName());
        }
    }

    ent::ChangeColor(SIColor);
    cout << endl << "SUCCESS" << endl;

    system("Pause");

    return 0;
}
