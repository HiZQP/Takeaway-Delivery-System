#pragma once
#include <QObject>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <vector>

#include "Order.h"
#include "Map/Map.h"

struct OrderEditWidgetControls {
	QLabel* orderIDLabel;
	QLineEdit* consigneeLineEdit;
	QLineEdit* phoneLineEdit;
	QPushButton* saveButton;
};

struct DeliveryWidgetControls {
	QLabel* pathLabel;
	QLabel* distenceLabel;
	QPushButton* deliverButton;
};

class OrderManager : public QObject {
	Q_OBJECT

signals:
	void saveOrders(const std::vector<Order>& orders);
	void ordersChanged();
private:
	std::vector<Order> m_orders;
	Map m_map;
	std::string stratPoint;

	int m_selectedRow;

	OrderEditWidgetControls m_orderEditControls;
	QWidget* m_orderEditWidget;

	DeliveryWidgetControls m_deliveryControls;
	QWidget* m_deliveryWidget;

	void connectSignalsAndSlots();
	void setupOrderEditWidget();
	void setupDeliveryWidget();
public:
	OrderManager();
	~OrderManager();

	void loadOrders(const std::vector<Order>& orders);
	void loadMap(const MapData& mapdata);
public slots:
	void showAllOrders(QTableWidget* orderTable);
	void showWatingOrders(QTableWidget* orderTable);
	void showFlitteredOrders(QTableWidget* orderTable, QLineEdit* lineEdit);
	void showOrderEditWidget(QTableWidget* orderTable);
	void saveOrderEdit();
	void showDeliveryWidget();
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

