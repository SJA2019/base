#pragma once


#include <memory>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include "IObject.h"
#include "Pipeline.h"

using namespace std;


// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_plane_vertex_buffer_data[] = {
    
    -1.0f, 0.0f, -1.0f, // triangle 1 : begin
    1.0f,  0.0f, 1.0f,
    -1.0f, 0.0f, 1.0f, // triangle 1 : end
    
    -1.0f, 0.0f, -1.0f, // triangle 2 : begin
    1.0f, 0.0f, -1.0f,
    1.0f, 0.0f, 1.0f, // triangle 2 : end
    
    -1.0f, -1.0f, 0.0f, // triangle 1 : begin 
    1.0f, 1.0f, 0.0f,
    -1.0f,1.0f, 0.0f, // triangle 1 : end
    
    -1.0f, -1.0f, 0.0f, // triangle 2 : begin
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, // triangle 2 : end

    0.0f, -1.0f, -1.0f, // triangle 1 : begin
    0.0f,  1.0f, 1.0f,
    0.0f, -1.0f, 1.0f, // triangle 1 : end
    
    0.0f, -1.0f, -1.0f, // triangle 2 : begin
    0.0f, 1.0f, -1.0f,
    0.0f, 1.0f, 1.0f // triangle 2 : end
    
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_plane_color_buffer_data[] = {
    0.0f, 0.0f, 1.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f, // triangle 1 : begin

    0.0f, 0.0f, 1.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f, // triangle 1 : begin


    0.0f, 0.1f, 0.0f, // triangle 2 : begin
    0.0f, 0.1f, 0.0f, // triangle 2 : begin
    0.0f, 0.1f, 0.0f, // triangle 2 : begin

    0.0f, 0.1f, 0.0f, // triangle 2 : begin
    0.0f, 0.1f, 0.0f, // triangle 2 : begin
    0.0f, 0.1f, 0.0f, // triangle 2 : begin

    0.1f, 0.0f, 0.0f, // triangle 2 : begin
    0.1f, 0.0f, 0.0f, // triangle 2 : begin
    0.1f, 0.0f, 0.0f, // triangle 2 : begin

    0.1f, 0.0f, 0.0f, // triangle 2 : begin
    0.1f, 0.0f, 0.0f, // triangle 2 : begin
    0.1f, 0.0f, 0.0f // triangle 2 : begin
};

#if 0
// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_plane_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f, // triangle 1 : begin
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    
    1.0f, 1.0f, -1.0f, // triangle 2 : begin
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f, // triangle 2 : end
    
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f  
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_plane_color_buffer_data[] = {
    0.0f, 0.0f, 0.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, // triangle 1 : end
    
    1.0f, 1.0f, 0.0f, // triangle 2 : begin
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, // triangle 2 : end
    
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f
};
#endif

class GridPlane : public IObject {
    private:
    GLuint vertexbuffer;
    GLuint colorbuffer;
    glm::mat4 Model;
    GLuint VertexArrayID;

    public:
    GridPlane();
    virtual glm::mat4 getModelMatrix();
    virtual void rotate(float angle, glm::vec3 axis);
    virtual void translate(glm::vec3 offset);
    virtual void Draw();

};

typedef shared_ptr<GridPlane> GridPlaneSPTR;