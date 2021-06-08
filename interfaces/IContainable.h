#pragma once

namespace lab4 {
	class ShapeComposite;
	class IContainable {
	public:
		virtual ShapeComposite* get_parent() = 0;
		virtual void set_parent(ShapeComposite* parent) = 0;
	protected:
		ShapeComposite* parent;
	};
}