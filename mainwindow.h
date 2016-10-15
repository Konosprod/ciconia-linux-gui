#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QxtGlobalShortcut>
#include <QString>
#include <QKeyEvent>
#include <QKeySequence>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QFile>
#include <QSettings>
#include <QNetworkReply>
#include <QClipboard>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <phonon>
#include <QSound>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QMenu>
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
    void systrayAction(QSystemTrayIcon::ActivationReason r);
    void uploadFile(QString filename, QString path="");
    void uploadFinished(QNetworkReply* r);
    void uploadProgress(qint64 a, qint64 b);
    void selectAndUpload();
    void openInBrowser();

protected:
    GlobalShortcut* m_shortcuts[5];
    ScreenshotManager* m_screenmanager;
    QSystemTrayIcon* m_systray;
    QNetworkAccessManager* m_manager;
    QString m_lastFilename;
    QString m_url;
    QMenu* m_systrayMenu;

    void setupSystrayMenu();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    int FULLSCREEN = 0;
    int AREA = 1;
    int WINDOW = 2;
    int FILE = 3;

    void doConnexions();
};

#endif // MAINWINDOW_H
