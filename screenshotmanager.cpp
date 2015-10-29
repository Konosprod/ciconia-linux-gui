#include "screenshotmanager.h"

ScreenshotManager::ScreenshotManager(QWidget *parent) :
    QWidget(parent)
{
    m_process = new QProcess(this);
}

void ScreenshotManager::takeFullscreen()
{
    QStringList args;

    m_process->execute("gnome-screenshot");
}

void ScreenshotManager::takeArea()
{
    QStringList args;

    args << "-quality";
    args << "100";
    args << "-silent";
    args << "/home/kono/Images/test.png";

    m_process->execute("import", args);
}

void ScreenshotManager::takeWindow()
{
    QStringList args;

    args << "-w";

    m_process->execute("gnome-screenshot", args);
}
