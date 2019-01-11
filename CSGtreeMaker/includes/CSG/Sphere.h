#pragma once

#include "CSGnode.h"

class Sphere : CSGnode {
public:
	CSGnodeStatus displayGUI();
	void getCSGtree(std::vector<CSGelement> tree);
	std::string getCSGtree();
	Sphere();
private:
	glm::vec3 position;
	float radius;
	int id;
};

