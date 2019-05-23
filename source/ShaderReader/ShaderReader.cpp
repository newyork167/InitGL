//
// Created by Cody Dietz on 2019-05-22.
//

#include "ShaderReader.h"

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
