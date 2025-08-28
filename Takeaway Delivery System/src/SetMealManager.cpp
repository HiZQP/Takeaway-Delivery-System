#include "SetMealManager.h"
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

SetMealManager::SetMealManager(const std::string& filename){
	m_totalPrice = 0;

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

void SetMealManager::updateBasketSetMeals() {
	if (!m_fBasketLayout) return;
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
