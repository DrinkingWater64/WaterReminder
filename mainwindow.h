#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSoundEffect>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void showReminder();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateInterval(int value);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *traymenu;
    QTimer *reminderTimer;
    QSoundEffect *reminderSound;
};
#endif // MAINWINDOW_H
