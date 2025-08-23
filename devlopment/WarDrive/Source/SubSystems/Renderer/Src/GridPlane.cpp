
#include "SDL.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "GridPlane.h"


GridPlane::GridPlane(){


    std::cout << "CubeObject() ++" << std::endl;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_plane_vertex_buffer_data), g_plane_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_plane_color_buffer_data), g_plane_color_buffer_data, GL_STATIC_DRAW);
     std::cout << "CubeObject() --" << std::endl;
}


glm::mat4 GridPlane::getModelMatrix() {
    return Model;
}

void GridPlane::Draw() {
    
    glBindVertexArray(VertexArrayID);
        // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6 * 3); // 2*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void GridPlane::rotate(float angle, glm::vec3 axis) {
    Model = glm::rotate(Model, angle, axis );
}
void GridPlane::translate(glm::vec3 offset) {
    Model = glm::translate(Model, offset);
}

