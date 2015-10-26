#include "screenshotmanager.h"

ScreenshotManager::ScreenshotManager(QWidget *parent) :
    QWidget(parent)
{
}

void ScreenshotManager::takeFullscreen()
{
    QProcess* process = new QProcess(this);

    process->start("gnome-screenshot");
}
