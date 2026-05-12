#include "file_reader.h"

namespace {
using CsvTable = std::vector<std::vector<float>>;

bool readCell(const std::string& rawCell, float& value) {
    size_t parsedSize = 0;

    try {
        value = std::stof(rawCell, &parsedSize);
    } catch (...) {
        return false;
    }

    return parsedSize == rawCell.find_last_not_of(" \t\r\n") + 1;
}

bool appendCsvRow(const std::string& line, CsvTable& table) {
    std::stringstream stream(line);
    std::string rawCell;
    std::vector<float> row;

    while (std::getline(stream, rawCell, Constants::SEPARATOR)) {
        float value = 0;
        if (!readCell(rawCell, value))
            return false;

        row.push_back(value);
    }

    if (row.empty())
        return line.empty();

    table.push_back(row);
    return true;
}

bool loadTable(std::ifstream& input, CsvTable& table) {
    std::string line;

    while (std::getline(input, line))
        if (!appendCsvRow(line, table))
            return false;

    return !table.empty();
}

bool hasRectangularShape(const CsvTable& table) {
    const size_t width = table.front().size();

    if (width == 0)
        return false;

    return std::all_of(table.begin(), table.end(), [width](const auto& row) {
        return row.size() == width;
    });
}

std::pair<float, float> measureRange(const CsvTable& table) {
    float minValue = table.front().front();
    float maxValue = minValue;

    for (const auto& row : table)
        for (float value : row) {
            minValue = std::min(minValue, value);
            maxValue = std::max(maxValue, value);
        }

    return {minValue, maxValue};
}

size_t roundedStride(double rawStep) {
    return static_cast<size_t>(std::lround(rawStep));
}

float normalizeZ(float value, float sourceMin, float sourceMax, const NormalizationParameters& params) {
    if (sourceMax == sourceMin)
        return static_cast<float>((params.min + params.max) / 2.0);

    return params.min + (value - sourceMin) / (sourceMax - sourceMin) * (params.max - params.min);
}

void makeVertices(const CsvTable& table,
                  const NormalizationParameters& params,
                  std::vector<Vertex>& vertices,
                  size_t& rowsCount,
                  size_t& colsCount) {
    const auto [sourceMin, sourceMax] = measureRange(table);
    const size_t yStride = roundedStride(params.dyStep);
    const size_t xStride = roundedStride(params.dxStep);

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
            const size_t current = row * colsCount + col;

            if (col + 1 < colsCount)
                edges.push_back(Edge(vertices[current], vertices[current + 1]));

            if (row + 1 < rowsCount)
                edges.push_back(Edge(vertices[current], vertices[current + colsCount]));
        }
    }
}
}

std::unique_ptr<Scene> FileReader::readScene(std::filesystem::path path, NormalizationParameters params) {
    std::ifstream input(path);
    CsvTable table;

    if (!input.is_open())
        return nullptr;

    if (!loadTable(input, table) || !hasRectangularShape(table))
        return nullptr;

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    size_t rowsCount = 0;
    size_t colsCount = 0;

    makeVertices(table, params, vertices, rowsCount, colsCount);
    makeEdges(vertices, rowsCount, colsCount, edges);

    auto scene = std::make_unique<Scene>();
    auto figure = std::make_shared<Figure>(vertices, edges);
    scene->getFigures().push_back(figure);

    return scene;
}
