#ifndef BEGINGAMEWINDOW_H
#define BEGINGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include "gamewindow.h"





namespace Ui {
class BeginGameWindow;
}

class BeginGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BeginGameWindow(QWidget *parent = nullptr);
    ~BeginGameWindow();
    QLabel *label = new QLabel(this);
    int i = 0;
    QString all_gamers;



signals:
    void show_main_window();

private slots:

    void on_add_player_button_clicked();

    void on_cancel_game_button_clicked();

    void on_play_game_button_clicked();

private:
    Ui::BeginGameWindow *ui;
    GameWindow *game_window;
};

#endif // BEGINGAMEWINDOW_H
