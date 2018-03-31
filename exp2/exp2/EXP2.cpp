//
// Laboratory 13 - Inheritance (exp2.cpp)
//
#include <assert.h>
#include "shadowrect.h"
float s1;
float s2;
SimpleWindow DemoWindow("Lab 13 - Experiment 2",
	15.0, 9.0, Position(3.0, 3.0));

int ApiMain() {

	DemoWindow.Open();
	assert(DemoWindow.GetStatus() == WindowOpen);
	//内外箱的厚度
	s1 = 1.0;
	s2 = 0.5;
	// Instantiate a red shadowed rectangle
	ShadowedRectangleShape R(DemoWindow, Position(5, 5), Blue, 10.0, 6.0);
	ShadowedRectangleShape S(DemoWindow, Position(5, 5), Red, 10.0-s1, 6.0-s1);
	ShadowedRectangleShape T(DemoWindow, Position(5, 5), Red, 4.0, 3.0);
	ShadowedRectangleShape U(DemoWindow, Position(5, 5), Red, 4.0-s2, 3.0-s2);
	R.Draw();
	//R.Erase();
	S.Draw();
	S.Erase();
	T.Draw();
	//T.Erase();
	U.Draw();
	U.Erase();
	return 0;
}
