#include "faustcreator-output.hpp"

using namespace Faust::Internal;

// ------------------------------------------------------------------------------------------------
// SVG_WIDGET
// ------------------------------------------------------------------------------------------------

FaustSvgWidget::FaustSvgWidget() :
    m_svg(new QSvgWidget(this)),
    m_layout(new QBoxLayout(QBoxLayout::LeftToRight, this))
{
    m_layout->addItem(new QSpacerItem(0, 0));
    m_layout->addWidget(m_svg);
    m_layout->addItem(new QSpacerItem(0, 0));
}

FaustSvgWidget::~FaustSvgWidget()
{

}

void FaustSvgWidget::display(QString path)
{
    m_path = path;
    refresh();
}

void FaustSvgWidget::refresh()
{
    QSize size;
    m_svg->load(m_path);
    size = m_svg->sizeHint();
    m_arw = size.width();
    m_arh = size.height();
}

void FaustSvgWidget::resizeEvent(QResizeEvent *ev)
{
    float ar = m_arw/m_arh;
    float evar = (float)ev->size().width()/ev->size().height();
    int wstretch, outstretch;;

    if (evar > ar) {
        m_layout->setDirection(QBoxLayout::LeftToRight);
        wstretch = height() * ar;
        outstretch = (width()-wstretch)/2+0.5;
    } else {
        m_layout->setDirection(QBoxLayout::TopToBottom);
        wstretch = width() * ar;
        outstretch = (height()-wstretch)/2+0.5;
    }
    m_layout->setStretch(0, outstretch);
    m_layout->setStretch(1, wstretch);
    m_layout->setStretch(2, outstretch);
}

// ------------------------------------------------------------------------------------------------
// OUTPUT_PANEL (FOOTER)
// ------------------------------------------------------------------------------------------------

FaustOutputPane::FaustOutputPane() :
    m_widget(new FaustSvgWidget)
{

}

FaustOutputPane::~FaustOutputPane()
{
    delete m_widget;
}

void FaustOutputPane::displaySvg(QString path)
{
    m_widget->display(path);
    m_widget->show();
}

bool FaustOutputPane::canFocus() const
{
    return true;
}

bool FaustOutputPane::canNavigate() const
{
    return true;
}

bool FaustOutputPane::canNext() const
{
    return false;
}

bool FaustOutputPane::canPrevious() const
{
    return false;
}

void FaustOutputPane::clearContents()
{
    m_widget->hide();
}

QString FaustOutputPane::displayName() const
{
    return "Faust Graph";
}

void FaustOutputPane::goToNext()
{

}

void FaustOutputPane::goToPrev()
{

}

bool FaustOutputPane::hasFocus() const
{
    return true;
}

QWidget* FaustOutputPane::outputWidget(QWidget *parent)
{
    if (parent != m_widget->parent())
        m_widget->setParent(parent);
    return m_widget;
}

int FaustOutputPane::priorityInStatusBar() const
{
    return 0;
}

void FaustOutputPane::setFocus()
{

}

QList<QWidget*> FaustOutputPane::toolBarWidgets() const
{
    return QList<QWidget*>();
}

void FaustOutputPane::visibilityChanged(bool visible)
{

}
