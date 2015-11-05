#include "screenshotmanager.h"

ScreenshotManager::ScreenshotManager(QWidget *parent) :
    QWidget(parent)
{
    m_process = new QProcess(this);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Konosprod", "Ciconia");

    settings.beginGroup("global");
    m_path = settings.value("path", "").toString();
    settings.endGroup();
}

void ScreenshotManager::takeFullscreen()
{
    QStringList args;

    QString filename("Capture-"+QDateTime::currentDateTime().toString("dd-MM-yyyy-hh-mm-ss.png"));

    args << "-f";
    args << m_path + filename;

    m_process->execute("gnome-screenshot", args);

    emit screenshotDone(filename);
}

void ScreenshotManager::takeArea()
{
    QStringList args;

    QString filename("Capture-"+QDateTime::currentDateTime().toString("dd-MM-yyyy-hh-mm-ss.png"));

    args << "-quality";
    args << "100";
    args << "-silent";
    args << m_path + filename;

    m_process->execute("import", args);

    emit screenshotDone(filename);
}

void ScreenshotManager::takeWindow()
{
    QStringList args;

    QString filename("Capture-"+QDateTime::currentDateTime().toString("dd-MM-yyyy-hh-mm-ss.png"));

    args << "-w";
    args << "-f";
    args << m_path + filename;

    m_process->execute("gnome-screenshot", args);

    emit screenshotDone(filename);
}
