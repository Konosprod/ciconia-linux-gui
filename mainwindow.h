#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QxtGlobalShortcut>
#include <QString>
#include <QKeyEvent>
#include <QKeySequence>
#include "shortcutreader.h"
#include "screenshotmanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QxtGlobalShortcut* m_shortcuts[5];
    ScreenshotManager* m_screenmanager;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
