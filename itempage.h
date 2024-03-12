#pragma once

#include <QWizardPage>
#include <QStandardItemModel>

class ItemModel;
class ItemPage : public QWizardPage
{
public:
    ItemPage(QWidget *parent = nullptr);

private:
    ItemModel *m_model;

    // QWizardPage interface
public:
    void initializePage() override;
};
