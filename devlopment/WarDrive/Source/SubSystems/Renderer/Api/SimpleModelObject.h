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
#include <map>
#include <tuple>

#include "IObject.h"
#include "Pipeline.h"

using namespace std;


#define BYTE_SIZE_VERTEX_BUFFER 1000000
#define BYTE_SIZE_COLOR_BUFFER 1000000

#if 0
//TBD: understand this better - how to manage the vertex buffer in efficient manner.
static  GLfloat g_smo_vertex_buffer_data[BYTE_SIZE_VERTEX_BUFFER] = {0.0f};
// One color for each vertex. They were generated randomly.
static  GLfloat g_smo_color_buffer_data[BYTE_SIZE_COLOR_BUFFER] = {0.0f};
#endif
static  GLfloat* g_smo_vertex_buffer_data = NULL;
// One color for each vertex. They were generated randomly.
static  GLfloat* g_smo_color_buffer_data = NULL;

struct BufferKey {
    unsigned int vertex_buffer_idx;
    unsigned int vertex_buffer_length;
    unsigned int color_buffer_idx;
    unsigned int color_buffer_length;
    GLuint vb_ref;
    GLuint cb_ref;
};

class SimpleModelObject : public IObject {
    private:
    
    GLuint vertexbuffer;
    GLuint vertex_buffer_data_count;

    GLuint colorbuffer;
    GLuint color_buffer_data_count;


    glm::mat4 Model;
    GLuint VertexArrayID;

    Assimp::Importer *importer = nullptr;
    aiScene *scene = nullptr;

    std::vector<BufferKey> buffer_keys;

    public:
    SimpleModelObject();
    virtual glm::mat4 getModelMatrix();
    virtual void rotate(float angle, glm::vec3 axis);
    virtual void translate(glm::vec3 offset);
    virtual void Draw();

    private:
    void initAssimp();
    void drawMeshes(BufferKey& bufferKey);

};

typedef shared_ptr<SimpleModelObject> SimpleModelObjectSPTR;