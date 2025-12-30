#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <memory>
#include <string>
#include "solid.h"

class Mesh {
public:
    Mesh(const std::string& filename);
    ~Mesh();

    void draw();
    void drawWireframe();
    void loadSolid(const std::string& filename);

private:
    void setupBuffers();
    void cleanupBuffers();

    std::unique_ptr<Solid> solid;
    GLuint VertexArrayID;
    GLuint vertexbuffer;
    GLuint triangleElementBuffer;
    GLuint edgeElementBuffer;
    GLuint triangleIndexCount;
    GLuint edgeIndexCount;
};

#endif