#include "begingamewindow.h"
#include "ui_begingamewindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QLayout>
#include <iostream>
#include <fstream>
#include <QFile>




BeginGameWindow::BeginGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeginGameWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint); // запретить изменять размер окна

}

BeginGameWindow::~BeginGameWindow()
{
    delete ui;
}

void BeginGameWindow::on_cancel_game_button_clicked()
{
    this -> close();
    all_gamers.clear();
    emit show_main_window();
}

void BeginGameWindow::on_add_player_button_clicked()
{

        QMessageBox add_players;
        QPushButton button_add;
        QFile fileOut("list_players.txt");

        add_players.setWindowFlags(Qt::ToolTip);
        add_players.setText("Введи Имя игрока");
        QLineEdit gamer_name;
        gamer_name.setGeometry(20,20,300,20);
        add_players.layout()->addWidget(&gamer_name);
        button_add.setText("Сохранить");
        add_players.addButton(&button_add, QMessageBox::AcceptRole);
        add_players.setDefaultButton(&button_add);
        int ret = add_players.exec();
        if (ret == QMessageBox::AcceptRole)
        {
            if(fileOut.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream writeStream(&fileOut);
                writeStream << gamer_name.text() + "\n";
                fileOut.close();
            }
            all_gamers.append(gamer_name.text());
            all_gamers.append('\n');
            i++;
        }

        ui->label_gamers->clear();
        ui->play_game_button->setStyleSheet("color: rgb(180, 180, 180); background-color: qlineargradient(spread:pad, x1:0.133876, y1:0.205, x2:0.134328, y2:0.875, stop:0.189055 rgba(187, 4, 4, 255), stop:0.626866 rgba(236, 5, 5, 255), stop:0.950249 rgba(195, 45, 45, 255)); font: 87 14pt Segoe UI Black");
        ui->label_gamers->setStyleSheet("color: rgb(255, 255, 255); font: 14pt");
        ui->label_gamers->setText("Список игроков: \n" + all_gamers);
        if (i == 5)
        {
            ui->add_player_button->setText("Ограничение игроков - 5");
            ui->add_player_button->setStyleSheet("color: rgb(180, 180, `80); background-color: qlineargradient(spread:pad, x1:0.133876, y1:0.205, x2:0.134328, y2:0.875, stop:0.189055 rgba(187, 4, 4, 255), stop:0.626866 rgba(236, 5, 5, 255), stop:0.950249 rgba(195, 45, 45, 255)); font: 87 14pt Segoe UI Black");
            ui->add_player_button->setEnabled(false);
        }
        if (i > 1)
        {
            ui->play_game_button->setText("ИГРАТЬ!");
            ui->play_game_button->setStyleSheet("color: rgb(255, 255, 255); background-color: qlineargradient(spread:pad, x1:0.133876, y1:0.205, x2:0.134328, y2:0.875, stop:0.189055 rgba(187, 4, 4, 255), stop:0.626866 rgba(236, 5, 5, 255), stop:0.950249 rgba(195, 45, 45, 255)); font: 87 14pt Segoe UI Black");
            ui->play_game_button->setEnabled(true);
            ui->play_game_button->setDefault(true);
        }
}

void BeginGameWindow::on_play_game_button_clicked()
{
    this -> close();
    game_window = new GameWindow(i, nullptr);
    game_window->show();
}
