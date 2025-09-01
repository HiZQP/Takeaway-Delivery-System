#include "FileSystem.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <iomanip>

#define S(x) std::setw(x) <<

void FileSystem::connectSignalsAndSlots() {
	connect(m_fileSystemControls.browseButton, &QPushButton::clicked, this, &FileSystem::selectDataPath);
	connect(m_fileSystemControls.loadButton, &QPushButton::clicked, this, &FileSystem::setDataPath);
}

void FileSystem::setupFileSystemWidget(){
	m_fileSystemWidget = new QWidget();
	m_fileSystemWidget->setParent(nullptr);
	m_fileSystemWidget->setWindowTitle(QString::fromUtf8("文件系统"));
	QVBoxLayout* vLayout = new QVBoxLayout(m_fileSystemWidget);

	QGroupBox* pathGroupBox = new QGroupBox(QString::fromUtf8("数据路径"));
	QHBoxLayout* hLayout = new QHBoxLayout(pathGroupBox);
	m_fileSystemControls.dataPathLineEdit = new QLineEdit();
	m_fileSystemControls.dataPathLineEdit->setText(QString::fromStdString(m_dataPath));
	m_fileSystemControls.browseButton = new QPushButton(QString::fromUtf8("浏览"));
	m_fileSystemControls.loadButton = new QPushButton(QString::fromUtf8("确定"));

	hLayout->addWidget(m_fileSystemControls.dataPathLineEdit);
	hLayout->addWidget(m_fileSystemControls.browseButton);
	vLayout->addWidget(pathGroupBox);
	vLayout->addWidget(m_fileSystemControls.loadButton);
}

FileSystem::FileSystem(){
	m_dataPath = "res/data/";
	setupFileSystemWidget();
	connectSignalsAndSlots();
}

FileSystem::~FileSystem(){
	delete m_fileSystemWidget;
}

std::vector<SetMeal*> FileSystem::loadSetMeals(){
	std::ifstream file(m_dataPath + "setMeals.txt");
	if (!file.is_open()) {
		QMessageBox::critical(nullptr, QString::fromUtf8("错误"), QString::fromUtf8("无法打开套餐数据文件！"));
		return std::vector<SetMeal*>();
	}
	std::vector<SetMeal*> setMeals;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string id, name, description;
		int price, status;
		if (!(iss >> id >> name >> description >> price >> status)) {
			continue;
		}
		SetMeal* meal = new SetMeal(id, name, description, price, status);
		setMeals.push_back(meal);
	}
	file.close();
    return setMeals;
}

std::vector<std::string> FileSystem::loadAddresses(){
	std::ifstream file(m_dataPath + "addresses.txt");
	if (!file.is_open()) {
		QMessageBox::critical(nullptr, QString::fromUtf8("错误"), QString::fromUtf8("无法打开地址数据文件！"));
		return std::vector<std::string>();
	}
	std::vector<std::string> addresses;
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string startPoint, endPoint;
		float distance;
		if (!(ss >> startPoint >> endPoint >> distance)) {
			continue;
		}
		int flag = 0;
		for(auto& addr : addresses)
			if(addr == startPoint){
				flag = 1;
				break;
			}
		if (flag == 0)
			addresses.push_back(startPoint);
	}
	file.close();
	return addresses;
}

std::vector<Order> FileSystem::loadOrders(){
	std::ifstream file(m_dataPath + "orders.txt");
	if (!file.is_open()) {
		QMessageBox::critical(nullptr, QString::fromUtf8("错误"), QString::fromUtf8("无法打开订单数据文件！"));
		return std::vector<Order>();
	}
	std::vector<Order> orders;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string orderId, consignee, phone, address, setMealID, setMealCount, totalPrice, orderTime1, orderTime2, orderStatus;
		if (!(iss >> orderId >> consignee >> phone >> address >> setMealID >> setMealCount >> totalPrice >> orderTime1 >> orderTime2 >> orderStatus)) {
			continue;
		}
		Order order{
			orderId,
			consignee,
			phone,
			address,
			setMealID,
			setMealCount,
			std::stoi(totalPrice),
			orderTime1 + " " + orderTime2,
			orderStatus
		};
		orders.push_back(order);
	}
	file.close();
	return orders;
}

MapData FileSystem::loadMap(){
	std::fstream file;
	file.open(m_dataPath + "addresses.txt", std::ios::in);
	if (!file)
	{
		QMessageBox::critical(nullptr, QString::fromUtf8("错误"), QString::fromUtf8("无法打开地址数据文件！"));
		return MapData();
	}
	MapData mapData;
	std::string line;
	while (getline(file, line))
	{
		std::istringstream iss(line);
		std::string a, b;
		double l;
		iss >> a >> b >> l;
		if (mapData.myMap.find(a) == mapData.myMap.end())
		{
			mapData.myMap[a] = mapData.map.size();
			mapData.map.push_back(a);
			mapData.arcs.emplace_back(mapData.map.size(), 0);
			for (int i = 0; i < mapData.arcs.size(); i++)
			{
				mapData.arcs[i].resize(mapData.map.size(), 0);
			}
		}
		if (mapData.myMap.find(b) == mapData.myMap.end())
		{
			mapData.myMap[b] = mapData.map.size();
			mapData.map.push_back(b);
			mapData.arcs.emplace_back(mapData.map.size(), 0);
			for (int i = 0; i < mapData.arcs.size(); i++)
			{
				mapData.arcs[i].resize(mapData.map.size(), 0);
			}
		}
		int k = mapData.myMap[a];
		int j = mapData.myMap[b];
		mapData.arcs[k][j] = l;
		mapData.arcs[j][k] = l;
	}
	return mapData;
	file.close();
}

void FileSystem::selectDataPath() {
	QString enteredPath = QFileDialog::getExistingDirectory(nullptr, tr("选择文件夹"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	m_fileSystemControls.dataPathLineEdit->setText(enteredPath);
}

void FileSystem::setDataPath() {
	m_dataPath = m_fileSystemControls.dataPathLineEdit->text().toStdString();
	QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("数据路径已更改！"));
}

void FileSystem::saveOrdersToFile(const std::vector<Order>& orders) {
	std::ofstream file(m_dataPath + "orders.txt");
	if (!file.is_open()) {
		QMessageBox::critical(nullptr, QString::fromUtf8("错误"), QString::fromUtf8("无法写入订单数据文件！"));
	}
	for (auto order : orders) {
		file << S(30) order.orderId
			 << S(12) order.consignee
			 << S(30) order.phone
			 << S(30) order.address
			 << S(30) order.setMealID
			 << S(20) order.setMealCount
			 << S(8)  order.totalPrice
			 << S(30) order.orderTime
			 << S(12) order.orderStatus
			 << std::endl;
	}
	file.close();
}

void FileSystem::showFileSystemWidget() {
	m_fileSystemWidget->show();
}