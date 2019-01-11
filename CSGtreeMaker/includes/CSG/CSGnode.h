#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <String>

#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_impl_glfw.h"
#include "..\ImGui\imgui_impl_opengl3.h"

enum CSGnodeStatus {
	CSG_NODE_STATUS_NONE,
	CSG_NDOE_STATUS_REMOVE,
};

//used in shader to create CSG tree
struct CSGelement {
	glm::vec4 param0;
	glm::vec4 param1;
	glm::vec3 position;
	float radius;
};

class CSGnode {
public:
	virtual CSGnodeStatus displayGUI() = 0;
	virtual void getCSGtree(std::vector<CSGelement> tree) = 0;
	virtual std::string getCSGtree() = 0;
private:
	int id;
};