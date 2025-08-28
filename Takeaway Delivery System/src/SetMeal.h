#pragma once

#include "ui_MainWindow.h"
#include <string>
#include <QObject>
#include <QWidget>
// ���ܽ���ؼ��ṹ��
struct ShelvesWidgetControls {
	QPushButton* labelButton;
	QLabel* nameLabel;
	QLabel* priceLabel;
	QPushButton* addButton;
	QPushButton* subButton;
	QLabel* countLabel;
};

// ���ﳵ����ؼ��ṹ��
struct BasketWidgetControls {
	QPushButton* labelButton;
	QLabel* nameLabel;
	QPushButton* addButton;
	QPushButton* subButton;
	QLabel* countLabel;
	QLabel* totalPriceLabel;
};


class SetMeal : public QObject{
	Q_OBJECT

signals:
	void countChanged();
private:
	std::string m_id;
	std::string m_name;
	std::string m_description;
	int m_price;
	int m_status;

	int m_count; // ���ﳵ�и��ײ͵�����
	int m_totalPrice; // ���ײ͵��ܼ�

	ShelvesWidgetControls m_shelvesControls;
	BasketWidgetControls m_basketControls;

	QWidget* m_shelvesWidget;
	QWidget* m_basketWidget;

	void connectSignalsAndSlots();

	void setupShelvesWidget(const std::string& id, const std::string& name, const int& price, const int& status);
	void setupBasketWidget(const std::string& id, const std::string& name);
public:
	SetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status);
	~SetMeal();

	inline QWidget* getShelvesWidget() { return m_shelvesWidget; }
	inline QWidget* getBasketWidget() { return m_basketWidget; }

	inline int getCount() { return m_count; }
	inline int getTotalPrice() { return m_totalPrice; }

	int calculateTotalPrice();
public slots:
	void addToCount();
	void subFromCount();
};

