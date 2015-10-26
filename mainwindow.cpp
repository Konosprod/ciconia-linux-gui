#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Ciconia");

    connect(ui->pushButton, SIGNAL(clicked()), ui->lineEdit_2, SLOT(readEntry()));
    connect(ui->pushButton_2, SIGNAL(clicked()), ui->lineEdit_3, SLOT(readEntry()));
    connect(ui->pushButton_3, SIGNAL(clicked()), ui->lineEdit_4, SLOT(readEntry()));
    connect(ui->pushButton_4, SIGNAL(clicked()), ui->lineEdit_5, SLOT(readEntry()));
    connect(ui->pushButton_5, SIGNAL(clicked()), ui->lineEdit_6, SLOT(readEntry()));

    m_screenmanager = new ScreenshotManager(this);

    m_shortcuts[0] = new GlobalShortcut(QKeySequence(ui->lineEdit_2->text()), this);


    connect(m_shortcuts[0], SIGNAL(activated()), m_screenmanager, SLOT(takeFullscreen()));

    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), m_shortcuts[0], SLOT(updateShortcut(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
