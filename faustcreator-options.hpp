#ifndef FAUSTCREATOR_OPTIONS_HPP
#define FAUSTCREATOR_OPTIONS_HPP

#include <coreplugin/dialogs/ioptionspage.h>

namespace Faust {
namespace Internal {

class FaustOptionsWidget : public QWidget
{
public:
    FaustOptionsWidget();
    ~FaustOptionsWidget();
};

class FaustOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    FaustOptionsPage();
    ~FaustOptionsPage();
    virtual void apply() override;
    virtual void finish() override;
    virtual QWidget* widget() override;

private:
    FaustOptionsWidget* m_widget;
};
}
}

#endif
