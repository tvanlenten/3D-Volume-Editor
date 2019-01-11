#pragma once

#include "CSGnode.h"

#include "Sphere.h"
#include "Box.h"
#include "Union.h"

class Subtract : CSGnode {
public:
	Subtract();
	CSGnodeStatus displayGUI();
	void getCSGtree(std::vector<CSGelement> tree);
	std::string getCSGtree();
	~Subtract();
private:
	int id;
	std::vector<CSGnode*> args;
	bool isValid;
};

