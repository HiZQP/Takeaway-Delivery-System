#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <qtimer.h>
#include <qdatetime.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    QTimer* m_timer;

private slots:
    void updateTime();
};

