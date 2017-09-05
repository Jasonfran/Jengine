#include "ModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

std::map<std::string, std::shared_ptr<Model>> ModelLoader::loadedModels;

std::shared_ptr<Model> ModelLoader::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR: ASSIMP: " << importer.GetErrorString() << std::endl;
		return NULL;
	}
	if (loadedModels.count(path)) {
		return loadedModels[path];
	}
	std::shared_ptr<Model> model = std::shared_ptr<Model>(new Model());
	loadedModels[path] = model;
	processNode(scene->mRootNode, scene, path);
	return model;
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene, std::string path) {
	for (GLuint i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		loadedModels[path]->meshes.push_back(processMesh(mesh, scene, path));
	}

	for (GLuint i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene, path);
	}
}

std::shared_ptr<Mesh> ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene, std::string path) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (GLuint i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) // can check if there are texture coordinatee
		{
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f);
		}
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}
	
	std::shared_ptr<Mesh> newMesh = std::shared_ptr<Mesh>(new Mesh());
	newMesh->vertices = vertices;
	newMesh->indices = indices;

	// Set up mesh
	glGenVertexArrays(1, &newMesh->VAO);
	glGenBuffers(1, &newMesh->VBO);
	glGenBuffers(1, &newMesh->EBO);
	glBindVertexArray(newMesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, newMesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, newMesh->vertices.size() * sizeof(Vertex), newMesh->vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, newMesh->indices.size() * sizeof(GLuint), newMesh->indices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);

	return newMesh;
}