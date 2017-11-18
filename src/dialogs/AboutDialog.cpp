include "AboutDialog.hpp"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setFixedSize(size());
    // Remove "what's this" icon in title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void AboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}
