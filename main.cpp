#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include"Camera.h"
#include "stb_image.h" 
#include "Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"
#pragma region Init Function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void TimeToGreen(unsigned int shaderProgram);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLint format, int textureSlot);
#pragma endregion

#pragma region Model Data
/*float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};*/
/*float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};*/
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
unsigned int indices[] = { // ע��������0��ʼ! 
	0, 1, 2, // ��һ��������
	 2, 3,0  // �ڶ���������
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

#pragma endregion

#pragma region Camera Declare
//Camera camera(glm::vec3(0,0,3.0f),glm::vec3(0,0.0f,0),glm::vec3(0,1.0f,0));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion


#pragma region Light Declare
LightDirectional lightD = LightDirectional(glm::vec3(1.0f,1.0f,-1.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(0.2f,0.2f,0.2f));
LightPoint lightP1 = LightPoint(glm::vec3(0.0f,0.0f,-3.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(1.0f,0.0f,0.0f));
LightPoint lightP2 = LightPoint(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(0.0f,1.0f,0.0f));
LightPoint lightP3 = LightPoint(glm::vec3(0.0f,-3.0f,0.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(0.0f,0.0f,1.0f));
LightPoint lightP4 = LightPoint(glm::vec3(0.0f,3.0f,0.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0),glm::vec3(0.0f,0.0f,0.1f));
LightSpot lightS = LightSpot(glm::vec3(0.0f,3.0f,-2.0f),glm::vec3(glm::radians(90.0f),0,0),glm::vec3(1.0f,1.0f,1.0f));
#pragma endregion


#pragma region Input Declare
bool firstMouse = true;
float lastX;
float lastY;
#pragma endregion
int main()
{
	#pragma region Open a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);MacOSXϵͳ������һ��
	//�����ǳ�ʼ��Glfw��˵������Ҫʹ�õ�OPENGL�汾��3.3������ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)����ȷ����GLFW������Ҫʹ�ú���ģʽ��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ���

	GLFWwindow* window = glfwCreateWindow(800, 600, "DogFish2.0", NULL, NULL);//ǰ���������������ɴ��ڴ�С
	if (window == NULL)
	{
		std::cout << "GLFW���ڳ�ʼ��ʧ��" << std::endl;
		glfwTerminate();//������ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	//GLFW��ʼ��
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW��ʼ��ʧ��" << std::endl;
		return -1;
	}
	//Glew�ĳ�ʼ��
	glViewport(0, 0, 800, 600);//��Ⱦ���ڴ�С
	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//��̬�������ڴ�С

    #pragma endregion

	#pragma region Init Shader Program
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion
#pragma region Init Material
	Material* myMaterial = new Material(myShader,
		LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, 0),
		LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, 1),
		LoadImageToGPU("matrix.jpg", GL_RGB, GL_RGB, 2),
		glm::vec3(0.0f, 0.0f, 0.0f),
		64.0f);
#pragma endregion


	#pragma region Init and Load Model to VAO VBO
 	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//�������ݰ�
	unsigned int VBO;
	glGenBuffers(1, &VBO);//һ������ID����һ��VBO���������㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�´����Ļ���󶨵�GL_ARRAY_BUFFERĿ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�����֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
	
	unsigned EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ����
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*(sizeof(float))));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * (sizeof(float))));
	glEnableVertexAttribArray(2);
	/*glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * (sizeof(float))));
	glEnableVertexAttribArray(4);*/
	stbi_set_flip_vertically_on_load(true);

#pragma endregion

#pragma region Init and Load Texture
	/*unsigned int TexBufferA;
	TexBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
	unsigned int TexBufferB;
	TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);*/
#pragma endregion
	


	myShader->use();
	/*glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);*/

	
	//glm::mat4 trans;
	glm::mat4 viewMat;
	glm::mat4 modelMat;
	glm::mat4 proMat;
	modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	proMat = glm::perspective(glm::radians(45.0f), 800.0f/ 600.0f, 0.1f, 100.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 0, 0));
	while (!glfwWindowShouldClose(window))
	{
		/*trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(0.1f, 1, 1));*/
		//trans = glm::translate(trans, glm::vec3(0.001f, 0, 0));

		//����
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//�����������Ļ���õ���ɫ,��ʾ��������ɫ
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�����ɫ����֮��
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
		glActiveTexture(GL_TEXTURE0+1);
		glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
		glActiveTexture(GL_TEXTURE0+2);
		glBindTexture(GL_TEXTURE_2D, myMaterial->emission);
		//TimeToGreen(shaderProgram);
		
		
		glBindVertexArray(VAO); 
		 
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(EBO);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 modelMat2;
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);
			float angle = 20.0f * i;
			//modelMat2 = glm::rotate(modelMat2, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glBindVertexArray(EBO);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		myShader->use();
		viewMat = camera.GetViewMatrix();
		//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));
		//glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.05f, 0.05f, 0.05f);

		/*myShader->SetUniform3f("lightPos", light.position);
		myShader->SetUniform3f("lightColor", light.color);
		myShader->SetUniform3f("lightDirUniform", light.direction);*/
		myShader->SetUniform3f("lightD.pos", lightD.position);
		myShader->SetUniform3f("lightD.color", lightD.color);
		myShader->SetUniform3f("lightD.dirToLight", lightD.direction);

		myShader->SetUniform3f("lightP1.pos", lightP1.position);
		myShader->SetUniform3f("lightP1.color", lightP1.color);
		//myShader->SetUniform3f("lightP1.dirToLight", lightP1.direction);
		myShader->SetUniform1f("lightP1.constant", lightP1.constant);
		myShader->SetUniform1f("lightP1.linear", lightP1.linear);
		myShader->SetUniform1f("lightP1.quadratic", lightP1.quadratic);

		myShader->SetUniform3f("lightP2.pos", lightP2.position);
		myShader->SetUniform3f("lightP2.color", lightP2.color);
		myShader->SetUniform1f("lightP2.constant", lightP2.constant);
		myShader->SetUniform1f("lightP2.linear", lightP2.linear);
		myShader->SetUniform1f("lightP2.quadratic", lightP2.quadratic);

		myShader->SetUniform3f("lightP3.pos", lightP3.position);
		myShader->SetUniform3f("lightP3.color", lightP3.color);
		myShader->SetUniform1f("lightP3.constant", lightP3.constant);
		myShader->SetUniform1f("lightP3.linear", lightP3.linear);
		myShader->SetUniform1f("lightP3.quadratic", lightP3.quadratic);

		myShader->SetUniform3f("lightP4.pos", lightP4.position);
		myShader->SetUniform3f("lightP4.color", lightP4.color);
		myShader->SetUniform1f("lightP4.constant", lightP4.constant);
		myShader->SetUniform1f("lightP4.linear", lightP4.linear);
		myShader->SetUniform1f("lightP4.quadratic", lightP4.quadratic);
		
		myShader->SetUniform3f("lightS.pos", lightS.position);
		myShader->SetUniform3f("lightS.color", lightS.color);
		myShader->SetUniform3f("lightS.dirToLight", lightS.direction);
		myShader->SetUniform1f("lightS.constant", lightS.constant);
		myShader->SetUniform1f("lightS.linear", lightS.linear);
		myShader->SetUniform1f("lightS.quadratic", lightS.quadratic);
		myShader->SetUniform1f("lightS.cosPhyInner", lightS.cosPhyInner);
		myShader->SetUniform1f("lightS.cosPhyOutter", lightS.cosPhyOutter);
	


		/*glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), 10.0f, 10.0f, -5.0f);
		glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);*/
		glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x,camera.Position.y, camera.Position.z);
		myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
		myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
		myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
		myMaterial->shader->SetUniform1i("material.emission", Shader::EMISSION);
		myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);//����vaoû�е�
		//��鲢�����¼�����������
		glfwSwapBuffers(window);//������Ļ����
		glfwPollEvents();//��麯����û�д����¼�
		camera.updateCameraPos();
	}
	glfwTerminate();

	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	//����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = 0.0f;
	}if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else {
		camera.speedY = 0.0f;
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) // ���bool������ʼʱ���趨Ϊtrue��
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xoffset = lastX- xpos ;
	float yoffset =  ypos-lastY; // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
	lastX = xpos;
	lastY = ypos;
	if (glfwGetMouseButton(window, 0) == GLFW_PRESS) {
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}
unsigned int LoadImageToGPU(const char* filename,GLint internalFormat,GLint format,int textureSlot) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0+textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, nrChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}

void TimeToGreen(unsigned int shaderProgram)
{//��ʱ��仯����ɫ
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}