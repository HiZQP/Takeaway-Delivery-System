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

	void setupAllStatsWidget();
	void setupDailyOrdersStatsWidget();
	void setupMonthlyOrdersStatsWidget();
public:
	StatsManager();
	~StatsManager();

	void showDailyOrdersStats(const std::vector<Order>& orders);
	void showMonthlyOrdersStats(const std::vector<Order>& orders, std::vector<SetMeal*> setMealData);
	void showAllOrdersStats(const std::vector<Order>& orders);
public slots:
};

