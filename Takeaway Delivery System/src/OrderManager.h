#pragma once
#include <QObject>
#include <QTableWidget>
#include <vector>
#include "Order.h"

class OrderManager : public QObject {
	Q_OBJECT
signals:
	void ordersChanged();
private:
	std::vector<Order> m_waitingOrders;
	std::vector<Order> m_deliveredOrders;
	std::vector<Order> m_cancelledOrders;
	std::vector<Order> m_flitteredOrders;

	void connectSignalsAndSlots();
public:
	OrderManager();
	~OrderManager();

	void loadOrders(const std::vector<Order>& orders);
public slots:
	void showAllOrders(QTableWidget* orderTable);
	void receiveNewOrder(
		const std::string& orderId,
		const std::string& consignee,
		const std::string& phone,
		const std::string& address,
		const std::string& setMealID,
		const std::string& setMealCount,
		const std::string& totalPrice,
		const std::string& orderTime,
		const std::string& orderStatus);
};

