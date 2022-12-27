// #include "FilesManagment.hpp"
#include "Menu.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    // cout << "Hello World!" << endl;

    // vector<string> pliki;
    // fm::ReadDirectory("/mnt/MAIN/Wymiennik/ŻĆŚĄĄ", pliki, {"*.h", "*.cpp", "*"}, true);

    // for(auto& file : pliki)
    //     printf("'%s'\n", file.c_str());

    // int i = 0;
    // while(i++ < 10)
    //     cout << (int)getcharr();

    menu::Menu_t* confirming =
        menu::Menu_t::CreateMenu(1, 5, 7, "Dzialasz?",
                                 {{"Tak ",
                                   [&confirming]() {
                                       menu::ClearScreen();
                                       confirming->Die();
                                   }},
                                  {"Nie", [&confirming]() { confirming->Die(); }}},
                                 DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
                                 DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

    confirming->StartMenu();
    confirming->DeleteMenu();

    return 0;
}