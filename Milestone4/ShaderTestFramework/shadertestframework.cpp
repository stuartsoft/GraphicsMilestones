#include "shadertestframework.h"

/**
 * This is the implementation for the main window of this framework.
 *
 * Code in this file should not require editing.
 * 
 * Cory D. Boatright
 * Feb. 11, 2016
 * COMP 361
 */

#include <QFileDialog>
#include <QFile>

ShaderTestFramework::ShaderTestFramework(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ShaderTestFramework::~ShaderTestFramework()
{

}

void ShaderTestFramework::updateShaders() {
	if(ui.graphicDisplay->updateVertexShader(ui.vertText->toPlainText())) {
		if(ui.graphicDisplay->updateFragmentShader(ui.fragText->toPlainText())) {
			ui.graphicDisplay->updateShaderProgram();
		}
	}	
}

void ShaderTestFramework::loadShaders() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Shaders"), QDir::currentPath(), tr("Shaders (*.frag *.vert)"));
	if(filename != "") {
		filename = filename.split(".")[0];	//split off the stem
		//load vertex shader to vertex text box
		QFile vertShader(filename + ".vert");
		if(!vertShader.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return;	//should probably give an error message
		}
		QString vertContents = vertShader.readAll();

		//load fragment shader to fragment text box
		QFile fragShader(filename + ".frag");
		if(!fragShader.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return; //as above
		}
		QString fragContents = fragShader.readAll();

		ui.vertText->setPlainText(vertContents);
		ui.fragText->setPlainText(fragContents);

		vertShader.close();
		fragShader.close();
	}
}

void ShaderTestFramework::saveShaders() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), QDir::currentPath(), tr("Shaders (*.frag *.vert)"));// tr("Shaders (*.frag *.vert)"));
	if(filename != "") {
		filename = filename.split(".")[0];	//in case something tried to add an extension

		//save the vertex shader
		QFile vertShader(filename + ".vert");
		if(!vertShader.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly)) {
			return;	//still should have an error message
		}

		QString vertContents = ui.vertText->toPlainText();

		vertShader.write(vertContents.toStdString().c_str());

		vertShader.close();
		//save the fragment shader
		QFile fragShader(filename + ".frag");
		if(!fragShader.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly)) {
			return;	//still should have an error message
		}

		QString fragContents = ui.fragText->toPlainText();

		fragShader.write(fragContents.toStdString().c_str());

		fragShader.close();
	}
}