#pragma once
#include <string>
#include <vector>
#include <QObject>
#include <QWidget>

#include "SetMeal.h"

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
	
	void setDataPath();

	void loadData();
	void saveData();

	void saveSetMeals();
	void loadOrders();
	void saveOrders();
public slots:
	void showFileSystemWidget();
	std::vector<SetMeal*> loadSetMeals();
	std::vector<std::string> loadAddresses();
};

