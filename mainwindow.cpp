#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QSpinBox>
#include <QString>
#include <QAbstractItemView>
#include <QModelIndex>
#include "intlistdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    disableAllButtons();
    ui->stackedWidget->setCurrentIndex(0);

    // set up models
    myGrainModel = new grainModel();
    myPowderModel = new powderModel();
    myBallModel = new ballisticianModel();

    myGrainsProxyModel = new QSortFilterProxyModel;
    myGrainsProxyModel->setSourceModel(myGrainModel);

    myBallProxyModel = new  QSortFilterProxyModel;
    myBallProxyModel->setSourceModel(myBallModel);



    mydb = new database();

    // mydb->clearSettings();  /* this line un-commented for testing only */

    if (mydb->openConn(true))
    {
        initModels();
        on_Home_button_clicked();
    }
}

void MainWindow::on_testConnPushButton_clicked()
{
    if (mydb->connectToServer(ui->hostLineEdit->text(),
                              ui->portLineEdit->text(),
                              ui->userLineEdit->text(),
                              ui->passwordLineEdit->text()))
    {
        mydb->setDBname("rbims");
        initModels();
        this->on_Home_button_clicked();
    }
    else
    {
        if (this->oddTry)
        {
            ui->connStatusLabel->setText("Oops, Try again!");
        }
        else
        {
            ui->connStatusLabel->setText("Nope, Still Wrong!");
        }
        this->oddTry = !this->oddTry;
    }
}

void MainWindow::showAddGrainDialog()
{
    IntListDialog aDialog;
    QLineEdit *grainBox = aDialog.findChild<QLineEdit*>("addGrainsLineEdit");
    if (aDialog.exec())// On Accept (OK Button pressed) ...
    {
        QString stringVal = grainBox->text();
        addGrainsEntry(stringVal.toInt());
    }
}

void MainWindow::addGrainsEntry(int entry)
{
    if (!this->myGrainModel->exists(entry))
    {
        this->myGrainModel->insertRows(0,1,QModelIndex());  // insert a blank row to put new data in
        QModelIndex index = this->myGrainModel->index(0,0,QModelIndex());  // get a reference to the index of the blank row
        if (this->myGrainModel->setData(index,entry, Qt::EditRole))  // attempt to insert data into the row
        {
            myGrainsProxyModel->sort(0); // sort the proxymodel (Updates view with sorted result)
            QString message =  QString::number(entry) + " grains was added.";
            displayMessage(message);
        }
        else
        {
            displayMessage("Sorry, but something went wrong in addGrains");
        }
    }
    else
    {
        displayMessage("Sorry, but that is a duplicate value!");
    }
}

void MainWindow::removeGrainsEntry(QModelIndex index)
{
    QVariant qv = this->myGrainModel->data(index, Qt::EditRole);
    this->myGrainModel->removeRows(ui->grainslistView->currentIndex().row(),1,index);
}




void MainWindow::displayMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Respond to "gestures"
void MainWindow::on_AddGrainspushButton_clicked()
{
    showAddGrainDialog();
}

void MainWindow::on_removeGrainPushButton_clicked()
{
    this->removeGrainsEntry(ui->grainslistView->currentIndex());
}

void MainWindow::on_quitApplicationButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_actionQuit_triggered()
{
    on_quitApplicationButton_clicked();
}

void MainWindow::enableAllButtons()
{
    ui->Home_button->setEnabled(true);
    ui->Settings_button->setEnabled(true);
    ui->History_button->setEnabled(true);
    ui->Projects_button->setEnabled(true);
    ui->Measure_button->setEnabled(true);
}

void MainWindow::disableAllButtons()
{
    ui->Home_button->setEnabled(false);
    ui->Settings_button->setEnabled(false);
    ui->History_button->setEnabled(false);
    ui->Projects_button->setEnabled(false);
    ui->Measure_button->setEnabled(false);
}

void MainWindow::on_Home_button_clicked()
{
    enableAllButtons();
    ui->Home_button->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Settings_button_clicked()
{
    enableAllButtons();
    ui->Settings_button->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_History_button_clicked()
{
    enableAllButtons();
    ui->History_button->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Projects_button_clicked()
{
    enableAllButtons();
    ui->Projects_button->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Measure_button_clicked()
{
    enableAllButtons();
    ui->Measure_button->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_GrainscomboBox_currentIndexChanged(int myindex)
{
    QModelIndex tempIndex = myGrainModel->index(myindex, 0);
    ui->grainslistView->setCurrentIndex(tempIndex);
    ui->grainsComboBox->setCurrentIndex(tempIndex.row());
}


// Set up models
void MainWindow::initModels()
{
    // Populate Models
    myGrainModel->populate();
    myPowderModel->populate();
    myBallModel->populate();

    // Tie Views to Models
    ui->grainslistView->setModel(myGrainsProxyModel);
    ui->grainsComboBox->setModel(myGrainsProxyModel);
    ui->ballisticianTableView->setModel(myBallProxyModel);
    ui->powdersTableView->setModel(myPowderModel);

    // Fix Headers
    ui->powdersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->powdersTableView->setAlternatingRowColors(true);
    ui->powdersTableView->verticalHeader()->hide();

    ui->grainslistView->setAlternatingRowColors(true);

    ui->ballisticianTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ballisticianTableView->setAlternatingRowColors(true);
    ui->ballisticianTableView->verticalHeader()->hide();
    ui->ballisticianTableView->setSortingEnabled(true);
    ui->ballisticianTableView->setSelectionBehavior(QTableView::SelectRows);
}

void MainWindow::on_grainslistView_clicked(const QModelIndex &index)
{
    ui->grainsComboBox->setCurrentIndex(index.row());

}

void MainWindow::on_testcomboBox_currentIndexChanged(int myindex)
{
    QModelIndex tempIndex = myGrainModel->index(myindex, 0);
    ui->grainslistView->setCurrentIndex(tempIndex);
}
