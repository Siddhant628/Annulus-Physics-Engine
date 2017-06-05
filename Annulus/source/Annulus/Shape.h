#pragma once

namespace Annulus
{
	/**
	* The 2D geometry which is used for collision detection.
	*/
	class Shape
	{
	public:
		/**
		* Destructor.
		*/
		~Shape() = default;
	/**
	* The various types of shapes supported by Annulus.
	*/
	enum class Type
	{
		Circle,
		Box
	};
	protected:
		Shape() = default;
	private:
		/**
		* The shape type for this shape.
		*/
		Shape::Type mType;
	};
}
