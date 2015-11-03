#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Ciconia");
    setWindowIcon(QIcon(":/rc/icon"));

    m_screenmanager = new ScreenshotManager(this);
    m_systray = new QSystemTrayIcon(this);
    m_manager = new QNetworkAccessManager(this);


    m_systray->setIcon(QIcon(":/rc/icon"));
    m_systray->show();

    loadSettings();

    if(ui->startHidden->isChecked())
        this->hide();

    m_shortcuts[0] = new GlobalShortcut(QKeySequence(ui->shortcutFullscreen->text()), this);
    m_shortcuts[1] = new GlobalShortcut(QKeySequence(ui->shortcutArea->text()), this);
    m_shortcuts[2] = new GlobalShortcut(QKeySequence(ui->shortcutCurrentWindow->text()), this);
    m_shortcuts[3] = new GlobalShortcut(QKeySequence(ui->shortcutUploadFile->text()), this);

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
    connect(m_shortcuts[3], SIGNAL(activated()), this, SLOT(selectAndUpload()));

    connect(ui->shortcutFullscreen, SIGNAL(textChanged(QString)), m_shortcuts[0], SLOT(updateShortcut(QString)));
    connect(ui->shortcutArea, SIGNAL(textChanged(QString)), m_shortcuts[1], SLOT(updateShortcut(QString)));
    connect(ui->shortcutCurrentWindow, SIGNAL(textChanged(QString)), m_shortcuts[2], SLOT(updateShortcut(QString)));
    connect(ui->shortcutUploadFile, SIGNAL(textChanged(QString)), m_shortcuts[3], SLOT(updateShortcut(QString)));

    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browsePath()));

    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    connect(m_screenmanager, SIGNAL(screenshotDone(QString)), this, SLOT(uploadFile(QString)));

    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));

    connect(m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(systrayAction(QSystemTrayIcon::ActivationReason)));
    connect(m_systray, SIGNAL(messageClicked()), this, SLOT(openInBrowser()));

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
    settings.setValue("hidden", ui->startHidden->isChecked());
    settings.endGroup();

    settings.beginGroup("account");
    settings.setValue("url", ui->urlLineEdit->text());
    settings.setValue("api", ui->apiLineEdit->text());
    settings.endGroup();

    settings.beginGroup("systray");
    settings.setValue("settings", ui->showSettings->isChecked());
    settings.setValue("screen", ui->beginScreenCapture->isChecked());
    settings.setValue("upload", ui->openUploadDialog->isChecked());
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
    ui->startHidden->setChecked(settings.value("hidden").toBool());
    settings.endGroup();

    settings.beginGroup("account");
    ui->urlLineEdit->setText(settings.value("url").toString());
    ui->apiLineEdit->setText(settings.value("api").toString());
    settings.endGroup();

    settings.beginGroup("systray");
    ui->openUploadDialog->setChecked(settings.value("upload").toBool());
    ui->showSettings->setChecked(settings.value("settings").toBool());
    ui->beginScreenCapture->setChecked(settings.value("screen").toBool());
    settings.endGroup();
}

void MainWindow::browsePath()
{
    ui->pathLineEdit->setText(QFileDialog::getExistingDirectory(this, "Save location")+"/");
}

void MainWindow::uploadFile(QString filename, QString path)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Konosprod", "Ciconia");

    settings.beginGroup("account");
    QString upUrl = settings.value("url", "").toString();
    QString apiKey = settings.value("api", "").toString();
    settings.endGroup();

    settings.beginGroup("global");

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);

    m_lastFilename = settings.value("path", "").toString() + filename;

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"k\""));
    textPart.setBody(apiKey.toUtf8());

    QHttpPart imagePart;
    QString f = filename.mid(filename.lastIndexOf('/'));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"img\"; filename=\""+f+"\""));
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));


    QFile *file = 0;

    if(path == "")
        file = new QFile(m_lastFilename);
    else
        file = new QFile(path + "/" + filename);

    if(!file->open(QIODevice::ReadOnly)) {
        qDebug() << file->errorString();
    }

    imagePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(textPart);
    multiPart->append(imagePart);

    QUrl url(upUrl);
    QNetworkRequest request(url);

    QNetworkReply* reply = m_manager->post(request, multiPart);

    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64, qint64)));

    settings.endGroup();
}

void MainWindow::uploadFinished(QNetworkReply* r)
{
    m_url = r->readAll();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Konosprod", "Ciconia");

    settings.beginGroup("global");

    if(settings.value("clipboard").toBool())
    {
        QClipboard* cb = QApplication::clipboard();

        cb->setText(m_url);
    }

    if(settings.value("playsound").toBool())
    {
        Phonon::MediaObject * sound = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(":/rc/notification"));
        sound->play();
    }

    if(settings.value("browser").toBool())
    {
        QDesktopServices::openUrl(QUrl(m_url));
    }

    if(!settings.value("save").toBool())
    {
        QFile::remove(m_lastFilename);
    }

    m_systray->showMessage("Upload done", m_url, QSystemTrayIcon::Information, 2000);
    m_systray->setToolTip("");

    settings.endGroup();
}

void MainWindow::uploadProgress(qint64 a, qint64 b)
{
    double progress = ((double)a/(double)b)*100.0;

    m_systray->setToolTip(QString::number(progress)+"%");
}

void MainWindow::systrayAction(QSystemTrayIcon::ActivationReason r)
{
    switch(r)
    {
    case QSystemTrayIcon::DoubleClick:
        if(ui->showSettings->isChecked())
        {
            this->show();
        }

        if(ui->beginScreenCapture->isChecked())
        {
            m_screenmanager->takeFullscreen();
        }

        if(ui->openUploadDialog->isChecked())
        {
            selectAndUpload();
        }
        break;

    case QSystemTrayIcon::Context:
        this->show();
        break;

    default:
        break;
    }
}

void MainWindow::selectAndUpload()
{
    QString file = QFileDialog::getOpenFileName(this, "Upload");
    QString filename = file.mid(file.lastIndexOf("/"));
    QString path = file.mid(0, file.lastIndexOf("/"));

    if(file != "")
        uploadFile(filename, path);
}

void MainWindow::openInBrowser()
{
    QDesktopServices::openUrl(QUrl(m_url));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isVisible())
    {
        this->hide();
        event->ignore();
    }
}
