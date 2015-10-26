#include "globalshortcut.h"

GlobalShortcut::GlobalShortcut(QObject *parent) : QxtGlobalShortcut(parent)
{
}

GlobalShortcut::GlobalShortcut(QKeySequence sequence, QObject *parent) : QxtGlobalShortcut(sequence, parent)
{

}

void GlobalShortcut::updateShortcut(QString newString)
{
    this->setShortcut(QKeySequence(newString));
}
