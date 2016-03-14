/**
 * This is the main function that starts the application.
 *
 * Code in this file should not require editing.
 * 
 * Cory D. Boatright
 * Feb. 11, 2016
 * COMP 361
 */

#include "shadertestframework.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ShaderTestFramework w;
	w.show();
	return a.exec();
}
