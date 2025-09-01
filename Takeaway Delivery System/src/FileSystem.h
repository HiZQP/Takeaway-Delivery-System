#pragma once
#include <string>
#include <vector>
#include <QObject>
#include <QWidget>

#include "SetMeal.h"
#include "Order.h"
#include "Map/MapData.h"


struct FileSystemWidgetControls {
	QLineEdit* dataPathLineEdit;
	QPushButton* browseButton;
	QPushButton* loadButton;
};

class FileSystem : public QObject{
	Q_OBJECT
private:
	std::string m_dataPath;

	FileSystemWidgetControls m_fileSystemControls;
	QWidget* m_fileSystemWidget;

	void connectSignalsAndSlots();
	void setupFileSystemWidget();
public:
	FileSystem();
	~FileSystem();

	inline std::string getDataPath() const { return m_dataPath; }

public slots:
	void showFileSystemWidget();
	std::vector<SetMeal*> loadSetMeals();
	std::vector<std::string> loadAddresses();
	std::vector<Order> loadOrders();
	MapData loadMap();
	void selectDataPath();
	void setDataPath();
	void saveOrdersToFile(const std::vector<Order>& orders);
};

