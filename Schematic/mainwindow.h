#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_saveButton_clicked();

    void on_LoadButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
