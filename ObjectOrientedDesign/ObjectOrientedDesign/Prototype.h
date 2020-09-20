#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

enum class Shape
{
	Circle,
	Rectangle,
};

class ColoredShapePrototype
{
protected:
	std::string shape_;
	std::string color_;
public:
	ColoredShapePrototype() {}
	ColoredShapePrototype(std::string color) : color_(color) {}
	virtual std::unique_ptr<ColoredShapePrototype> Clone() const = 0;
	virtual void                   ShapeDetails ()          { std::cout<<"Shape: "<<shape_<<"\nColor: " << color_ << "\n"; }
	virtual void                   UpdateColor  (std::string color) { color_ = color; }
	virtual ~ColoredShapePrototype() {}

};

class ColoredCirclePrototype : public ColoredShapePrototype
{
private:
	int radius_;
public:
	ColoredCirclePrototype(std::string color, int raduis) : ColoredShapePrototype(color), radius_(raduis) { shape_ = "Circle"; }
	std::unique_ptr<ColoredShapePrototype> Clone () const override { return std::make_unique<ColoredCirclePrototype>(*this); }
	void ShapeDetails() { ColoredShapePrototype::ShapeDetails(); std::cout << "Radius: " << radius_ << "\n"; }
};

class ColoredRectanglePrototype : public ColoredShapePrototype
{
private:
	int height_;
	int width_;
public:
	ColoredRectanglePrototype(std::string color, int height, int width) : ColoredShapePrototype(color), height_(height), width_(width) { shape_ = "Rectangle"; }
	std::unique_ptr<ColoredShapePrototype> Clone() const override { return std::make_unique<ColoredRectanglePrototype>(*this); }
	void ShapeDetails() { ColoredShapePrototype::ShapeDetails(); std::cout << "Height: " << height_ << "\nWidth:" << width_ << "\n"; }
};

class ShapesPrototypeFactory
{
private:
	std::unordered_map<Shape, std::unique_ptr<ColoredShapePrototype>> prototypes_;
public:
	ShapesPrototypeFactory() {
		prototypes_[Shape::Circle]    = std::make_unique<ColoredCirclePrototype>("White", 5);
		prototypes_[Shape::Rectangle] = std::make_unique<ColoredRectanglePrototype>("White", 2, 3);
	}
	~ShapesPrototypeFactory() { /* No need to explicitly delete memory because of the usage of smart pointers */}
	std::unique_ptr<ColoredShapePrototype> CreatePrototype(Shape shape) { return prototypes_[shape]->Clone(); }
};

#if 0
-----------------------------
Pattern Name : Prototype
Category : Creational Pattern
-----------------------------

/* Intent */
• Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

/* Applicability */
Use the Prototype pattern when a system should be independent of how its products are created, composed, and represented, and when the classes to instantiate are specified at run-time.

/* Participants */
• Prototype
	o declares an interface for cloning itself.
• ConcretePrototype
	o implements an operation for cloning itself.
• Client
	o creates a new object by asking a prototype to clone itself.

/* Collaborations */
• A client asks a prototype to clone itself.

/* Motivation */


/* Notes */
1. Each subclass of Prototype must implement the Clone operation, which may be difficult (classes that do not support copying or have circular references).
   Most languages provide some support for cloning objects. C++ provides a copy constructor, But these facilities don't solve the "shallow copy versus deep copy" problem.
   The default copy constructor in C++ does a member-wise copy, which means pointers will be shared between the copy and the original.
   But cloning prototypes with complex structures usually requires a deep copy, because the clone and the original must be independent.
   Therefore you must ensure that the clone's components are clones of the prototype's components. Cloning forces you to decide what if anything will be shared.
//usage of smart pointers
// override
#endif