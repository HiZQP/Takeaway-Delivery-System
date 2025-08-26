#include "myUtils.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

namespace utils {
	std::string getFormattedLocalTime() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm localTm{};
		std::stringstream ss;
		localtime_s(&localTm, &now_c);
		ss << std::put_time(&localTm, "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}
}
