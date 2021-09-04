#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>

#include <QObject>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>


class Player: public QGraphicsEllipseItem{
    QString name;
    int position;
    int money;
    int his_card[40];

    int px, py;

    int x[40] = {41, 129, 193, 257, 321, 385, 449, 513, 577, 641, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 641, 577, 513, 449, 385, 321, 257, 193, 129, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41};
    int y[40] = {41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 129, 193, 257, 321, 385, 449, 513, 577, 641, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 641, 577, 513, 449, 385, 321, 257, 193, 129};


public:
    Player(QString name, int x, int y, int ax, int ay, int money, int position, int pos_correction_x, int pos_correction_y) {
        this->name = name;
        this->money = money;
        this->position = position;
        this->px = pos_correction_x;
        this->py = pos_correction_y;
        memset(his_card, -1, 40);
        setRect(x,y,ax,ay);
    }

    Player() {
        this->name = "name";
        this->money = 0;
        this->position = 0;
        this->px = 0;
        this->py = 0;
        memset(his_card, -1, 40);
        setRect(0, 0, 0, 0);
    }

    Player & operator=(const Player& right) {
        name = right.name;
        position = right.position;
        money = right.money;
        for (int i = 0; i < 40; i++){
            his_card[i] = right.his_card[i];
        }
        px = right.px;
        py = right.py;

        return *this;
    }

    QString show_name(){
        return this->name;
    }

    int show_money(){
        return this->money;
    }

    void change_money(int change){
        this->money += change;
    }

    int show_position(){
        return this->position;
    }

    void move_position(int move){
        if (show_position() + move >= 40){
            this->change_money(1000); // за каждый пройденный круг игроку начисляется 1000 баллов
            move = show_position() + move - 40;
        } else
            move = show_position() + move;

        this->setPos(x[move] - px, y[move] - py);
    }

    int* show_his_card(){
        return his_card;
    }

    void change_his_card(int card_number){
        int i = 0;
        while (this->his_card[i] != -1){
            i++;
        }
        if (this->his_card[i] == -1)
            this->his_card[i] = card_number;
    }


};


namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(int count_players, QWidget *parent = nullptr);

    QString list_players[5];
    int players_cash[5] = {10000, 10000, 10000, 10000, 10000};

    QString all_info;

    ~GameWindow();

    int f_score = 0, f1_score = 0, f2_score = 0, f3_score = 0, f4_score = 0;
    int count_, num_players;
    int x[40] = {41, 129, 193, 257, 321, 385, 449, 513, 577, 641, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 641, 577, 513, 449, 385, 321, 257, 193, 129, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41};
    int y[40] = {41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 129, 193, 257, 321, 385, 449, 513, 577, 641, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 729, 641, 577, 513, 449, 385, 321, 257, 193, 129};

signals:
    void show_main_window();

private slots:
    void on_exit_from_game_button_clicked();

    void on_roll_cube_button_clicked();

    void on_buy_button_clicked();

    void on_sale_button_clicked();

private:
    Player *all_gamers;
    Ui::GameWindow *ui;
    QGraphicsView *graphicsView;
    QGraphicsScene* scene;
    Player *f, *f1, *f2, *f3, *f4;
};

#endif // GAMEWINDOW_H
