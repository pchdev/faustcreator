#include "faustcreator-options.hpp"
#include "faustcreator-constants.hpp"

using namespace Faust::Internal;

FaustOptionsWidget::FaustOptionsWidget()
{

}

FaustOptionsWidget::~FaustOptionsWidget()
{

}

FaustOptionsPage::FaustOptionsPage()
{
    setId(Constants::C_FAUST_OPTIONS_PAGE_ID);
    setDisplayName(Constants::C_FAUST_DISPLAY_NAME);
    setCategory(Constants::C_FAUST_CATEGORY);
    setDisplayCategory(Constants::C_FAUST_DISPLAY_NAME);
}

FaustOptionsPage::~FaustOptionsPage()
{

}

void FaustOptionsPage::apply()
{

}

void FaustOptionsPage::finish()
{
    delete m_widget;
    m_widget = nullptr;
}

QWidget* FaustOptionsPage::widget()
{
    if (!m_widget)
        m_widget = new FaustOptionsWidget;
    return m_widget;
}
