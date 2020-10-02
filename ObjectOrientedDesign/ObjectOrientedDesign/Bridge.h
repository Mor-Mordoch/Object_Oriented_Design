#pragma once
#include <iostream>

/* Implementor interface */
/*
 * The Implementation defines the interface for all implementation classes.
 * Typically the Implementation interface provides only primitive operations, while the Abstraction defines higher-level operations based on those primitives.
 */
class Device
{
public:
	Device(int volume, int mode) : device_volume_(0), device_operation_mode_("Disabled") {}
	virtual void GetDeviceName(void) = 0;
	std::string  IsEnabled    (void)       { return device_operation_mode_; }
	void         Enable       (void)       { device_operation_mode_ = "Enabled"; }
	void         Disable      (void)       { device_operation_mode_ = "Disabled"; }
	int          GetVolume    (void)       { return device_volume_; }
	void         SetVolume    (int volume) { device_volume_ = volume; }
	virtual void PrintStatus  (void)       { std::cout << "-----\nDevice: " << device_name_ << "\nMode: " << device_operation_mode_ << "\nVolume: " << device_volume_ << "\n-----\n"; }
	virtual     ~Device() {}
protected:
	std::string device_name_;
	int         device_volume_;
	std::string device_operation_mode_;
};

/* Concrete Implementor */
/* Each Concrete Implementation corresponds to a specific platform and implements the Implementation interface using that platform's API. */
class TV : public Device
{
public:
	TV() : Device(0, 0) { GetDeviceName(); }
	void GetDeviceName(void) { device_name_ = "TV"; }
};

/* Concrete Implementor */
class Radio : public Device
{
public:
	Radio() : Device(0, 0) { GetDeviceName(); }
	void GetDeviceName(void) { device_name_ = "Radio"; }
};

/* Abstraction */
/*
 * The Abstraction defines the interface for the "control" part of the two class hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 */
class Remote
{
public:
	virtual void Power     (void) = 0;
	virtual void VolumeUp  (void) = 0;
	virtual void VolumeDown(void) = 0;
};

/* RefinedAbstraction */
/*
 * You can extend the Abstraction without changing the Implementation classes.
 */
class BasicRemote : public Remote
{
public:
	BasicRemote(Device* device) : remote_type_("Basic Remote") { device_ = device; }
	void Power     (void) { std::cout << "Power toggle from *" << remote_type_ << "*\n"; if (device_->IsEnabled() == "Enabled") device_->Disable(); else device_->Enable(); }
	void VolumeUp  (void) { std::cout << "volume up from *" << remote_type_ << "*\n"; device_->SetVolume(device_->GetVolume() + 5); }
	void VolumeDown(void) { std::cout << "volume down from *" << remote_type_ << "*\n"; if (device_->GetVolume() < 5) device_->SetVolume(0); else device_->SetVolume(device_->GetVolume() - 5); }
	virtual ~BasicRemote() { delete device_; }
protected:
	Device* device_;
	std::string remote_type_;
};

/* RefinedAbstraction */
class AdvancedRemote : public BasicRemote
{
public:
	AdvancedRemote(Device* device) : BasicRemote(device) { remote_type_ = "Advanced Remote"; }
	void Mute() { std::cout << "Mute from *" << remote_type_ << "*\n"; device_->SetVolume(0); }
};

#if 0
------------------------------
Pattern Name : Bridge
Category : Structural Pattern
------------------------------

/* Intent */
Enables splitting a class or a set of closely related classes into two separate hierarchies— abstraction and implementation, which can be developed independently of each other.

/* Applicability */
Use the Bridge pattern when
• you want to avoid a permanent binding between an abstraction and its implementation(useful when you need to be able to switch implementations at runtime).
• both the abstractions and their implementations should be extensible by subclassing.
• changes in the implementation of an abstraction should have no impact on clients; that is, their code should not have to be recompiled.
• you want to hide the implementation of an abstraction completely from clients.In C++ the representation of a class is visible in the class interface.

/* Participants */
• Abstraction
	o defines the abstraction's interface.
	o maintains a reference to an object of type Implementor.
• RefinedAbstraction
	o Extends the interface defined by Abstraction.
• Implementor
	o defines the interface for implementation classes.
• ConcreteImplementor
	o implements the Implementor interface and defines its concrete implementation.

/* Collaborations */
• Abstraction forwards client requests to its Implementor object.

/* Motivation */

/* Note */
1. Consider API for colored shapes.Suppose we have{ triangle, rectangle, sqaure }, and {red, white, blue, green}.To cover all possibilites :
   class RedTriangle : public Red, public Triangle
   class WhiteTriangle : public White, public Triangle
   class BlueTriangle : public Blue, public Triangle
   class RedRectangle : public Red, public: Rectangle
	.
	.
	.
   Created 12 classes.With Bridge, we can create seperate hierarchies and decrease the number of classes to 7. (The more shapes / colors we add, hirerchy grows exponentially!)

#endif