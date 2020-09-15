#pragma once
#include <iostream>

enum class QuadrilateralShape
{
	Rectangle,
	Rhombus,
	Square,
};

/* Product */
class IQuadrilateralShape
{
public:
	virtual void drawQuadrilateralShape() = 0;
};

/* ConcreteProduct */
class CRectangle : public IQuadrilateralShape
{
public:
	void drawQuadrilateralShape() { std::cout << "Rectangle:\n*****\n*****\n"; }
};

/* ConcreteProduct */
class CRhombus : public IQuadrilateralShape
{
public:
	void drawQuadrilateralShape() { std::cout << "Rhombus:\n  *\n ***\n*****\n ***\n  *\n"; }
};

/* ConcreteProduct */
class CSquare : public IQuadrilateralShape
{
public:
	void drawQuadrilateralShape() { std::cout << "Sqaure:\n* * *\n* * *\n* * *\n"; }
};

/* Creator */
class CQuadrilateralShapeFactory
{
public:
	IQuadrilateralShape* createQuadrilateralShape(QuadrilateralShape quadrilateral_shape_type)
	{
		switch (quadrilateral_shape_type)
		{
		case QuadrilateralShape::Rectangle:
			return new CRectangle();
			break;
		case QuadrilateralShape::Rhombus:
			return new CRhombus();
			break;
		case QuadrilateralShape::Square:
			return new CSquare();
			break;
		default:
			return NULL;
			break;
		}
	}
};

#if 0
------------------------------
Pattern Name : Fatory Method
Category : Creational Pattern
------------------------------

/* Intent */
• Define an interface for creating an object, but let subclasses decide which class to instantiate.Factory Method lets a class defer instantiation to subclasses.

/* Applicability */
Use the Factory Method pattern when
• a class can't anticipate the class of objects it must create.
• a class wants its subclasses to specify the objects it creates.

/* Participants */
• Product
	o defines the interface of objects the factory method creates.
• ConcreteProduct
	o implements the Product interface.
• Creator
	o declares the factory method, which returns an object of type Product.
• ConcreteCreator
	o overrides the factory method to return an instance of a ConcreteProduct.

/* Collaborations */
• Creator relies on its subclasses to define the factory method so that it returns an instance of the appropriate ConcreteProduct.

/* Motivation */


/* Notes */
• The factory design pattern is used when we have a superclass with multiple sub-classes and based on input, we need to return one of the sub-class.
  This pattern takes out the responsibility of the instantiation of a class from the client program to the factory class.
• Client creates objects based on the input type.Without using factory method, client will have to manualy add conditions to create another object types.
  So each time a new change is made at the library, client has to change and recompile his code again. BAD DESIGN!
• There are other idioms for factory, like having an API for the factory and the concrete implementations of the factory do not accept a type,
  but they are coupled with the type of instances returned, like this :
  class ProductFactory
  {
  public:
	virtual Product* Make() = 0;
  }
  
  class BookProductFactory : public ProductFactory
  {
  public:
	virtual Product* Make() { return new Book(); }
  }
  In this class BookProductFactory always returns Book instances.
  ProductFactory* factory = new BookProductFactory();
  Product* p1 = factory->Make(); // p1 is a Book

#endif