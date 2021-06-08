#pragma once
#include <iostream>

namespace lab4 {
	class IPrintable {
	public: 
		virtual std::string to_string() = 0;
		virtual bool from_string(std::string string) = 0;
	};
}