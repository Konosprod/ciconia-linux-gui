#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Ciconia");

    m_screenmanager = new ScreenshotManager(this);
    m_systray = new QSystemTrayIcon(this);

    m_systray->show();

    loadSettings();

    m_shortcuts[0] = new GlobalShortcut(QKeySequence(ui->shortcutFullscreen->text()), this);
    m_shortcuts[1] = new GlobalShortcut(QKeySequence(ui->shortcutArea->text()), this);
    m_shortcuts[2] = new GlobalShortcut(QKeySequence(ui->shortcutCurrentWindow->text()), this);

    doConnexions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doConnexions()
{
    connect(ui->fullscreenButton, SIGNAL(clicked()), ui->shortcutFullscreen, SLOT(readEntry()));
    connect(ui->areaButton, SIGNAL(clicked()), ui->shortcutArea, SLOT(readEntry()));
    connect(ui->currentWindowButton, SIGNAL(clicked()), ui->shortcutCurrentWindow, SLOT(readEntry()));
    connect(ui->uploadFileButton, SIGNAL(clicked()), ui->shortcutUploadFile, SLOT(readEntry()));

    connect(m_shortcuts[0], SIGNAL(activated()), m_screenmanager, SLOT(takeFullscreen()));
    connect(m_shortcuts[1], SIGNAL(activated()), m_screenmanager, SLOT(takeArea()));
    connect(m_shortcuts[2], SIGNAL(activated()), m_screenmanager, SLOT(takeWindow()));

    connect(ui->shortcutFullscreen, SIGNAL(textChanged(QString)), m_shortcuts[0], SLOT(updateShortcut(QString)));
    connect(ui->shortcutArea, SIGNAL(textChanged(QString)), m_shortcuts[1], SLOT(updateShortcut(QString)));
    connect(ui->shortcutCurrentWindow, SIGNAL(textChanged(QString)), m_shortcuts[2], SLOT(updateShortcut(QString)));

    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browsePath()));

    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(saveSettings()));
}

void MainWindow::saveSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Konosprod", "Ciconia");

    settings.beginGroup("shortcuts");
    settings.setValue("fullscreen", ui->shortcutFullscreen->text());
    settings.setValue("area", ui->shortcutArea->text());
    settings.setValue("window", ui->shortcutCurrentWindow->text());
    settings.setValue("upload", ui->shortcutUploadFile->text());
    settings.endGroup();

    settings.beginGroup("global");
    settings.setValue("playsound", ui->playNotifcationSound->isChecked());
    settings.setValue("clipboard", ui->copyToClipboard->isChecked());
    settings.setValue("browser", ui->openInBrowser->isChecked());
    settings.setValue("save", ui->saveLocalCopy->isChecked());
    settings.setValue("path", ui->pathLineEdit->text());
    settings.endGroup();

    settings.beginGroup("account");
    settings.setValue("url", ui->urlLineEdit->text());
    settings.setValue("api", ui->apiLineEdit->text());
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "Konosprod", "Ciconia");
    settings.beginGroup("shortcuts");
    ui->shortcutFullscreen->setText(settings.value("fullscreen", "Ctrl+Shift+1").toString());
    ui->shortcutArea->setText(settings.value("area","Ctrl+Shift+3").toString());
    ui->shortcutCurrentWindow->setText(settings.value("window", "Ctrl+Shift+2").toString());
    ui->shortcutUploadFile->setText(settings.value("upload", "Ctrl+Shift+4").toString());
    settings.endGroup();

    settings.beginGroup("global");
    ui->playNotifcationSound->setChecked(settings.value("playsound").toBool());
    ui->copyToClipboard->setChecked(settings.value("clipboard").toBool());
    ui->openInBrowser->setChecked(settings.value("browser").toBool());
    ui->saveLocalCopy->setChecked(settings.value("save").toBool());
    ui->pathLineEdit->setText(settings.value("path").toString());
    settings.endGroup();

    settings.beginGroup("account");
    ui->urlLineEdit->setText(settings.value("url").toString());
    ui->apiLineEdit->setText(settings.value("api").toString());
    settings.endGroup();
}

void MainWindow::browsePath()
{
    ui->pathLineEdit->setText(QFileDialog::getExistingDirectory(this, "Save location")+"/");
}
