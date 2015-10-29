#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QxtGlobalShortcut>
#include <QString>
#include <QKeyEvent>
#include <QKeySequence>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QFileDialog>
#include "shortcutreader.h"
#include "screenshotmanager.h"
#include "globalshortcut.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void saveSettings();
    void loadSettings();
    void browsePath();

protected:
    GlobalShortcut* m_shortcuts[5];
    ScreenshotManager* m_screenmanager;
    QSystemTrayIcon* m_systray;

private:
    Ui::MainWindow *ui;

    void doConnexions();
};

#endif // MAINWINDOW_H
