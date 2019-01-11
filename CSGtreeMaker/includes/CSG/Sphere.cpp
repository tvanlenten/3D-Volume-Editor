#include "Sphere.h"

CSGnodeStatus Sphere::displayGUI() {
	char tree[32], remove[32], xTag[32], yTag[32], zTag[32], rTag[32], stepTag[32];
	snprintf(tree, 32, "Sphere###tree%d", id);
	snprintf(remove, 32, "Remove###remove%d", id);
	snprintf(xTag, 32, "X###x%d", id);
	snprintf(yTag, 32, "Y###y%d", id);
	snprintf(zTag, 32, "Z###z%d", id);
	snprintf(rTag, 32, "Radius###r%d", id);
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
		ImGui::InputScalar(rTag, ImGuiDataType_Float, &radius, &step);
		ImGui::PopItemWidth();

		ImGui::TreePop();
	}

	return CSG_NODE_STATUS_NONE;
}

void Sphere::getCSGtree(std::vector<CSGelement> tree) {

}

std::string Sphere::getCSGtree() {
	char* sph = new char[64];
	int s = snprintf(sph, 64, "sphere(p-vec3(%f,%f,%f),%f)", position.x, position.y, position.z, radius);
	std::string str = std::string(sph);
	delete[] sph;
	return str;
}

Sphere::Sphere() {
	position = glm::vec3(0.0);
	radius = 0.0;
	id = rand() % 99999;
}
