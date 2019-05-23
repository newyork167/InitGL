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

void ShaderReader::read_directory(const std::string& name, stringvec& v)
{
    boost::filesystem::path p(name);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_leaf_string());
}

const GLchar *ShaderReader::ReadFromFile(const GLchar *pathToFile) {
    stringvec v;
    ShaderReader::read_directory(".", v);
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

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
