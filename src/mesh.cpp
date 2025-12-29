#include <vector>
#include "../include/mesh.h"
#include <SDL.h>
#include <iostream>

Mesh::Mesh() {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Tetrahedron
    // GLfloat vertices[] = {
    //     0.0f,  0.0f,  0.577f,
    //     0.0f,  0.816f, -0.289f,
    //    -0.707f, -0.408f, -0.289f,
    //     0.707f, -0.408f, -0.289f
    // };
    // GLint triangles[] = {
    //     0, 1, 2,
    //     0, 3, 1,
    //     0, 2, 3,
    //     1, 3, 2
    // };

    // Cube
    // GLfloat vertices[] = {
    //     0.5f, -0.5f, 0.5f,
    //     -0.5f, -0.5f, 0.5f,
    //     0.5f, 0.5f, 0.5f,
    //     -0.5f, 0.5f, 0.5f,
    //     0.5f, -0.5f, -0.5f,
    //     -0.5f, -0.5f, -0.5f,
    //     0.5f, 0.5f, -0.5f,
    //     -0.5f, 0.5f, -0.5f
    // };
    // GLint triangles[] = {0, 2, 3, 0, 3, 1,
    //                       2, 6, 7, 2, 7, 3,
    //                       6, 4, 5, 6, 5, 7,
    //                       4, 0, 1, 4, 1, 5,
    //                       1, 3, 7, 1, 7, 5,
    //                       4, 6, 2, 4, 2, 0};

    // Regular octahedron
    // GLfloat vertices[] = {
    //     -0.5f, 0.0f, 0.0f,
    //     0.5f, 0.0f, 0.0f,
    //     0.0f, 0.5f, 0.0f,
    //     0.0f, -0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,
    //     0.0f, 0.0f, -0.5f
    // };
    // GLint triangles[] = {
    //     2, 0, 4,
    //     2, 4, 1,
    //     2, 1, 5,
    //     2, 5, 0,
    //     3, 4, 0,
    //     3, 1, 4,
    //     3, 5, 1,
    //     3, 0, 5
    // };

    // Icosahedron
    GLfloat phi = (1 + 2.2361) / 4;
    GLfloat vertices[] = {
        0.0f,  0.5f, phi,
        0.0f,  0.5f, -phi,
        0.0f,  -0.5f, phi,
        0.0f,  -0.5f, -phi,
        0.5f, phi, 0,
        0.5f, -phi, 0,
        -0.5f, phi, 0,
        -0.5f, -phi, 0,
        phi, 0, 0.5,
        -phi, 0, 0.5,
        phi, 0, -0.5,
        -phi, 0, -0.5,
    };
    GLint triangles[] = {
        // top
        4, 0, 8,
        0, 2, 8,
        2, 5, 8,
        5, 10, 8,
        10, 4, 8,
        // bottom
        3, 7, 11,
        7, 9, 11,
        9, 6, 11,
        6, 1, 11,
        1, 3, 11,
        // belt
        3, 7, 5,
        7, 9, 2,
        9, 6, 0,
        6, 1, 4,
        1, 3, 10
        // (other five faces of the belt are not added)
    };
    

    // Dodecahedron
    // (todo)

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    vertex_size = sizeof(triangles) / sizeof(GLint);
}

void Mesh::draw(){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glDrawElements(GL_TRIANGLES, vertex_size, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}
