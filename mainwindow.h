#pragma once

#include <QWizard>

class MainWindow : public QWizard
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
