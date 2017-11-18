#ifndef EDITORNEWLEVELDIALOG_HPP
#define EDITORNEWLEVELDIALOG_HPP

#include "ui_EditorLevelPropertiesDialog.h"

class TiledMap;

/** The level properties dialog of the editor. Also used when creating a new level.
*User can change the name, the author name and the size.
*/
class EditorLevelPropertiesDialog : public QDialog, private Ui::EditorNewLevelDialog
{
    Q_OBJECT
    
public:
    explicit EditorLevelPropertiesDialog(const TiledMap *level, QWidget *parent = 0);

    unsigned int levelSizeX() const;
    unsigned int levelSizeY() const;
    bool mouseRandomPos() const;

    QString levelName() const;
    QString levelAuthor() const;
    
protected:
    void changeEvent(QEvent *e);

private:
    const bool mNewLevelMode;

private slots:
    void on_lineEdit_name_textChanged(const QString &text);
};

#endif // EDITORNEWLEVELDIALOG_HPP
