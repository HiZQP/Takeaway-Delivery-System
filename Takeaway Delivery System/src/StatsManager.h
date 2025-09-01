#pragma once
#include <QWidget>
#include <QObject>
#include <QTableWidget>
#include <QVBoxLayout>

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
public slots:

};

