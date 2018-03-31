#ifndef BOX_H
#define BOX_H
#include "shape.h"
class BoxShape : public Shape {
public:
	BoxShape(SimpleWindow &Window,
		const Position &Center, const color &c = Red,
		float Length = 1.0f, float Width = 2.0f,float Thickness=1.0f);
	BoxShape(SimpleWindow &w,
		float XCoord, float YCoord,
		const color &c = Red, float Length = 1.0f,
		float Width = 2.0f, float Thickness = 1.0f);
	float GetWidth() const;
	float GetHeight() const;
	float GetThickness()const;
	void GetSize(float &Width, float &Height) const;
	void Draw();
	void SetSize(float Width, float Height);
	void Erase();
private:
	float Width;
	float Height;
	float Thickness;
};

// Your declaration of BoxShape should be placed in this file

#endif

