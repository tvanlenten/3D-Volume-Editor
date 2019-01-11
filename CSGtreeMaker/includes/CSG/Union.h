#pragma once

#include "CSGnode.h"


//#include "Primatives.h" //add header to organize

#include "Sphere.h"
#include "Box.h"
#include "Subtract.h"

class Union : CSGnode {
public:
	Union();
	CSGnodeStatus displayGUI();
	void getCSGtree(std::vector<CSGelement> tree);
	std::string getCSGtree();
	~Union();
private:
	int id;
	std::vector<CSGnode*> args;
	std::string getCSGtreeHelper(int index);
};

