//
// Laboratory 13 - Inheritance (exp3.cpp)
//
#include <assert.h>
#include "box.h"
#include "ezwin.h"

SimpleWindow DemoWindow("Lab 13 - Experiment 3",
	15.0, 9.0, Position(3.0, 3.0));

int ApiMain() {
	// Insert your code here

	DemoWindow.Open();
	assert(DemoWindow.GetStatus() == WindowOpen);

	// Instantiate a red shadowed rectangle
	BoxShape R(DemoWindow, Position(5, 5), Blue, 10.0, 6.0,1.0);
	BoxShape S(DemoWindow, Position(5, 5), Red, 4.0, 3.0,0.5);
	
	R.Draw();
	R.Erase();
	S.Draw();
	S.Erase();

	return 0;

}

