#pragma once

#include "ui_MainWindow.h"
#include <string>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>

// 货架界面控件结构体
struct ShelvesWidgetControls {
	QPushButton* labelButton;
	QLabel* nameLabel;
	QLabel* priceLabel;
	QPushButton* addButton;
	QPushButton* subButton;
	QLabel* countLabel;
};

// 购物车界面控件结构体
struct BasketWidgetControls {
	QPushButton* labelButton;
	QLabel* nameLabel;
	QPushButton* addButton;
	QPushButton* subButton;
	QLabel* countLabel;
	QLabel* totalPriceLabel;
};

struct detailsWidgetControls {
	QLabel* idLabel;
	QLineEdit* nameLineEdit;
	QTextEdit* descriptionTextEdit;
	QLineEdit* priceLineEdit;
	QComboBox* statusCombobox;
	QPushButton* editButton;
	QPushButton* deleteButton;
};


class SetMeal : public QObject{
	Q_OBJECT

signals:
	void countChanged();
	void deleteThisOrder(std::string id);
private:
	std::string m_id;
	std::string m_name;
	std::string m_description;
	int m_price;
	int m_status;

	int m_count; // 购物车中该套餐的数量
	int m_totalPrice; // 该套餐的总价

	ShelvesWidgetControls m_shelvesControls;
	BasketWidgetControls m_basketControls;
	detailsWidgetControls m_detailsControls;

	QWidget* m_shelvesWidget = nullptr;
	QWidget* m_basketWidget = nullptr;
	QWidget* m_detailsWidget = nullptr;

	void connectSignalsAndSlots();


	void setupShelvesWidget(const std::string& id, const std::string& name, const int& price, const int& status);
	void setupBasketWidget(const std::string& id, const std::string& name);
	void setupDetailsWidget();
public:
	SetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status);
	~SetMeal();

	inline QWidget* getShelvesWidget() { return m_shelvesWidget; }
	inline QWidget* getBasketWidget() { return m_basketWidget; }

	inline std::string getId() const { return m_id; }
	inline std::string getName() const { return m_name; }
	inline std::string getDescription() const { return m_description; }
	inline int getCount() const { return m_count; }
	inline int getTotalPrice() const { return m_totalPrice; }
	inline int getPrice() const { return m_price; }
	inline int getStatus() const { return m_status; }
	void setCount(const int& count);

	int calculateTotalPrice();
public slots:
	void addToCount();
	void subFromCount();
	void editDetails();
	void saveDetails();
	void showDetailsWidget();
};

