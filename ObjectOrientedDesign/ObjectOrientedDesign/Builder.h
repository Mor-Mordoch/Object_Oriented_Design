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
	virtual                 ~INutritionFactsBuilder() { delete nutrition_facts_; }
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
	void             BuildPartialNutritionFacts() {
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

/* Intent */
• Separate the construction of a complex object from its representation so that the same construction process can create different representations.

/* Applicability */
Use the Builder pattern when :
• the algorithm for creating a complex object should be independent of the parts that make up the objectand how they're assembled.
• the construction process must allow different representations for the object that's constructed.

/* Participants */
• Builder
	o specifies an abstract interface for creating parts of a Product object.
• ConcreteBuilder
	o constructs and assembles parts of the product by implementing the Builder interface.
	o provides an interface for retrieving the product.
• Director
	o constructs an object using the Builder interface.
• Product
	o represents the complex object under construction.ConcreteBuilder builds the product's internal representation and defines the process by which it's assembled.

/* Collaborations */
• The client creates the Director object and configures it with the desired Builder object.
• Director notifies the builder whenever a part of the product should be built.
• Builder handles requests from the director and adds parts to the product.
• The client retrieves the product from the builder.

/* Motivation */


/* Notes */
1. Empty methods as default in Builder.The build methods are intentionally not declared pure virtual member functions.They're defined as empty methods instead, letting clients override only the operations they're interested in.
2. Builder VS Factory Method :
• Builder is useful when you need to do lots of things to build an object.For example imagine a DOM.You have to create plenty of nodes and attributes to get your final object.
  Factory is used when the factory can easily create the entire object within one method call.
• Consider a restaurant.The creation of "today's meal" is a factory pattern, because you tell the kitchen "get me today's meal" and the kitchen(factory) decides what object to generate, based on hidden criteria.
  The builder appears if you order a custom pizza.In this case, the waiter tells the chef(builder) "I need a pizza; add cheese, onions and tomatoes to it!".
  Thus, the builder exposes the attributes the generated object should have, but hides how to set them.
3. Director can have multiple construction methods.
4. The builder pattern is useful to avoid "telescopic constructor":
	Pizza(int size) { ... }
	Pizza(int size, boolean cheese) { ... }
	Pizza(int size, boolean cheese, boolean tomato) { ... }
	Pizza(int size, boolean cheese, boolean tomato, boolean corn) { ... }
   Instead, Builder alllows creating objects step by step only with the needed data.

#endif