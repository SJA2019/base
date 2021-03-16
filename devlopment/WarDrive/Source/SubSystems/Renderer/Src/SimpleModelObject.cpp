#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "SDL.h"
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

//#include "assimp/scene.h"
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include "SimpleModelObject.h"


SimpleModelObject::SimpleModelObject(){

    initAssimp();
    glGenVertexArrays(1, &VertexArrayID);
    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
#if 1
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_smo_vertex_buffer_data), g_smo_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_smo_color_buffer_data), g_smo_color_buffer_data, GL_STATIC_DRAW);
#endif

}

void SimpleModelObject::initAssimp() { 
    importer = new Assimp::Importer();
    //auto scene = importer->ReadFile("Assets/SR71/sr71.obj", aiProcess_OptimizeMeshes);
    //auto scene = importer->ReadFile("Assets/low-poly-jeep/source/Jeep_1/Jeep_1.fbx", aiProcess_OptimizeMeshes);
    //auto scene = importer->ReadFile("Assets/low-poly-car/source/car/car.FBX", aiProcess_OptimizeMeshes);
    //auto scene = importer->ReadFile("Assets/mecha-low-poly-pbr-reupload/source/robo.fbx", aiProcess_OptimizeMeshes);
    auto scene = importer->ReadFile("Assets/jeep_collada/model.dae", aiProcess_Triangulate|aiProcess_SortByPType);
#if 1
    //Load vertices.
    auto nMeshes = scene->mNumMeshes;
    auto vertBuffIdx = 0;
    vertex_buffer_data_count = 0;
    color_buffer_data_count = 0;
    if (nullptr != scene) {
        cout<<"texdbg: nMeshes-count="<<nMeshes<<std::endl;
        for(auto meshIdx = 0; meshIdx < nMeshes; meshIdx++) {
            auto vertex_buffer_data = g_smo_vertex_buffer_data;//new GLfloat[scene->mMeshes[0]->mNumVertices * 3];
            vertex_buffer_data_count+= scene->mMeshes[meshIdx]->mNumVertices;
            auto color_buffer_data = g_smo_color_buffer_data;//new GLfloat[scene->mMeshes[0]->mNumVertices * 3];
            color_buffer_data_count+= scene->mMeshes[meshIdx]->mNumVertices;
            auto vertexCount = scene->mMeshes[meshIdx]->mNumVertices;
            aiColor4D diffuse;
            aiGetMaterialColor(scene->mMaterials[scene->mMeshes[meshIdx]->mMaterialIndex], AI_MATKEY_COLOR_DIFFUSE, &diffuse);
            for (auto vertIdx = 0; vertIdx<vertexCount; vertIdx++) {
                vertex_buffer_data[(vertBuffIdx*3)+0] = scene->mMeshes[meshIdx]->mVertices[vertIdx].x/10;
                vertex_buffer_data[(vertBuffIdx*3)+1] = scene->mMeshes[meshIdx]->mVertices[vertIdx].y/10;
                vertex_buffer_data[(vertBuffIdx*3)+2] = scene->mMeshes[meshIdx]->mVertices[vertIdx].z/10;
                /*color_buffer_data[(vertBuffIdx*3)+0] = ((meshIdx % 2) == 0) ? 0.2f : 0.5f; 
                color_buffer_data[(vertBuffIdx*3)+1] = ((meshIdx % 2) == 0) ? 0.2f : 0.5f; 
                color_buffer_data[(vertBuffIdx*3)+2] = ((meshIdx % 2) == 0) ? 0.2f : 0.5f; */
                /*color_buffer_data[(vertBuffIdx*3)+0] = (scene->mMeshes[meshIdx]->mVertices[vertIdx].x + 1)/2; 
                color_buffer_data[(vertBuffIdx*3)+1] = (scene->mMeshes[meshIdx]->mVertices[vertIdx].y + 1)/2; 
                color_buffer_data[(vertBuffIdx*3)+2] = (scene->mMeshes[meshIdx]->mVertices[vertIdx].z + 1)/2;*/
                color_buffer_data[(vertBuffIdx*3)+0] = diffuse.r; 
                color_buffer_data[(vertBuffIdx*3)+1] = diffuse.g; 
                color_buffer_data[(vertBuffIdx*3)+2] = diffuse.b;

                
                vertBuffIdx++;
                std::cout<<"v="<<scene->mMeshes[0]->mVertices[vertIdx].x/100<<","<<scene->mMeshes[0]->mVertices[vertIdx].y/100<<","<<scene->mMeshes[0]->mVertices[vertIdx].z/100<<std::endl;
                std::cout<<"r="<<diffuse.r<<",g="<<diffuse.g<<",b="<<diffuse.b<<",a="<<diffuse.a<<std::endl;
            }
        }
    }
    //Load texture.
    if (scene->HasMaterials())
    {
        cout<<"texdbg: has materials=true count="<<scene->mNumMaterials<<std::endl;
        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* material = scene->mMaterials[i];
            aiString texturePath;
            unsigned int numTextures= material->GetTextureCount(aiTextureType_DIFFUSE);   // always 0
            cout<<"texdbg: material#"<<i<<"texture-count="<<numTextures<<std::endl;
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 && material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) 
            {
                cout<<"texdbg: material#"<<i<<"0th texture-path="<<texturePath.C_Str()<<std::endl;
                // never happens..
                // scene->mNumTextures is always 0 aswell.
            }
        }
    } else {
        cout<<"texdbg: has materials=false"<<std::endl;
    }
#else
    vertex_buffer_data_count=3;
    color_buffer_data_count=3;
    vertex_buffer_data = new GLfloat[vertex_buffer_data_count * 3];
    color_buffer_data = new GLfloat[color_buffer_data_count * 3];
    
    //GLfloat vertex_buffer_data_arr[] =  {0.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  1.0f,1.0f,0.0f };
    //GLfloat color_buffer_data_arr[] =  {0.0f,0.0f,0.0f,  0.0f,0.0f,0.0f,  0.0f,0.0f,0.0f };

    vertex_buffer_data[0+0] = 0.0f;
    vertex_buffer_data[0+1] = 0.0f;
    vertex_buffer_data[0+2] = 0.0f;

    vertex_buffer_data[1+0] = 0.0f;
    vertex_buffer_data[1+1] = 1.0f;
    vertex_buffer_data[1+2] = 0.0f;

    vertex_buffer_data[2+0] = 1.0f;
    vertex_buffer_data[2+1] = 1.0f;
    vertex_buffer_data[2+2] = 1.0f;

    
    for (auto vertIdx = 0; vertIdx<vertex_buffer_data_count; vertIdx++) {
            color_buffer_data[(vertIdx*3)+0] = 0.0f;//((vertIdx % 2) == 0) ? 0.8f : 1.0f; 
            color_buffer_data[(vertIdx*3)+1] = 0.0f;//((vertIdx % 2) == 0) ? 0.8f : 0.1f; 
            color_buffer_data[(vertIdx*3)+2] = 0.0f;//((vertIdx % 2) == 0) ? 0.8f : 0.1f; 
            std::cout<<"v="<<scene->mMeshes[0]->mVertices[vertIdx].x<<","<<scene->mMeshes[0]->mVertices[vertIdx].y<<","<<scene->mMeshes[0]->mVertices[vertIdx].z<<std::endl;
    }
#endif

    
    


}

glm::mat4 SimpleModelObject::getModelMatrix() {
    return Model;
}

void SimpleModelObject::Draw() {
    
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
    //glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data_count * 3 ); // 12*3 indices starting at 0 -> 12 triangles
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_buffer_data_count * 3 );
    //glDrawArrays(GL_LINE_LOOP, 0, vertex_buffer_data_count * 3 );
    glDrawArrays(GL_LINE_LOOP, 0, vertex_buffer_data_count * 3 );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void SimpleModelObject::rotate(float angle, glm::vec3 axis) {
    Model = glm::rotate(Model, angle, axis );
}
void SimpleModelObject::translate(glm::vec3 offset) {
    Model = glm::translate(Model, offset);
}

