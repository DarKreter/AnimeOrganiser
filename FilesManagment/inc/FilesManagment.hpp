#ifndef FILESMANAGMENT_H
#define FILESMANAGMENT_H

#include <string>
#include <vector>

#include "StringManagment.hpp"

namespace fm {
constexpr uint_least32_t LOG_SLEEP = 100'000;

struct Error_t {
    std::string what;
    std::string What() { return what; }
};

/**
        Sluzy do filtrowania kontenerow z nazwami plikow podajac rozszerzenia jakie maja zostac
        Najlepiej utworzyc lamdbe ktora zwraca wywolanie tej funkcji dla stringa i wrzucic ja
        jako funkcje decydujaca czy wyrzucic plik z kontenera
        @param nazwa do sprawdzenia poprawnosci
        @param wektor rozszerzen do zachowania | FORMAT: .*
        @return zwraca true jesli string [arg1] nie ma rozszerzenia z wektora [arg2]
*/
bool FilesFilter(const std::string& s, const std::vector<std::string>& extension);

/**
        Funkcja przeszukuje wskazany katalog i zwraca wszystkie nazwy plikow i folderow
        znajdujace sie w nim jako stringi. Mozna podac filtr w ktorym po podaniu rozszerzen tylko
        pliki z tymi rozszerzeniami pozostana w wektorze
        @param sciezka do katalogu do przejrzenia | "" - oznacza katalog pliku wykonywalnego
        @param wektor do ktorego zostana dodane wykryte pliki spelniajace filtr | REFERENCJA
                   moze byc to wektor STRING'ow, musi miec kontruktor tworzacy obiekt na
                   podstawie stringa
        @param wektor rozszerzen do zachowania | FORMAT: .* |
        domniemany argument [pusta lista] - nazwy nie beda filtrowane |
        "" oznacza brak rozszerzenia
        @param bool oznaczajacy czy wpisywac nazwy folderow do wektora
        @param bool czy wpisywac pelne sciezki czy tylko nazwy plikow
        | JESLI CHCEMY WPISYWAC PELNE JAKO 1arg TRZEBA PRZYSLAC SCIEZKE BEZWZGLEDNA
        @return brak
*/
template <typename T>
void ReadDirectory(std::string, std::vector<T>&, const std::vector<std::string>& = {}, bool = false,
                   bool = false);

/**
        Otwiera binarnie plik i czyta jego zawartosc
        @param sciezka do pliku do otworzenia
        @param maksymalny rozmiar pliku [wielkosc bufora] | jesli plik jest wiekszy rzuci wyjatek
        @return zwraca dane binarne z pliku
*/
std::string ReadFile(std::string name, const unsigned long long rozmiar);

/**
        OTworzy plik i wpisuje tam binarne dane
        @param sciezka do pliku do utworzenia
        @param binarne dane do wpisania do pliku
        @return nic nie zwraca
*/
void MakeFile(std::string name, std::string data);

/**
        Kopiuje plik
        @param sciezka do pliku ktory mamy skopiowac
        @param sciezka do pliku ktory ma powstac
        @return nic nie zwraca
*/
void CopyFile(std::string nameIn, std::string nameOUT);
/**
        CopyFile z opcja wypisania logow
*/
void CopyFileLog(std::string nameIn, std::string nameOUT, std::ostream&);

/**
        przenosi plik
        @param sciezka do pliku ktory mamy przenisc
        @param sciezka do pliku ktory ma powstac
        @return nic nie zwraca
*/
void MoveFile(std::string nameIn, std::string nameOUT);
/**
        MoveFile z opcja wypisania logow
*/
void MoveFileLog(std::string nameIn, std::string nameOUT, std::ostream&);

/**
        Zmienia nazwe pliku
        @param sciezka do pliku
        @param nowa nazwa
        @return nic nie zwraca
*/
void RenameFile(std::string oldName, std::string newName);
/**
        RenameFile z opcja wypisania logow
*/
void RenameFileLog(std::string oldName, std::string newName, std::ostream&);
/**
        RenameFile dla nazw plikow okreslonych jako wstringi
*/

/**
        pobiera aktualna sciezke w jakiej znajduje sie plik .exe
        @return sciezka w stringu
*/
std::string GetExecutablePath();

/**
 * execute 'cmd' command in shell, but returns stdout output of the command
 * @param command to execute
 * @return returning stdout answer of command
 */
std::string exec(const char* cmd);

} // namespace fm

#include "FilesManagment.tpp"

#endif
