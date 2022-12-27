#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

namespace ent {
enum Color : uint8_t {
    black,
    darkBlue,
    green,
    turquoise,
    darkRed,
    purple,
    shitDillyPink,
    silver,
    gray,
    blue,
    lime,
    cyan,
    red,
    pink,
    yellow,
    white
};

/*
    Wyswietla jakis znak podana ilosc razy z podanym odstepem czasowym
    @param ile czasu ma byc pomiedzy kolejnymi znakami [ms]
    @param ile znakow ma sie wypisac
    @param Jaki to ma byc znak | domniemanie '.'
*/
void Dots(int, int = 3, char = '.');

/*
    Symuluje dzialanie wiatraka na jednym polu w konsoli uzywaja znakow / | \ -
    @param okresla ile razy ma sie obrocic wiatraczek
    @param okresla ile ms ma byc odstepu pomiedzy kolejnymi charami
*/
void Fan(int, int);

/*
    Zmienia kolor konsoli
    Works only for Windows
    Will have no effect on Linux/Unix
    @param foreground color
    @param background color
*/
void ChangeColor(Color, Color = black);

} // namespace ent

#endif // !ENTERTAINMENT_H
