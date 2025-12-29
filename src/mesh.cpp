#include <vector>
#include "../include/mesh.h"
#include <SDL.h>
#include <iostream>

Mesh::Mesh() {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLfloat phi = (1 + 2.2361) / 4;
    GLfloat sqrt2 = 1.414;

    // Tetrahedron
    // GLfloat vertices[] = {
    //     0.5f, 0.0f, -0.5f/sqrt2,
    //     -0.5f, 0.0f, -0.5f/sqrt2,
    //     0.0f, 0.5f, 0.5f/sqrt2,
    //     -0.0f, -0.5f, 0.5f/sqrt2,
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
    // GLfloat vertices[] = {
    //     0.0f,  0.5f, phi,
    //     0.0f,  0.5f, -phi,
    //     0.0f,  -0.5f, phi,
    //     0.0f,  -0.5f, -phi,
    //     0.5f, phi, 0,
    //     0.5f, -phi, 0,
    //     -0.5f, phi, 0,
    //     -0.5f, -phi, 0,
    //     phi, 0, 0.5f,
    //     -phi, 0, 0.5f,
    //     phi, 0, -0.5f,
    //     -phi, 0, -0.5f
    // };
    // GLint triangles[] = {
    //     // top
    //     4, 0, 8,
    //     0, 2, 8,
    //     2, 5, 8,
    //     5, 10, 8,
    //     10, 4, 8,
    //     // bottom
    //     3, 7, 11,
    //     7, 9, 11,
    //     9, 6, 11,
    //     6, 1, 11,
    //     1, 3, 11,
    //     // belt
    //     3, 7, 5,
    //     7, 9, 2,
    //     9, 6, 0,
    //     6, 1, 4,
    //     1, 3, 10
    //     // (other five faces of the belt are not added)
    // };
    
    // Dodecahedron
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.25f/phi, 0.0f, phi,
        0.25f/phi, 0.0f, -phi,
        -0.25f/phi, 0.0f, phi,
        -0.25f/phi, 0.0f, -phi,
        0.0f, phi, 0.25f/phi,
        0.0f, -phi, 0.25f/phi,
        0.0f, phi, -0.25f/phi,
        0.0f, -phi, -0.25f/phi,
        phi, 0.25f/phi, 0,
        -phi, 0.25f/phi, 0,
        phi, -0.25f/phi, 0,
        -phi, -0.25f/phi, 0
    };
    // each face receives three triangles
    GLuint triangles[] = {
        0, 16, 18,
        1, 16, 18,
        0, 1, 8,
        
        2, 16, 18,
        3, 16, 18,
        2, 3, 9,

        4, 17, 19,
        5, 17, 19,
        4, 5, 10,

        6, 17, 19,
        7, 17, 19,
        6, 7, 11,

        8, 10, 1,
        8, 10, 5,
        1, 5, 13,

        8, 10, 0,
        8, 10, 4,
        0, 4, 12,

        9, 11, 2,
        9, 11, 6,
        2, 6, 14,

        9, 11, 3,
        9, 11, 7,
        3, 7, 15,

        12, 14, 0,
        12, 14, 2,
        0, 2, 16,

        12, 14, 4,
        12, 14, 6,
        4, 6, 17,

        13, 15, 1,
        13, 15, 3,
        1, 3, 18,

        13, 15, 5,
        13, 15, 7,
        5, 7, 19
    };

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
