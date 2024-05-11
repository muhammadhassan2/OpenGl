#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

const int width = 720;
const int height = 720;

int main()
{
	glfwInit();
	// first step define the opengl version used
	// 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] = {
		-0.5f ,-0.0f * float(sqrt(3)) / 3,.0f,
		0.5f ,-0.5f * float(sqrt(3)) / 3,.0f,
		0.0f ,0.5f * float(sqrt(3)) * 2 / 3,.0f,
		0.4f ,0.5f * float(sqrt(3)) * 2 / 3,.0f
	};

	
	// 
	GLFWwindow* window =  glfwCreateWindow(width, height, "MY_WIndow", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create a window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	///////////////////Handeling Shaders///////////////////////////////
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderprogram;

	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram,vertexShader);
	glAttachShader(shaderprogram, fragmentShader);
	glLinkProgram(shaderprogram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	///////////////////////////////////////////////////////

	GLuint VAO , VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.7f, 0.21f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	//	glfwSwapBuffers(window);
	}

	glDeleteProgram(shaderprogram);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
