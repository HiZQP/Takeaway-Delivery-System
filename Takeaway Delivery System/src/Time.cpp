#include "myUtils.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
//"%Y-%m-%d %H:%M:%S"
namespace utils {
	std::string getFormattedLocalTime(std::string format) {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm localTm{};
		std::stringstream ss;
		localtime_s(&localTm, &now_c);
		ss << std::put_time(&localTm, format.c_str());
		return ss.str();
	}
}
