//
// Created by Cody Dietz on 2019-05-22.
//

#include "ShaderReader.h"

struct path_leaf_string
{
    std::string operator()(const boost::filesystem::directory_entry& entry) const
    {
        return entry.path().leaf().string();
    }
};

void ShaderReader::read_directory(const std::string& parentDirectory)
{
    namespace fs = boost::filesystem;
    fs::path dir = parentDirectory;
    fs::recursive_directory_iterator it(dir), end;

    std::vector<std::string> files;
    for (auto& entry : boost::make_iterator_range(it, end))
        if (is_regular(entry))
            files.push_back(entry.path().native());

    for (auto& file : files)
        std::cout << file << "\n";
}

const GLchar *ShaderReader::ReadFromFile(const GLchar *pathToFile) {
    std::string content;
    std::ifstream fileStream(pathToFile, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
        return "";
    }

    std::string line;
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    std::cout << "'" << content << "'" << std::endl;

    auto * source = new char[content.length()+1];
    strcpy(source, content.c_str());
    return source;
}
