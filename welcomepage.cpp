#include "welcomepage.h"
#include <QVBoxLayout>
#include <QLabel>

WelcomePage::WelcomePage(QWidget *parent)
    : QWizardPage(parent)
{
    setCommitPage(false);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Welcome!"));
}
