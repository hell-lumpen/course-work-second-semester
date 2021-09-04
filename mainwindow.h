#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutwindow.h"
#include "begingamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit_button_clicked();

    void on_about_button_clicked();

    void on_play_button_clicked();

private:
    Ui::MainWindow *ui;
    AboutWindow *about_window;
    BeginGameWindow *begin_game_window;
    GameWindow *game_window;
};
#endif // MAINWINDOW_H
