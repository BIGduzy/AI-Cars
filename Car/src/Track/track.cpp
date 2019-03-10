#include "track.h"

#include<iostream>

Track::Track(const sf::VertexArray& innerTrack, const sf::VertexArray& outerTrack)
{
	objects.reserve(2);
	objects.emplace_back(innerTrack);
	objects.emplace_back(outerTrack);
	/*
		THIS TRACK HAS TO MANY RIGHTS TO LEARN
	*/
	// Length: 20
	// Outer
	//objects[0]  = {{50, 50},		{150, 150, 150}};
	//objects[1]  = {{450, 50},		{150, 150, 150}};
	//objects[2]  = {{850, 150},		{150, 150, 150}};
	//objects[3]  = {{1200, 350},	{150, 150, 150}};
	//objects[4]  = {{1200, 650},	{150, 150, 150}};
	//objects[5]  = {{1100, 650},	{150, 150, 150}};
	//objects[6]  = {{1000, 600},	{150, 150, 150}};
	//objects[7]  = {{450, 600},		{150, 150, 150}};
	//objects[8]  = {{50, 300},		{150, 150, 150}};
	//objects[9]  = {{50, 50},		{250, 50, 50}};

	//// 9 - 10 = finish line

	//// TODO: Make new vertex array for inner
	//// Inner
	//objects[10]  = {{150, 150},	{250, 50, 50}};
	//objects[11]  = {{450, 150},	{150, 150, 150}};
	//objects[12]  = {{850, 250},	{150, 150, 150}};
	//objects[13]  = {{1100, 450},	{150, 150, 150}};
	//objects[14]  = {{1100, 550},	{150, 150, 150}};
	//objects[15]  = {{1100, 550},	{150, 150, 150}};
	//objects[16]  = {{1000, 500},	{150, 150, 150}};
	//objects[17]  = {{450, 500},	{150, 150, 150}};
	//objects[18]  = {{150, 200},	{150, 150, 150}};
	//objects[19]  = {{150, 150},	{150, 150, 150}};
	// Outer
	// Length: 72
	//objects.append({{ 100,  25},	{150, 150, 150}});

	//objects.append({{1155,  25},	{150, 150, 150}});
	//objects.append({{1180,  50},	{150, 150, 150}});
	//objects.append({{1205,  75},	{150, 150, 150}});
	//objects.append({{1230, 100},	{150, 150, 150}});
	//objects.append({{1255, 125},	{150, 150, 150}});

	//objects.append({{1255, 595},	{150, 150, 150}});
	//objects.append({{1230, 620},	{150, 150, 150}});
	//objects.append({{1205, 645},	{150, 150, 150}});
	//objects.append({{1180, 670},	{150, 150, 150}});
	//objects.append({{1155, 695},	{150, 150, 150}});

	//objects.append({{ 900, 695},	{150, 150, 150}});
	//objects.append({{ 875, 670},	{150, 150, 150}});
	//objects.append({{ 850, 645},	{150, 150, 150}});
	//objects.append({{ 825, 620},	{150, 150, 150}});
	//objects.append({{ 800, 595},	{150, 150, 150}});

	//objects.append({{ 700, 450},	{150, 150, 150}});
	//objects.append({{ 725, 425},	{150, 150, 150}});
	//objects.append({{ 750, 400},	{150, 150, 150}});
	//objects.append({{ 775, 375},	{150, 150, 150}});
	//objects.append({{ 800, 350},	{150, 150, 150}});

	//objects.append({{ 900, 325},	{150, 150, 150}});
	//objects.append({{ 925, 300},	{150, 150, 150}});
	//objects.append({{ 925, 250},	{150, 150, 150}});
	//objects.append({{ 925, 225},	{150, 150, 150}});
	//objects.append({{ 900, 200},	{150, 150, 150}});

	//objects.append({{ 700, 200},	{150, 150, 150}});
	//objects.append({{ 675, 225},	{150, 150, 150}});
	//objects.append({{ 650, 250},	{150, 150, 150}});
	//objects.append({{ 625, 275},	{150, 150, 150}});
	//objects.append({{ 600, 300},	{150, 150, 150}});

	//objects.append({{ 600, 450},	{150, 150, 150}});
	//objects.append({{ 675, 620},	{150, 150, 150}});
	//objects.append({{ 675, 645},	{150, 150, 150}});
	//objects.append({{ 650, 670},	{150, 150, 150}});
	//objects.append({{ 650, 695},	{150, 150, 150}});

	//objects.append({{ 400, 695},	{150, 150, 150}});
	//objects.append({{ 375, 670},	{150, 150, 150}});
	//objects.append({{ 350, 645},	{150, 150, 150}});
	//objects.append({{ 325, 620},	{150, 150, 150}});
	//objects.append({{ 300, 400},	{150, 150, 150}});

	//objects.append({{ 200, 375},	{150, 150, 150}});
	//objects.append({{ 200, 350},	{150, 150, 150}});
	//objects.append({{ 175, 325},	{150, 150, 150}});
	//objects.append({{ 150, 300},	{150, 150, 150}});

	//objects.append({{ 50, 175},	{150, 150, 150}});
	//objects.append({{ 25, 125},	{150, 150, 150}});
	//objects.append({{ 25, 100},	{150, 150, 150}});
	//objects.append({{ 50,  75},	{150, 150, 150}});
	//objects.append({{ 75,  50},	{150, 150, 150}});
	//objects.append({{100,  25},	{150, 150, 150}});

	//// Finish
	//objects.append({{100,   25},	{200, 50, 50}});
	//objects.append({{200,  125},	{200, 50, 50}});

	//// Inner
	//objects.append({{200,  125},	{150, 150, 150}});
	//objects.append({{1050, 125},	{150, 150, 150}});
	//objects.append({{1155, 150},	{150, 150, 150}});
	//objects.append({{1150, 570},	{150, 150, 150}});

	//objects.append({{1100, 600},	{150, 150, 150}});
	//objects.append({{925, 580},	{150, 150, 150}});

	//objects.append({{850, 475},	{150, 150, 150}});
	//objects.append({{1050, 400},	{150, 150, 150}});
	//objects.append({{1050, 127},	{150, 150, 150}});
	//
	//objects.append({{500, 127},	{150, 150, 150}});
	//objects.append({{500, 275},	{150, 150, 150}});
	//objects.append({{500, 500},	{150, 150, 150}});

	//objects.append({{550, 600},	{150, 150, 150}});
	//objects.append({{450, 600},	{150, 150, 150}});
	//objects.append({{450, 400},	{150, 150, 150}});

	//
	//objects.append({{400, 300},	{150, 150, 150}});
	//objects.append({{300, 300},	{150, 150, 150}});

	//objects.append({{200,  125},	{200, 50, 50}});
}
