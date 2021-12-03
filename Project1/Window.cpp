#include "Window.h"
#include "Sphere.h"
#include "Shader.h"
#include "Camera.h"
#include "Engine.h"
#include "SkyBox.h"
#include "PointLight.h"
uint32_t Window::width = 0;
uint32_t Window::height = 0;
GLFWwindow* Window::InitWindow()
{
	// glfw: 初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mWindowCreateInfo.majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mWindowCreateInfo.minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);
	// glfw 创建窗口
	mWindowHandle = glfwCreateWindow(mWindowCreateInfo.width, mWindowCreateInfo.height, mWindowCreateInfo.title.c_str(), NULL, NULL);
	if (mWindowHandle == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(mWindowHandle);
	glfwSetFramebufferSizeCallback(mWindowHandle,&Window::resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	return mWindowHandle;
}

void Window::resize(GLFWwindow* window, int width, int height)
{
	Window::width = static_cast<uint32_t>(width);
	Window::height = static_cast<uint32_t>(height);
	glViewport(0, 0, width, height);
}

void Window::setClearColor(double r, double g, double b, double a)
{
	mClearColor[0] = r;
	mClearColor[1] = g;
	mClearColor[2] = b;
	mClearColor[3] = a;
}

void Window::run()
{
	static double t = 0.0;
	Engine *engine=Engine::GetEngineInstance();
	SceneNode *sphereNode= Sphere::getASphereNode(glm::dvec3(0.0, 0.0, 0.0), 0.4, 100, 100);
	Camera *camera=new Camera;
	camera->lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SkyBox *skyBox = new SkyBox("Resources/skybox.jpg");

	engine->scene()->setSkyBox(skyBox);
	engine->scene()->appendChild(sphereNode);
	engine->scene()->setCamera(camera);




	while (!glfwWindowShouldClose(mWindowHandle))
	{
		glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW);
		//glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		camera->perspective(glm::radians(50.0f), (double)Window::width / (double)Window::height, 0.1, 10);

		//camera.ortho(-(double)Window::width / (double)Window::height, (double)Window::width / (double)Window::height, -1, 1, 0, 10);
		camera->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);
		//camera->rotateRoundTarget(glm::vec3(1.0, 0.0, 0.0), 0.01);
		//sphereNode->rotate(glm::vec3(1.0, 1.0, 1.0), 0.01);

		//sphereNode->setMaterial(engine->getShader("displayNormal"));
		//camera->renderScene();

		sphereNode->setMaterial(engine->getShader("default"));
		camera->renderScene();

		glfwSwapBuffers(mWindowHandle);
		glfwPollEvents();
		t += 0.05;
	}
	glfwTerminate();
}

Window::Window(const WindowCreateInfo &createInfo) :
	mClearColor(0.0, 0.0, 0.0, 0.0)
{

	Window::width = (createInfo.width);
	Window::height = (createInfo.height);
	mWindowCreateInfo = createInfo;
	InitWindow();
}


GLFWwindow* Window::GetWindowHandle()
{
	return mWindowHandle;
}