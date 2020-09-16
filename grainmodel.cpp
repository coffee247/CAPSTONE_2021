#include "grainmodel.h"


/*  The grainModel Constructor */
grainModel::grainModel(QObject *parent) : QAbstractListModel(parent)
{
}

/* When subclassing QAbstractListModel, you must provide
 * implementations of the rowCount() and data() functions.
 * Well behaved models also provide a headerData() implementation.
 */



/* Required method rowCount returns number of data rows currently in
 * the grainModel.
 */
int grainModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : grainsList.size();
}


/* Required method data returns the data stored under the given role
 * for the item referred to by the index.
*/
QVariant grainModel::data(const QModelIndex &index, int role) const
{
    /* First some error checking (next two if statements */
    if (!index.isValid())
        return QVariant();  // No value to return, return an invalid QVariant instead of returning 0.

    if (index.row() >= grainsList.size() || index.row() < 0)
        return QVariant();

    /* Then the meat and potatoes */
    if (role == Qt::DisplayRole) {
        return grainsList.at(index.row());
    }

    /* resort to a catch-all when all no IF statements satisfy */
    return QVariant();
}


Qt::ItemFlags grainModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool grainModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QVariant intVal = value;
    QString val = value.toString();
    QSqlQuery query;
    QString theQuery = "insert into grains(grainWeight) values (" + val + ");";
    query.prepare(theQuery);
    if (query.exec()){
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        grainsList.replace(row, intVal.toInt());
        this->sort(0);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    }

    return false;
}

/*
 * Wen implementing insertRows it is important to make sure views are made aware of changes.
 * so call beginInsertRows() before inserting new rows into the data structure,
 * and call endInsertRows() immediately afterwards.
*/
bool grainModel::insertRows(int position, int countOfRowsToInsert = 1, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + countOfRowsToInsert - 1);

    this->grainsList.insert(position, 1);

    endInsertRows();
    return true;
}

/*
 * removes count rows starting with the given row under parent parent from the model.
*/
bool grainModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        this->grainsList.removeAt(position);

    endRemoveRows();
    return true;
}

const QVector<int> &grainModel::getGrainsList() const
{
    return this->grainsList;
}

/* Method to query the database at launch (to do initial populate of ListView */
void grainModel::populate()
{
    QString theQuery = "select grainweight from grains order by grainweight asc";
    QSqlQuery query(theQuery);
    QVector<int> memberList;
    while (query.next())
    {
        memberList.append(query.value(0).toInt());
    }
    this->grainsList = memberList;
}

int grainModel::sortedIndex(int testVal)
{
    QVectorIterator<int> i(this->grainsList);
    int rowIndex = 0;
    while (i.hasNext())
    {
        int lVal = i.next();
        if (lVal < testVal){
            rowIndex ++;
        }
        else return rowIndex + 1;
    }
    return rowIndex +1;
}


bool grainModel::exists(int testVal)
{
    QString theQuery = "select grainweight from grains where grainweight = (" + QString::number(testVal) + ");";
    QSqlQuery query(theQuery);
    query.prepare(theQuery);
    query.exec();
    if (query.size() >= 1) return true;
    return false;
}


