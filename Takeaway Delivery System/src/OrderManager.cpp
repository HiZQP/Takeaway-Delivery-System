#include "OrderManager.h"

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
	m_waitingOrders.clear();
	m_deliveredOrders.clear();
	m_cancelledOrders.clear();
	// 分类存储订单
	for (const auto& order : orders) {
		if (order.orderStatus == "待配送") {
			m_waitingOrders.push_back(order);
		}
		else if (order.orderStatus == "已配送") {
			m_deliveredOrders.push_back(order);
		}
		else if (order.orderStatus == "已取消") {
			m_cancelledOrders.push_back(order);
		}
	}
	emit ordersChanged();
}

void OrderManager::showAllOrders(QTableWidget* orderTable) {
	// 清空表格
	orderTable->clearContents();

	orderTable->setRowCount(m_waitingOrders.size() + m_deliveredOrders.size() + m_cancelledOrders.size());
	int row = 0;
	// 显示待配送订单
	for (const auto& order : m_waitingOrders) {
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
	// 显示已配送订单
	for (const auto& order : m_deliveredOrders) {
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
	// 显示已取消订单
	for (const auto& order : m_cancelledOrders) {
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
	m_waitingOrders.insert(m_waitingOrders.begin(), newOrder);
	std::vector<Order> orders;
	orders.insert(orders.end(), m_waitingOrders.begin(), m_waitingOrders.end());
	orders.insert(orders.end(), m_deliveredOrders.begin(), m_deliveredOrders.end());
	orders.insert(orders.end(), m_cancelledOrders.begin(), m_cancelledOrders.end());
	emit ordersChanged();
	emit saveOrders(orders);
}