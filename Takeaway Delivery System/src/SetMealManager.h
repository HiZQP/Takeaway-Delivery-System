#pragma once
#include <QObject>

#include <vector>
#include "vendor/qflowlayout/flowlayout.h"

#include "SetMeal.h"

struct SettleWidgetControls {
	QVBoxLayout* orderDetailsLayout;
	QComboBox* addressCombobox;
	QPushButton* settleButton;
	QLineEdit* consigneeLineEdit;
	QLineEdit* phoneLineEdit;
	QLabel* totalPriceLabel;
};

class SetMealManager : public QObject {
	Q_OBJECT

signals:
	void totalPriceChanged();
	void newOrderPlaced(
		const std::string& orderId,
		const std::string& consignee,
		const std::string& phone,
		const std::string& address,
		const std::string& setMealID,
		const std::string& setMealCount,
		const std::string& totalPrice,
		const std::string& orderTime,
		const std::string& orderStatus);
private:
	std::vector<SetMeal*> m_setMeals;
	std::vector<std::string> m_adddresses;
	int m_totalPrice;
	int m_basketStatus;

	FlowLayout* m_fShelvesLayout;
	QVBoxLayout* m_fBasketLayout;

	SettleWidgetControls m_settleControls;
	QWidget* m_settleWidget;

	void connectSignalsAndSlots();
	void calculateTotalPrice();
	void createSettleWidget();
public:
	SetMealManager(const std::string& filename);
	~SetMealManager();

	void loadSetMeals(const std::vector<SetMeal*>& setMeals);
	void loadAddresses(const std::vector<std::string>& addresses);
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
	inline int basketHasSetMeals() const { return m_basketStatus; }
	std::vector<SetMeal*> getSetmeals() const { return m_setMeals; }
public slots:
	void showSettleWidget();
	void updateBasketSetMeals();
	void clearAllBasketSetMeals();
	void settleBasket();
};

