#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <qtimer.h>
#include <qdatetime.h>
#include "vendor/qflowlayout/flowlayout.h"
#include "SetMealManager.h"
#include "FileSystem.h"
#include "OrderManager.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    QTimer* m_timer;
	SetMealManager* m_setMealManager;
	FileSystem* m_fileSystem;
	OrderManager* m_orderManager;

	void connectSignalsAndSlots();
private slots:
    void updateTime();
};

