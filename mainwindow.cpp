#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox->setRange(1, 120);
    ui->spinBox->setValue(10);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateInterval);

    setWindowTitle("Drink Water");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/treyIcon.jpg"));

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);


    reminderSound = new QSoundEffect(this);
    reminderSound->setSource(QUrl("qrc:/sfx/water-drop-plop.wav"));
    reminderSound->play();

    traymenu = new QMenu(this);
    QAction *quitaction = new QAction("Quit", this);
    connect(quitaction, &QAction::triggered, qApp, &QApplication::quit);
    traymenu->addAction(quitaction);

    trayIcon->setContextMenu(traymenu);
    trayIcon->show();

    reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &MainWindow::showReminder);
    updateInterval(ui->spinBox->value());

    trayIcon->showMessage("Water Reminder", "Time to drink water", QSystemTrayIcon::Information, 3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showReminder(){
    trayIcon->showMessage("Water Reminder", "It's time to drink some water!", QSystemTrayIcon::Information, 3000);
    reminderSound->play();
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if(isHidden()){
            showNormal();
            activateWindow();
        }else {
            hide();
        }
    }
}

void MainWindow::updateInterval(int value)
{
    reminderTimer->setInterval(value * 60000);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

