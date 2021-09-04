#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_go_main_window_button_clicked()
{
    this -> close();
    emit show_main_window();
}
