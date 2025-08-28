#include "SetMeal.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <qfont.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

void SetMeal::connectSignalsAndSlots(){
	connect(m_shelvesControls.addButton, &QPushButton::clicked, this, &SetMeal::addToCount);
	connect(m_shelvesControls.subButton, &QPushButton::clicked, this, &SetMeal::subFromCount);
	connect(m_basketControls.addButton, &QPushButton::clicked, this, &SetMeal::addToCount);
	connect(m_basketControls.subButton, &QPushButton::clicked, this, &SetMeal::subFromCount);
}

void SetMeal::setupShelvesWidget(const std::string& id,
								 const std::string& name, 
								 const int& price, 
								 const int& status){
	m_shelvesWidget = new QWidget();
	QVBoxLayout* vLayout = new QVBoxLayout(m_shelvesWidget);
	QHBoxLayout* hLayout = new QHBoxLayout();

	m_shelvesControls.nameLabel = new QLabel();
	m_shelvesControls.nameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_shelvesControls.nameLabel->setText(QString::fromStdString(m_name));

	m_shelvesControls.labelButton = new QPushButton();
	m_shelvesControls.labelButton->setMinimumSize(110, 100);
	m_shelvesControls.labelButton->setText(QString::fromStdString(id));

	m_shelvesControls.priceLabel = new QLabel();
	m_shelvesControls.priceLabel->setText(QString::fromUtf8("价格：%1 元").arg(QString::number(m_price)));

	m_shelvesControls.addButton = new QPushButton();
	m_shelvesControls.addButton->setMaximumSize(30, 30);
	m_shelvesControls.addButton->setText("+");

	m_shelvesControls.countLabel = new QLabel();
	m_shelvesControls.countLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_shelvesControls.countLabel->setText("0");

	m_shelvesControls.subButton = new QPushButton();
	m_shelvesControls.subButton->setMaximumSize(30, 30);
	m_shelvesControls.subButton->setText("-");

	hLayout->addWidget(m_shelvesControls.subButton);
	hLayout->addWidget(m_shelvesControls.countLabel);
	hLayout->addWidget(m_shelvesControls.addButton);
	vLayout->addWidget(m_shelvesControls.labelButton);
	vLayout->addWidget(m_shelvesControls.nameLabel);
	vLayout->addWidget(m_shelvesControls.priceLabel);
	vLayout->addLayout(hLayout);
}

void SetMeal::setupBasketWidget(const std::string& id, const std::string& name){
	m_basketWidget = new QWidget();
	QHBoxLayout* hLayout1 = new QHBoxLayout(m_basketWidget);
	QHBoxLayout* hLayout2 = new QHBoxLayout();
	QVBoxLayout* vLayout = new QVBoxLayout();

	m_basketControls.labelButton = new QPushButton();
	m_basketControls.labelButton->setMinimumSize(50, 50);
	m_basketControls.labelButton->setText(QString::fromStdString(id));

	m_basketControls.nameLabel = new QLabel();
	m_basketControls.nameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_basketControls.nameLabel->setText(QString::fromStdString(m_name));

	m_basketControls.addButton = new QPushButton();
	m_basketControls.addButton->setMaximumSize(30, 30);
	m_basketControls.addButton->setText("+");

	m_basketControls.countLabel = new QLabel();
	m_basketControls.countLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_basketControls.countLabel->setText("0");

	m_basketControls.subButton = new QPushButton();
	m_basketControls.subButton->setMaximumSize(30, 30);
	m_basketControls.subButton->setText("-");

	m_basketControls.totalPriceLabel = new QLabel();
	m_basketControls.totalPriceLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_basketControls.totalPriceLabel->setText(QString::fromUtf8("%1 元").arg(QString::number(m_totalPrice)));

	hLayout2->addWidget(m_basketControls.subButton);
	hLayout2->addWidget(m_basketControls.countLabel);
	hLayout2->addWidget(m_basketControls.addButton);
	vLayout->addWidget(m_basketControls.nameLabel);
	vLayout->addLayout(hLayout2);
	hLayout1->addWidget(m_basketControls.labelButton);
	hLayout1->addLayout(vLayout);
	hLayout1->addWidget(m_basketControls.totalPriceLabel);
}

SetMeal::SetMeal(const std::string& id, 
				 const std::string& name, 
				 const std::string& description,
				 const int& price, 
				 const int& status)
	:m_id(id), m_name(name), m_description(description), m_price(price), m_status(status){
	m_count = 0;
	m_totalPrice = 0;

	setupShelvesWidget(id, name, price, status);
	setupBasketWidget(id, name);
	connectSignalsAndSlots();

}

SetMeal::~SetMeal()
{
	delete m_shelvesWidget;
	delete m_basketWidget;
}

int SetMeal::calculateTotalPrice(){
	m_totalPrice = m_count * m_price;
	return m_totalPrice;
}

void SetMeal::addToCount(){
	m_count++;
	m_shelvesControls.countLabel->setText(QString::number(m_count));
	m_basketControls.countLabel->setText(QString::number(m_count));
	m_totalPrice = calculateTotalPrice();
	m_basketControls.totalPriceLabel->setText(QString::fromUtf8("%1 元").arg(QString::number(m_totalPrice)));
	emit countChanged();
}

void SetMeal::subFromCount(){
	if (m_count > 0) {
		m_count--;
		m_shelvesControls.countLabel->setText(QString::number(m_count));
		m_basketControls.countLabel->setText(QString::number(m_count));
		m_totalPrice = calculateTotalPrice();
		m_basketControls.totalPriceLabel->setText(QString::fromUtf8("%1 元").arg(QString::number(m_totalPrice)));
		emit countChanged();
	}
}
