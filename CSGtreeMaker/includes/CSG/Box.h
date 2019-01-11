#pragma once

#include "CSGnode.h"

class Box : CSGnode {
public:
	Box();
	CSGnodeStatus displayGUI();
	void getCSGtree(std::vector<CSGelement> tree);
	std::string getCSGtree();
private:
	int id;
	glm::vec3 position;
	glm::vec3 dim;
};

