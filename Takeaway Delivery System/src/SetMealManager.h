#pragma once
#include <QObject>

#include <vector>
#include "vendor/qflowlayout/flowlayout.h"

#include "SetMeal.h"

class SetMealManager : public QObject {
	Q_OBJECT

signals:
	void totalPriceChanged();
private:
	std::vector<SetMeal*> m_setMeals;
	int m_totalPrice;

	FlowLayout* m_fShelvesLayout;
	QVBoxLayout* m_fBasketLayout;
	

	void connectSignalsAndSlots();
	void loadSetMealsFromFile(const std::string& filename);
	void calculateTotalPrice();
public:
	SetMealManager(const std::string& filename);
	~SetMealManager();

	void addSetMeal(const std::string& id,
					const std::string& name,
					const std::string& description,
					const int& price,
					const int& status);
	void addSetMeal(SetMeal* meal);
	void showAllShelvesSetMeals();

	inline QVBoxLayout* getBasketLayout() { return m_fBasketLayout; }
	inline FlowLayout* getShelvesLayout() { return m_fShelvesLayout; }

	inline int getTotalPrice() const { return m_totalPrice; }
public slots:
	void updateBasketSetMeals();
	void clearAllBasketSetMeals();
};

