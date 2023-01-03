#ifndef STRINGMANAGMENT_H
#define STRINGMANAGMENT_H

#include <string>

namespace sm {
/**
        Zmienia wstringa na stringa
*/
std::string WSTS(std::wstring const& text); // WStringToString

/**
        Zmienia stringa na wstringa
*/
std::wstring STWS(std::string const& text); // StringToString

/*
        Zmienia stringa na TCHAR*
*/
// const TCHAR* S2TCharP(std::string); // stringToTCharPointer

/*
        Usuwa biale znaki z poczatku napisu
        @param napis do edycji
        @param napis ktory zawiera znaki do usuniecia z przodu napisu
                        domniemanie " \t"
*/
std::string RemoveWSBegin(const std::string&, const std::string = " \t");

/*
        Usuwa biale znaki z konca napisu
        @param napis do edycji
        @param napis ktory zawiera znaki do usuniecia z tylu napisu
                        domniemanie " \t"
*/
std::string RemoveWSEnd(const std::string&, const std::string = " \t");

/*
        Usuwa biale znaki z poczatku i konca napisu dla stringow
        @param napis do edycji
        @param napis ktory zawiera znaki do usuniecia z przodu i tylu napisu
                        domniemanie " \t"
*/
std::string RemoveWSBeginEnd(const std::string&, const std::string = " \t");

/*
        Usuwa biale znaki z poczatku i konca napisu dla wstringow
        @param napis do edycji
        @param napis ktory zawiera znaki do usuniecia z przodu i tylu napisu
                        domniemanie " \t"
*/
std::wstring RemoveWSBeginEndW(const std::wstring&, const std::wstring = L" \t");

/*
        Zamienia ciagi bialych znakow na spacje(dowolny znak) dla stringow
        @param napis do edycji
        @param na jaki znak ma taki ciag byc zamieniony | domniemanie " "
        @param napis ktory zawiera znaki ktoych ciagi beda zamieniane
                        domniemanie " \t"
*/
std::string RemoveDoubleWS(std::string, const std::string = " ", const std::string = " \t");
/*
        Zamienia ciagi bialych znakow na spacje(dowolny znak) dla wstringow
        @param napis do edycji
        @param na jaki znak ma taki ciag byc zamieniony | domniemanie " "
        @param napis ktory zawiera znaki ktoych ciagi beda zamieniane
                        domniemanie " \t"
*/
std::wstring RemoveDoubleWSW(std::wstring, const std::wstring = L" ", const std::wstring = L" \t");
} // namespace sm

#endif // !STRINGMANAGMENT_H
