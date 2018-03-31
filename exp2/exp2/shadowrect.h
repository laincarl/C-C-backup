#include "rect.h"

class ShadowedRectangleShape : public RectangleShape {
public: ShadowedRectangleShape(SimpleWindow &Window,
	   const Position &Center, const color &c = Red,
	   float Length = 1.0f, float Width = 2.0f);
		ShadowedRectangleShape(SimpleWindow &w,
			float XCoord, float YCoord,
			const color &c = Red, float Length = 1.0f,
			float Width = 2.0f);
	// prototype constructor         
		void Draw();

	// prototype Draw()
		void Erase();
	// prototype Erase()
private:
	Position Offset;
};
