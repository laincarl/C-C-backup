
#include "shadowrect.h"
ShadowedRectangleShape::ShadowedRectangleShape(SimpleWindow &Window,
	const Position &Center, const color &c,
	float Length, float Width) :RectangleShape(Window, Center,
	c, Length, Width){}
ShadowedRectangleShape::ShadowedRectangleShape(SimpleWindow &Window,
	float XPosition, float YPosition,
	const color &c, float w, float h) : RectangleShape(Window,
	Position(XPosition, YPosition), c){
	// No code needed
}

// define ShadowedRectangleShape's constructor here
void ShadowedRectangleShape::Draw() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center
		+ Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center
		+ Position(.5f * Width, .5f * Height);
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
		GetColor(), HasBorder());
	return;
}

/// define ShadowedRectangleShape's draw function here

void ShadowedRectangleShape::Erase() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center
		+ Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center
		+ Position(.5f * Width, .5f * Height);

	// Erase main rectangle first
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
		White, false);
	if (HasBorder()) {
		GetWindow().RenderRectangle(UpperLeft, LowerRight,
			White, true);
	}
	GetWindow().RenderRectangle(UpperLeft + Offset,
		LowerRight + Offset, White, false);
	if (HasBorder()) {
		GetWindow().RenderRectangle(UpperLeft + Offset, LowerRight + Offset,
			White, true);
	}
	return;
}
