#include "OpenGL\OpenGL.h"

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw.h"
#include "ImGui\imgui_impl_opengl3.h"

#include "CSG\Union.h"

#include "CSG\RayMarchingShaders.h"


#define width 1920
#define height 1080

//#define width 1280
//#define height 720

/*
	TODO:
	upload to GitHub
	add invalid subtraction if not 2 args
	add add above
	add cut, copy, paste
	add root node and/or CSGtree node to act as entry point
	add noise node
	add color/ texture node
	add all primatives
	add all operations
	add unary operations
	add smooth operators
*/

int main() {
	Control control(width, height, "OpenGL GUI", false);
	FrameBuffer screen(width, height);
	Camera camera(width, height, glm::vec3(-1.0f, 1.0f, -1.0f), 90.0f, 0.1f, 100.0f, 0.1f, 0.1f);
	
	Texture tex("textures/t1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);

	
	std::string map = " float map(vec3 p){ return sphere(p, 0.5); }";
	std::string fCode = rayMarchFrag + map;



	//Shader shader("shaders/vertex2D.vert", "shaders/rayMarcher.frag", nullptr, false);
	Shader shader(rayMarchVertex.c_str(), fCode.c_str(), false);
	shader.use();
	shader.setInt("tex", 0);

	Mesh rect;
	rect.createRect2D();

	//Set Up ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 430";
	ImGui_ImplGlfw_InitForOpenGL(control.getWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	bool GUImode = false;
	
	Union u;

	//control.wireframe(true);
	control.hideMouse();
	while (!control.shouldQuit()) {
		control.update();

		if(!GUImode)camera.update(&control);

		if (control.keyPressed(GLFW_KEY_C)) {
			control.hideMouse();
			GUImode = false;
		}
		if (control.keyPressed(GLFW_KEY_G)) {
			control.showMouse();
			GUImode = true;
		}
		
		std::string treeString;
		//DRAW GUI MAIN WINDOW
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("CSG Tree Editor");
		{
			u.displayGUI();
			treeString = u.getCSGtree();
			std::string map0 = "float map(vec3 p){ return ";
			std::string map1 = "; }";
			treeString = map0 + treeString + map1;

			char text[1024 * 16];
			strcpy_s(text, treeString.c_str());
			ImGui::InputTextMultiline("###treeText", text, IM_ARRAYSIZE(text));

			ImGui::Text("Camera Pos: %f, %f, %f", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		}
		ImGui::End();

		////////////SUPER SLOW DYNAMIC SHADER
		std::string map = " float map(vec3 p){ return U(0.0,0.0); }";
		std::string fCode = rayMarchFrag + treeString;

		shader.reCompile(rayMarchVertex.c_str(), fCode.c_str(), false);

		shader.use();
		shader.setInt("tex", 0);
		//////////////////////
		

		screen.use();
		screen.clear();

		//Render scene
		shader.use();
		shader.setVec3("POS", camera.getPosition());
		shader.setVec3("Uplane", camera.getU());
		shader.setVec3("Vplane", camera.getV());
		shader.setVec3("DIR", camera.getDir());
		tex.use(0);
		rect.draw();

		//Render GUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		control.swapBuffers();
	}

	//Destroy ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}
