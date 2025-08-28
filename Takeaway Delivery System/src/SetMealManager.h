#pragma once
#include <vector>
#include "vendor/qflowlayout/flowlayout.h"

#include "SetMeal.h"

class SetMealManager{
private:
	std::vector<SetMeal*> m_setMeals;

	void loadSetMealsFromFile(const std::string& filename);
public:
	SetMealManager(const std::string& filename);
	~SetMealManager();

	void addSetMeal(const std::string& id,
					const std::string& name,
					const std::string& description,
					const int& price,
					const int& status);
	void addSetMeal(SetMeal* meal);
	void showAllSetMeals(FlowLayout* layout);
};

