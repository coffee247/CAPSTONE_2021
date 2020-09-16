#include "powdermodel.h"



powderModel::powderModel(QObject *parent) : QAbstractTableModel(parent)
{
}



int powderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return parent.isValid() ? 0 : powdersList.size();
}

int powderModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant powderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        if (index.row() >= powdersList.size() || index.row() < 0)
            return QVariant();  // OVERKILL ?

        if (role == Qt::DisplayRole) {
            const powder& powder = powdersList.at(index.row());
            switch (index.column()) {
            case 0:
                return powder.m_name;
            default:
                return QVariant();
            }
        }
        else if (role == Qt::TextAlignmentRole){
            if (index.column() == 0)
                return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
            else
                return Qt::AlignCenter;
        }
        return QVariant();
}

QVariant powderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Powder");
            default:
                return QVariant();
            }
        }
        return section + 1;
}

void powderModel::populate()
{
    QString theQuery = "select brandname from powders order by brandname asc";
    QSqlQuery query(theQuery);
    QList<powder> temppowderList;
    while (query.next())
    {
        temppowderList.append(powder(query.value(0).toString()));
    }
    this->powdersList = temppowderList;
}

Qt::ItemFlags powderModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

//bool powderModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{

//    return false;
//}






