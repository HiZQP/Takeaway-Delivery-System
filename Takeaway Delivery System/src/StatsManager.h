#pragma once
#include <QWidget>
#include <QObject>
#include <QTableWidget>
#include <QVBoxLayout>

#include "Order.h"
#include "SetMeal.h"

struct AllStatsWidgetControls {
	QVBoxLayout* vLayout;
};

struct DailyOrdersWidgetControls {
	QTableWidget* orderTable;
};
struct MonthlyOrdersWidgetControls {
	QTableWidget* orderTable;
};
struct AddressOrdersWidgetControls {
	QTableWidget* orderTable;
};

class StatsManager : public QObject {
	Q_OBJECT
signals:

private:
	AllStatsWidgetControls m_allStatsControls;
	QWidget* m_allStatsWidget;

	DailyOrdersWidgetControls m_dailyOrdersControls;
	QWidget* m_dailyOrdersStatsWidget;

	MonthlyOrdersWidgetControls m_monthlyOrdersControls;
	QWidget* m_monthlyOrdersStatsWidget;

	AddressOrdersWidgetControls m_addressOrdersControls;
	QWidget* m_addressOrdersStatsWidget;
	void setupAllStatsWidget();
	void setupDailyOrdersStatsWidget();
	void setupMonthlyOrdersStatsWidget();
	void setupAddressOrdersStatsWidget();
public:
	StatsManager();
	~StatsManager();

	void showDailyOrdersStats(const std::vector<Order>& orders);
	void showMonthlyOrdersStats(const std::vector<Order>& orders, const std::vector<SetMeal*>& setMealData);
	void showAddressOrdersStats(const std::vector<Order>& orders);
public slots:
};

