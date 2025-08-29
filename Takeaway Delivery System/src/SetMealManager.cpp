#include "SetMealManager.h"
#include <QFormLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>

void SetMealManager::connectSignalsAndSlots(){
	for (SetMeal* meal : m_setMeals) {
		connect(meal, &SetMeal::countChanged, this, &SetMealManager::updateBasketSetMeals);
	}
}

void SetMealManager::loadSetMealsFromFile(const std::string& filename){
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filename);
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string id, name, description;
		int price, status;
		if (!(iss >> id >> name >> description >> price >> status)) {
			continue; // Skip malformed lines
		}
		addSetMeal(id, name, description, price, status);
	}
}

void SetMealManager::calculateTotalPrice() {
	m_totalPrice = 0;
	for (SetMeal* meal : m_setMeals) {
		m_totalPrice += meal->getTotalPrice();
	}
}

void SetMealManager::createSettleWidget() {
	m_settleWidget = new QWidget();
	m_settleWidget->setParent(nullptr);
	m_settleWidget->setWindowTitle(QString::fromUtf8("结算"));
	QVBoxLayout* vLayout = new QVBoxLayout(m_settleWidget);

	QFormLayout* formLayout = new QFormLayout();
	formLayout->setLabelAlignment(Qt::AlignRight);

	QLabel* addressLabel = new QLabel();
	addressLabel->setText(QString::fromUtf8("送餐地址："));
	m_settleControls.addressCombobox = new QComboBox();

	QLabel* consigneeLabel = new QLabel();
	consigneeLabel->setText(QString::fromUtf8("收货人："));
	m_settleControls.consigneeLineEdit = new QLineEdit();

	QLabel* phoneLabel = new QLabel();
	phoneLabel->setText(QString::fromUtf8("联系电话："));
	m_settleControls.phoneLineEdit = new QLineEdit();

	QScrollArea* orderDetailsScrollArea = new QScrollArea();
	orderDetailsScrollArea->setWidgetResizable(true);
	QWidget* orderDetailsWidget = new QWidget();
	QVBoxLayout* orderDetailsLayout = new QVBoxLayout(orderDetailsWidget);
	orderDetailsScrollArea->setWidget(orderDetailsWidget);

	QLabel* totalPriceLabel = new QLabel();
	QFont totalFont = totalPriceLabel->font();
	totalFont.setPointSize(14);
	totalFont.setBold(true);
	totalPriceLabel->setFont(totalFont);
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	m_settleControls.settleButton = new QPushButton();
	m_settleControls.settleButton->setText(QString::fromUtf8("下单"));
	buttonLayout->addWidget(totalPriceLabel);
	buttonLayout->addWidget(m_settleControls.settleButton);

	vLayout->addLayout(formLayout);
	formLayout->addRow(addressLabel, m_settleControls.addressCombobox);
	formLayout->addRow(consigneeLabel, m_settleControls.consigneeLineEdit);
	formLayout->addRow(phoneLabel, m_settleControls.phoneLineEdit);
	vLayout->addWidget(orderDetailsScrollArea);
	vLayout->addLayout(buttonLayout);

	//connect(m_settleControls.settleButton, &QPushButton::clicked, this, &SetMealManager::settleBasket);
	m_settleWidget->show();
}

SetMealManager::SetMealManager(const std::string& filename){
	m_totalPrice = 0;
	m_basketStatus = 0;

	createSettleWidget();
	loadSetMealsFromFile(filename);
	connectSignalsAndSlots();
	m_fShelvesLayout = new FlowLayout();
	m_fBasketLayout = new QVBoxLayout();
	// 置顶对齐
	m_fBasketLayout->setAlignment(Qt::AlignTop);
}

SetMealManager::~SetMealManager(){
	for (SetMeal* meal : m_setMeals) {
		delete meal;
	}
	m_setMeals.clear();
	delete m_fShelvesLayout;
	delete m_fBasketLayout;
	delete m_settleWidget;
}

void SetMealManager::addSetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status){
	SetMeal* meal = new SetMeal(id, name, description, price, status);
	m_setMeals.push_back(meal);
}

void SetMealManager::addSetMeal(SetMeal* meal){
	m_setMeals.push_back(meal);
}

void SetMealManager::showAllShelvesSetMeals(){
	for (SetMeal* meal : m_setMeals) {
		m_fShelvesLayout->addWidget(meal->getShelvesWidget());
	}
}

void SetMealManager::showSettleWidget() {
	if (m_basketStatus == 0) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("购物车为空，无法结算！"));
		return;
	}
	for (SetMeal* meal : m_setMeals) {
		if (meal->getCount() > 0) {
			QLabel* itemLabel = new QLabel();
			itemLabel->setText(QString::fromStdString(
				meal->getName() + " x " + std::to_string(meal->getCount()) + " = " + std::to_string(meal->getTotalPrice()) + " 元"
			));
		}
	}
}

void SetMealManager::clearAllBasketSetMeals(){
	if (!m_fBasketLayout) return;
	// 重置所有套餐的数量和总价
	for (SetMeal* meal : m_setMeals) {
		while (meal->getCount() > 0) {
			meal->subFromCount();
		}
	}
	updateBasketSetMeals();
	calculateTotalPrice();
	emit totalPriceChanged();
}

void SetMealManager::settleBasket(){

}

void SetMealManager::updateBasketSetMeals() {
	if (!m_fBasketLayout) return;
	m_basketStatus = 0;
	for (SetMeal* meal : m_setMeals) {
		if (meal->getCount() > 0) {
			m_basketStatus = 1;
			break;
		}
	}
	// 只添加/移除变化的widget
	for (SetMeal* meal : m_setMeals) {
		QWidget* basketWidget = meal->getBasketWidget();
		bool shouldBeInLayout = (meal->getCount() > 0);
		bool isInLayout = (basketWidget->parent() == m_fBasketLayout->parentWidget());

		if (shouldBeInLayout && !isInLayout) {
			m_fBasketLayout->addWidget(basketWidget);
		}
		else if (!shouldBeInLayout && isInLayout) {
			m_fBasketLayout->removeWidget(basketWidget);
			basketWidget->setParent(nullptr);  // 从布局中移除
		}
	}
	calculateTotalPrice();
	emit totalPriceChanged();
}
