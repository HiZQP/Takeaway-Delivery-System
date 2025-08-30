#include "FileSystem.h"
#include <QMessageBox>
#include <fstream>
#include <sstream>

void FileSystem::connectSignalsAndSlots() {

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
    return setMeals;
}

void FileSystem::showFileSystemWidget() {
	m_fileSystemWidget->show();
}