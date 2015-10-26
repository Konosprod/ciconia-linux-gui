#ifndef SHORTCUTREADER_H
#define SHORTCUTREADER_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QWidget>

class ShortcutReader : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortcutReader(QWidget *parent = 0);

signals:

protected:
    void keyPressEvent(QKeyEvent* );

public slots:
    void readEntry();
};

#endif // SHORTCUTREADER_H
