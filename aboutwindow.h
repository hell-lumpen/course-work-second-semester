#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

signals:
    void show_main_window();

private slots:
    //void on_about_button_clicked();

    void on_go_main_window_button_clicked();

private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
