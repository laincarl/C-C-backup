//
// Laboratory 13 - Inheritance (exp1.cpp)
//
#include <assert.h>
#include "rect.h"
#include <iostream>
using namespace std;

SimpleWindow DemoWindow("Lab 13 - Experiment 1",
	15.0, 9.0, Position(3.0, 3.0));

int ApiMain() {

	DemoWindow.Open();
	assert(DemoWindow.GetStatus() == WindowOpen);

	// Instantiate a red rectangle
	RectangleShape R(DemoWindow, Position(5, 5), Red, 5.0, 5.0);
	R.Draw();

	cout << "Hit ctl-c to terminate" << endl;
	cin.get();
	return 0;
}
