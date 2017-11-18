#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include "ui_AboutDialog.h"

/** AboutDialog shows the project's licence.
*
*/
class AboutDialog : public QDialog, private Ui::AboutDialog
{
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0);
    
protected:
    void changeEvent(QEvent *e);
};

#endif // ABOUTDIALOG_HPP
