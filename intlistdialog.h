#ifndef INTLISTDIALOG_H
#define INTLISTDIALOG_H

#include <QDialog>

namespace Ui {
class IntListDialog;
}

class IntListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntListDialog(QWidget *parent = nullptr);
    ~IntListDialog();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::IntListDialog *ui;
};

#endif // INTLISTDIALOG_H
