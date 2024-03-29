#include "UEngine.h"
#include <QtWidgets/QApplication>

#include <qfile.h>
#include <qtextstream.h>
#include <UGM/UGM>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// load style sheet
	QFile f(":qdarkstyle/Resources/style.qss");
	if (f.exists()){
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}
	else
		printf("Unable to set stylesheet, file not found\n");

	UEngine w;
	w.show();
	return a.exec();

	//using namespace Ubpa;
	//vecf3 v(1, 1, 1);
	//std::cout << v.norm();
}
