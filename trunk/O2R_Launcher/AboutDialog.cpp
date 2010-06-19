#include "AboutDialog.hpp"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setFixedSize(280, 150);
    QString aboutText = "<strong>"
            + tr("Open Rodent's Revenge - Official Launcher")
            + "</strong><br /><br />"
            + tr("Copyright &copy; 2010 Pierre-Yves Diallo (Pierreyoda)")
            + "<br />"
            + tr("License : GPL 3");
    label->setText(aboutText);
}

void AboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    /*switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }*/
}
