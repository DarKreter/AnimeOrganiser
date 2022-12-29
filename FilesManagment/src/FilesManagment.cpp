#include "FilesManagment.hpp"

#include <fstream>
#include <memory>
#include <unistd.h>

using namespace std;

namespace fm {
void CopyFile(std::string nameIn, std::string nameOUT)
{
    string command = "cp -a \"" + nameIn + "\" \"" + nameOUT + "\"";
    unsigned short error = system(command.c_str());

    if(error)
        throw Error_t{"Error in copying file.\nFrom: " + nameIn + "\nTo: " + nameOUT +
                      "\nError log: " + to_string(error)};
}

void CopyFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
{
    strumien << "-------------COPY FILE-------------" << endl
             << "FROM:\t" << nameIn << endl
             << "TO:\t" << nameOUT << endl;
    usleep(LOG_SLEEP);

    string command = "cp -a \"" + nameIn + "\" \"" + nameOUT + "\"";
    unsigned short error = system(command.c_str());
    usleep(LOG_SLEEP);

    if(error)
        strumien << "ERROR: " << error << endl;
    else
        strumien << "SUCCESS!" << endl;
    usleep(LOG_SLEEP);
}

void MoveFile(std::string nameIn, std::string nameOUT)
{
    string command = "mv -f \"" + nameIn + "\" \"" + nameOUT + "\" 2> /dev/null";
    unsigned short error = system(command.c_str());

    if(error && error != 256)
        throw Error_t{"Error in moving file.\nFrom: " + nameIn + "\nTo: " + nameOUT +
                      "\nError log: " + to_string(error)};
}

void MoveFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
{
    strumien << "-------------MOVE FILE-------------" << endl
             << "FROM:\t" << nameIn << endl
             << "TO:\t" << nameOUT << endl;
    usleep(LOG_SLEEP);

    string command = "mv -f \"" + nameIn + "\" \"" + nameOUT + "\" 2> /dev/null";
    unsigned short error = system(command.c_str());
    usleep(LOG_SLEEP);

    if(error)
        strumien << "ERROR: " << error << endl;
    else
        strumien << "SUCCESS!" << endl;
    usleep(LOG_SLEEP);
}

void RenameFile(std::string oldName, std::string newName)
{
    string command = "mv \"" + oldName + "\" \"" +
                     oldName.substr(0, oldName.find_last_of('/') + 1) + newName + "\" 2> /dev/null";
    unsigned short error = system(command.c_str());

    if(error && error != 256)
        throw Error_t{"Error in moving file.\nFrom: " + oldName + "\nTo: " + newName +
                      "\nError log: " + to_string(error)};
}

void RenameFileLog(std::string oldName, std::string newName, std::ostream& strumien)
{
    strumien << "-------------RENAME FILE-------------" << endl
             << "File : " << oldName << endl
             << "New name : " << newName << endl;
    usleep(LOG_SLEEP);

    string command = "mv \"" + oldName + "\" \"" +
                     oldName.substr(0, oldName.find_last_of('/') + 1) + newName + "\" > /dev/null";
    unsigned short error = system(command.c_str());
    usleep(LOG_SLEEP);

    if(error)
        strumien << "ERROR: " << error << endl;
    else
        strumien << "SUCCESS!" << endl;
    usleep(LOG_SLEEP);
}

std::string ReadFile(std::string name, const unsigned long long rozmiar)
{
    std::fstream file;
    file.open(name.c_str(), std::ios::in | std::ios::binary);
    if(!file.good())
        throw Error_t{"Blad otwarcia pliku: " + name + " do czytania!"};

    char* tab = new char[rozmiar];
    file.read(tab, rozmiar);
    std::streamsize gcount = file.gcount();

    if(gcount == rozmiar)
        throw Error_t{"Nie udalo sie wczytac calego pliku!\n Jego rozmiar jest wiekszy niz: " +
                      std::to_string(rozmiar)};

    std::string temp(tab, gcount);

    delete[] tab;

    return temp;
}

void MakeFile(std::string name, std::string data)
{
    std::fstream file;
    file.open(name.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.good())
        throw Error_t{"Blad stworzenia pliku " + name + " !"};

    file.write(data.c_str(), data.size());
    file.close();
}

bool FilesFilter(const string& s,
                 const std::vector<std::string>& extension) // zwraca true jesli mamy usunac
{
    bool havingExt = true;

    for(const auto& ex : extension)
        if(!ex.length())
            havingExt = false;
        else if(s.length() > 3 &&
                ex ==
                    s.substr(s.length() - ex.length())) /// Jesli dana nazwa jest tego rozszerzenia
            return false;                               /// To ja zachowujemy

    if(!havingExt && s.find('.') == string::npos)
        return false;

    return true; // Jesli nie byla zadnego z powyzszych usuwamy
}

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if(!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string GetExecutablePath()
{
    string temp = exec("pwd");
    return temp.substr(0, temp.length() - 1) + '/'; // cut new line from the end
}
} // namespace fm