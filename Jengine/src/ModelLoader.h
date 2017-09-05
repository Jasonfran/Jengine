#pragma once
#include "Mesh.h"
#include "Model.h"
#include <memory>
#include <map>
#include <assimp/scene.h>

class ModelLoader {
	static std::map<std::string, std::shared_ptr<Model>> loadedModels;
	static void processNode(aiNode* node, const aiScene* scene, std::string path);
	static std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene, std::string path);
public:
	static std::shared_ptr<Model> loadModel(std::string path);
};