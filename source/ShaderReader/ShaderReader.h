//
// Created by Cody Dietz on 2019-05-22.
//

#ifndef INITGL_SHADERREADER_H
#define INITGL_SHADERREADER_H

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::string> stringvec;

class ShaderReader {
public:
    static const GLchar* ReadFromFile(const GLchar* pathToFile);
private:
    static void read_directory(const std::string& parentDirectory);

};


#endif //INITGL_SHADERREADER_H
