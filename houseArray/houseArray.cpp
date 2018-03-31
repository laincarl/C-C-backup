
// Display a dream house
#include <iostream>
#include <vector>

using namespace std;

#include "shape.h"
#include "triangle.h"
#include "circle.h"
#include "rect.h"
#include "square.h"

Shape* shapeList[17] = {0};

// prototypes
void BuildHouse(SimpleWindow &W);
void DrawFigure();

SimpleWindow Window("House", 10, 10);


// ApiMain(); manage building and display of house
int ApiMain() 
{
	Window.Open();

	BuildHouse(Window);
	DrawFigure();
   
	cout << "Type a line to terminate the program:";
    char reply;
    cin >> reply;

	return 0;
}

// BuildHouse(): use basic shapes to make a house
void BuildHouse(SimpleWindow &W) 
{
    int i = 0;
	// 1
	// house has a square frame
	SquareShape* pFrame = new SquareShape(W, Position(5, 7), Blue, 5);
	shapeList[i++] = pFrame;
	//house has a Chimney
	RectangleShape* pChimney = new RectangleShape(W, Position(6.7, 3), Blue, 0.5, 1.5);
	shapeList[i++] = pChimney;
	// 2
    // house has a triangular roof	
    TriangleShape* pRoof = new TriangleShape(W, Position(5, 3), Red, 5);
	shapeList[i++] = pRoof;
	
	// 3
	// house has a skylight
	CircleShape* pSkylight = new CircleShape(W, Position(5, 7.75), Yellow, 1.5);
	shapeList[i++] = pSkylight;
	
	// 4
	// house has a door
    RectangleShape* pDoor = new RectangleShape(W, Position(5, 8.5), Yellow, 1.5, 2);
	shapeList[i++] = pDoor;
	
	// 5
	// house has a left window
    SquareShape* pLeftWindow = new SquareShape(W, Position(4,6), Yellow, 1.5);
	shapeList[i++] = pLeftWindow;
	
	// 6
	// house has a right window
    SquareShape* pRightWindow = new SquareShape(W, Position(6,6), Yellow, 1.5);
	shapeList[i++] = pRightWindow;
	//house has a Left Fence
	RectangleShape* pFence1 = new RectangleShape(W, Position(1.3, 8.7), Black, 2, 0.2);
	shapeList[i++] = pFence1;
	RectangleShape* pFence2 = new RectangleShape(W, Position(1.3, 9.2), Black, 2, 0.2);
	shapeList[i++] = pFence2;
	RectangleShape* pFence3 = new RectangleShape(W, Position(0.7, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence3;
	RectangleShape* pFence4 = new RectangleShape(W, Position(1.3, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence4;
	RectangleShape* pFence5 = new RectangleShape(W, Position(1.9, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence5;

	//house has a Right Fence
	RectangleShape* pFence6 = new RectangleShape(W, Position(8.7, 8.7), Black, 2, 0.2);
	shapeList[i++] = pFence6;
	RectangleShape* pFence7 = new RectangleShape(W, Position(8.7, 9.2), Black, 2, 0.2);
	shapeList[i++] = pFence7;
	RectangleShape* pFence8 = new RectangleShape(W, Position(8.1, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence8;
	RectangleShape* pFence9 = new RectangleShape(W, Position(8.7, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence9;
	RectangleShape* pFence10 = new RectangleShape(W, Position(9.3, 8.95), Black, 0.2, 1.0);
	shapeList[i++] = pFence10;
	
}

// DrawFigure(): draw shapes in list shapeList
void DrawFigure() 
{ 
	for (int i=0; i<17; ++i) 
	{
		shapeList[i]->Draw();
		delete shapeList[i];
	}
}


