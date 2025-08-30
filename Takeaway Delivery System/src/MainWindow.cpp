#include "MainWindow.h"

#include "SetMeal.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    ui.setupUi(this);
	m_setMealManager = new SetMealManager("res/setMeals.txt");
	m_fileSystem = new FileSystem();

	m_setMealManager->showAllShelvesSetMeals();

    ui.shelvesSetMealScrollArea->widget()->setLayout(m_setMealManager->getShelvesLayout());
	ui.basketSetMealScrollArea->widget()->setLayout(m_setMealManager->getBasketLayout());

    connect(m_setMealManager, &SetMealManager::totalPriceChanged, this, [this]() {
        ui.totalPriceLineEdit->setText(QString::number(m_setMealManager->getTotalPrice()));
		});
	connect(ui.settalPushButton, &QPushButton::clicked, m_setMealManager, &SetMealManager::showSettleWidget);
	connect(ui.clearAllBasketSetMealsButton, &QPushButton::clicked, m_setMealManager, &SetMealManager::clearAllBasketSetMeals);
	connect(ui.fileSettingButton, &QAction::triggered, m_fileSystem, &FileSystem::showFileSystemWidget);
	// ¼ÓÔØ 
    connect(ui.loadSetMeals, &QAction::triggered, this, [this]() {
		m_setMealManager->loadSetMeals(m_fileSystem->loadSetMeals());
		});
	connect(ui.loadAddresses, &QAction::triggered, this, [this]() {
		m_setMealManager->loadAddresses(m_fileSystem->loadAddresses());
		});

    // Ê±¼ä
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTime);
    m_timer->start(1000);
    updateTime();
}

MainWindow::~MainWindow(){
	delete m_timer;
	delete m_setMealManager;
	delete m_fileSystem;
}

void MainWindow::updateTime() {
    QString localTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui.localTimeLineEdit->setText(localTime);
}
