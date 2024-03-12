#include "itempage.h"
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QEvent>
#include <QAbstractItemModel>

class ItemModel : public QAbstractItemModel
{
public:
    ItemModel(QObject *parent = nullptr) : QAbstractItemModel(parent) {
        for (int i = 0; i < 10; i++) {
            m_data.push_back(QString("item%1").arg(i));
        }
    }

    void refresh() {
        beginResetModel();
        endResetModel();
    }
private:
    QStringList m_data;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return QAbstractItemModel::createIndex(row, column, nullptr);
}

QModelIndex ItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return 10;
}

int ItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return 1;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    return m_data[index.row()];
}


ItemPage::ItemPage(QWidget *parent)
    : QWizardPage(parent)
{
    setCommitPage(true);
    m_model = new ItemModel(this);
    auto listView = new QListView(this);
    listView->setModel(m_model);
    auto vLayout = new QVBoxLayout(this);
    vLayout->addWidget(listView);
    auto label = new QLabel(listView->currentIndex().data().toString());
    connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, label](const QItemSelection &selected, const QItemSelection &deselected){
        qDebug() << "selected:" << selected << "deselected:" << deselected;
        if (selected.isEmpty()) {
            label->setText("none");
        } else {
            label->setText(selected.indexes().first().data().toString());
        }
    });
    vLayout->addWidget(label);
    // auto button = new QPushButton("toggle list view");
    // vLayout->addWidget(button);
    // connect(button, &QPushButton::clicked, this, [listView]() {
    //     listView->setVisible(!listView->isVisible());
    // });
}

void ItemPage::initializePage()
{
    m_model->refresh();
}

