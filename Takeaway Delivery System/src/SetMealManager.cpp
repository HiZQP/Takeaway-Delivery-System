#include "SetMealManager.h"
#include <fstream>
#include <sstream>

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

SetMealManager::SetMealManager(const std::string& filename){
	loadSetMealsFromFile(filename);
}

SetMealManager::~SetMealManager()
{
	for (SetMeal* meal : m_setMeals) {
		delete meal;
	}
	m_setMeals.clear();
}

void SetMealManager::addSetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status)
{
	SetMeal* meal = new SetMeal(id, name, description, price, status);
	m_setMeals.push_back(meal);
}

void SetMealManager::addSetMeal(SetMeal* meal)
{
	m_setMeals.push_back(meal);
}

void SetMealManager::showAllSetMeals(FlowLayout* layout)
{
	for (SetMeal* meal : m_setMeals) {
		layout->addWidget(meal->getWidget());
	}
}
