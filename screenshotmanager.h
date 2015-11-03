#ifndef SCREENSHOTMANAGER_H
#define SCREENSHOTMANAGER_H

#include <QWidget>
#include <QProcess>
#include <QDateTime>
#include <QSettings>
#include <QString>
#include <QDebug>

class ScreenshotManager : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenshotManager(QWidget *parent = 0);

signals:
    void screenshotDone(const QString &filename);

public slots:
    void takeFullscreen();
    void takeArea();
    void takeWindow();

protected:
    QProcess* m_process;
    QString m_path;

};

#endif // SCREENSHOTMANAGER_H
