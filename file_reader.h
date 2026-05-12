#ifndef FILEREADER_H
#define FILEREADER_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

#include "normalizationparameters.h"
#include "base_file_reader.h"
#include "figure.h"
#include "constants.h"

class FileReader: public BaseFileReader {
public:
    std::unique_ptr<Scene> readScene(std::filesystem::path path, NormalizationParameters params) override;
};

#endif // FILEREADER_H
