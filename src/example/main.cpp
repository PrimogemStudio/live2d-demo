#define GLAD_GL_IMPLEMENTATION
#include <Framework/CubismFramework.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

import Allocator;
import Util;
import Module;

using namespace std;
using namespace Live2D::Cubism::Framework;

static GLFWwindow* window;
static CustomModel* model;

static void Render()
{
	Timer::UpdateTime();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);
	model->ModelOnUpdate(window);
}

static void LoadLive2D()
{
	static CustomAllocator allocator;
	static CubismFramework::Option option;
	CubismFramework::StartUp(&allocator, &option);
	CubismFramework::Initialize();
	model = new CustomModel("草神", "C:/Users/Hacker/Downloads/nahida/nahida/草神/");
	model->SetupModel();
}

static double x;
static double y;

void OnMouseCallBack(GLFWwindow* window, int button, int action, int modify) {
	if (GLFW_RELEASE == action) {
		cout << model->HitTest(Constants::HitAreaNameBody, x, y) << endl;
		cout << model->HitTest(Constants::HitAreaNameHead, x, y) << endl;
		if (model->ModelJson->GetMotionCount(Constants::MotionGroupIdle) != 0) model->StartMotion(Constants::MotionGroupIdle, rand() % model->ModelJson->GetMotionCount(Constants::MotionGroupIdle), Constants::PriorityNormal);
	}
}
void OnCursorCallBack(GLFWwindow* window, double x, double y) {
	::x = x;
	::y = y;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1280, 720, "Live2D OpenGL Demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, const int width, const int height) { glViewport(0, 0, width, height); });

	glfwSetMouseButtonCallback(window, ::OnMouseCallBack);
	glfwSetCursorPosCallback(window, ::OnCursorCallBack);

	LoadLive2D();
	while (!glfwWindowShouldClose(window))
	{
		Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete model;
	CubismFramework::Dispose();
	CubismFramework::CleanUp();
	glfwTerminate();
	return 0;
}
