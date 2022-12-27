#ifndef FMTEMPLATES_H
#define FMTEMPLATES_H

template <typename T>
inline void ReadDirectory(std::string name, std::vector<T>& v,
                          const std::vector<std::string>& filters, bool dir, bool fullPath)
{
    if(name == "") // legacy compatibility
        name = ".";

    // find in given dir with given filter
    auto find = [&v, &name](std::string filter, std::string type) {
        std::string command =
            "find " + name + " -maxdepth 1 -type " + type + " -name \"" + filter + "\"";
        std::string output = exec(command.c_str());
        std::stringstream split(output);
        std::string segment;
        while(std::getline(split, segment, '\n')) {
            v.push_back(segment);
        }
    };

    if(dir)
        find("*", "d");
    // if no filters, detect all files from dir
    if(filters.empty())
        find("*", "f");
    // find with every filter specification
    for(const auto& filter : filters) {
        find(filter, "f");
    }

    // remove duplicates
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

// template <typename T>
// void ReadDirectoryWS(const std::wstring name, std::vector<T>& v,
//                      const std::vector<std::string>& filters, bool dir, bool fullPath)
// {
//     // std::cout << "name = " << name << std::endl;

//     std::vector<std::wstring> tempFiles;
//     std::vector<std::wstring> tempDir;

//     WIN32_FIND_DATA data;
//     HANDLE hFind;

//     std::wstring stemp = name + L"*";
//     LPCWSTR sw = stemp.c_str();

//     if((hFind = FindFirstFile(sw, &data)) != INVALID_HANDLE_VALUE) {
//         do {

//             if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//                 if(dir) {
//                     std::wstring wsTmp(name.begin(), name.end());

//                     if(fullPath)
//                         tempDir.push_back(wsTmp + data.cFileName);
//                     else
//                         tempDir.push_back(data.cFileName);
//                 }
//             }
//             else {
//                 std::wstring wsTmp(name.begin(), name.end());

//                 if(fullPath)
//                     tempFiles.push_back(wsTmp + data.cFileName);
//                 else
//                     tempFiles.push_back(data.cFileName);
//             }

//         } while(FindNextFile(hFind, &data) != 0);
//         FindClose(hFind);
//     }

//     if(filters.empty() == false) {
//         auto RemoverFiles([&filters](std::wstring t) {
//             return FilesFilter(t, filters);
//         }); // Lambda ktora zwroci true dla rozszerzen spoza puli
//         remove_copy_if(begin(tempFiles), end(tempFiles), back_inserter(v), RemoverFiles);
//     }
//     else
//         copy(begin(tempFiles), end(tempFiles), back_inserter(v));

//     auto RemoverDir([](std::wstring t) {
//         return (t.substr(t.length() - 1) == L"." ||
//                 (t.length() > 1 && t.substr(t.length() - 2) == L".."));
//     }); // Lambda ktora zwroci true dla kropek

//     remove_copy_if(begin(tempDir), end(tempDir), back_inserter(v), RemoverDir);
// }

#endif // FMTEMPLATES_H