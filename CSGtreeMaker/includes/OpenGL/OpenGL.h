#ifndef OPENGL_H_
#define OPENGL_H_

#include "Control.h"
#include "Camera.h"
#include "Mesh.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "FrameBuffer.h"

/*
	By Tyler Van Lenten
	This is a basic OpenGL and GLEW framework.  It is mainly tailored for
	Volume rendering and Ray Casting.  It has support for simple meshes and all
	GLSL shader types including Vertex, Fragment, Gemotry, and Compute shaders.
	It also has easy to create and use Buffers, Textures, and FrameBuffers.

	A simple GUI is also included which supports Sliders, Text, and Buttons.
	last updated: 1/04/19

	Things Supported
	-FBOs(FrameBuffers)
	-buffers of all types
	-Mesh(VAO w/ extra features)
	-GUI(simple GUI with Sliders, Text, and Buttons)
	-support for all 4 types of shaders(Vertex, Fragment, Gemotry, and Compute)
	-Has a standard 3D camera that can also be used for ray casting
	-Also has support for keyboard, mouse movement, mouse buttons, and mouse scroll

	TO DO:
	-Textures report if loading failed
	-Textures auto flip
	-GLFW multi window support
	-Buffer maps and ranges
	-Objects (Mesh, Shaders, Textures, and Buffers combined with a init(), update(), and draw() method)
*/

//EXAMPLE PROGRAM//
/*
	#include "OpenGL\OpenGL.h"
	#define width 1920
	#define height 1080

	int main() {
		Control control(width, height, "OpenGL Example", true);
		FrameBuffer screen(width, height);
		Camera camera(width, height, glm::vec3(-0.1f, 1.0f, -0.1f), 90.0f, 0.1f, 100.0f, 0.1f, 0.1f);
		Shader shader("shaders/test.vert", "shaders/test.frag", nullptr, false);
	
		Mesh rect;
		rect.createRect2D();

		control.cull(GL_FRONT);
		control.depthTest(true);
		control.showMouse();
		while (!control.shouldQuit()) {
			control.update();
			camera.update(&control);
		
			screen.use();
			screen.clear();
			rect.draw();

			control.swapBuffers();
		}
		return 0;
	}
*/

#endif //OpenGL.h