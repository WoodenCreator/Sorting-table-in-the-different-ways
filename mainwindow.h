#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void qsort(double* mass, int size_);

private slots:
    void on_do_2_clicked();

    void on_close_clicked();

    void on_pushButton_random_clicked();

    void on_pushButton_sort_bubble_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_average_clicked();

    void on_pushButton_qsort_clicked();



    void on_pushButton_comb_clicked();

    void on_pushButton_gnome_sort_clicked();

    void on_pushButton_bogosort_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
