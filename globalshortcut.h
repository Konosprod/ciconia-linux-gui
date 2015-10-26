#ifndef GLOBALSHORTCUT_H
#define GLOBALSHORTCUT_H

#include <QString>
#include <QxtGlobalShortcut>
#include <QKeySequence>

class GlobalShortcut : public QxtGlobalShortcut
{
    Q_OBJECT
public:
    GlobalShortcut(QObject* parent = 0);
    GlobalShortcut(QKeySequence sequence, QObject* parent = 0);

public slots:
    void updateShortcut(QString);
};

#endif // GLOBALSHORTCUT_H
