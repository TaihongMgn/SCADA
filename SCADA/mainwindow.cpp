#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->navList,&QListWidget::currentRowChanged,
            ui->pages,&QStackedWidget::setCurrentIndex);

    ui->navList->setCurrentRow(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}
