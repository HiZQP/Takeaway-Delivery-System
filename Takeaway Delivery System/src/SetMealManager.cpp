#include "SetMealManager.h"
#include <QFormLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>

#include "myUtils.h"

void SetMealManager::connectSignalsAndSlots(){
	connect(m_settleControls.settleButton, &QPushButton::clicked, this, &SetMealManager::settleBasket);
}

void SetMealManager::loadSetMeals(const std::vector<SetMeal*>& setMeals){
	for(SetMeal* meal : m_setMeals)
		delete meal;

	m_setMeals.clear();
	for (SetMeal* meal : setMeals) {
		addSetMeal(meal);
		connect(meal, &SetMeal::countChanged, this, &SetMealManager::updateBasketSetMeals);
	}
	showAllShelvesSetMeals();
}

void SetMealManager::loadAddresses(const std::vector<std::string>& addresses){
	m_adddresses = addresses;
	m_settleControls.addressCombobox->clear();
	for (const std::string& address : m_adddresses) {
		m_settleControls.addressCombobox->addItem(QString::fromStdString(address));
	}
}

void SetMealManager::calculateTotalPrice() {
	m_totalPrice = 0;
	for (SetMeal* meal : m_setMeals) {
		m_totalPrice += meal->getTotalPrice();
	}
}

void SetMealManager::createSettleWidget() {
	m_settleWidget = new QWidget();
	m_settleWidget->setParent(nullptr);
	m_settleWidget->setWindowTitle(QString::fromUtf8("结算"));
	QVBoxLayout* vLayout = new QVBoxLayout(m_settleWidget);

	QFormLayout* formLayout = new QFormLayout();
	formLayout->setLabelAlignment(Qt::AlignRight);

	QLabel* addressLabel = new QLabel();
	addressLabel->setText(QString::fromUtf8("送餐地址："));
	m_settleControls.addressCombobox = new QComboBox();

	QLabel* consigneeLabel = new QLabel();
	consigneeLabel->setText(QString::fromUtf8("收货人："));
	m_settleControls.consigneeLineEdit = new QLineEdit();

	QLabel* phoneLabel = new QLabel();
	phoneLabel->setText(QString::fromUtf8("联系电话："));
	m_settleControls.phoneLineEdit = new QLineEdit();

	QScrollArea* orderDetailsScrollArea = new QScrollArea();
	orderDetailsScrollArea->setWidgetResizable(true);
	m_settleControls.orderDetailsLayout = new QVBoxLayout(orderDetailsScrollArea);

	m_settleControls.totalPriceLabel = new QLabel();
	QFont totalFont = m_settleControls.totalPriceLabel->font();
	totalFont.setPointSize(14);
	totalFont.setBold(true);
	m_settleControls.totalPriceLabel->setFont(totalFont);
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	m_settleControls.settleButton = new QPushButton();
	m_settleControls.settleButton->setText(QString::fromUtf8("下单"));
	buttonLayout->addWidget(m_settleControls.totalPriceLabel);
	buttonLayout->addWidget(m_settleControls.settleButton);

	vLayout->addLayout(formLayout);
	formLayout->addRow(addressLabel, m_settleControls.addressCombobox);
	formLayout->addRow(consigneeLabel, m_settleControls.consigneeLineEdit);
	formLayout->addRow(phoneLabel, m_settleControls.phoneLineEdit);
	vLayout->addWidget(orderDetailsScrollArea);
	vLayout->addLayout(buttonLayout);

	//connect(m_settleControls.settleButton, &QPushButton::clicked, this, &SetMealManager::settleBasket);
}

SetMealManager::SetMealManager(const std::string& filename){
	m_totalPrice = 0;
	m_basketStatus = 0;

	createSettleWidget();
	connectSignalsAndSlots();
	m_fShelvesLayout = new FlowLayout();
	m_fBasketLayout = new QVBoxLayout();
	// 置顶对齐
	m_fBasketLayout->setAlignment(Qt::AlignTop);
}

SetMealManager::~SetMealManager(){
	for (SetMeal* meal : m_setMeals) {
		delete meal;
	}
	m_setMeals.clear();
	delete m_fShelvesLayout;
	delete m_fBasketLayout;
	delete m_settleWidget;
}

void SetMealManager::addSetMeal(const std::string& id, const std::string& name, const std::string& description, const int& price, const int& status){
	SetMeal* meal = new SetMeal(id, name, description, price, status);
	m_setMeals.push_back(meal);
}

void SetMealManager::addSetMeal(SetMeal* meal){
	m_setMeals.push_back(meal);
}

void SetMealManager::showAllShelvesSetMeals(){
	for (SetMeal* meal : m_setMeals) {
		m_fShelvesLayout->addWidget(meal->getShelvesWidget());
	}
}

void SetMealManager::showSettleWidget() {
	if (m_basketStatus == 0) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("购物车为空，无法结算！"));
		return;
	}
	// 清空之前的订单详情
	QLayoutItem* child;
	while ((child = m_settleControls.orderDetailsLayout->takeAt(0)) != nullptr) {
		if (child->widget()) {
			child->widget()->setParent(nullptr);
			delete child->widget();
		}
		delete child;
	}
	for (SetMeal* meal : m_setMeals) {
		if (meal->getCount() > 0) {
			QLabel* itemLabel = new QLabel();
			itemLabel->setText(QString::fromStdString(
				meal->getName() + " x " + std::to_string(meal->getCount()) + " = " + std::to_string(meal->getTotalPrice()) + " 元"
			));
			m_settleControls.orderDetailsLayout->addWidget(itemLabel);
		}
	}
	m_settleControls.totalPriceLabel->setText(QString::fromUtf8("总价：%1 元").arg(QString::number(m_totalPrice)));
	m_settleWidget->update();
	m_settleWidget->show();
}

void SetMealManager::clearAllBasketSetMeals(){
	// 重置所有套餐的数量和总价
	for (SetMeal* meal : m_setMeals) {
		while (meal->getCount() > 0) {
			meal->setCount(0);
			meal->calculateTotalPrice();
		}
	}
	updateBasketSetMeals();
	m_settleWidget->close();
	calculateTotalPrice();
	emit totalPriceChanged();
}

void SetMealManager::settleBasket(){
	std::string consignee = m_settleControls.consigneeLineEdit->text().toStdString();
	std::string phone = m_settleControls.phoneLineEdit->text().toStdString();
	std::string address = m_settleControls.addressCombobox->currentText().toStdString();
	if (address.empty() || consignee.empty() || phone.empty()) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("请完整填写订单信息！"));
		return;
	}
	if(phone.size() != 11 || !std::all_of(phone.begin(), phone.end(), ::isdigit)) {
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("请输入有效的11位电话号码！"));
		return;
	}
	std::string orderId = utils::getFormattedLocalTime("%Y%m%d%H%M%S");
	std::string setMealID;
	std::string setMealCount;
	for (SetMeal* meal : m_setMeals)
		if (meal->getCount() > 0) {
			setMealID += meal->getId() + "/";
			setMealCount += std::to_string(meal->getCount()) + "/";
		}
	std::string orderTime = utils::getFormattedLocalTime("%Y-%m-%d %H:%M:%S");
	std::string orderStatus = "未派送";
	std::string totalPriceStr = std::to_string(m_totalPrice);
	emit newOrderPlaced(orderId, consignee, phone, address, setMealID, setMealCount, totalPriceStr, orderTime, orderStatus);
	clearAllBasketSetMeals();
	QMessageBox::information(nullptr, QString::fromUtf8("成功"), QString::fromUtf8("订单已提交！"));
}

void SetMealManager::updateBasketSetMeals() {
	if (!m_fBasketLayout) return;
	m_basketStatus = 0;
	for (SetMeal* meal : m_setMeals) {
		if (meal->getCount() > 0) {
			m_basketStatus = 1;
			break;
		}
	}
	// 只添加/移除变化的widget
	for (SetMeal* meal : m_setMeals) {
		QWidget* basketWidget = meal->getBasketWidget();
		bool shouldBeInLayout = (meal->getCount() > 0);
		bool isInLayout = (basketWidget->parent() == m_fBasketLayout->parentWidget());

		if (shouldBeInLayout && !isInLayout) {
			m_fBasketLayout->addWidget(basketWidget);
		}
		else if (!shouldBeInLayout && isInLayout) {
			m_fBasketLayout->removeWidget(basketWidget);
			basketWidget->setParent(nullptr);  // 从布局中移除
		}
	}
	calculateTotalPrice();
	emit totalPriceChanged();
}
