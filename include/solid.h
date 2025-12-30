#ifndef SOLID_H
#define SOLID_H

#include <vector>
#include <string>
#include <GL/glew.h>

class Solid {
public:
    Solid(const std::string& filename);

    const std::vector<GLfloat>& getVertices() const { return vertices; }
    const std::vector<GLuint>& getTriangleIndices() const { return triangleIndices; }
    const std::vector<GLuint>& getEdgeIndices() const { return edgeIndices; }

private:
    void loadFromFile(const std::string& filename);

    std::vector<GLfloat> vertices;
    std::vector<GLuint> triangleIndices;
    std::vector<GLuint> edgeIndices;
};

#endif
