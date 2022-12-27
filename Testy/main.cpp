#include "FilesManagment.hpp"
#include <iostream>

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    // vector<string> pliki;
    // fm::ReadDirectory("/mnt/MAIN/Wymiennik/ŻĆŚĄĄ", pliki, {"*.h", "*.cpp", "*"}, true);

    // for(auto& file : pliki)
    //     printf("'%s'\n", file.c_str());

    cout << fm::GetExecutablePath() << endl;

    return 0;
}