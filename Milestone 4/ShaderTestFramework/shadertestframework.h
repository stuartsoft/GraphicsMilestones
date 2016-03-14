#pragma once

/**
 * This is the class declaration for the main window of this framework.
 *
 * Code in this file should not require editing.
 * 
 * Cory D. Boatright
 * Feb. 11, 2016
 * COMP 361
 */

#include <QtWidgets/QMainWindow>
#include "ui_shadertestframework.h"

class ShaderTestFramework : public QMainWindow
{
	Q_OBJECT

public:
	ShaderTestFramework(QWidget *parent = 0);
	~ShaderTestFramework();

public slots:
	void updateShaders(void);
	void loadShaders(void);
	void saveShaders(void);

private:
	Ui::ShaderTestFrameworkClass ui;
};