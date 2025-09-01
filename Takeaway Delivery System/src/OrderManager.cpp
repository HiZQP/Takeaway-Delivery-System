#include "OrderManager.h"
#include <QMessageBox>
#include <vector>

void OrderManager::connectSignalsAndSlots() {
	connect(m_orderEditControls.saveButton, &QPushButton::clicked, this, &OrderManager::saveOrderEdit);
	connect(m_deliveryControls.deliverButton, &QPushButton::clicked, this, &OrderManager::);
}

void OrderManager::setupOrderEditWidget(){
	m_orderEditWidget = new QWidget();
	QVBoxLayout* vLayout = new QVBoxLayout(m_orderEditWidget);
	QFormLayout* formLayout = new QFormLayout();

	QLabel* label1 = new QLabel();
	label1->setText(QString::fromUtf8("订单编号"));

	m_orderEditControls.orderIDLabel = new QLabel();
	QFont Font = m_orderEditControls.orderIDLabel->font();
	Font.setPointSize(14);
	Font.setBold(true);
	m_orderEditControls.orderIDLabel->setFont(Font);

	QLabel* label2 = new QLabel();
	label2->setText(QString::fromUtf8("收货人姓名："));
	QLabel* label3 = new QLabel();
	label3->setText(QString::fromUtf8("收货人电话："));

	m_orderEditControls.consigneeLineEdit = new QLineEdit();
	m_orderEditControls.phoneLineEdit = new QLineEdit();

	m_orderEditControls.saveButton = new QPushButton();
	m_orderEditControls.saveButton->setText(QString::fromUtf8("保存修改"));

	vLayout->addWidget(label1);
	vLayout->addWidget(m_orderEditControls.orderIDLabel);
	formLayout->addRow(label2, m_orderEditControls.consigneeLineEdit);
	formLayout->addRow(label3, m_orderEditControls.phoneLineEdit);
	vLayout->addLayout(formLayout);
	vLayout->addWidget(m_orderEditControls.saveButton);
}

void OrderManager::setupDeliveryWidget() {
	m_deliveryWidget = new QWidget();
	QVBoxLayout* vLayout = new QVBoxLayout(m_deliveryWidget);
	QFormLayout* formLayout = new QFormLayout();

	QLabel* label1 = new QLabel();
	label1->setText(QString::fromUtf8("配送信息"));
	label1->setAlignment(Qt::AlignCenter);

	QLabel* label2 = new QLabel();
	label2->setText(QString::fromUtf8("最短路线："));
	m_deliveryControls.pathLabel = new QLabel();
	QLabel* label3 = new QLabel();
	label3->setText(QString::fromUtf8("最短距离："));
	m_deliveryControls.distenceLabel = new QLabel();

	m_deliveryControls.deliverButton = new QPushButton();

	formLayout->addRow(label2, m_deliveryControls.pathLabel);
	formLayout->addRow(label3, m_deliveryControls.distenceLabel);
	vLayout->addWidget(label1);
	vLayout->addLayout(formLayout);
	vLayout->addWidget(m_deliveryControls.deliverButton);
}

OrderManager::OrderManager() {
	setupOrderEditWidget();
	setupDeliveryWidget();
	connectSignalsAndSlots();
}

OrderManager::~OrderManager() {
	delete m_orderEditWidget;
	delete m_deliveryWidget;
}

void OrderManager::loadOrders(const std::vector<Order>& orders){
	// 清空现有订单
	m_orders.clear();

	for (const auto& order : orders)
		m_orders.push_back(order);
	emit ordersChanged();
}

void OrderManager::loadMap(const MapData& mapdata){
	m_map.loadMap(mapdata);
}

void OrderManager::showAllOrders(QTableWidget* orderTable) {
	// 清空表格
	orderTable->clearContents();

	orderTable->setRowCount(m_orders.size());
	int row = 0;
	// 显示订单
	for (const auto& order : m_orders) {
		orderTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(order.orderId)));
		orderTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(order.consignee)));
		orderTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(order.phone)));
		orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(order.address)));
		orderTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(order.setMealID)));
		orderTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(order.setMealCount)));
		orderTable->setItem(row, 6, new QTableWidgetItem(QString::number(order.totalPrice)));
		orderTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(order.orderTime)));
		orderTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(order.orderStatus)));
		row++;
	}
}

void OrderManager::showWatingOrders(QTableWidget* orderTable) {
	orderTable->clearContents();
	orderTable->setRowCount(m_orders.size());
	int row = 0;
	for (std::vector<Order>::reverse_iterator it = m_orders.rbegin(); it != m_orders.rend(); ++it) {
		if (it->orderStatus == "待配送") {
			orderTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(it->orderId)));
			orderTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(it->consignee)));
			orderTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(it->phone)));
			orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(it->address)));
			orderTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(it->setMealID)));
			orderTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(it->setMealCount)));
			orderTable->setItem(row, 6, new QTableWidgetItem(QString::number(it->totalPrice)));
			orderTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(it->orderTime)));
			row++;
		}
	}
}

void OrderManager::showFlitteredOrders(QTableWidget* orderTable, QLineEdit* lineEdit) {
	// 清空表格
	if (lineEdit->text().isEmpty())
		showAllOrders(orderTable);
	orderTable->clearContents();
	std::string fliter = lineEdit->text().toStdString();
	std::vector<Order> fliteredOrders;
	int row = 0;
	for (auto order : m_orders) {
		if (order.orderId.find(fliter) != std::string::npos || order.consignee.find(fliter) != std::string::npos) {
			orderTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(order.orderId)));
			orderTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(order.consignee)));
			orderTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(order.phone)));
			orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(order.address)));
			orderTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(order.setMealID)));
			orderTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(order.setMealCount)));
			orderTable->setItem(row, 6, new QTableWidgetItem(QString::number(order.totalPrice)));
			orderTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(order.orderTime)));
			orderTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(order.orderStatus)));
			row++;
		}
	}
}

void OrderManager::showOrderEditWidget(QTableWidget* orderTable)
{
	if (orderTable->selectedItems().isEmpty())
		return;
	m_selectedRow = 0;
	m_selectedRow = orderTable->selectedItems().first()->row();
	m_orderEditControls.orderIDLabel->setText(QString::fromStdString(m_orders[m_selectedRow].orderId));
	m_orderEditControls.consigneeLineEdit->setText(QString::fromStdString(m_orders[m_selectedRow].consignee));
	m_orderEditControls.phoneLineEdit->setText(QString::fromStdString(m_orders[m_selectedRow].phone));
	m_orderEditWidget->show();
}

void OrderManager::saveOrderEdit(){
	std::string consignee, phone;
	consignee = m_orderEditControls.consigneeLineEdit->text().toStdString();
	phone = m_orderEditControls.phoneLineEdit->text().toStdString();
	if (consignee.empty() || phone.empty()) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("请完整填写订单信息！"));
		return;
	}
	if (phone.size() != 11 || !std::all_of(phone.begin(), phone.end(), ::isdigit)) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("请输入有效的11位电话号码！"));
		return;
	}

	m_orders[m_selectedRow].consignee = consignee;
	m_orders[m_selectedRow].phone = phone;

	m_orderEditControls.consigneeLineEdit->clear();
	m_orderEditControls.phoneLineEdit->clear();
	m_orderEditWidget->close();

	emit ordersChanged();
}

void OrderManager::showDeliveryWidget(){
	for (std::vector<Order>::reverse_iterator it = m_orders.rbegin(); it != m_orders.rend(); ++it) {
		if (it->orderStatus == "待配送") {
			m_deliveryControls.pathLabel
			break;
		}
	}
}

void OrderManager::receiveNewOrder(
	const std::string& orderId,
	const std::string& consignee,
	const std::string& phone,
	const std::string& address,
	const std::string& setMealID,
	const std::string& setMealCount,
	const std::string& totalPrice,
	const std::string& orderTime,
	const std::string& orderStatus) {
	Order newOrder{
			orderId,
			consignee,
			phone,
			address,
			setMealID,
			setMealCount,
			std::stoi(totalPrice),
			orderTime,
			orderStatus
	};
	m_orders.insert(m_orders.begin(), newOrder);

	emit ordersChanged();
}