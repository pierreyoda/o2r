#ifndef MODSDIALOG_HPP
#define MODSDIALOG_HPP

#include "ui_ModsDialog.h"
#include <QStringListModel>


/** Add/remove mods, and change their load order.
*
*/
class ModsDialog : public QDialog, private Ui::ModsDialog
{
    Q_OBJECT
    
public:
    explicit ModsDialog(const QStringList &modsList, QWidget *parent = 0);

    const QStringList &modsList() const { return mModsList; }
    
protected:
    void changeEvent(QEvent *e);

private:
    void buildModsList();

    QStringList mModsList;

private slots:
    void buildResult(int result);
    void on_buttonAdd_clicked();
    void on_buttonDelete_clicked();
    void on_buttonUp_clicked();
    void on_buttonDown_clicked();
    void on_modsListWidget_itemSelectionChanged();
};

#endif // MODSDIALOG_HPP
