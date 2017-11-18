#include <QPushButton>
#include "EditorLevelPropertiesDialog.hpp"
#include "../map/TiledMap.hpp"

EditorLevelPropertiesDialog::EditorLevelPropertiesDialog(const TiledMap *level,
                                                         QWidget *parent) :
    QDialog(parent), mNewLevelMode(level == 0)
{
    setupUi(this);
    setFixedSize(size());
    // Remove "what's this" icon in title bar
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    spinBox_xSize->setMinimum(TiledMap::SIZE_MIN_LIMIT_X);
    spinBox_xSize->setMaximum(TiledMap::SIZE_MAX_LIMIT_X);
    spinBox_ySize->setMinimum(TiledMap::SIZE_MIN_LIMIT_Y);
    spinBox_ySize->setMaximum(TiledMap::SIZE_MAX_LIMIT_Y);

    // If a level is edited, load its current properties
    if (mNewLevelMode)
        return;
    spinBox_xSize->setValue(level->sizeX());
    spinBox_ySize->setValue(level->sizeY());
    lineEdit_name->setText(level->info().name);
    lineEdit_author->setText(level->info().author);
    checkBox_mouseRandomPos->setChecked(level->info().mouseRandomPos);
}

unsigned int EditorLevelPropertiesDialog::levelSizeX() const
{
    return spinBox_xSize->value();
}

unsigned int EditorLevelPropertiesDialog::levelSizeY() const
{
    return spinBox_ySize->value();
}

bool EditorLevelPropertiesDialog::mouseRandomPos() const
{
    return checkBox_mouseRandomPos->isChecked();
}

QString EditorLevelPropertiesDialog::levelName() const
{
    return lineEdit_name->text();
}

QString EditorLevelPropertiesDialog::levelAuthor() const
{
    return lineEdit_author->text();
}

void EditorLevelPropertiesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void EditorLevelPropertiesDialog::on_lineEdit_name_textChanged(const QString &text)
{
    if (mNewLevelMode)
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

