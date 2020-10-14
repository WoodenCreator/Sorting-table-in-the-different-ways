#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random> // генератор псевдорандомных чисел с использованием текущего времени
#include <ctime>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_error->setVisible(false);
    ui->label_error->setStyleSheet("color: rgb(255, 0, 0)");
    ui->pushButton_average->setEnabled(false);
    ui->pushButton_max->setEnabled(false);
    ui->pushButton_min->setEnabled(false);
    ui->pushButton_random->setEnabled(false);
    ui->radioButton_raws->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_do_2_clicked()
{
    bool ok = true;
    if (ui->lineEdit_points->text().toInt(&ok))
    {
        ui->pushButton_average->setEnabled(true);
        ui->pushButton_max->setEnabled(true);
        ui->pushButton_min->setEnabled(true);
        ui->pushButton_random->setEnabled(true);
    }
    if (ui->radioButton_raws->isChecked())
    {
        while (ui->table->columnCount() > 1)
        {
            ui->table->removeColumn(1);
        }
        ui->table->setRowCount(0);
        int count = ui->lineEdit_points->text().toInt();
        ui->table->setRowCount(count);
        for (int i = 0;i < count; i++)
        {
            ui->table->setItem(i,0, new QTableWidgetItem("0"));
        }
    }
    else if (ui->radioButton_columns->isChecked())
    {
        while (ui->table->rowCount() > 1)
        {
            ui->table->removeRow(1);
        }
        ui->table->setColumnCount(0);
        int count = ui->lineEdit_points->text().toInt();
        ui->table->setColumnCount(count);
        for (int i = 0;i < count; i++)
        {
            ui->table->setItem(0,i, new QTableWidgetItem("0"));
        }
    }



}

void MainWindow::on_close_clicked()
{
    qApp->exit();
}

void MainWindow::on_pushButton_random_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double val = 0.0;

    std::mt19937 engine;
    engine.seed(std::time(nullptr));
    if (colCount == 1)
    {
        for(int i = 0; i < rowCount; i++)
        {
          val = engine() / 98213.05;
          ui->table->item(i,0)->setText(QString::number(val));

        }
    }
    else if (rowCount == 1)
    {
    for(int j = 0; j < colCount;j++)
       {
        val = engine() / 98213.05;;
        ui->table->item(0,j)->setText(QString::number(val));
       }
    }
}


void MainWindow::on_pushButton_sort_bubble_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double value = 0.0;
    double mass[colCount][rowCount];
    double temp = 0;
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                ui->table->item(r,c)->setBackground(Qt::red);
                ui->table->item(r,c)->isSelected();
                return;
                }
                ui->label_error->setVisible(false);
                mass[c][r] = value;

        }
    }

    //сортировка пузырьком
    if (colCount == 1)
    {
        //mass[0][i]
        int i = 0;
        int g = 1;
        while(i < rowCount)
        {
            while(g < rowCount)
            {
                if (mass[0][i] > mass[0][g])
                {
                    temp = mass[0][g];
                    mass[0][g] = mass[0][i];
                    mass[0][i] = temp;
                }
                g++;
            }
            i++;
            g = i+1;
        }
        QString temp;
        for (int r =0; r < rowCount; r++) {
            temp.setNum(mass[0][r]);
            ui->table->item(r, 0)->setText(temp);
        }
    }

    else if (rowCount == 1)
    {
        //mass[i][0]
        int i = 0;
        int g = 1;
        while(i < colCount)
        {
            while(g < colCount)
            {
                if (mass[i][0] > mass[g][0])
                {
                    temp = mass[g][0];
                    mass[g][0] = mass[i][0];
                    mass[i][0] = temp;
                }
                g++;
            }
            i++;
            g = i+1;
        }
        QString temp;
        for (int r =0; r < colCount; r++)
        {
            temp.setNum(mass[r][0]);
            ui->table->item(0, r)->setText(temp);
        }
    }

}

void MainWindow::qsort(double *mass, int size_)
{
    int mid;
       int i = 0;
       double temp = 0;
       int j = size_-1;
       mid = (size_ / 2);
       while (i <= j)
       {
           while(*(mass+i) < *(mass+mid))
              i++;
           while(*(mass+j) > *(mass+mid))
               j--;
           if (i <= j) {
               temp = *(mass+i);
               *(mass+i) = *(mass+j);
               *(mass+j) = temp;

               i++;
               j--;
           }
       }
       if(j > 0) {
           //"Левый кусок"
           qsort(mass, j + 1);
       }
       if (i < size_) {
           //"Прaвый кусок"
           qsort(&mass[i], size_ - i); // начало i-го элемента
       }
}

void MainWindow::on_pushButton_qsort_clicked()
{
    int colCount = ui->table->columnCount();
        int rowCount = ui->table->rowCount();
        double value = 0.0;
        double *mass;
        bool ok = true;
        if ((colCount > 1) && (rowCount == 1)) {
            mass = new double [colCount];
            for (int c = 0; c < colCount; c++)
            {
                QTableWidgetItem* item =ui->table->item(0, c);
                if (!item){
                    continue;
                }
                value = item->text().toDouble(&ok);
                if (ok == false) {
                    ui->label_error->setVisible(true);
                    ui->table->item(0,c)->setBackground(Qt::red);
                    ui->table->item(0,c)->isSelected();
                    return;
                    }
                     ui->label_error->setVisible(false);
                     mass[c] = value;
            }
            qsort(mass, colCount);
        }
        if ((colCount == 1) && (rowCount > 1)) {
            mass = new double [rowCount];
            for (int r = 0; r < rowCount; r++)
            {
                QTableWidgetItem* item =ui->table->item(r, 0);
                if (!item){
                    continue;
                }
                value = item->text().toDouble(&ok);
                if (ok == false) {
                    ui->label_error->setVisible(true);
                    ui->table->item(r, 0)->setBackground(Qt::red);
                    ui->table->item(r,0)->isSelected();
                    return;
                    }
                mass[r] = value;
            }
            qsort(mass, rowCount);
        }

        QString temp;
        if ((colCount > 1) && (rowCount == 1)) {
            for (int c = 0; c < colCount; c++)
            {
                temp.setNum(mass[c]);
                ui->table->item(0, c)->setText(temp);
            }
            delete mass;
        }
        if ((colCount == 1) && (rowCount > 1)) {
            for (int c = 0; c < rowCount; c++)
            {
                temp.setNum(mass[c]);
                ui->table->item(c, 0)->setText(temp);
            }
            delete mass;
        }
}

void MainWindow::on_pushButton_comb_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double value = 0.0;
    double mass[colCount][rowCount];
    int jump = 0;// расстояние между двумя переменными, которые будут сортироваться
    bool swapped = true; // varaible, that shows, was sorting or not
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                 ui->table->item(r,c)->setBackground(Qt::red);
                 ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;
        }
    }

    if (colCount == 1)
    {
        jump = rowCount;
        while (jump > 1 || swapped)
        {
            if (jump > 1)
                jump = (int)(jump / 1.25);
            swapped = false;
            for (int i = 0;i +jump < rowCount; i++)
                if (mass[0][i] > mass[0][i+jump])
                    std::swap(mass[0][i], mass[0][i+jump]), swapped = true;
        }
        QString temp;
        for (int r =0; r < rowCount; r++) {
            temp.setNum(mass[0][r]);
            ui->table->item(r, 0)->setText(temp);
            }
    }
    else if (rowCount == 1)
    {
        jump = colCount;
        while (jump > 1 || swapped)
        {
            if (jump > 1)
                jump = (int)(jump / 1.25);
            swapped = false;
            for (int i = 0;i +jump < colCount; i++)
                if (mass[0][i] > mass[0][i+jump])
                    std::swap(mass[0][i], mass[0][i+jump]), swapped = true;
        }
    }
    QString temp;
    for (int r =0; r < colCount; r++) {
        temp.setNum(mass[r][0]);
        ui->table->item(0, r)->setText(temp);
        }
}

void MainWindow::on_pushButton_gnome_sort_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double value = 0.0;
    double mass[colCount][rowCount];
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                 ui->table->item(r,c)->setBackground(Qt::red);
                 ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;
        }
    }
    int i = 1;
    int j = 2;
    if (colCount == 1)
    {
        while (i < rowCount)
        {
            if (mass[0][i-1] < mass[0][i])
            {
                i = j;
                j = j+1;
            }
            else
            {
                std::swap(mass[0][i-1], mass[0][i]);
                i = i-1;
                if (i ==0)
                {
                    i = j;
                    j = j+1;
                }
            }
        }
        QString temp;
        for (int r =0; r < rowCount; r++) {
            temp.setNum(mass[0][r]);
            ui->table->item(r, 0)->setText(temp);
            }
    }
    else if (rowCount == 1)
    {
        while (i < colCount)
        {
            if (mass[i-1][0] < mass[i][0])
            {
                i = j;
                j = j+1;
            }
            else
            {
                std::swap(mass[i-1][0], mass[i][0]);
                i = i-1;
                if (i ==0)
                {
                    i = j;
                    j = j+1;
                }
            }
        }
        QString temp;
        for (int r =0; r < colCount; r++) {
            temp.setNum(mass[r][0]);
            ui->table->item(0, r)->setText(temp);
            }
    }
}

void MainWindow::on_pushButton_bogosort_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double value = 0.0;
    double mass[colCount][rowCount];
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                 ui->table->item(r,c)->setBackground(Qt::red);
                 ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;
        }
    }
    int i = 0;
    if (colCount == 1)
    {
        while (i < rowCount-1)
        {
           if (mass[0][i] < mass[0][i+1])
           {
               i++;
               continue;
           }
           else
           {
               for(int j = 0; j < rowCount; j++)
                   std::swap(mass[0][i], mass[0][(rand() % rowCount)]);
               i = 0;
           }
        }
        QString temp;
        for (int r =0; r < rowCount; r++) {
            temp.setNum(mass[0][r]);
            ui->table->item(r, 0)->setText(temp);
            }
    }
    else if (rowCount == 1)
    {
        while (i < colCount-1)
        {
           if (mass[i][0] < mass[i+1][0])
           {
               i++;
               continue;
           }
           else
           {
               for(int j = 0; j < colCount; j++)
                   std::swap(mass[i][0], mass[(rand() % colCount)][0]);
               i = 0;
           }
        }
        QString temp;
        for (int r =0; r < colCount; r++) {
            temp.setNum(mass[r][0]);
            ui->table->item(0, r)->setText(temp);
            }
    }
}


void MainWindow::on_pushButton_min_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    int i = 0;
    double value = 0.0;

    double mass[colCount][rowCount];
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                ui->table->item(r,c)->setBackground(Qt::red);
                ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;

        }
    }
    double res = mass[0][0];
    if (colCount == 1)
    {
        while (i < rowCount)
        {
          if (mass[0][i] < res)
            res = mass[0][i];
          i++;
        }
        ui->label_res->setText(QString::number(res));
     }
    else if (rowCount == 1)
    {
        while (i < colCount)
        {
            if (mass[i][0] < res)
              res = mass[i][0];
            i++;
        }
        ui->label_res->setText(QString::number(res));
    }
}

void MainWindow::on_pushButton_max_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    int i = 0;
    double value = 0.0;

    double mass[colCount][rowCount];
    double res = mass[0][0];
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                ui->table->item(r,c)->setBackground(Qt::red);
                ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;

        }
    }
    if (colCount == 1)
    {
        while (i < rowCount)
        {
          if (mass[0][i] > res)
            res = mass[0][i];
          i++;
        }
        ui->label_res->setText(QString::number(res));
     }
    else if (rowCount == 1)
    {
        while (i < colCount)
        {
            if (mass[i][0] > res)
              res = mass[i][0];
            i++;
        }
        ui->label_res->setText(QString::number(res));
    }
}

void MainWindow::on_pushButton_average_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    int i = 0;
    double value = 0.0;

    double mass[colCount][rowCount];
    double res = mass[0][0];
    bool ok = true;
    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
            }
            value = item->text().toDouble(&ok);
            if (ok == false) {
                ui->label_error->setVisible(true);
                ui->table->item(r,c)->setBackground(Qt::red);
                ui->table->item(r,c)->isSelected();
                return;
                }
            ui->label_error->setVisible(false);
                mass[c][r] = value;

        }
    }
    if (colCount == 1)
    {
        while (i < rowCount)
        {
            res += mass[0][i];
            i++;
        }
        res = res/rowCount;
        ui->label_res->setText(QString::number(res));
     }
    else if (rowCount == 1)
    {
        while (i < colCount)
        {
              res += mass[i][0];
                i++;
        }
              res = res/colCount;
        ui->label_res->setText(QString::number(res));
    }
}
