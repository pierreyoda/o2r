#ifndef AVAILABLEMODSDIALOG_HPP
#define AVAILABLEMODSDIALOG_HPP

#include "ui_AvailableModsDialog.h"

/** Simple list dialog where you can choose one or several mods if they are not
*already chosen and thus different from the default mod.
*
*/
class AvailableModsDialog : public QDialog, private Ui::AvailableModsDialog
{
    Q_OBJECT
    
public:
    /** Default constructor.
    *@param modsList Already chosen mods.
    *@param parent Parent widget.
    */
    explicit AvailableModsDialog(const QStringList &modsList, QWidget *parent = 0);

    /** Get the selected mods.
    */
    const QStringList &selectedMods() const { return mSelectedMods; }
    
protected:
    void changeEvent(QEvent *e);

private:
    QStringList mSelectedMods;

private slots:
    void on_availableModsList_itemDoubleClicked(QListWidgetItem *item);
    void on_availableModsList_itemSelectionChanged();
};

#endif // AVAILABLEMODSDIALOG_HPP
