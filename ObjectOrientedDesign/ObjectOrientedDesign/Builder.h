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
	void             BuildNutritionFacts() {
		nutrition_facts_builder_->BuildCalories();
		nutrition_facts_builder_->BuildProtein();
		nutrition_facts_builder_->BuildCarbohydrate();
		nutrition_facts_builder_->BuildFat();
		nutrition_facts_builder_->BuildSodium();
	}
private:
	INutritionFactsBuilder* nutrition_facts_builder_;
};