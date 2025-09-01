#include "MainWindow.h"

#include "SetMeal.h"

void MainWindow::connectSignalsAndSlots() {
	connect(m_setMealManager, &SetMealManager::totalPriceChanged, this, [this]() {
		ui.totalPriceLineEdit->setText(QString::number(m_setMealManager->getTotalPrice()));
		});
	connect(ui.settalPushButton, &QPushButton::clicked, m_setMealManager, &SetMealManager::showSettleWidget);
	connect(ui.clearAllBasketSetMealsButton, &QPushButton::clicked, m_setMealManager, &SetMealManager::clearAllBasketSetMeals);
	connect(ui.fileSettingButton, &QAction::triggered, m_fileSystem, &FileSystem::showFileSystemWidget);
	connect(ui.orderEditButton, &QPushButton::clicked, this, [this]() {
		m_orderManager->showOrderEditWidget(ui.orderListTable);
		});
	connect(m_orderManager, &OrderManager::ordersChanged, this, [this]() {
		m_orderManager->showAllOrders(ui.orderListTable);
		m_orderManager->showWatingOrders(ui.waitingOrderTable);
		ui.stratPointLabel->setText(QString::fromUtf8(m_orderManager->getNowPoint()));
		});
	connect(ui.fliterLineEdit, &QLineEdit::textChanged, this, [this]() {
		m_orderManager->showFlitteredOrders(ui.orderListTable, ui.fliterLineEdit);
		});
	connect(ui.deliverButton, &QPushButton::clicked, m_orderManager, &OrderManager::showDeliveryWidget);
	connect(m_setMealManager, &SetMealManager::newOrderPlaced, m_orderManager, &OrderManager::receiveNewOrder);
	// 加载 
	connect(ui.startWorkButton, &QAction::triggered, this, [this]() {
		m_setMealManager->loadSetMeals(m_fileSystem->loadSetMeals());
		m_setMealManager->loadAddresses(m_fileSystem->loadAddresses());
		m_orderManager->loadOrders(m_fileSystem->loadOrders());
		m_orderManager->loadMap(m_fileSystem->loadMap());
		});
	connect(ui.loadSetMeals, &QAction::triggered, this, [this]() {
		m_setMealManager->loadSetMeals(m_fileSystem->loadSetMeals());
		});
	connect(ui.loadAddresses, &QAction::triggered, this, [this]() {
		m_setMealManager->loadAddresses(m_fileSystem->loadAddresses());
		m_orderManager->loadMap(m_fileSystem->loadMap());
		});
	connect(ui.loadOrders, &QAction::triggered, this, [this]() {
		m_orderManager->loadOrders(m_fileSystem->loadOrders());
		});
	// 退出
	connect(ui.afterWorkButton, &QAction::triggered, m_orderManager, &OrderManager::CAN_I_GET_OFF_WORK);
	connect(m_orderManager, &OrderManager::HappyHappyHappy, m_fileSystem, &FileSystem::saveOrdersToFile);
	connect(m_orderManager, &OrderManager::HappyHappyHappy, this, &QApplication::quit);
}

void MainWindow::setupOrderTable()
{
	ui.orderListTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.orderListTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    ui.setupUi(this);
	m_setMealManager = new SetMealManager("res/setMeals.txt");
	m_fileSystem = new FileSystem();
	m_orderManager = new OrderManager();
	setupOrderTable();

	m_setMealManager->showAllShelvesSetMeals();

    ui.shelvesSetMealScrollArea->widget()->setLayout(m_setMealManager->getShelvesLayout());
	ui.basketSetMealScrollArea->widget()->setLayout(m_setMealManager->getBasketLayout());

	// 连接信号与槽
	connectSignalsAndSlots();

    // 时间
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTime);
    m_timer->start(1000);
    updateTime();
}

MainWindow::~MainWindow(){
	delete m_timer;
	delete m_setMealManager;
	delete m_fileSystem;
	delete m_orderManager;
}

void MainWindow::updateTime() {
    QString localTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui.localTimeLineEdit->setText(localTime);
}
