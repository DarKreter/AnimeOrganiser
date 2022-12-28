#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <unistd.h>

namespace ent {

class Format_t {
    // Constants
    constexpr static char const* begin_sequence = "\033[";
    constexpr static char const* end_sequence = "m";
    constexpr static char const* rgb_sequence = "2;";

    enum Ground : uint8_t {
        foreground = 3,
        background
    };

public:
    // Enumerate types
    enum Color : uint8_t {
        black,
        red,
        green,
        yellow,
        blue,
        purple,
        cyan,
        white,
        rgb,
        none
    };

    enum Mode : uint8_t {
        normal = 0,
        italic = 1,       // 3;
        underline = 2,    // 4;
        slowBlinking = 4, // 5;
        fastBlinking = 8, // 6;
        reverse = 16,     // 7;
        hide = 32,        // 8;
        cross_out = 64    // 9;
    };

    friend Mode operator|(const Mode& mode1, const Mode& mode2)
    {
        return Mode(uint8_t(mode1) | uint8_t(mode2));
    }

    struct RGB {
        uint8_t red, green, blue;
    };

private:
    // private variables
    Color foregroundColor = none, backgroundColor = none;
    RGB fRGB, bRGB;
    uint8_t mode;

public:
    // Access functions
    void SetFColor(Color _color, RGB _rgb = {0, 0, 0});
    void SetBColor(Color _color, RGB _rgb = {0, 0, 0});
    void SetMode(Mode _mode) { mode = uint8_t(_mode); }
    std::string Sequence() const;

    friend std::ostream& operator<<(std::ostream& stream, const Format_t& _format);
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

} // namespace ent

#endif // !ENTERTAINMENT_H
