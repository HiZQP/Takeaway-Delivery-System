#include "StatsManager.h"
#include <QTableWidget>
#include <QLabel>
#include <sstream>
#include <unordered_map>

#include "myUtils.h"

void StatsManager::setupAllStatsWidget() {
	m_allStatsWidget = new QWidget();
	m_allStatsControls.vLayout = new QVBoxLayout(m_allStatsWidget);

	QLabel* dailyLabel = new QLabel();
	dailyLabel->setText(QString::fromUtf8("当天订单"));
	QFont Font = dailyLabel->font();
	Font.setPointSize(14);
	Font.setBold(true);
	dailyLabel->setFont(Font);
	QLabel* monthlyLabel = new QLabel();
	monthlyLabel->setText(QString::fromUtf8("当月订单"));
	monthlyLabel->setFont(Font);

	m_allStatsControls.vLayout->addWidget(dailyLabel);
	m_allStatsControls.vLayout->addWidget(m_dailyOrdersStatsWidget);
	m_allStatsControls.vLayout->addWidget(monthlyLabel);
	m_allStatsControls.vLayout->addWidget(m_monthlyOrdersStatsWidget);
}

void StatsManager::setupDailyOrdersStatsWidget() {
	m_dailyOrdersStatsWidget = new QWidget();
	m_dailyOrdersStatsWidget->setFixedSize(550, 120);
	QVBoxLayout* vLayout = new QVBoxLayout(m_dailyOrdersStatsWidget);
	m_dailyOrdersControls.orderTable = new QTableWidget();

	QLabel* titleLabel = new QLabel(QString::fromUtf8("当天订单统计"));
	QFont Font = titleLabel->font();
	Font.setPointSize(16);
	titleLabel->setFont(Font);

	m_dailyOrdersControls.orderTable->setColumnCount(5);
	QStringList headerLabels;
	headerLabels << "已配送" << "待配送" << "已取消" << "总单数" << "总营收";
	m_dailyOrdersControls.orderTable->setHorizontalHeaderLabels(headerLabels);
	m_dailyOrdersControls.orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	vLayout->addWidget(titleLabel);
	vLayout->addWidget(m_dailyOrdersControls.orderTable);
}

void StatsManager::setupMonthlyOrdersStatsWidget() {
	m_monthlyOrdersStatsWidget = new QWidget();
	m_monthlyOrdersStatsWidget->setFixedWidth(340);
	QVBoxLayout* vLayout = new QVBoxLayout(m_monthlyOrdersStatsWidget);
	m_monthlyOrdersControls.orderTable = new QTableWidget();

	QLabel* titleLabel = new QLabel(QString::fromUtf8("当月套餐热销统计"));
	QFont Font = titleLabel->font();
	Font.setPointSize(16);
	titleLabel->setFont(Font);

	m_monthlyOrdersControls.orderTable->setColumnCount(3);
	QStringList headerLabels;
	headerLabels << "套餐编号" << "数量" << "营收";
	m_monthlyOrdersControls.orderTable->setHorizontalHeaderLabels(headerLabels);
	// 数据加载完成后调用这句进行排序
	// m_monthlyOrdersControls.orderTable->sortItems(1, Qt::DescendingOrder);
	m_monthlyOrdersControls.orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	vLayout->addWidget(titleLabel);
	vLayout->addWidget(m_monthlyOrdersControls.orderTable);
}

void StatsManager::setupAddressOrdersStatsWidget() {
	m_addressOrdersStatsWidget = new QWidget();
	m_addressOrdersStatsWidget->setFixedWidth(340);
	QVBoxLayout* vLayout = new QVBoxLayout(m_addressOrdersStatsWidget);
	m_addressOrdersControls.orderTable = new QTableWidget();

	QLabel* titleLabel = new QLabel(QString::fromUtf8("配送地址订单统计"));
	QFont Font = titleLabel->font();
	Font.setPointSize(16);
	titleLabel->setFont(Font);

	m_addressOrdersControls.orderTable->setColumnCount(3);
	QStringList headerLabels;
	headerLabels << "地点" << "订单数量" << "营收";
	m_addressOrdersControls.orderTable->setHorizontalHeaderLabels(headerLabels);
	// 数据加载完成后调用这句进行排序
	// m_monthlyOrdersControls.orderTable->sortItems(1, Qt::DescendingOrder);
	m_addressOrdersControls.orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	vLayout->addWidget(titleLabel);
	vLayout->addWidget(m_addressOrdersControls.orderTable);
}

StatsManager::StatsManager() {
	setupDailyOrdersStatsWidget();
	setupMonthlyOrdersStatsWidget();
	setupAddressOrdersStatsWidget();
	//setupAllStatsWidget();
}

StatsManager::~StatsManager() {
	delete m_dailyOrdersStatsWidget;
	delete m_monthlyOrdersStatsWidget;
	delete m_allStatsWidget;
	delete m_addressOrdersStatsWidget;
}

void StatsManager::showDailyOrdersStats(const std::vector<Order>& orders) {
	std::string nowDay = utils::getFormattedLocalTime("%d");
	std::vector<Order> fliteredOrders;
	for (const auto& order : orders) {
		std::string orderDay = order.orderId.substr(6, 2);
		if (nowDay == orderDay)
			fliteredOrders.push_back(order);
	}

	m_dailyOrdersControls.orderTable->clearContents();
	m_dailyOrdersControls.orderTable->setRowCount(1);
	int waitingCount = 0;
	int deliveredCount = 0;
	int canceledCount = 0;
	int orderCount = fliteredOrders.size();
	int totalRevenue = 0;
	for (const auto& order : fliteredOrders) {
		if ("已配送" == order.orderStatus) {
			deliveredCount++;
			totalRevenue += order.totalPrice;
		}
		else if ("已取消" == order.orderStatus)
			canceledCount++;
	}
	waitingCount = orderCount - deliveredCount - canceledCount;
	m_dailyOrdersControls.orderTable->setItem(0, 0, new QTableWidgetItem(QString::number(deliveredCount)));
	m_dailyOrdersControls.orderTable->setItem(0, 1, new QTableWidgetItem(QString::number(waitingCount)));
	m_dailyOrdersControls.orderTable->setItem(0, 2, new QTableWidgetItem(QString::number(canceledCount)));
	m_dailyOrdersControls.orderTable->setItem(0, 3, new QTableWidgetItem(QString::number(orderCount)));
	m_dailyOrdersControls.orderTable->setItem(0, 4, new QTableWidgetItem(QString::number(totalRevenue)));

	m_dailyOrdersStatsWidget->show();
}

void StatsManager::showMonthlyOrdersStats(const std::vector<Order>& orders, const std::vector<SetMeal*>& setMealData) {

	m_monthlyOrdersControls.orderTable->clearContents();

	std::string nowMonth = utils::getFormattedLocalTime("%m");
	std::vector<Order> fliteredOrders;
	for (const auto& order : orders) {
		std::string orderMonth = order.orderId.substr(4, 2);
		if (nowMonth == orderMonth && order.orderStatus == "已配送")
			fliteredOrders.push_back(order);
	}
	
	std::unordered_map<std::string, int> setMeals;
	for (const auto& order : fliteredOrders) {
		std::stringstream ss_count;
		std::stringstream ss_setMeal;
		ss_setMeal << order.setMealID;
		ss_count << order.setMealCount;
		std::string temp_count = {};
		std::string temp_setMeal = {};
		while (std::getline(ss_setMeal, temp_setMeal, '/')) {
			std::getline(ss_count, temp_count, '/');
			if (!temp_setMeal.empty()) {
				if (setMeals.find(temp_setMeal) != setMeals.end())
					setMeals[temp_setMeal] += std::stoi(temp_count);
				else
					setMeals.emplace(temp_setMeal, std::stoi(temp_count));
			}
		}
	}
	m_monthlyOrdersControls.orderTable->setSortingEnabled(false);
	m_monthlyOrdersControls.orderTable->setRowCount(setMeals.size());

	int row = 0;
	for (const auto& pair : setMeals) {
		m_monthlyOrdersControls.orderTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pair.first)));
		QTableWidgetItem* countItem = new QTableWidgetItem();
		countItem->setData(Qt::DisplayRole, pair.second); // 设置为数字类型
		m_monthlyOrdersControls.orderTable->setItem(row, 1, countItem);
		for (const auto& data : setMealData) {
			if (data->getId() == pair.first) {
				int totalPrice = pair.second * data->getPrice();
				QTableWidgetItem* priceItem = new QTableWidgetItem();
				priceItem->setData(Qt::DisplayRole, totalPrice); // 设置为数字类型
				m_monthlyOrdersControls.orderTable->setItem(row, 2, priceItem);
				break;
			}
		}
		row++;
	}
	m_monthlyOrdersControls.orderTable->setSortingEnabled(true);
	m_monthlyOrdersControls.orderTable->sortItems(1, Qt::DescendingOrder);
	m_monthlyOrdersStatsWidget->show();
}

void StatsManager::showAddressOrdersStats(const std::vector<Order>& orders) {
	m_addressOrdersControls.orderTable->clearContents();
	std::vector<Order> fliteredOrders;
	for (const auto& order : orders)
		if (order.orderStatus == "已配送")
			fliteredOrders.push_back(order);

	std::unordered_map<std::string, std::pair<int, int>> um_fliteredOrders;
	std::vector<int> totalPrice;
	for (const auto& order : fliteredOrders) {
		if (um_fliteredOrders.find(order.address) != um_fliteredOrders.end()) {
			um_fliteredOrders[order.address].first++;
			um_fliteredOrders[order.address].second += order.totalPrice;
		}
		else
			um_fliteredOrders.emplace(order.address, std::pair(1, order.totalPrice));
	}
	m_addressOrdersControls.orderTable->setSortingEnabled(false);
	m_addressOrdersControls.orderTable->setRowCount(um_fliteredOrders.size());
	
	int row = 0;
	for (const auto& pair : um_fliteredOrders) {
		m_addressOrdersControls.orderTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pair.first)));
		QTableWidgetItem* countItem = new QTableWidgetItem();
		countItem->setData(Qt::DisplayRole, pair.second.first); // 设置为数字类型
		m_addressOrdersControls.orderTable->setItem(row, 1, countItem);

		QTableWidgetItem* priceItem = new QTableWidgetItem();
		priceItem->setData(Qt::DisplayRole, pair.second.second); // 设置为数字类型
		m_addressOrdersControls.orderTable->setItem(row, 2, priceItem);
		row++;
	}
	m_addressOrdersControls.orderTable->setSortingEnabled(true);
	m_addressOrdersControls.orderTable->sortItems(1, Qt::DescendingOrder);
	m_addressOrdersStatsWidget->show();
}

