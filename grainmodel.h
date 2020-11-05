#ifndef GRAINMODEL_H
#define GRAINMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVector>
#include <QAbstractListModel>
#include <QDebug>
#include "commonutils.h"



class grainModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit grainModel(QObject *parent = nullptr);

    /*
     * We are subclassing QAbstractListModel, so we must provide implementations of the rowCount() and data() functions.
     * Well behaved models also provide a headerData() implementation.
     * Our model implements an editable list, so we must also provide
     * an implementation of setData(), and implement the flags() function
     * so that it returns a value containing Qt::ItemIsEditable.
    */
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /* Our model interfaces to a resizable list, so we have decided to provide
     * implementations of insertRows() and removeRows().
    */
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    const QVector<int> &getGrainsList() const;

    void populate();
    bool exists(int testVal);


signals:

private:
    QVector<int> grainsList;  // A vector of ints ... these are our individual grainWeights
    CommonUtils *commonUtils;
};

#endif // GRAINMODEL_H
