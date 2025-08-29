#include "SetMeal.h"
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
	connect(m_shelvesControls.labelButton, &QPushButton::clicked, this, &SetMeal::createDetailsWidget);
}

void SetMeal::createDetailsWidget(){
	m_detailsWidget = new QWidget();
	m_detailsWidget->setParent(nullptr);
	QVBoxLayout* vLayout = new QVBoxLayout(m_detailsWidget);
	m_detailsWidget->setWindowTitle(QString::fromStdString("套餐详情"));

	QHBoxLayout* idLayout = new QHBoxLayout();
	QLabel* idLabel = new QLabel();
	idLabel->setText(QString::fromStdString("套餐编号："));
	m_detailsControls.idLineEdit = new QLineEdit();
	m_detailsControls.idLineEdit->setText(QString::fromStdString(m_id));
	m_detailsControls.idLineEdit->setReadOnly(true);
	idLabel->setAlignment(Qt::AlignLeft);

	QHBoxLayout* nameLayout = new QHBoxLayout();
	QLabel* nameLabel = new QLabel();
	nameLabel->setText(QString::fromStdString("套餐名称："));
	m_detailsControls.nameLineEdit = new QLineEdit();
	m_detailsControls.nameLineEdit->setText(QString::fromStdString(m_name));
	m_detailsControls.nameLineEdit->setReadOnly(true);
	nameLabel->setAlignment(Qt::AlignLeft);
	QFont font = nameLabel->font();
	font.setPointSize(16);
	font.setBold(true);
	nameLabel->setFont(font);
	m_detailsControls.nameLineEdit->setFont(font);


	QLabel* descTitleLabel = new QLabel();
	descTitleLabel->setText(QString::fromUtf8("套餐描述："));
	m_detailsControls.descriptionTextEdit = new QTextEdit();
	QFont descFont = m_detailsControls.descriptionTextEdit->font();
	descFont.setPointSize(12);
	m_detailsControls.descriptionTextEdit->setFont(descFont);
	m_detailsControls.descriptionTextEdit->setReadOnly(true);
	//m_detailsControls.descriptionLabel->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	m_detailsControls.descriptionTextEdit->setText(QString::fromStdString(m_description));

	QHBoxLayout* priceLayout = new QHBoxLayout();
	QLabel* priceLabel = new QLabel();
	priceLabel->setText(QString::fromUtf8("套餐价格:").arg(QString::number(m_price)));
	m_detailsControls.priceLineEdit = new QLineEdit();
	m_detailsControls.priceLineEdit->setText(QString::number(m_price));
	// 设置只读
	m_detailsControls.priceLineEdit->setReadOnly(true);
	QLabel* priceUnitLabel = new QLabel();
	priceUnitLabel->setText(QString::fromUtf8("元"));

	QHBoxLayout* statusLayout = new QHBoxLayout();
	QLabel* statusLabel = new QLabel();
	statusLabel->setText(QString::fromUtf8("套餐状态："));
	m_detailsControls.statusCombobox = new QComboBox();
	m_detailsControls.statusCombobox->addItem(QString::fromUtf8("可预定"));
	m_detailsControls.statusCombobox->addItem(QString::fromUtf8("不可预定"));
	m_detailsControls.statusCombobox->setCurrentIndex(m_status);
	// 设置只读
	m_detailsControls.statusCombobox->setEnabled(false);

	QHBoxLayout* hLayout = new QHBoxLayout();
	m_detailsControls.editButton = new QPushButton();
	m_detailsControls.editButton->setText(QString::fromUtf8("编辑套餐"));

	m_detailsControls.deleteButton = new QPushButton();
	m_detailsControls.deleteButton->setText(QString::fromUtf8("删除套餐"));

	idLayout->addWidget(idLabel);
	idLayout->addWidget(m_detailsControls.idLineEdit);
	vLayout->addLayout(idLayout);
	hLayout->addWidget(m_detailsControls.editButton);
	hLayout->addWidget(m_detailsControls.deleteButton);
	nameLayout->addWidget(nameLabel);
	nameLayout->addWidget(m_detailsControls.nameLineEdit);
	vLayout->addLayout(nameLayout);
	vLayout->addWidget(descTitleLabel);
	vLayout->addWidget(m_detailsControls.descriptionTextEdit);
	priceLayout->addWidget(priceLabel);
	priceLayout->addWidget(m_detailsControls.priceLineEdit);
	priceLayout->addWidget(priceUnitLabel);
	vLayout->addLayout(priceLayout);
	statusLayout->addWidget(statusLabel);
	statusLayout->addWidget(m_detailsControls.statusCombobox);
	vLayout->addLayout(statusLayout);
	vLayout->addLayout(hLayout);

	m_detailsWidget->show();
	connect(m_detailsControls.editButton, &QPushButton::clicked, this, &SetMeal::editDetails);
}

void SetMeal::editDetails(){
	m_detailsControls.idLineEdit->setReadOnly(false);
	m_detailsControls.nameLineEdit->setReadOnly(false);
	m_detailsControls.descriptionTextEdit->setReadOnly(false);
	m_detailsControls.priceLineEdit->setReadOnly(false);
	m_detailsControls.statusCombobox->setEnabled(true);
	m_detailsControls.editButton->setText(QString::fromUtf8("保存修改"));
	disconnect(m_detailsControls.editButton, &QPushButton::clicked, this, &SetMeal::editDetails);
	connect(m_detailsControls.editButton, &QPushButton::clicked, this, &SetMeal::saveDetails);
	// 刷新界面
	m_detailsWidget->update();
}

void SetMeal::saveDetails(){
	m_id = m_detailsControls.idLineEdit->text().toStdString();
	m_name = m_detailsControls.nameLineEdit->text().toStdString();
	m_description = m_detailsControls.descriptionTextEdit->toPlainText().toStdString();
	m_price = m_detailsControls.priceLineEdit->text().toInt();
	m_status = m_detailsControls.statusCombobox->currentIndex();
	m_detailsControls.idLineEdit->setReadOnly(true);
	m_detailsControls.nameLineEdit->setReadOnly(true);
	m_detailsControls.descriptionTextEdit->setReadOnly(true);
	m_detailsControls.priceLineEdit->setReadOnly(true);
	m_detailsControls.statusCombobox->setEnabled(false);
	m_detailsControls.editButton->setText(QString::fromUtf8("编辑套餐"));
	disconnect(m_detailsControls.editButton, &QPushButton::clicked, this, &SetMeal::saveDetails);
	connect(m_detailsControls.editButton, &QPushButton::clicked, this, &SetMeal::editDetails);
	// 更新货架和购物车界面
	m_shelvesControls.labelButton->setText(QString::fromStdString(m_id));
	m_shelvesControls.nameLabel->setText(QString::fromStdString(m_name));
	m_shelvesControls.priceLabel->setText(QString::fromUtf8("价格：%1 元").arg(QString::number(m_price)));
	m_basketControls.labelButton->setText(QString::fromStdString(m_id));
	m_basketControls.nameLabel->setText(QString::fromStdString(m_name));
	m_totalPrice = calculateTotalPrice();
	m_basketControls.totalPriceLabel->setText(QString::fromUtf8("%1 元").arg(QString::number(m_totalPrice)));
	emit countChanged();
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
	delete m_detailsWidget;
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
