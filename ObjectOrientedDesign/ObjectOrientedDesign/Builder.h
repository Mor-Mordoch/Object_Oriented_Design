#pragma once
#include <iostream>

/* Product class */
class CNutritionFacts
{
public:
	void SetCalories       (const int calories)     { calories_ = calories; }
	void SetFat            (const int fat)          { fat_ = fat; }
	void SetSodium         (const int sodium)       { sodium_ = sodium; }
	void SetCarbohydrate   (const int carbohydrate) { carbohydrate_ = carbohydrate; }
	void SetProtein        (const int protein)      { protein_ = protein; }
	void ShowNutritionFacts() {
		std::cout << "Calories: " << calories_ << "\nFat: " << fat_ << "\nSodium: " << sodium_ << "\nCarbohydrate: " <<
			carbohydrate_ << "\nProtein: " << protein_ << "\n";
	}
private:
	int calories_;
	int fat_;
	int sodium_;
	int carbohydrate_;
	int protein_;
};

/* Builder class */
class INutritionFactsBuilder
{
public:
	virtual void             BuildCalories         () {}
	virtual void             BuildFat              () {}
	virtual void             BuildSodium           () {}
	virtual void             BuildCarbohydrate     () {}
	virtual void             BuildProtein          () {}
	virtual  	            ~INutritionFactsBuilder() { delete nutrition_facts_; }
	virtual CNutritionFacts* GetNutritionFacts     () { return nutrition_facts_; }
protected:
	CNutritionFacts* nutrition_facts_;
	INutritionFactsBuilder() { nutrition_facts_ = new CNutritionFacts(); }
};

/* ConcreteBuilder class */
class MilkNutritionFactsBuilder : public INutritionFactsBuilder
{
public:
	void BuildCalories    () { nutrition_facts_->SetCalories(61); }
	void BuildFat         () { nutrition_facts_->SetFat(3); }
	void BuildSodium      () { nutrition_facts_->SetSodium(50); }
	void BuildCarbohydrate() { nutrition_facts_->SetCarbohydrate(5); }
	void BuildProtein     () { nutrition_facts_->SetProtein(3); }
};

/* ConcreteBuilder class */
class HamburgerNutritionFactsBuilder : public INutritionFactsBuilder
{
public:
	void BuildCalories    () { nutrition_facts_->SetCalories(285); }
	void BuildFat         () { nutrition_facts_->SetFat(13); }
	void BuildSodium      () { nutrition_facts_->SetSodium(500); }
	void BuildCarbohydrate() { nutrition_facts_->SetCarbohydrate(30); }
	void BuildProtein     () { nutrition_facts_->SetProtein(12); }
};

/* Director class */
class NutritionFactsDirector
{
public:
	void             SetNutritionFactsBuilder(INutritionFactsBuilder* nutrition_facts_builder) { nutrition_facts_builder_ = nutrition_facts_builder; }
	CNutritionFacts* GetNutritionFacts() { return nutrition_facts_builder_->GetNutritionFacts(); }
	void             BuildFullNutritionFacts() {
		nutrition_facts_builder_->BuildCalories();
		nutrition_facts_builder_->BuildProtein();
		nutrition_facts_builder_->BuildCarbohydrate();
		nutrition_facts_builder_->BuildFat();
		nutrition_facts_builder_->BuildSodium();
	}
	void              BuildPartialNutritionFacts() {
		nutrition_facts_builder_->BuildCalories();
		nutrition_facts_builder_->BuildProtein();
	}
private:
	INutritionFactsBuilder* nutrition_facts_builder_;
};

#if 0
------------------------------
Pattern Name : Builder
Category : Creational Pattern
------------------------------
Intent
• Separate the construction of a complex object from its representation so that the same construction process can create different representations.

///Motivation

Applicability
Use the Builder pattern when :
• the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
• the construction process must allow different representations for the object that's constructed.

Participants
• Builder
o specifies an abstract interface for creating parts of a Product object.
• ConcreteBuilder
o constructs and assembles parts of the product by implementing the Builder interface.
o defines and keeps track of the representation it creates.
o provides an interface for retrieving the product.
• Director
o constructs an object using the Builder interface.
• Product
o represents the complex object under construction.ConcreteBuilder builds the product's internal representation and defines the process by which it's assembled.
o includes classes that define the constituent parts, including interfaces for assembling the parts into the final result.

Collaborations
• The client creates the Director object and configures it with the desired Builder object.
• Director notifies the builder whenever a part of the product should be built.
• Builder handles requests from the director and adds parts to the product.
• The client retrieves the product from the builder.

Consequences
1. It lets you vary a product's internal representation. The Builder object provides the director with an abstract interface for constructing the product.
The interface lets the builder hide the representation and internal structure of the product.It also hides how the product gets assembled.
Because the product is constructed through an abstract interface, all you have to do to change the product's internal representation is define a new kind of builder.
2. It isolates code for construction and representation.The Builder pattern improves modularity by encapsulating the way a complex object is constructed and represented.
Clients needn't know anything about the classes that define the product's internal structure; such classes don't appear in Builder's interface.
Each ConcreteBuilder contains all the code to create and assemble a particular kind of product.The code is written once;
then different Directors can reuse it to build Product variants from the same set of parts.
3. It gives you finer control over the construction process.Unlike creational patterns that construct products in one shot, the Builder pattern constructs the product step by step
under the director's control. Only when the product is finished does the director retrieve it from the builder.
Hence the Builder interface reflects the process of constructing the product more than other creational patterns.
This gives you finer control over the construction process and consequently the internal structure of the resulting product.

Implementation
Typically there's an abstract Builder class that defines an operation for each component that a director may ask it to create. The operations do nothing by default.
A ConcreteBuilder class overrides operations for components it's interested in creating.
Here are other implementation issues to consider :
1. Assembly and construction interface.Builders construct their products in step - by - step fashion.Therefore the Builder class interface must be general enough to allow the construction of products for all kinds of concrete builders.
2. Why no abstract class for products ? In the common case, the products produced by the concrete builders differ so greatly in their representation that there is little to gain from giving different
products a common parent class.Because the client usually configures the director with the proper concrete builder, the client is in a position to know which concrete subclass of Builder is in use and can handle its products accordingly.
3. Empty methods as default in Builder.In C++, the build methods are intentionally not declared pure virtual member functions.They're defined as empty methods instead, letting clients override only the operations they're interested in.

More Info
1. The key difference between a builder and factory IMHO, is that a builder is useful when you need to do lots of things to build an object.For example imagine a DOM.You have to create plenty of nodes and attributes to get your final object.
A factory is used when the factory can easily create the entire object within one method call.
2. The builder pattern is a good choice when designing classes whose constructors or static factories would have more than a handful of parameters.
We've all at some point encountered a class with a list of constructors where each addition adds a new option parameter:
Pizza(int size) { ... }
Pizza(int size, boolean cheese) { ... }
Pizza(int size, boolean cheese, boolean tomato) { ... }
Pizza(int size, boolean cheese, boolean tomato, boolean corn) { ... }
This is called the Telescoping Constructor Pattern.The problem with this pattern is that once constructors are 4 or 5 parameters long it becomes difficult to remember the required order of the parameters as well as what particular constructor you might want in a given situation.
The better alternative is to use the Builder Pattern.
3. Consider a restaurant.The creation of "today's meal" is a factory pattern, because you tell the kitchen "get me today's meal" and the kitchen(factory) decides what object to generate, based on hidden criteria.
The builder appears if you order a custom pizza.In this case, the waiter tells the chef(builder) "I need a pizza; add cheese, onions and tomatoes to it!" Thus, the builder exposes the attributes the generated object should have, but hides how to set them.
4. Advantages of Builder Design Pattern
• The parameters to the constructor are reduced and are provided in highly readable method calls.
• Builder design pattern also helps in minimizing the number of parameters in constructor and thus there is no need to pass in null for optional parameters to the constructor.
• Object is always instantiated in a complete state
• Immutable objects can be build without much complex logic in object building process.
Disadvantages of Builder Design Pattern
• The number of lines of code increase at least to double in builder pattern, but the effort pays off in terms of design flexibility and much more readable code.
• Requires creating a separate ConcreteBuilder for each different type of Product.

/////////Advanteges:
/////////Disadveteges:
#endif