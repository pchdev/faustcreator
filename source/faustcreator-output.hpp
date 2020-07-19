#ifndef FAUSTCREATOR_OUTPUT_HPP
#define FAUSTCREATOR_OUTPUT_HPP

#include <coreplugin/ioutputpane.h>
#include <QtSvg>

namespace Faust {
namespace Internal {

class FaustSvgWidget : public QWidget
{
public:
    FaustSvgWidget();
    ~FaustSvgWidget();

    virtual void resizeEvent(QResizeEvent* ev) override;
    void display(QString path);

private:
    void refresh();
    QString m_path;
    QSvgWidget* m_svg;
    QBoxLayout* m_layout;
    float m_arw;
    float m_arh;
};

class FaustOutputPane : public Core::IOutputPane
{
    Q_OBJECT

public:
    FaustOutputPane();
    ~FaustOutputPane();

    virtual bool canFocus() const override;
    virtual bool canNavigate() const override;
    virtual bool canNext() const override;
    virtual bool canPrevious() const override;
    virtual void clearContents() override;
    virtual QString displayName() const override;
    virtual void goToNext() override;
    virtual void goToPrev() override;
    virtual bool hasFocus() const override;
    virtual QWidget* outputWidget(QWidget* parent) override;
    virtual int priorityInStatusBar() const override;
    virtual void setFocus() override;
    virtual QList<QWidget*> toolBarWidgets() const override;
    virtual void visibilityChanged(bool visible) override;

    void displaySvg(QString path);

private:
    FaustSvgWidget* m_widget;
};
}
}
#endif
