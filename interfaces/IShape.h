#pragma once
#include "IDrawable.h"
#include "IPrintable.h"
#include "IClickable.h"
#include "IContainable.h"

namespace lab4 {
	enum ShapeType {
		unknown = 0,
		shape,
		circle,
		rectangle,
		shape_composite
	};

	static std::string STRING_DELIMITER = "%%";

	class IShape : public IDrawable, public IPrintable, public IClickable, public IContainable{
	public:
		virtual ShapeType get_type() = 0;
	};
}