#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray data = file.readAll();
    ui->tableWidget->setColumnCount(8);
    int rowCount = data.length() / 8;
    if (data.length() % 8 > 0) {
        rowCount++;
    }
    ui->tableWidget->setRowCount(rowCount);
    int bytePos = 0;
    for (int col = 0; col < 8; col++) {
        for (int row = 0; row < rowCount; row++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number((unsigned char)data[bytePos], 16));
            ui->tableWidget->setItem(col, row, item);
            bytePos++;
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

