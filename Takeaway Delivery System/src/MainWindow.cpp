#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    FlowLayout* fLayout = new FlowLayout();
    for (int i = 0;i < 50;i++) {
        QWidget* widget = new QWidget();
        QVBoxLayout* vLayout = new QVBoxLayout(widget);
        QLabel* label = new QLabel();
        label->setText("hello");
        vLayout->addWidget(label);
        fLayout->addWidget(widget);
    }
    ui.set_meal_scrollArea->widget()->setLayout(fLayout);

    // Ê±¼ä
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
