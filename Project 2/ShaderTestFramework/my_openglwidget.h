#pragma once

/**
 * This is the class declaration for the promoted OpenGL widget in Qt 5.5.
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

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include "glm\glm.hpp"
#include "SceneGraph.h"

class My_OpenGLWidget :	public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
	My_OpenGLWidget(QWidget*);
	~My_OpenGLWidget(void);

	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);

	bool updateVertexShader(QString);
	bool updateFragmentShader(QString);
	void updateShaderProgram(void);

public slots:
	void rotateDown(void);
	void rotateLeft(void);

private:

	unsigned int vbo;
	unsigned int vbo2;//normals
	unsigned int vbo3;//shinyness
	unsigned int cbo;

	glm::mat4 cameraMatrix;
	glm::mat4 projectionMatrix;
	glm::vec4 up;
	glm::vec4 focus;
	glm::vec4 camLocation;

	unsigned int vLocation;//RESET
	unsigned int vNormal;//RESET
	unsigned int vShiny;//RESET
	unsigned int cLocation;//RESET
	unsigned int modelMatrixLocation;//RESET
	unsigned int viewMatrixLocation;
	unsigned int camVecLocation;

	float leftAngle;
	float downAngle;

	void generateGeometry(void);
	void createCamera(void);
	void clearShaders(void);

	SceneGraph* sg;

	QOpenGLShader* vertexShader;
	QOpenGLShader* backupVert;
	QOpenGLShader* fragmentShader;
	QOpenGLShader* backupFrag;
	QOpenGLShaderProgram* shaderProgram;
	QOpenGLShaderProgram* backupShaders;
};

