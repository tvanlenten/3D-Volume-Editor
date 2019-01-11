#include "Box.h"



Box::Box() {
	id = rand() % 99999;
	position = glm::vec3(0.0);
	dim = glm::vec3(0.0);
}

CSGnodeStatus Box::displayGUI() {
	char tree[32], remove[32], xTag[32], yTag[32], zTag[32], 
		dxTag[32], dyTag[32], dzTag[32], stepTag[32];
	snprintf(tree, 32, "Box###tree%d", id);
	snprintf(remove, 32, "Remove###remove%d", id);
	snprintf(xTag, 32, "X###x%d", id);
	snprintf(yTag, 32, "Y###y%d", id);
	snprintf(zTag, 32, "Z###z%d", id);
	snprintf(dxTag, 32, "X Side###dx%d", id);
	snprintf(dyTag, 32, "Y Side###dy%d", id);
	snprintf(dzTag, 32, "Z Side###dz%d", id);
	snprintf(stepTag, 32, "Step Size###stepSize%d", id);
	if (ImGui::TreeNode(tree)) {
		if (ImGui::Button(remove)) {
			ImGui::TreePop();
			return CSG_NDOE_STATUS_REMOVE;
		}
		static float step = 0.5;
		ImGui::PushItemWidth(40);
		ImGui::InputScalar(stepTag, ImGuiDataType_Float, &step);
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(120);
		ImGui::InputScalar(xTag, ImGuiDataType_Float, &position.x, &step);
		ImGui::InputScalar(yTag, ImGuiDataType_Float, &position.y, &step);
		ImGui::InputScalar(zTag, ImGuiDataType_Float, &position.z, &step);
		ImGui::InputScalar(dxTag, ImGuiDataType_Float, &dim.x, &step);
		ImGui::InputScalar(dyTag, ImGuiDataType_Float, &dim.y, &step);
		ImGui::InputScalar(dzTag, ImGuiDataType_Float, &dim.z, &step);
		ImGui::PopItemWidth();
		ImGui::TreePop();
	}

	return CSG_NODE_STATUS_NONE;
}

void Box::getCSGtree(std::vector<CSGelement> tree) {

}

std::string Box::getCSGtree() {
	char* sph = new char[128];
	int s = snprintf(sph, 128, "box(p-vec3(%f,%f,%f),vec3(%f,%f,%f))", position.x, position.y, position.z, dim.x, dim.y, dim.z);
	std::string str = std::string(sph);
	delete[] sph;
	return str;
}
