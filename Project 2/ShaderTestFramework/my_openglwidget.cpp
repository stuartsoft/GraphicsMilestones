/**
 * This is the implementation file for the promoted OpenGL widget in Qt 5.5.
 *
 * This is a starting framework for making an interactive shader-editor program.
 * Sections of this code will need to be completed by the students during class.
 * A "default" shader is loaded in as the initial and backup shader programs, but
 * the user can modify the programs through the interface and update the shaders.
 * If there is an error in the user's submitted shaders the program reverts to the
 * default.
 *
 * Note that the introduction of new attributes/uniforms into a shader program requires
 * included support in the C++ code itself, for instance adding texture coordinates
 * in the shader will not automatically create texture coordinates for geometry.
 * 
 * 
 * Cory D. Boatright
 * Feb. 11, 2016
 * COMP 361
 */

#include "my_openglwidget.h"
#include <QMessageBox>
#include "glm\gtx\transform.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat4;

My_OpenGLWidget::My_OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
	vertexShader = nullptr;
	fragmentShader = nullptr;
	shaderProgram = nullptr;
	backupVert = nullptr;
	backupFrag = nullptr;
	backupShaders = nullptr;
	leftAngle = 0.0f;
	downAngle = 0.0f;

	/**** Any additional attributes and/or uniforms should be initialized here *******/
	vLocation = 0;
	vNormal = 0;
	cLocation = 0;
	modelMatrixLocation = 0;
	viewMatrixLocation;

	
	vbo = 0;
	vbo2 = 0;
	vbo3 = 0;
	cbo = 0;
}

My_OpenGLWidget::~My_OpenGLWidget() {
	makeCurrent();		//this makeCurrent() function seems to be necessary to ensure that the rendering context is being accessed?
						//this is new to recent versions of Qt's OpenGL support
	delete vertexShader;
	delete fragmentShader;
	delete shaderProgram;
	delete backupShaders;
	delete backupVert;
	delete backupFrag;
}

void My_OpenGLWidget::initializeGL() {
	//boilerplate
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	//setup shader resources
	backupVert = new QOpenGLShader(QOpenGLShader::Vertex, this);
	backupFrag = new QOpenGLShader(QOpenGLShader::Fragment, this);
	backupShaders = new QOpenGLShaderProgram(this);

	//load and compile shaders
	backupVert->compileSourceFile("super_simple.vert");
	backupFrag->compileSourceFile("super_simple.frag");

	//attach and link shaders
	backupShaders->addShader(backupVert);
	backupShaders->addShader(backupFrag);
	backupShaders->link();

	//get the attribute locations -- IF NEW ATTRIBUTES/UNIFORMS ARE ADDED, INCLUDE THEM HERE
	vLocation = backupShaders->attributeLocation("vs_position");
	vNormal = backupShaders->attributeLocation("vs_normal");
	vShiny = backupShaders->attributeLocation("vs_shinyness");
	cLocation = backupShaders->attributeLocation("vs_color");

	//active the shader program
	backupShaders->bind();

	//also generate the buffer resources -- IF NEW BUFFERS ARE NEEDED, GENERATE THEM HERE
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &cbo);

	//create the geometry
	generateGeometry();

	//create the camera settings
	createCamera();
}

void My_OpenGLWidget::generateGeometry() {
	//if new attributes are added, make sure their data is created
	sg = new SceneGraph();
	sg->Parse("scene1.txt");

}

void My_OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/************* If new attributes/uniforms are added, make sure they are set up here *********/
	mat4 modelMatrix = glm::rotate(glm::rotate(downAngle, vec3(1.0f, 0.0f, 0.0f)), leftAngle, vec3(0.0f, 1.0f, 0.0f));
	mat4 projMatrix = projectionMatrix * cameraMatrix;

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &projMatrix[0][0]);
	glUniform4f(camVecLocation,camLocation.x, camLocation.y, camLocation.z, 1.0f);

	sg->traverse(cameraMatrix * modelMatrix);//traverse the scene graph
	sg->draw(vLocation, vNormal, vShiny, cLocation, vbo, vbo2, vbo3, cbo);

}

void My_OpenGLWidget::createCamera() {
	camLocation = vec4(0.0f, 0.0f, 3.0f, 1.0f);
	up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	focus = vec4(0.0, 0.0, 0.0, 1.0f);

	//create the three basis vectors
	vec4 n = glm::normalize(focus - camLocation);
	vec4 u = vec4(glm::cross(vec3(up.x, up.y, up.z), vec3(n.x, n.y, n.z)), 0.0f);
	vec4 v = vec4(glm::cross(vec3(n.x, n.y, n.z), vec3(u.x, u.y, u.z)), 0.0f);

	mat4 cameraRotation(vec4(u.x, v.x, n.x, 0.0f), vec4(u.y, v.y, n.y, 0.0f), vec4(u.z, v.z, n.z, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	mat4 cameraTranslation = glm::translate(vec3(-camLocation.x, -camLocation.y, -camLocation.z));

	cameraMatrix = cameraTranslation * cameraRotation;
}

void My_OpenGLWidget::rotateDown() {
	makeCurrent();
	downAngle += 0.25f;
	repaint();
}

void My_OpenGLWidget::rotateLeft() {
	makeCurrent();
	leftAngle += 0.25f;
	repaint();
}

void My_OpenGLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	//top, bottom, near, and far are still ok, aspect ratio is the problem

	float bottom = -1.0f;
	float nearZ = 2.0f;
	float top = nearZ * tan(3.14/8.0f);
	float farZ = -1.0f;
	float right = aspectRatio;
	float left = -aspectRatio;	//near and far had namespace collisions

	//mat4 projectionScale = mat4(vec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f), vec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f), vec4(0.0f, 0.0f, 2.0f / (farZ - nearZ), 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));

	mat4 projectionScale = mat4(vec4((nearZ/right), 0, 0, 0), vec4(0, (nearZ/top), 0,0), vec4(0,0,((-farZ+nearZ)/(farZ-nearZ)),((-2*farZ*nearZ)/(farZ-nearZ))), vec4(0,0,-1, 0));

	//mat4 projectionTranslate = glm::translate(vec3(0.0f, 0.0f, 1.0f));
	//projectionMatrix = projectionScale * projectionTranslate;
	projectionMatrix = projectionScale;
}

bool My_OpenGLWidget::updateVertexShader(QString contents) {
	makeCurrent();
	clearShaders();
	
	vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	bool success = vertexShader->compileSourceCode(contents);

	if(!success) {
		backupShaders->bind();	//revert to backup shaders
		QMessageBox::critical(this, "Vertex Shader Compilation Failed", vertexShader->log());
		return false;
	}
	else {
		return true;
	}
}

bool My_OpenGLWidget::updateFragmentShader(QString contents) {
	makeCurrent();
	fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	bool success = fragmentShader->compileSourceCode(contents);

	if(!success) {
		backupShaders->bind();
		QMessageBox::critical(this, "Fragment Shader Compilation Failed", fragmentShader->log());
		return false;
	}
	else {
		return true;
	}
}

void My_OpenGLWidget::updateShaderProgram() {
	makeCurrent();
	shaderProgram = new QOpenGLShaderProgram(this);
	shaderProgram->addShader(vertexShader);
	shaderProgram->addShader(fragmentShader);

	bool success = shaderProgram->link();
	bool success2;
	if(!success) {
		vLocation = backupShaders->attributeLocation("vs_position");
		vNormal = backupShaders->attributeLocation("vs_normal");
		vShiny = backupShaders->attributeLocation("vs_shinyness");
		cLocation = backupShaders->attributeLocation("vs_color");
		backupShaders->bind();
		
		QMessageBox::critical(this, "Shader Linking Failed", shaderProgram->log());
	}
	else {
		/******** NOTE: this section must be updated when adding new uniforms and attributes **************/
		vLocation = shaderProgram->attributeLocation("vs_position");
		vNormal = shaderProgram->attributeLocation("vs_normal");
		vShiny = shaderProgram->attributeLocation("vs_shinyness");
		cLocation = shaderProgram->attributeLocation("vs_color");
		modelMatrixLocation = shaderProgram->uniformLocation("u_modelMatrix");
		viewMatrixLocation = shaderProgram->uniformLocation("u_viewMatrix");
		camVecLocation = shaderProgram->uniformLocation("u_camVecLocation");
		success2 = shaderProgram->bind();
	}
	repaint();
}

void My_OpenGLWidget::clearShaders() {
	//dismantle the shaders "properly" just to be sure
	if(shaderProgram) {
		shaderProgram->removeAllShaders();
		delete shaderProgram;
		shaderProgram = nullptr;
	}
	if(vertexShader) {
		delete vertexShader;
		vertexShader = nullptr;
	}
	if(fragmentShader) {
		delete fragmentShader;
		fragmentShader = nullptr;
	}
}