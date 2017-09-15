#pragma once

#include <QColor>
#include <QWidget>
#include <QtPdfium/QtPdfiumDepends>

class QPdfiumDemo;
class CPdfDisplayWnd : public QWidget
{
	Q_OBJECT

public:
	CPdfDisplayWnd(QWidget *parent = Q_NULLPTR);
	~CPdfDisplayWnd();

	void DisplayPDFFile(const QString& strPDFFileName, QPdfiumDemo* pParent);

	void SetAutoScale(bool blScale);

protected:
	void paintEvent(QPaintEvent *event);
	void GetPDFTotalSize(QPdfium& pdf,qreal& height,qreal& width);
	QSize	sizeHint() const;
	void resizeEvent(QResizeEvent *event);

	void GenDisplayImage(QPdfium* pPdfium,QPdfiumDemo*pParentWnd);


private:
	QPdfiumDemo* m_pParentWnd;
	QImage* m_pImagePDF;
	qreal m_totalHeight;
	qreal m_totalWidth;

	bool m_blAutoScal;
	qreal m_fScaleRatio;

	QPdfium* m_pPdfiumObj;

};
