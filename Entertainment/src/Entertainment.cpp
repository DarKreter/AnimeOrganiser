#include "Entertainment.h"

using namespace std;

namespace ent
{
    void Dots(int czas, int howManyTimes, char znak)
    {
        for (int i = 1; i <= howManyTimes; i++)
        {
            Sleep(czas);
            std::cout << znak;
        }
        Sleep(czas);
    }

    void Fan(int howLong, int breakTime)
    {
        char tab[] = { '\\', '-', '/', '|' };
        for (int i = 0; i < howLong; i++)
        {
            cout << tab[i % 4] << "\b";
            Sleep(breakTime);
        }
    }

    void ChangeColor(Color f, Color b)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast <int> (f) + static_cast <int> (b) * 16);
    }
}