#pragma once
#include <gl/glew.h>
#include <vector>
#include <memory>

class Mesh;
class Model {
public:
	std::vector<std::shared_ptr<Mesh>> meshes;
};