#include "../include/solid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Solid::Solid(const std::string& filename) {
    loadFromFile(filename);
}

void Solid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    enum class Section { NONE, VERTICES, TRIANGLES, EDGES };
    Section currentSection = Section::NONE;

    while (std::getline(file, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        if (line == "VERTICES") {
            currentSection = Section::VERTICES;
            continue;
        } else if (line == "TRIANGLES") {
            currentSection = Section::TRIANGLES;
            continue;
        } else if (line == "EDGES") {
            currentSection = Section::EDGES;
            continue;
        }

        std::stringstream ss(line);

        switch (currentSection) {
            case Section::VERTICES: {
                GLfloat x, y, z;
                if (ss >> x >> y >> z) {
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                } else {
                    std::cerr << "Warning: Failed to parse vertex line: " << line << std::endl;
                }
                break;
            }
            case Section::TRIANGLES: {
                GLuint v1, v2, v3;
                if (ss >> v1 >> v2 >> v3) {
                    triangleIndices.push_back(v1);
                    triangleIndices.push_back(v2);
                    triangleIndices.push_back(v3);
                } else {
                    std::cerr << "Warning: Failed to parse triangle line: " << line << std::endl;
                }
                break;
            }
            case Section::EDGES: {
                GLuint v1, v2;
                if (ss >> v1 >> v2) {
                    edgeIndices.push_back(v1);
                    edgeIndices.push_back(v2);
                } else {
                    std::cerr << "Warning: Failed to parse edge line: " << line << std::endl;
                }
                break;
            }
            case Section::NONE:
                std::cerr << "Warning: Data found before section header: " << line << std::endl;
                break;
        }
    }

    file.close();

    std::cout << "Loaded solid from " << filename << std::endl;
    std::cout << "  Vertices: " << vertices.size() / 3 << std::endl;
    std::cout << "  Triangles: " << triangleIndices.size() / 3 << std::endl;
    std::cout << "  Edges: " << edgeIndices.size() / 2 << std::endl;
}
