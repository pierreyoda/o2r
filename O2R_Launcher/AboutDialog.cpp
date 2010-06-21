#include "AboutDialog.hpp"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setFixedSize(280, 150);
    writeAboutText();
}

void AboutDialog::writeAboutText()
{
    text = "<strong>"
            + tr("Open Rodent's Revenge - Official Launcher")
            + "</strong><br /><br />"
            + tr("Copyright &copy; 2010 Pierre-Yves Diallo (Pierreyoda)")
            + "<br />"
            + tr("License : GPL 3") + "<br />"
            + tr("Icons from : <a href=www.pixel-mixer.com>pixel-mixer</a>");
    label->setText(text);
}

void AboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
    {
        retranslateUi(this);
        writeAboutText();
    }
}
