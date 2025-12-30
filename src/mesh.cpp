#include "../include/mesh.h"
#include <iostream>

Mesh::Mesh(const std::string& filename) {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    solid = std::make_unique<Solid>(filename);
    setupBuffers();
}

Mesh::~Mesh() {
    cleanupBuffers();
    glDeleteVertexArrays(1, &VertexArrayID);
}

void Mesh::setupBuffers() {
    const auto& verts = solid->getVertices();
    const auto& tris = solid->getTriangleIndices();
    const auto& edges = solid->getEdgeIndices();

    // Vertex buffer (shared by both triangle and edge rendering)
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat),
                 verts.data(), GL_STATIC_DRAW);

    // Triangle element buffer
    glGenBuffers(1, &triangleElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(GLuint),
                 tris.data(), GL_STATIC_DRAW);
    triangleIndexCount = tris.size();

    // Edge element buffer
    glGenBuffers(1, &edgeElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, edges.size() * sizeof(GLuint),
                 edges.data(), GL_STATIC_DRAW);
    edgeIndexCount = edges.size();
}

void Mesh::cleanupBuffers() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &triangleElementBuffer);
    glDeleteBuffers(1, &edgeElementBuffer);
}

void Mesh::draw() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleElementBuffer);
    glDrawElements(GL_TRIANGLES, triangleIndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

void Mesh::drawWireframe() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeElementBuffer);
    glDrawElements(GL_LINES, edgeIndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

void Mesh::loadSolid(const std::string& filename) {
    cleanupBuffers();
    solid = std::make_unique<Solid>(filename);
    glBindVertexArray(VertexArrayID);
    setupBuffers();
}
