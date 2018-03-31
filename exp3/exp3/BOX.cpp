#include "box.h"
BoxShape::BoxShape(SimpleWindow &Window,
	const Position &Center, const color &c, float w,
	float h, float T) : Shape(Window, Center, c),
	Width(w), Height(h), Thickness(T){
	// No code needed
}

BoxShape::BoxShape(SimpleWindow &Window,
	float XPosition, float YPosition,
	const color &c, float w, float h, float T) : Shape(Window,
	Position(XPosition, YPosition), c),
	Width(w), Height(h), Thickness(T) {
	// No code needed
}

float BoxShape::GetWidth() const {
	return Width;
}

float BoxShape::GetHeight() const {
	return Height;
}
float BoxShape::GetThickness()const {
	return Thickness;
}
void BoxShape::GetSize(float &W, float &H) const {
	W = Width;
	H = Height;
	return;
}

void BoxShape::Draw() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();
	const float Thickness = GetThickness();
	const Position UpperLeft = Center
		+ Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center
		+ Position(.5f * Width, .5f * Height);
	const Position UpperLeft1 = Center
		+ Position(-.5f * (Width - Thickness), -.5f * (Height - Thickness));
	const Position LowerRight1 = Center
		+ Position(.5f * (Width - Thickness), .5f * (Height - Thickness));
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
		GetColor(), HasBorder());

	GetWindow().RenderRectangle(UpperLeft1,LowerRight1, GetColor(), HasBorder());
	return;
}

void BoxShape::SetSize(float W, float H) {
	Width = W;
	Height = H;
	return;
}

void BoxShape::Erase() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();
	const float Thickness = GetThickness();
	const Position UpperLeft1 = Center
		+ Position(-.5f * (Width - Thickness), -.5f * (Height - Thickness));
	const Position LowerRight1 = Center
		+ Position(.5f * (Width - Thickness), .5f * (Height - Thickness));
	GetWindow().RenderRectangle(UpperLeft1, LowerRight1,
		White, false);
	if (HasBorder()) {
		GetWindow().RenderRectangle(UpperLeft1, LowerRight1,
			White, true);
	}
	
	return;
}





// Your implementation of BoxShape should be placed in this file

