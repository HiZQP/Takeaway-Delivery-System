#include "StatsManager.h"
#include <QTableWidget>

void StatsManager::setupAllStatsWidget() {
	m_allStatsWidget = new QWidget();
	m_allStatsControls.vLayout = new QVBoxLayout(m_allStatsWidget);
}

void StatsManager::setupDailyOrdersStatsWidget() {
	m_dailyOrdersStatsWidget = new QWidget();
	m_dailyOrdersControls.orderTable = new QTableWidget();

}

void StatsManager::setupMonthlyOrdersStatsWidget() {
	m_monthlyOrdersStatsWidget = new QWidget();
	m_monthlyOrdersControls.orderTable = new QTableWidget();
}

StatsManager::~StatsManager() {
	delete m_dailyOrdersStatsWidget;
	delete m_monthlyOrdersStatsWidget;
}
