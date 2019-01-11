#include "Subtract.h"

Subtract::Subtract() {
	id = rand() % 99999;
	args = std::vector<CSGnode*>();
}

CSGnodeStatus Subtract::displayGUI() {
	char treeTag[32], removeTag[32], addTag[32], popUpTag[32];
	snprintf(treeTag, 32, "Subtract###tree%d", id);
	snprintf(removeTag, 32, "Remove###remove%d", id);
	snprintf(addTag, 32, "Add###add%d", id);
	snprintf(popUpTag, 32, "Popup###popup%d", id);
	static int selected_node = -1;
	const char* names[] = { "Sphere", "Box", "Union", "Subtract"};


	if (ImGui::TreeNode(treeTag)) {
		if (args.size() <= 1) {
			if (ImGui::Button(addTag)) {
				ImGui::OpenPopup(popUpTag);
			}
			ImGui::SameLine();
		}
		if (ImGui::Button(removeTag)) {
			ImGui::TreePop();
			return CSG_NDOE_STATUS_REMOVE;
		}

		if (ImGui::BeginPopup(popUpTag)) {
			ImGui::Text("Options");
			ImGui::Separator();
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
					selected_node = i;
			ImGui::EndPopup();
		}
		if (selected_node != -1) {
			CSGnode* node;
			switch (selected_node) {
			case 0:
				node = (CSGnode*)new Sphere();
				break;
			case 1:
				node = (CSGnode*)new Box();
				break;
			case 2:
				node = (CSGnode*)new Union();
				break;
			case 3:
				node = (CSGnode*)new Subtract();
				break;
			default:
				node = (CSGnode*)new Sphere();
				break;
			}
			args.push_back(node);
			selected_node = -1;
		}
		for (int i = 0; i < args.size(); i++) {
			CSGnode* node = args[i];
			CSGnodeStatus s = node->displayGUI();
			if (s == CSG_NDOE_STATUS_REMOVE) {
				delete node;
				args.erase(args.begin() + i);
			}
		}

		ImGui::TreePop();
	}


	return CSG_NODE_STATUS_NONE;
}
void Subtract::getCSGtree(std::vector<CSGelement> tree) {

}

std::string Subtract::getCSGtree() {
	std::string str = "S(";
	std::string arg1 = (args.size() > 0)? args[0]->getCSGtree() : "0.0";
	std::string arg2 = (args.size() > 1) ? args[1]->getCSGtree() : "0.0";
	str = str + arg1 + "," + arg2 + ")";
	return str;
}

Subtract::~Subtract() {
	for (int i = 0; i < args.size(); i++) {
		delete args[i];
	}
	args.clear();
}

