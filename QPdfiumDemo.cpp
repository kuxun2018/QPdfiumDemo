#include "QPdfiumDemo.h"
#include "QFileDialog"
#include <QFileInfo>

QPdfiumDemo::QPdfiumDemo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->Init();
}

void QPdfiumDemo::Init()
{
	ui.checkBox->setChecked(false);
	ui.checkBox->setEnabled(false);

	this->SetFileNameInfo("");
	this->SetPDFPageCount(0);

	Qt::WindowFlags wndFlag = this->windowFlags();
	wndFlag &= ~Qt::WindowContextHelpButtonHint;
	wndFlag |= Qt::WindowMinMaxButtonsHint;
	this->setWindowFlags(wndFlag);
	this->setWindowTitle(QStringLiteral("QPDFium 类 Demo"));
	m_pSA = ui.scrollArea;
	m_pSA->setBackgroundRole(QPalette::Dark);
	m_pSA->setWidgetResizable(true);
	m_pSA->setAlignment(Qt::AlignCenter);
	CPdfDisplayWnd* pDisplayWnd = new CPdfDisplayWnd(m_pSA);
	m_pSA->setWidget(pDisplayWnd);
	m_pSA->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
	this->connect(ui.pushButton_sel, SIGNAL(clicked()),this,SLOT(SlotOpenPdfFile()));
	this->connect(ui.checkBox, SIGNAL(clicked(bool)),this,SLOT(SlotAutoScalChecked(bool)));

}

void QPdfiumDemo::SetFileNameInfo(const QString& strFileName)
{
	ui.label_filename->setText(strFileName);
}

void QPdfiumDemo::SetPDFPageCount(int nCn)
{
	ui.label_pagecn->setText(QString::number(nCn));
}

void QPdfiumDemo::resizeEvent(QResizeEvent * event)
{
	QDialog::resizeEvent(event);
}

void QPdfiumDemo::SlotOpenPdfFile()
{
	QString strFileName = QFileDialog::getOpenFileName(NULL, QStringLiteral("请选择PDF文件"), QApplication::applicationDirPath(), tr("Image Files ( *.PDF *.pdf)"));
	if (!strFileName.isEmpty())
	{
		QFileInfo fileInfo(strFileName);
		this->SetFileNameInfo(fileInfo.fileName());
		QWidget* pScrollWidget = m_pSA->widget();
		CPdfDisplayWnd* pDisplayWnd = dynamic_cast<CPdfDisplayWnd *>(pScrollWidget);
		if (NULL != pDisplayWnd)
		{
			pDisplayWnd->DisplayPDFFile(strFileName,this);
		}
	}
}


void QPdfiumDemo::SlotAutoScalChecked(bool checked)
{
	QWidget* pScrollWidget = m_pSA->widget();
	CPdfDisplayWnd* pDisplayWnd = dynamic_cast<CPdfDisplayWnd *>(pScrollWidget);
	if (NULL != pDisplayWnd)
	{
		pDisplayWnd->SetAutoScale(checked);
	}
}