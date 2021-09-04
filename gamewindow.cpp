#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <begingamewindow.h>
#include <QTimer>
#include <windows.h>
#include <QFile>
#include <iostream>

struct Card{
    QString card_name[40] = {"Старт. При проходе вы получите 1000$", "Chanel", "?", "Hugo Boss", "money", "Mersedes", "Adidas", "?", "Puma", "LACOSTE", "Prison", "VK", "Rockstar", "Facebook", "Twitter", "Audi", "Coca Cola", "?", "Pepsi", "Fanta", "nothing", "American Airlines", "?", "Lufthansa", "British Airways", "Ford", "McDonald's", "Burger King", "Rovio", "KFC", "police", "Holiday Inn", "Radisson", "?", "Novotel", "Land Rover", "diamond", "Apple", "?", "Nokia"};
    int purchase_price[40] = {0, 2000, 0, 3000, 0, 5000, 4000, 0, 2500, 3000, 0, 6000, 5500, 6500, 4500, 4000, 3500, 0, 2000, 2500, 0, 3000, 0, 3500, 2500, 4000, 3500, 2000, 2500, 5000, 0, 2500, 3000, 0, 4000, 4000, 0, 5000, 0, 4500};
    int sale_price[40] = {0};
    int card_holder[40];
} Card ;


GameWindow::GameWindow(int count_players, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowFullScreen);
    num_players = count_players;

    memset(&Card.card_holder, -1, 40);

    QFile file("list_players.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
    }

    QTextStream in(&file);

    for (int i = 0; i < count_players; i++){
            list_players[i] = in.readLine();
            std::cout << list_players[i].toLocal8Bit().constData();
    }

    file.close();
    file.remove();


    ui->graphicsView->setGeometry(0, 0, 800, 800);
    QGraphicsScene *scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height(), this);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());

    ui->label->setStyleSheet("color: rgb(255, 255, 255); font: 14pt");
    ui->label->setText("Сейчас ходит " + list_players[0].toUpper() + "\nДалее " + list_players[1]);

    ui->label_3->setStyleSheet("color: rgb(255, 255, 255); font: 14pt");
    ui->label_3->setText("Начало игры. " + list_players[0] + " бросай кубик");

    for (int i = 0; i < num_players; i++){
        all_info.append(list_players[i] + " ");
        all_info.append(QString::number(players_cash[i]) + "\n");
    }

    ui->label_2->setStyleSheet("color: rgb(255, 255, 255); font: 14pt");
    ui->label_2->setText(all_info); // при нажатии на кнопки купить продать или попадании на специальные поля переписывать инфу

    Player *all_gamers = new Player[count_players];

    Qt::GlobalColor color[5] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::white};

    int corr_pos_x[5] = {0, 20, -20, 20, -20}; // расстояния для размещения новых объектов относительно середины карточки
    int corr_pos_y[5] = {0, 0, 0, -20, -20};


    for (int i = 0; i < count_players; i++) {
        all_gamers[i] = Player(list_players[i], 0, 0, 30, 30, 10000, 0, corr_pos_x[i], corr_pos_y[i]);
        all_gamers[i].setBrush(QBrush(color[i], Qt::SolidPattern));
        scene->addItem(&all_gamers[i]);
    }

    scene->setBackgroundBrush(QBrush(QImage("../monopoly/monopoly_area_photo-resizer.ru.PNG")));

    count_ = 0;
}

GameWindow::~GameWindow()
{
    delete [] all_gamers;
    delete ui;
}

void GameWindow::on_exit_from_game_button_clicked()
{
    this->close();
    emit show_main_window();
}


void GameWindow::on_roll_cube_button_clicked()
{
    srand(time(0));
    int cube1  = 1 + rand() % 5;
    int cube2 = 1 + rand() % 5;
    ui->label_4->setText(QString::number(cube1) + " : " + QString::number(cube2));
    all_gamers[count_].move_position(cube1 + cube2);


    if (count_ == 0){
        f_score += cube1 + cube2;
        if (f_score >= 40){
            f_score -= 40;
        }
        f->setPos(x[f_score], y[f_score]);
        if (Card.purchase_price[f_score] != 0)
            ui->label_3->setText("Карта: " + Card.card_name[f_score] + "\nСтоимость покупки " + QString::number(Card.purchase_price[f_score]));
        else
            ui->label_3->setText("Карта: " + Card.card_name[f_score]);
    }
    else if (count_ == 1){
        f1_score += cube1 + cube2;
        if (f1_score >= 40){
            f1_score -= 40;
        }
        f1->setPos(x[f1_score] + 20, y[f1_score]);
        if (Card.purchase_price[f1_score] != 0)
            ui->label_3->setText("Карта: " + Card.card_name[f1_score] + "\nСтоимость покупки " + QString::number(Card.purchase_price[f1_score]));
        else
            ui->label_3->setText("Карта: " + Card.card_name[f1_score]);
    }
    else if (count_ == 2){
        f2_score += cube1 + cube2;
        if (f2_score >= 40){
            f2_score -= 40;
        }
        f2->setPos(x[f2_score] - 20, y[f2_score]);
        if (Card.purchase_price[f2_score] != 0)
            ui->label_3->setText("Карта: " + Card.card_name[f2_score] + "\nСтоимость покупки " + QString::number(Card.purchase_price[f2_score]));
        else
            ui->label_3->setText("Карта: " + Card.card_name[f2_score]);
    }
    else if (count_ == 3){
        f3_score += cube1 + cube2;
        if (f3_score >= 40){
            f3_score -= 40;
        }
        f3->setPos(x[f3_score] + 20, y[f3_score] - 20);
        if (Card.purchase_price[f3_score] != 0)
            ui->label_3->setText("Карта: " + Card.card_name[f3_score] + "\nСтоимость покупки " + QString::number(Card.purchase_price[f3_score]));
        else
            ui->label_3->setText("Карта: " + Card.card_name[f3_score]);
    }
    else if (count_ == 4){
        f4_score += cube1 + cube2;
        if (f4_score >= 40){
            f4_score -= 40;
        }
        f4->setPos(x[f4_score] - 20, y[f4_score] - 20);
        if (Card.purchase_price[f4_score] != 0)
            ui->label_3->setText("Карта: " + Card.card_name[f4_score] + "\nСтоимость покупки " + QString::number(Card.purchase_price[f4_score]));
        else
            ui->label_3->setText("Карта: " + Card.card_name[f4_score]);


    }

    if (count_ + 1 < num_players)
        count_++;
    else
        count_ = 0;

    ui->label->setText("Сейчас ходит " + list_players[(count_ == num_players) ? 0 : count_].toUpper() + "\nДалее " + list_players[(count_ + 1 == num_players) ? 0 : count_ + 1]);
}


void GameWindow::on_buy_button_clicked()
{

}

void GameWindow::on_sale_button_clicked()
{

}
