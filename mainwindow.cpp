#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowFullScreen);

    QPixmap bkgnd("../monopoly/monopoly-preview-1920x1440px-1920_auto_x2_colored_light_ai.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    about_window = new AboutWindow();
    begin_game_window = new BeginGameWindow();
    game_window = new GameWindow(0, nullptr);

    connect(game_window, &GameWindow::show_main_window, this, &MainWindow::show);
    connect(about_window, &AboutWindow::show_main_window, this, &MainWindow::show);
    connect(begin_game_window, &BeginGameWindow::show_main_window, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_button_clicked()
{
    QMessageBox confirmation_closing;
    confirmation_closing.setWindowFlags(Qt::ToolTip);
    QPushButton button_yes, button_no;
    confirmation_closing.setText("Вы уверены что хотите закрыть приложение?");

    button_no.setText("Нет");
    button_yes.setText("Да");
    confirmation_closing.addButton(&button_no, QMessageBox::RejectRole);
    confirmation_closing.addButton(&button_yes, QMessageBox::AcceptRole);
    confirmation_closing.setDefaultButton(&button_no);
    int ret = confirmation_closing.exec();

    if (ret == QMessageBox::RejectRole)
    {
      QApplication::exit();
    }
}

void MainWindow::on_about_button_clicked()
{
    about_window -> show();
    //this->close();
}

void MainWindow::on_play_button_clicked()
{
    begin_game_window -> show();
    //this->close();
}
