#include "Adapter.h"

int main()
{
	/* Adapter - Class adapter implementation */
	Rectangle* r = new RectangleAdapter(5, 10);
	std::cout << "Rectangle area is : " << r->GetArea() << "\n";
	r->Draw();

	/* Adapter - Object adapter implementation */
	Square* s = new SquareAdapter(new AnotherLine(3));
	std::cout << "Square area is : " << s->GetArea() << "\n";
	s->Draw();

	return 0;
}