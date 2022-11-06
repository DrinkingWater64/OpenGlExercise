#include<glad/glad.h>
#include<glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// vertex shader code
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
// fragment shader code
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";
// fragment shader code 2
const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.97f, 0.0f, 1.0f);\n"
	"}\n\0";



int main() {


	// glfw: inintialization
	glfwInit();
	// Configureation of openGL version and set core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	


	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(800, 800, "wow a window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to make a window \n";
		glfwTerminate();
		return 1;
	}
	
	// set the current context
	glfwMakeContextCurrent(window);
	// callback function for resized window width height
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad for loading all the openGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to load glad \n";
		return 1;
	}
	
	//build and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// check for error 
	GLint success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR compiling Vertex shader\n" << infolog << std::endl;
	}

	// build and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// check for error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR compiling Fragment shader\n" << infolog << std::endl;
	}

	//build and compile 2nd fragment shader
	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	// check for error
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infolog);
		std::cout << "ERROR compiling Fragment shader2\n" << infolog << std::endl;
	}

	
	// link shader
	GLuint shaderprogram = glCreateProgram();
	GLuint shaderprogram2 = glCreateProgram();
	
	//link shader orrange
	glAttachShader(shaderprogram, vertexShader);
	glAttachShader(shaderprogram, fragmentShader);
	glLinkProgram(shaderprogram);

	//linkn shader 2 or yellow
	glAttachShader(shaderprogram2, vertexShader);
	glAttachShader(shaderprogram2, fragmentShader2);
	glLinkProgram(shaderprogram2);
	
	// link error
	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success)	
	{
		glGetProgramInfoLog(shaderprogram, 512, NULL, infolog);
		std::cout << "ERROR linking shader\n" << infolog << std::endl;

	}
	// link error for shader 2
	glGetProgramiv(shaderprogram2, GL_LINK_STATUS, &success);
	if (!success)	
	{
		glGetProgramInfoLog(shaderprogram, 512, NULL, infolog);
		std::cout << "ERROR linking shader 2\n" << infolog << std::endl;

	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	// set up vertex data 9 and buffers and configure vertex attributes
	
	GLfloat triangel1[] =
	{
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f  // top
	};

	GLfloat triangel2[] = 
	{
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};

	// creating buffer objects
	GLuint VAO[2];
	GLuint VBO[2];

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	// bind the vertex array first, then bind and set vertex buffer(s),
	// and then configure vertex atrributes
	// 
	// 
	//First triangle setup
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangel1), triangel1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	//Second Triangle setup
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangel2), triangel2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);  // because the vertex data is tightly packed we can 
																   // also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	



	// the call to glVertexAttribPointer registered vbo as the vertex attribute's bound vertex buffer object
	// so afterward we can safely unbind 
	// glBindBuffer(GL_ARRAY_BUFFER, 0);  // no need to bind as in the second triangle we set it directly
	
	// the VAO can be unbounded afterwards so other VAO calls won't accidentally modifty this
	// VAO. Modifying other VAOs require a call to goBindVertexArray.
	// glBindVertexArray(0);






	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// render window pixels
		glClearColor(.6f, .7f, .8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// draw triangle

		// use first shader to draw first triangle 
		glUseProgram(shaderprogram);

			// first triangle
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// use second shader to draw to second triangle
		glUseProgram(shaderprogram2);
		// second triangle
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);




		//swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
		

		// input
		process_input(window);
	}


	// de allocate all resources once they are no longer necessery
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderprogram);

	// terminate glfw and clear all allocated resources
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
