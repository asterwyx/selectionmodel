#include "mainwindow.h"
#include "welcomepage.h"
#include "itempage.h"

MainWindow::MainWindow(QWidget *parent)
    : QWizard(parent)
{
    addPage(new WelcomePage(this));
    addPage(new ItemPage(this));
}

MainWindow::~MainWindow() {}
