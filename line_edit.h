#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "ui_line_edit.h"

#include <QWidget>
#include <QLineEdit>

class LineEdit : public QWidget
{
    Q_OBJECT

public:
    LineEdit();
    ~LineEdit();

public slots:
    void alignChanged(int);
    void maskChanged(int);
    void passwordChanged(int);
    void validChanged(int);
    void readonlyChanged(int);

private:
    Ui::LineEdit *ui;
    QLineEdit *align_LineEdit;
    QLineEdit *mask_LineEdit;
    QLineEdit *password_LineEdit;
    QLineEdit *valid_LineEdit;
    QLineEdit *readonly_LineEdit;
};


#endif
