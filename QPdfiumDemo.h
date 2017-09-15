#pragma once

#include <QScrollArea>
#include <QtWidgets/QDialog>
#include "ui_QPdfiumDemo.h"
#include "pdfDisplayWnd.h"

class QPdfiumDemo : public QDialog
{
	Q_OBJECT

public:
	QPdfiumDemo(QWidget *parent = Q_NULLPTR);
	void SetPDFPageCount(int nCn);

protected:
	void Init();
	void resizeEvent(QResizeEvent * event);

	void SetFileNameInfo(const QString& strFileName);


protected slots:

void SlotOpenPdfFile();

void SlotAutoScalChecked(bool checked);

private:
	Ui::QPdfiumDemoClass ui;
	QScrollArea* m_pSA;

};
