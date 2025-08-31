#pragma once
#include <string>
struct Order {
	// 订单信息
	std::string orderId;
	std::string consignee;
	std::string phone;
	std::string address;
	std::string setMealID;
	std::string setMealCount;
	int totalPrice;
	std::string orderTime;
	std::string orderStatus;
	// 订单派送信息
	std::string startPoint;
	std::string endPoint;
	int distance;
};