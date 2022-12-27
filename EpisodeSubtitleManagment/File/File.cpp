#include "File.h"
#include "FilesManagment.h"
#include "StringManagment.h"
#include "Entertainment.h"
#include  <algorithm>

using namespace std;
using file::File;

ent::Color errorColor = ent::darkRed, SIColor = ent::blue, userColor = ent::lime, dataColor = ent::darkBlue;

namespace file
{
	wstring	File::animeName = L"";
	wstring	File::animeDirectory = L"";
	int		File::seasonNumber = 0;
	int		File::maxEpisodeNumber = 0;

    std::wstring File::GetFileExtension()
    {
        return originalName.substr(originalName.find_last_of('.'));
    }

    std::wstring File::NewNameWithoutExt()
    {
        wostringstream s;
        s << animeName << L" - s" << std::setw(2) << setfill(L'0') << seasonNumber << L"e" << setw(2) << setfill(L'0') << episodeNumber;
        return s.str();
    }

    std::wstring File::NewName()
    {
        wostringstream s;
        s << animeName << L" - s" << std::setw(2) << setfill(L'0') << seasonNumber << L"e" << setw(2) << setfill(L'0') << episodeNumber
            << GetFileExtension();
        return s.str();
    }

    std::wstring File::NewNameWithPath()
    {
        return fm::GetExecutablePathW() + NewName();
    }

	void File::Configure(std::wstring aN, std::wstring aD, int sN)
	{
		animeName = aN;
		animeDirectory = aD;
		seasonNumber = sN;
	}

	void File::FindEpNumber(int offset)
	{
		try
		{
			string::size_type begPos = 0;
			string::size_type endPos = 0;

			for (int i = 0; i <= offset; i++)
			{
				//cout << i << "\t";
				begPos = originalName.find_first_of(L"1234567890", endPos);
				//cout << begPos << "\t";
				endPos = originalName.find_first_not_of(L"1234567890", begPos);
				//cout << endPos << "\n";
			}

            auto temp = stoi(originalName.substr(begPos, endPos - begPos));
            
            //tutaj mozesz se zmienic numerek jakbys chcial
            temp += EPISODE_DELAY;

			//cout << originalName.substr(begPos, endPos - begPos) << "\n";
			episodeNumber = temp;
			maxEpisodeNumber = max(episodeNumber, maxEpisodeNumber);
		}
		catch (...)
		{
			episodeNumber = -1;
		}

	}

    wstring File::GetAnimeName(wstring path)
    {
        string name;
        ent::ChangeColor(errorColor);// cout << endl;

        try
        {
            path.erase(path.length() - 1, 1);
            path = path.substr(path.find_last_of('\\') + 1, string::npos);
            string::size_type beg = path.find('[');
            string::size_type end = path.find(']');

            if (beg != string::npos && end != string::npos)
                path.erase(beg, end + 1);
            
            vector<string> maybeErase = {" - HQ", " -HQ", " - LQ", " -LQ"};

            for (auto& mE : maybeErase)
            {
                auto find = std::search(begin(path), std::end(path), begin(mE), std::end(mE));
                if (find != std::end(path))
                    path.erase(find, std::end(path));
            }

            path = sm::RemoveDoubleWSW(sm::RemoveWSBeginEndW(path));

            wstring animeName;
            ChangeColor(SIColor);    cout << "Suggesting name of anime:" << endl << "\t\'" << sm::WSTS(path) << "\'" <<endl
                << "If the name is correct press ENTER, if not write your \"better\" name: ";
            ChangeColor(userColor);  getline(wcin, animeName);

            if (animeName.empty())
                return path;
            else
                return animeName;
        }
        catch (...)
        {
            wstring animeName;

            ChangeColor(SIColor);    cout << "Enter the name of Anime to transmutation: ";
            ChangeColor(userColor);  getline(wcin, animeName);

            return animeName;
        }

    }

    int File::GetSeasonNumber(wstring path)
    {
        int sN;
        ent::ChangeColor(errorColor);// cout << endl;

        try
        {
            path.erase(path.length() - 1, 1);
            path = path.substr(path.find_last_of('\\') + 1, string::npos);
            string::size_type beg = path.find('[');
            string::size_type end = path.find(']');

            if (beg == string::npos)
                throw Error_t{ "Could not find [" };

            if (end == string::npos)
                throw Error_t{ "Could not find ]" };

            sN = std::stoi(path.substr(beg + 1, end));

            return sN;
        }
        catch (std::invalid_argument& e)
        {
            cout << "Extracting the number of season ended with error." << endl;
            cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
                << "\tCatched exception: invalid_Argument." << endl
                << "\texception.what \"" << e.what() << "\"" << endl << endl;
        }
        catch (std::out_of_range& e)
        {
            cout << "Extracting the number of season ended with error." << endl;
            cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
                 << "\tCatched exception: out_of_range." << endl
                 << "\texception.what \"" << e.what() << "\"" << endl << endl;
        }
        catch (file::Error_t& e)
        {
            cout << "Extracting the number of season ended with error." << endl;
            cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
                << "\tCatched exception: file::Error_t." << endl
                << "\texception.what \"" << e.what << "\"" << endl << endl;
        }
        catch (...)
        {
            cout << "Extracting the number of season ended with error." << endl;
            cout << "\tIn " << __FUNCTION__ << " line " << __LINE__ << "." << endl
                << "\tCatched unknown exception." << endl << endl;
        }

        ent::ChangeColor(SIColor); cout << endl;

        cout << "Please check if the number of season is in square brackets \"[]\"" << endl;
        cout << "You can also enter this data manually: ";
        string line;

    back:
        ent::ChangeColor(userColor); getline(cin, line);

        try
        {
            sN = stoi(line);
        }
        catch (...)
        {
            ent::ChangeColor(errorColor);
            cout << "Error! Please enter the CORRECT number of season: ";
            goto back;
        }

        return sN;
    }

}