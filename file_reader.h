#ifndef FILEREADER_H
#define FILEREADER_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>

#include "normalization_parameters.h"
#include "base_file_reader.h"
#include "figure.h"
#include "constants.h"
#include "scene.h"

class BaseFileReader {
public:
    virtual ~BaseFileReader() = default;
    virtual std::unique_ptr<Scene> readScene(std::filesystem::path path, NormalizationParameters params) = 0;
};

class FileReader: public BaseFileReader {
public:
    std::unique_ptr<Scene> readScene(std::filesystem::path path, NormalizationParameters params) override;
};

#endif // FILEREADER_H
