#include "ballisticianmodel.h"


ballisticianModel::ballisticianModel(QAbstractTableModel *parent)
{

}

int ballisticianModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return parent.isValid() ? 0 : ballisticianList.size();
}

int ballisticianModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant ballisticianModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        if (index.row() >= ballisticianList.size() || index.row() < 0)
            return QVariant();  // OVERKILL ?

        if (role == Qt::DisplayRole) {
            const ballistician& ballistician = ballisticianList.at(index.row());
            switch (index.column()) {
            case 0:
                return ballistician.m_fname;
            case 1:
                return ballistician.m_lname;
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


QVariant ballisticianModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("First");
            case 1:
                return tr("Last");
            default:
                return QVariant();
            }
        }
        return section + 1;
}

void ballisticianModel::populate()
{
    QString theQuery = "select firstname, lastname from ballisticians order by lastname asc";
    QSqlQuery query(theQuery);
    QList<ballistician> tempballList;
    while (query.next())
    {
        tempballList.append(ballistician(query.value(0).toString(), query.value(1).toString()));
    }
    this->ballisticianList = tempballList;
}

Qt::ItemFlags ballisticianModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const QList<ballistician> &ballisticianModel::getBallisticianList() const
{
    return ballisticianList;
}
