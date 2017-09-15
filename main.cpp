#include "QPdfiumDemo.h"
#include <QDesktopWidget>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setAttribute(Qt::AA_EnableHighDpiScaling);
	QDesktopWidget* pDeskTopWidget = QApplication::desktop();
	QRect rcDesk = pDeskTopWidget->availableGeometry();
	rcDesk.adjust(0, 30, 0, 0);
	QPdfiumDemo w;
	w.resize(QSize(rcDesk.width() * 0.75,rcDesk.height() - 40));
	QRect rcClient = w.frameGeometry();
	rcClient.moveCenter(rcDesk.center());
	w.setGeometry(rcClient);
	w.show();
	return a.exec();
}
