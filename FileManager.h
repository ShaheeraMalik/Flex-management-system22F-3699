#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
public:
    static std::string readFile(const std::string& fileName);
    static void writeFile(const std::string& fileName, const std::string& data);
};

#endif // FILEMANAGER_H
