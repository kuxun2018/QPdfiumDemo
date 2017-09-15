#include "pdfDisplayWnd.h"
#include "QPdfiumDemo.h"


CPdfDisplayWnd::CPdfDisplayWnd(QWidget *parent)
	: QWidget(parent)
{
	m_pImagePDF = NULL;
	m_totalWidth = 0;
	m_totalHeight = 0;
	m_blAutoScal = false;
	m_fScaleRatio = 1.0;
}

CPdfDisplayWnd::~CPdfDisplayWnd()
{

}

void CPdfDisplayWnd::GetPDFTotalSize(QPdfium& pdf, qreal& height, qreal& width)
{
	static qreal pageSpan = 10;
	height = 0;
	width = 0;
	int nPageCn = pdf.pageCount();
	for (int i = 0; i < nPageCn;i++)
	{
		QPdfiumPage pfPage = pdf.page(i);
		width = qMax(width, pfPage.width());
		height += pfPage.height() + pageSpan;
	}
}

void CPdfDisplayWnd::DisplayPDFFile(const QString& strPDFFileName, QPdfiumDemo* pParent)
{
	m_pParentWnd = pParent;
	
	static QPdfium pdfium(strPDFFileName);
	m_pPdfiumObj = &pdfium;
	m_pParentWnd->SetPDFPageCount(pdfium.pageCount());

	this->GenDisplayImage(m_pPdfiumObj, pParent);

}

void CPdfDisplayWnd::GenDisplayImage(QPdfium* pPdfium,QPdfiumDemo*pParentWnd)
{
	qreal totalHeight = 0;
	qreal totalWidth = 0;
	this->GetPDFTotalSize(*pPdfium, totalHeight, totalWidth);

	if (m_blAutoScal)
	{
		m_fScaleRatio = (pParentWnd->size().width() - 20) / totalWidth;
		totalWidth *= m_fScaleRatio;
		totalHeight *= m_fScaleRatio;
	}

	this->setMinimumSize(QSize(totalWidth, totalHeight));

	m_pImagePDF = new QImage(totalWidth, totalHeight, QImage::Format_ARGB32_Premultiplied);
	int nPageCn = pPdfium->pageCount();
	QPainter painter(m_pImagePDF);
	int nPosX = 0;
	int nPosY = 0;
	for (int i = 0; i < nPageCn; i++)
	{
		QPdfiumPage pfPage = pPdfium->page(i);
		painter.drawImage(nPosX, nPosY, pfPage.image(m_fScaleRatio));
		nPosY += pfPage.height();
	}
	update();
}

void CPdfDisplayWnd::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	if (m_pImagePDF != NULL )
	{
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
		painter.drawImage((event->rect().width() - m_pImagePDF->width())/2, 0,*m_pImagePDF);
	}
}

QSize	CPdfDisplayWnd::sizeHint() const
{
	return QSize(m_totalWidth,m_totalHeight);
}

void CPdfDisplayWnd::SetAutoScale(bool blScale)
{
	m_blAutoScal = blScale;
}

void CPdfDisplayWnd::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	if (m_blAutoScal)
	{
		this->GenDisplayImage(m_pPdfiumObj, m_pParentWnd);
	}
}