#ifndef SCREENSHOTMANAGER_H
#define SCREENSHOTMANAGER_H

#include <QWidget>
#include <QProcess>

class ScreenshotManager : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenshotManager(QWidget *parent = 0);

signals:

public slots:
    void takeFullscreen();

};

#endif // SCREENSHOTMANAGER_H
