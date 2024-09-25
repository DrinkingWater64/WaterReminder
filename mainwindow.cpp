#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/treyIcon.jpg"));

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);


    traymenu = new QMenu(this);
    QAction *quitaction = new QAction("Quit", this);
    connect(quitaction, &QAction::triggered, qApp, &QApplication::quit);
    traymenu->addAction(quitaction);

    trayIcon->setContextMenu(traymenu);
    trayIcon->show();

    reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &MainWindow::showReminder);
    reminderTimer->start(10000);

    trayIcon->showMessage("Water Reminder", "Time to drink water", QSystemTrayIcon::Information, 3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showReminder(){
    trayIcon->showMessage("Water Reminder", "It's time to drink some water!", QSystemTrayIcon::Information, 3000);
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

void MainWindow::closeEvent(QCloseEvent *event) {
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

