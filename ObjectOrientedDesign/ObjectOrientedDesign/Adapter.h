#pragma once
#include <iostream>
/*
Intent
Adapter is a structural design pattern that lets classes work together (that couldn't otherwise because of incompatible interfaces).

Applicability
Use the Adapter pattern when:
• you want to use an existing class, and its interface does not match the one you need.
• you want to create a reusable class that cooperates with unrelated or unforeseen classes, that is, classes that don't necessarily have compatible interfaces.

Participants
• Target
	o defines the domain-specific interface that Client uses.
• Client
	o collaborates with objects conforming to the Target interface.
• Adaptee
	o defines an existing interface that needs adapting.
• Adapter
	o adapts the interface of Adaptee to the Target interface.

Collaborations
• Clients call operations on an Adapter instance. In turn, the adapter calls Adaptee operations that carry out the request.

Implementation
• Object adapter
	o This implementation uses the object composition principle: the adapter implements the interface of one object and wraps the other one.
• Class adapter
	o This implementation uses inheritance: the adapter inherits interfaces from both objects at the same time (this approach can only be implemented in programming languages that support multiple inheritance).
	  (Adapter would inherit publicly from Target and privately from Adaptee. Thus Adapter would be a subtype of Target but not of Adaptee.)

More on Adapter
This is a special object that converts the interface of one object so that another object can understand it. The wrapped object isn’t even aware of the adapter.
Adapters can not only convert data into various formats but can also help objects with different interfaces collaborate. Here’s how it works:
1. The adapter gets an interface, compatible with one of the existing objects.
2. Using this interface, the existing object can safely call the adapter’s methods.
3. Upon receiving a call, the adapter passes the request to the second object, but in a format and order that the second object expects.
*/

typedef int Length;
typedef int Width;

/*-----------------------------------------------------*/
/* Class Adapter Implementation (Multiple Inheritance) */
/*-----------------------------------------------------*/

/**
* Target
* The Target defines the domain-specific interface used by the client code.
*/
class Rectangle
{
public:
	Rectangle             (Width rec_wid, Length rec_len) : rec_wid_(rec_wid), rec_len_(rec_len) {}
	virtual int  GetArea  () = 0;
	virtual void Draw     () = 0;
	virtual     ~Rectangle() = default;
protected:
	Length rec_len_;
	Width  rec_wid_;
};


/**
* Adaptee
* The Adaptee contains some useful behavior, but its interface is incompatible with the existing client code.
* The Adaptee needs some adaptation before the client code can use it.
*/
class Line
{
public:
	void DrawLine(Length line_len) {
		for (int i = 0; i < line_len; ++i)
			std::cout << "* ";
		std::cout << "\n";
	}
};

/**
*  Adapter
* The Adapter makes the Adaptee's interface compatible with the Target's interface.
*/
class RectangleAdapter : public Rectangle, private Line
{
public:
	RectangleAdapter(Width w, Length l) : Rectangle(w, l) {}
	virtual int  GetArea() { return rec_len_ * rec_wid_; }
	virtual void Draw   () {
		for (int i = 0; i < rec_wid_; ++i)
			Line::DrawLine(rec_len_);
	}
};

/*----------------------------------------------------*/
/* Object Adapter Implementation (Object Composition) */
/*----------------------------------------------------*/

class Square
{
public:
	virtual int  GetArea() = 0;
	virtual void Draw   () = 0;
	virtual     ~Square () = default;
};

class AnotherLine
{
public:
	AnotherLine(Length line_len) : line_len_(line_len) {}
	void DrawLine() {
		for (int i = 0; i < line_len_; ++i)
			std::cout << "@ ";
		std::cout << "\n";
	}
	int GetLineLen() { return line_len_; }
private:
	Length line_len_;
};

class SquareAdapter : public Square
{
public:
	SquareAdapter      (AnotherLine* l) : line_(l) {}
	virtual int GetArea() { return (line_->GetLineLen() * line_->GetLineLen()); }
	virtual void Draw  () {
		for (int i = 0; i < line_->GetLineLen(); ++i)
			line_->DrawLine();
	}
private:
	AnotherLine* line_;
};