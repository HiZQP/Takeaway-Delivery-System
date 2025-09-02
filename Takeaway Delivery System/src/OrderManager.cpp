#include "OrderManager.h"
#include <QMessageBox>
#include <vector>

void OrderManager::connectSignalsAndSlots() {
	connect(m_orderEditControls.saveButton, &QPushButton::clicked, this, &OrderManager::saveOrderEdit);
	connect(m_deliveryControls.deliverButton, &QPushButton::clicked, this, &OrderManager::deliverOrder);
	connect(m_orderEditControls.cancelOrderButton, &QPushButton::clicked, this, &OrderManager::cancelOrder);
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

	QHBoxLayout* hLayout = new QHBoxLayout();
	m_orderEditControls.saveButton = new QPushButton();
	m_orderEditControls.saveButton->setText(QString::fromUtf8("保存修改"));
	m_orderEditControls.cancelOrderButton = new QPushButton();
	m_orderEditControls.cancelOrderButton->setText(QString::fromUtf8("取消订单"));

	vLayout->addWidget(label1);
	vLayout->addWidget(m_orderEditControls.orderIDLabel);
	formLayout->addRow(label2, m_orderEditControls.consigneeLineEdit);
	formLayout->addRow(label3, m_orderEditControls.phoneLineEdit);
	vLayout->addLayout(formLayout);
	hLayout->addWidget(m_orderEditControls.saveButton);
	hLayout->addWidget(m_orderEditControls.cancelOrderButton);
	vLayout->addLayout(hLayout);
}

void OrderManager::setupDeliveryWidget() {
	m_deliveryWidget = new QWidget();
	QVBoxLayout* vLayout = new QVBoxLayout(m_deliveryWidget);
	QFormLayout* formLayout = new QFormLayout();
	formLayout->setLabelAlignment(Qt::AlignRight);

	QLabel* label1 = new QLabel();
	label1->setText(QString::fromUtf8("配送信息"));
	label1->setAlignment(Qt::AlignCenter);
	QFont Font = label1->font();
	Font.setPointSize(14);
	Font.setBold(true);
	label1->setFont(Font);

	QLabel* label4 = new QLabel();
	label4->setText(QString::fromUtf8("起点："));
	m_deliveryControls.stratPoint = new QLabel();
	QLabel* label5 = new QLabel();
	label5->setText(QString::fromUtf8("终点："));
	m_deliveryControls.endPoint = new QLabel();

	QLabel* label2 = new QLabel();
	label2->setText(QString::fromUtf8("最短路线："));
	m_deliveryControls.pathLabel = new QLabel();
	QLabel* label3 = new QLabel();
	label3->setText(QString::fromUtf8("最短距离："));
	m_deliveryControls.distenceLabel = new QLabel();

	m_deliveryControls.deliverButton = new QPushButton();
	m_deliveryControls.deliverButton->setText(QString::fromUtf8("确定配送"));

	formLayout->addRow(label4, m_deliveryControls.stratPoint);
	formLayout->addRow(label5, m_deliveryControls.endPoint);
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
	m_nowPoint = mapdata.map[0];
	emit ordersChanged();
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
	for (auto& order : m_orders) {
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
	int selectedRow = orderTable->selectedItems().first()->row();
	QTableWidgetItem* item = orderTable->item(selectedRow, 0);
	m_selectedOrderID = item->text().toStdString();
	for (auto& order : m_orders) {
		if (m_selectedOrderID == order.orderId) {
			m_orderEditControls.orderIDLabel->setText(QString::fromStdString(order.orderId));
			m_orderEditControls.consigneeLineEdit->setText(QString::fromStdString(order.consignee));
			m_orderEditControls.phoneLineEdit->setText(QString::fromStdString(order.phone));
			break;
		}
	}
	
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
	for (auto& order : m_orders) {
		if (m_selectedOrderID == order.orderId) {
			order.consignee = consignee;
			order.phone = phone;
			break;
		}
	}
	m_orderEditControls.consigneeLineEdit->clear();
	m_orderEditControls.phoneLineEdit->clear();
	m_orderEditWidget->close();

	emit ordersChanged();
}

void OrderManager::showDeliveryWidget(){
	for (std::vector<Order>::reverse_iterator it = m_orders.rbegin(); it != m_orders.rend(); ++it) {
		if (it->orderStatus == "待配送") {
			ShortestPath shortestPath = m_map.floyd(m_nowPoint, it->address);
			m_deliveryControls.stratPoint->setText(QString::fromUtf8(m_nowPoint));
			m_deliveryControls.endPoint->setText(QString::fromUtf8(it->address));
			m_deliveryControls.pathLabel->setText(QString::fromUtf8(shortestPath.path)); 
			m_deliveryControls.distenceLabel->setText(QString::fromUtf8(std::to_string(shortestPath.pathLength) + "km"));
			m_deliveryWidget->show();
			break;
		}
	}
}

void OrderManager::deliverOrder(){
	for (std::vector<Order>::reverse_iterator it = m_orders.rbegin(); it != m_orders.rend(); ++it) {
		if (it->orderStatus == "待配送") {
			it->orderStatus = "已配送";
			m_nowPoint = it->address;
			m_deliveryWidget->close();
			emit ordersChanged();
			break;
		}
	}
}

void OrderManager::cancelOrder(){
	for (auto& order : m_orders) {
		if (m_selectedOrderID == order.orderId) {
			if (order.orderStatus == "已配送") {
				QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("订单已配送，取消无效！"));
				return;
			}
			order.orderStatus = "已取消";
			QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("订单已取消！"));
			break;
		}
	}
	m_orderEditWidget->close();

	emit ordersChanged();
}

void OrderManager::CAN_I_GET_OFF_WORK(){
	for (auto& order : m_orders) {
		if (order.orderStatus == "待配送") {
			QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("仍有订单未完成，不能下班！"));
			return;
		}
	}
	QMessageBox msgBox;
	msgBox.setWindowTitle(QString::fromUtf8("下班了！"));
	msgBox.setText(QString::fromUtf8("感谢使用本系统！"));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int result = msgBox.exec();
	emit HappyHappyHappy();
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