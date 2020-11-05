#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "grainmodel.h"
#include "powdermodel.h"
#include "database.h"
#include "ballisticianmodel.h"
#include <QDebug>
#include <QPoint>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_AddGrainspushButton_clicked();

    void on_removeGrainPushButton_clicked();

    void on_testConnPushButton_clicked();

    void on_quitApplicationButton_clicked();

    void on_actionQuit_triggered();

    void on_Home_button_clicked();

    void on_Settings_button_clicked();

    void on_History_button_clicked();

    void on_Projects_button_clicked();

    void on_Measure_button_clicked();

//    void on_GrainscomboBox_currentIndexChanged(int index);

    void on_grainslistView_clicked(const QModelIndex &index);

    void on_GWcomboBox_currentIndexChanged(int index);

    void on_grainsComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    grainModel * myGrainModel;
    powderModel * myPowderModel;
    ballisticianModel *myBallModel;
    QSortFilterProxyModel *myBallProxyModel;
    QSortFilterProxyModel * powderProxyModel;
    QSortFilterProxyModel * myGrainsProxyModel;

    database *mydb;
    bool oddTry;

    void initModels();

    void scaleMainWindow(double percentage);

    void disableAllButtons();
    void enableAllButtons();

    void displayMessage(QString message);

    void showAddGrainDialog();
    void addGrainsEntry(int entry);
    void removeGrainsEntry(QModelIndex index);
    void ScrollGrainsIntoView(int index);
    void on_grainscomboBox_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
