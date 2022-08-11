#include "StatusShow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QApplication::setQuitOnLastWindowClosed(false);
	QWidget* parent = new QWidget;
	StatusShow *w = new StatusShow(parent);
	w->show();
	w->activateWindow();
	int ret = a.exec();
	delete parent;
	return ret;
}
