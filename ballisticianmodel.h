#ifndef BALLISTICIANMODEL_H
#define BALLISTICIANMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QList>
#include <QAbstractTableModel>
#include <QDebug>


struct ballistician{
    ballistician(const QString &firstname = QString(), const QString &lastname = QString()): m_fname(firstname), m_lname(lastname){}
        QString m_fname;
        QString m_lname;
};

class ballisticianModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ballisticianModel(QAbstractTableModel *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    const QList<ballistician> &getBallisticianList() const;

    void populate();
    int sortedIndex(int testVal);
    bool exists(int testVal);

private:
    QList<ballistician> ballisticianList;

signals:

};

#endif // BALLISTICIANMODEL_H
