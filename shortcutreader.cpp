#include "shortcutreader.h"

ShortcutReader::ShortcutReader(QWidget *parent) :
    QLineEdit(parent)
{

}

void ShortcutReader::keyPressEvent(QKeyEvent *e)
{
    if(!isEnabled())
    {
        QLineEdit::keyPressEvent(e);
        return;
    }

    e->accept();

    if(!e->text().isEmpty())
    {
        QKeySequence sequence(e->key() | e->modifiers());
        setText(sequence.toString());

        this->setEnabled(false);
    }
}

void ShortcutReader::readEntry()
{
    this->setText("");
    this->setEnabled(true);
}
