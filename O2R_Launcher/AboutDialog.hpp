#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "ui_AboutDialog.h"

class AboutDialog : public QDialog, private Ui::AboutDialog {
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void writeAboutText();

    QString text;
};

#endif /* DIALOG_HPP */
