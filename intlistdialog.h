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

private:
    Ui::IntListDialog *ui;
};

#endif // INTLISTDIALOG_H
