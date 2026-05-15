#include "file_reader.h"

bool readCell(const std::string& rawCell, float& value) {
    size_t parsedSize = 0;
    bool isOk = true;

    try {
        value = std::stof(rawCell, &parsedSize);
    } catch (...) {
        isOk = false;
    }

    return isOk && parsedSize == rawCell.find_last_not_of(" \t\r\n") + 1;
}

bool appendCsvRow(const std::string& line, std::vector<std::vector<float>>& table) {
    std::stringstream stream(line);
    std::string rawCell;
    std::vector<float> row;
    bool isOk = true;

    while (isOk && std::getline(stream, rawCell, Constants::SEPARATOR)) {
        float value = 0;
        if (!readCell(rawCell, value))
            isOk = false;
        else
            row.push_back(value);
    }

    if (isOk && row.empty())
        isOk = line.empty();

    if (isOk)
        table.push_back(row);
    return isOk;
}

bool loadTable(std::ifstream& input, std::vector<std::vector<float>>& table) {
    std::string line;
    bool isOk = true;

    while (isOk && std::getline(input, line))
        if (!appendCsvRow(line, table))
            isOk = false;

    if (isOk)
        isOk = !table.empty();

    return isOk;
}

bool hasRectangularShape(const std::vector<std::vector<float>>& table) {
    bool isRectangular = !table.empty();
    size_t width = 0;

    if (isRectangular) {
        width = table.front().size();
        isRectangular = width != 0;
    }

    for (size_t rowIndex = 0; isRectangular && rowIndex < table.size(); rowIndex++)
        if (table[rowIndex].size() != width)
            isRectangular = false;

    return isRectangular;
}

std::pair<float, float> measureRange(const std::vector<std::vector<float>>& table) {
    float minValue = table.front().front();
    float maxValue = minValue;

    for (const auto& row : table)
        for (float value : row) {
            minValue = std::min(minValue, value);
            maxValue = std::max(maxValue, value);
        }

    return {minValue, maxValue};
}

float normalizeZ(float value, float sourceMin, float sourceMax, const NormalizationParameters& params) {
    float normalized = static_cast<float>((params.min + params.max) / 2.0);

    if (sourceMax != sourceMin)
        normalized = params.min + (value - sourceMin) / (sourceMax - sourceMin) * (params.max - params.min);

    return normalized;
}

void makeVertices(const std::vector<std::vector<float>>& table,
                  const NormalizationParameters& params,
                  std::vector<Vertex>& vertices,
                  size_t& rowsCount,
                  size_t& colsCount) {
    const auto [sourceMin, sourceMax] = measureRange(table);
    const size_t yStride = static_cast<size_t>(std::lround(params.dyStep));
    const size_t xStride = static_cast<size_t>(std::lround(params.dxStep));

    rowsCount = 0;
    colsCount = 0;

    for (size_t y = 0; y < table.size(); y += yStride) {
        size_t rowVertices = 0;

        for (size_t x = 0; x < table[y].size(); x += xStride) {
            Point3D point(static_cast<float>(x * params.dxStep),
                          static_cast<float>(y * params.dyStep),
                          normalizeZ(table[y][x], sourceMin, sourceMax, params));
            vertices.push_back(Vertex(point));
            rowVertices++;
        }

        if (colsCount == 0)
            colsCount = rowVertices;

        rowsCount++;
    }
}

void makeEdges(const std::vector<Vertex>& vertices, size_t rowsCount, size_t colsCount, std::vector<Edge>& edges) {
    for (size_t row = 0; row < rowsCount; row++) {
        for (size_t col = 0; col < colsCount; col++) {
            size_t current = row * colsCount + col;

            if (col + 1 < colsCount)
                edges.push_back(Edge(vertices[current], vertices[current + 1]));

            if (row + 1 < rowsCount)
                edges.push_back(Edge(vertices[current], vertices[current + colsCount]));
        }
    }
}

std::unique_ptr<Scene> FileReader::readScene(std::filesystem::path path, NormalizationParameters params) {
    std::ifstream input(path);
    std::vector<std::vector<float>> table;
    std::unique_ptr<Scene> scene = nullptr;

    if (input.is_open() && loadTable(input, table) && hasRectangularShape(table)) {
        std::vector<Vertex> vertices;
        std::vector<Edge> edges;
        size_t rowsCount = 0;
        size_t colsCount = 0;

        makeVertices(table, params, vertices, rowsCount, colsCount);
        makeEdges(vertices, rowsCount, colsCount, edges);

        scene = std::make_unique<Scene>();
        scene->getFigures().push_back(Figure(edges));
    }

    return scene;
}
