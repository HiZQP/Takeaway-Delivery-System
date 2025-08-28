#include "SetMeal.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <qfont.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

void SetMeal::setupWidget(const std::string& id,
						  const std::string& name, 
						  const int& price, 
						  const int& status){
	m_widget = new QWidget();
	QVBoxLayout* vLayout = new QVBoxLayout(m_widget);
	QHBoxLayout* hLayout = new QHBoxLayout();

	QLabel* setMealNameLabel = new QLabel();
	setMealNameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	setMealNameLabel->setText(QString::fromStdString(m_name));

	QPushButton* labelButton = new QPushButton();
	labelButton->setMinimumSize(110, 100);
	labelButton->setText(QString::fromStdString(id));

	QLabel* priceLabel = new QLabel();
	priceLabel->setText(QString::fromUtf8("价格：%1 元").arg(QString::number(m_price)));

	QPushButton* addButton = new QPushButton();
	addButton->setMaximumSize(30, 30);
	addButton->setText("+");

	QLabel* countLabel = new QLabel();
	countLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	countLabel->setText("0");

	QPushButton* subButton = new QPushButton();
	subButton->setMaximumSize(30, 30);
	subButton->setText("-");

	hLayout->addWidget(subButton);
	hLayout->addWidget(countLabel);
	hLayout->addWidget(addButton);
	vLayout->addWidget(labelButton);
	vLayout->addWidget(setMealNameLabel);
	vLayout->addWidget(priceLabel);
	vLayout->addLayout(hLayout);
}

SetMeal::SetMeal(const std::string& id, 
				 const std::string& name, 
				 const std::string& description,
				 const int& price, 
				 const int& status)
	:m_id(id), m_name(name), m_description(description), m_price(price), m_status(status){
	setupWidget(id, name, price, status);
}

SetMeal::~SetMeal()
{
	delete m_widget;
}
