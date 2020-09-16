#ifndef POWDERMODEL_H
#define POWDERMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QList>
#include <QAbstractTableModel>
#include <QDebug>

struct powder{
    powder(const QString &name = QString()): m_name(name){}
        QString m_name;
};


class powderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit powderModel(QObject *parent = nullptr);
    /*
     * We are subclassing QAbstractListModel, so we must provide implementations of the rowCount() and data() functions.
     * Well behaved models also provide a headerData() implementation.
     * Our model implements an editable list, so we must also provide
     * an implementation of setData(), and implement the flags() function
     * so that it returns a value containing Qt::ItemIsEditable.
    */
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /* Our model interfaces to a resizable list, so we have decided to provide
     * implementations of insertRows() and removeRows().
    */
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    const QList<powder> &getPowdersList() const;

    void populate();
    int sortedIndex(int testVal);
    bool exists(int testVal);


signals:

private:
    QList<powder> powdersList;  // A vector of ints ... these are our individual powders

    // QAbstractItemModel interface
public:
};

#endif // POWDERMODEL_H
