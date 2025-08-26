#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTime);
    m_timer->start(1000);
    updateTime();
}

MainWindow::~MainWindow()
{}

void MainWindow::updateTime() {
    QString localTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui.localTimeLineEdit->setText(localTime);
}
