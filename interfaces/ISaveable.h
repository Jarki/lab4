#pragma once

namespace lab4 {
	class ISaveable {
	public:
		virtual void set_instance() = 0;
		virtual void get_instance() = 0;
		virtual void save() = 0;
		virtual void load() = 0;
	};
}