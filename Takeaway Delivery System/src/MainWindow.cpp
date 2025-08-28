#include "MainWindow.h"

#include "SetMeal.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    ui.setupUi(this);
	m_setMealManager = new SetMealManager("res/setMeals.txt");

	m_setMealManager->showAllShelvesSetMeals();

    ui.shelvesSetMealScrollArea->widget()->setLayout(m_setMealManager->getShelvesLayout());
	ui.basketSetMealScrollArea->widget()->setLayout(m_setMealManager->getBasketLayout());

    connect(m_setMealManager, &SetMealManager::totalPriceChanged, this, [this]() {
        ui.totalPriceLineEdit->setText(QString::number(m_setMealManager->getTotalPrice()));
		});

	connect(ui.clearAllBasketSetMealsButton, &QPushButton::clicked, m_setMealManager, &SetMealManager::clearAllBasketSetMeals);
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
