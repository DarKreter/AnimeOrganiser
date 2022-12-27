#include "FilesManagment.h"

using namespace std;



namespace fm
{
    void CopyFile(std::string nameIn, std::string nameOUT)
    {
        string command = "copy /B /-Y /Z \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in copying file.\nFrom: " + nameIn + "\nTo: " + nameOUT + "\nError log: " + to_string(error) };
    }

    void CopyFileW(std::wstring nameIn, std::wstring nameOUT)
    {
        wstring command = L"copy /B /-Y /Z \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in copying file.\nFrom: " + nameIn + L"\nTo: " + nameOUT + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }

    void CopyFileWLog(std::wstring nameIn, std::wstring nameOUT, std::wostream& strumien)
    {
        strumien << "-------------COPY FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"copy /B /-Y /Z \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }

    void CopyFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
    {
        strumien << "-------------COPY FILE-------------" 
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        string command = "copy /B /-Y /Z \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }


    void MoveFile(std::string nameIn, std::string nameOUT)
    {
        string command = "move /-Y \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in moving file.\nFrom: " + nameIn + "\nTo: " + nameOUT + "\nError log: " + to_string(error) };
    }

    void MoveFileW(std::wstring nameIn, std::wstring nameOUT)
    {
        wstring command = L"move /-Y \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in moving file.\nFrom: " + nameIn + L"\nTo: " + nameOUT + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }
    void MoveFileWLog(std::wstring nameIn, std::wstring nameOUT, std::wostream& strumien)
    {
        strumien << "-------------MOVE FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"move /-Y \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }
    void MoveFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
    {
        strumien << "-------------MOVE FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        string command = "move /-Y \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }


    void RenameFile(std::string oldName, std::string newName)
    {
        string command = "rename \"" + oldName + "\" \"" + newName + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in changing file name.\nFile: " + oldName + "\nNew name: " + newName + "\nError log: " + to_string(error) };
    }
    void RenameFileW(std::wstring oldName, std::wstring newName)
    {
        wstring command = L"rename \"" + oldName + L"\" \"" + newName + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in changing file name.\nFile: " + oldName + L"\nNew name: " + newName + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }
    void RenameFileWLog(std::wstring oldName, std::wstring newName, std::wostream& strumien)
    {
        strumien << "-------------RENAME FILE-------------"
            << endl << "File : " << oldName << endl << "New name : " << newName << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"rename \"" + oldName + L"\" \"" + newName + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }
    void RenameFileLog(std::string oldName, std::string newName, std::ostream& strumien)
    {
        strumien << "-------------RENAME FILE-------------"
            << endl << "File : " << oldName << endl << "New name : " << newName << endl;
        Sleep(LOG_SLEEP);

        string command = "rename \"" + oldName + "\" \"" + newName + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }

    std::string ReadFile(std::string name, const unsigned long long rozmiar)
    {
        std::fstream file;
        file.open(name.c_str(), std::ios::in | std::ios::binary);
        if (!file.good())
            throw Error_t{ "Blad otwarcia pliku: " + name + " do czytania!" };

        char* tab = new char[rozmiar];
        file.read(tab, rozmiar);
        std::streamsize gcount = file.gcount();

        if (gcount == rozmiar)
            throw Error_t{ "Nie udalo sie wczytac calego pliku!\n Jego rozmiar jest wiekszy niz: " + std::to_string(rozmiar) };

        std::string temp(tab, gcount);

        delete[] tab;

        return temp;
    }

    void MakeFile(std::string name, std::string data)
    {
        std::fstream file;
        file.open(name.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file.good())
            throw Error_t{ "Blad stworzenia pliku " + name + " !" };

        file.write(data.c_str(), data.size());
        file.close();
    }

    static std::string WSTS(std::wstring const& text) //WStringToWtring
    {
        std::locale const loc("");
        wchar_t const* from = text.c_str();
        std::size_t const len = text.size();
        std::vector<char> buffer(len + 1);
        std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
        return std::string(&buffer[0], &buffer[len]);
    }

    bool FilesFilter(const string& s,const std::vector<std::string>& extension) //zwraca true jesli mamy usunac
    {
        bool havingExt = true;

        for (const auto& ex : extension)
            if (!ex.length())
                havingExt = false;
            else if (s.length() > 3 && ex == s.substr( s.length() - ex.length() )) ///Jesli dana nazwa jest tego rozszerzenia
                return false;   ///To ja zachowujemy

        if (!havingExt && s.find('.') == string::npos)
            return false;

        return true; //Jesli nie byla zadnego z powyzszych usuwamy       
    }

    bool FilesFilter(const wstring& s, const std::vector<std::string>& e) //zwraca true jesli mamy usunac
    {
        bool havingExt = true;
        std::vector<std::wstring> extension;

        for (const auto& s : e)
        {
            wstring abc(begin(s), end(s));
            extension.push_back(abc);
        }

        for (const auto& ex : extension)
            if (!ex.length())
                havingExt = false;
            else if (s.length() > 3 && ex == s.substr(s.length() - ex.length())) ///Jesli dana nazwa jest tego rozszerzenia
                return false;   ///To ja zachowujemy

        if (!havingExt && s.find('.') == string::npos)
            return false;

        return true; //Jesli nie byla zadnego z powyzszych usuwamy       
    }

    std::string GetExecutablePath()
    {
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);

        wstring ws(buffer);

        string temp = string(ws.begin(), ws.end());
        string::size_type pos = temp.find_last_of('\\');
        return temp.substr(0, pos + 1);
    }

    std::wstring GetExecutablePathW()
    {
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);

        wstring ws(buffer);

        string::size_type pos = ws.find_last_of('\\');
        return ws.substr(0, pos + 1);
    }

}
