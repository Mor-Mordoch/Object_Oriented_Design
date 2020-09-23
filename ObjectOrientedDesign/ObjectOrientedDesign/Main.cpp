#include "Builder.h"
#include "Factory_Method.h"
#include "Adapter.h"
#include "Prototype.h"

int main()
{
	std::cout << "               /*---------*/\n";
	std::cout << "               /* Builder */\n";
	std::cout << "               /*---------*/\n";
	NutritionFactsDirector hamburger_director;
	hamburger_director.SetNutritionFactsBuilder(new HamburgerNutritionFactsBuilder());
	hamburger_director.BuildFullNutritionFacts();
	CNutritionFacts* hamburger = hamburger_director.GetNutritionFacts();
	hamburger->ShowNutritionFacts();

	std::cout << "\n";

	NutritionFactsDirector milk_director;
	INutritionFactsBuilder* milk_builder = new MilkNutritionFactsBuilder();
	milk_director.SetNutritionFactsBuilder(milk_builder);
	milk_director.BuildPartialNutritionFacts();
	CNutritionFacts* milk = milk_director.GetNutritionFacts();
	milk->ShowNutritionFacts();

	std::cout << "               /*----------------*/\n";
	std::cout << "               /* Factory Method */\n";
	std::cout << "               /*----------------*/\n";
	CQuadrilateralShapeFactory *shape_factory = new CQuadrilateralShapeFactory();
	IQuadrilateralShape* rectangle = shape_factory->createQuadrilateralShape(QuadrilateralShape::Rectangle);
	rectangle->drawQuadrilateralShape();
	IQuadrilateralShape* rhombus = shape_factory->createQuadrilateralShape(QuadrilateralShape::Rhombus);
	rhombus->drawQuadrilateralShape();
	IQuadrilateralShape* square = shape_factory->createQuadrilateralShape(QuadrilateralShape::Square);
	square->drawQuadrilateralShape();
	delete rectangle;
	delete rhombus;
	delete square;

	std::cout << "               /*---------*/\n";
	std::cout << "               /* Adapter */\n";
	std::cout << "               /*---------*/\n";
	/* Adapter - Class adapter implementation */
	Rectangle* r = new RectangleAdapter(5, 10);
	std::cout << "Rectangle area is : " << r->GetArea() << "\n";
	r->Draw();

	/* Adapter - Object adapter implementation */
	Square* s = new SquareAdapter(new AnotherLine(3));
	std::cout << "Square area is : " << s->GetArea() << "\n";
	s->Draw();

	std::cout << "               /*-----------*/\n";
	std::cout << "               /* Prototype */\n";
	std::cout << "               /*-----------*/\n";
	ShapesPrototypeFactory prototype_factory;
	auto circ = prototype_factory.CreatePrototype(Shape::Circle);
	circ->ShapeDetails();
	auto rect = prototype_factory.CreatePrototype(Shape::Rectangle);
	rect->ShapeDetails();
	rect->UpdateColor("Red");
	rect->ShapeDetails();
	return 0;
}