#include "OrderManager.h"
#include "QLineEdit"

void OrderManager::connectSignalsAndSlots() {

}

OrderManager::OrderManager()
{
	connectSignalsAndSlots();
}

OrderManager::~OrderManager()
{
}

void OrderManager::loadOrders(const std::vector<Order>& orders){
	// 清空现有订单
	m_orders.clear();

	for (const auto& order : orders)
		m_orders.push_back(order);
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
	emit saveOrders(m_orders);
}