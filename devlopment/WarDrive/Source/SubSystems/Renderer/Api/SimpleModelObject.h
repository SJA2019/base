#pragma once


#include <memory>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include "IObject.h"
#include "Pipeline.h"

using namespace std;


static  GLfloat g_smo_vertex_buffer_data[1000000] = {0.0f};

// One color for each vertex. They were generated randomly.
static  GLfloat g_smo_color_buffer_data[1000000] = {0.0f};

class SimpleModelObject : public IObject {
    private:
    
    GLuint vertexbuffer;
    //GLfloat* vertex_buffer_data;
    GLuint vertex_buffer_data_count;

    GLuint colorbuffer;
    //GLfloat* color_buffer_data;
    GLuint color_buffer_data_count;


    glm::mat4 Model;
    GLuint VertexArrayID;

    Assimp::Importer *importer = nullptr;
    aiScene *scene = nullptr;

    public:
    SimpleModelObject();
    virtual glm::mat4 getModelMatrix();
    virtual void rotate(float angle, glm::vec3 axis);
    virtual void translate(glm::vec3 offset);
    virtual void Draw();

    private:
    void initAssimp();

};

typedef shared_ptr<SimpleModelObject> SimpleModelObjectSPTR;