#pragma once
#include <string>
#include <QWidget>

class SetMeal{
private:
	std::string m_id;
	std::string m_name;
	std::string m_description;
	int m_price;
	int m_status;

	QWidget* m_widget;

	void setupWidget(const std::string& id, const std::string& name, const int& price, const int& status);
public:
	SetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status);
	~SetMeal();

	inline QWidget* getWidget() { return m_widget; }
};

