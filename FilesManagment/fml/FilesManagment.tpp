#ifndef FMTEMPLATES_H
#define FMTEMPLATES_H

#include <sstream>

namespace fm {

template <typename T>
inline void ReadDirectory(std::string name, std::vector<T>& v,
                          const std::vector<std::string>& filters, bool dir, bool fullPath)
{
    if(name == "") // legacy compatibility
        name = ".";

    // find in given dir with given filter
    auto find = [&v, &name](std::string filter, std::string type) {
        std::string command = "find \"" + name + "\" -maxdepth 1 -type " + type + " -name \"" +
                              filter + "\" 2>/dev/null";
        // std::cout << command << std::endl;
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

} // namespace fm

#endif // FMTEMPLATES_H