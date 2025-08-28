#include "MainWindow.h"

#include "SetMeal.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    ui.setupUi(this);
	m_setMealManager = new SetMealManager("D://setMeals.txt");

    FlowLayout* fLayout = new FlowLayout();
	m_setMealManager->showAllSetMeals(fLayout);

    ui.set_meal_scrollArea->widget()->setLayout(fLayout);

    // Ê±¼ä
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTime);
    m_timer->start(1000);
    updateTime();
}

MainWindow::~MainWindow(){
	delete m_timer;
	delete m_setMealManager;
}

void MainWindow::updateTime() {
    QString localTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui.localTimeLineEdit->setText(localTime);
}
