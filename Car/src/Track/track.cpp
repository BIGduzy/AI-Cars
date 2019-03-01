#include "track.h"

#include<iostream>

Track::Track():
	vertices(sf::LineStrip, 72)
{
	/*
		THIS TRACK HAS TO MANY RIGHTS TO LEARN
	*/
	// Length: 20
	// Outer
	//vertices[0]  = {{50, 50},		{150, 150, 150}};
	//vertices[1]  = {{450, 50},		{150, 150, 150}};
	//vertices[2]  = {{850, 150},		{150, 150, 150}};
	//vertices[3]  = {{1200, 350},	{150, 150, 150}};
	//vertices[4]  = {{1200, 650},	{150, 150, 150}};
	//vertices[5]  = {{1100, 650},	{150, 150, 150}};
	//vertices[6]  = {{1000, 600},	{150, 150, 150}};
	//vertices[7]  = {{450, 600},		{150, 150, 150}};
	//vertices[8]  = {{50, 300},		{150, 150, 150}};
	//vertices[9]  = {{50, 50},		{250, 50, 50}};

	//// 9 - 10 = finish line

	//// TODO: Make new vertex array for inner
	//// Inner
	//vertices[10]  = {{150, 150},	{250, 50, 50}};
	//vertices[11]  = {{450, 150},	{150, 150, 150}};
	//vertices[12]  = {{850, 250},	{150, 150, 150}};
	//vertices[13]  = {{1100, 450},	{150, 150, 150}};
	//vertices[14]  = {{1100, 550},	{150, 150, 150}};
	//vertices[15]  = {{1100, 550},	{150, 150, 150}};
	//vertices[16]  = {{1000, 500},	{150, 150, 150}};
	//vertices[17]  = {{450, 500},	{150, 150, 150}};
	//vertices[18]  = {{150, 200},	{150, 150, 150}};
	//vertices[19]  = {{150, 150},	{150, 150, 150}};
	// Outer
	// Length: 72
	vertices.append({{ 100,  25},	{150, 150, 150}});

	vertices.append({{1155,  25},	{150, 150, 150}});
	vertices.append({{1180,  50},	{150, 150, 150}});
	vertices.append({{1205,  75},	{150, 150, 150}});
	vertices.append({{1230, 100},	{150, 150, 150}});
	vertices.append({{1255, 125},	{150, 150, 150}});

	vertices.append({{1255, 595},	{150, 150, 150}});
	vertices.append({{1230, 620},	{150, 150, 150}});
	vertices.append({{1205, 645},	{150, 150, 150}});
	vertices.append({{1180, 670},	{150, 150, 150}});
	vertices.append({{1155, 695},	{150, 150, 150}});

	vertices.append({{ 900, 695},	{150, 150, 150}});
	vertices.append({{ 875, 670},	{150, 150, 150}});
	vertices.append({{ 850, 645},	{150, 150, 150}});
	vertices.append({{ 825, 620},	{150, 150, 150}});
	vertices.append({{ 800, 595},	{150, 150, 150}});

	vertices.append({{ 700, 450},	{150, 150, 150}});
	vertices.append({{ 725, 425},	{150, 150, 150}});
	vertices.append({{ 750, 400},	{150, 150, 150}});
	vertices.append({{ 775, 375},	{150, 150, 150}});
	vertices.append({{ 800, 350},	{150, 150, 150}});

	vertices.append({{ 900, 325},	{150, 150, 150}});
	vertices.append({{ 925, 300},	{150, 150, 150}});
	vertices.append({{ 925, 250},	{150, 150, 150}});
	vertices.append({{ 925, 225},	{150, 150, 150}});
	vertices.append({{ 900, 200},	{150, 150, 150}});

	vertices.append({{ 700, 200},	{150, 150, 150}});
	vertices.append({{ 675, 225},	{150, 150, 150}});
	vertices.append({{ 650, 250},	{150, 150, 150}});
	vertices.append({{ 625, 275},	{150, 150, 150}});
	vertices.append({{ 600, 300},	{150, 150, 150}});

	vertices.append({{ 600, 450},	{150, 150, 150}});
	vertices.append({{ 700, 620},	{150, 150, 150}});
	vertices.append({{ 700, 645},	{150, 150, 150}});
	vertices.append({{ 675, 670},	{150, 150, 150}});
	vertices.append({{ 650, 695},	{150, 150, 150}});

	vertices.append({{ 400, 695},	{150, 150, 150}});
	vertices.append({{ 375, 670},	{150, 150, 150}});
	vertices.append({{ 350, 645},	{150, 150, 150}});
	vertices.append({{ 325, 620},	{150, 150, 150}});
	vertices.append({{ 325, 400},	{150, 150, 150}});

	vertices.append({{ 250, 375},	{150, 150, 150}});
	vertices.append({{ 200, 350},	{150, 150, 150}});
	vertices.append({{ 175, 325},	{150, 150, 150}});
	vertices.append({{ 150, 300},	{150, 150, 150}});

	vertices.append({{ 50, 175},	{150, 150, 150}});
	vertices.append({{ 25, 125},	{150, 150, 150}});
	vertices.append({{ 25, 100},	{150, 150, 150}});
	vertices.append({{ 50,  75},	{150, 150, 150}});
	vertices.append({{ 75,  50},	{150, 150, 150}});
	vertices.append({{100,  25},	{150, 150, 150}});

	// Finish
	vertices.append({{100,   25},	{200, 50, 50}});
	vertices.append({{200,  125},	{200, 50, 50}});

	// Inner
	vertices.append({{200,  125},	{150, 150, 150}});
	vertices.append({{1050, 125},	{150, 150, 150}});
	vertices.append({{1155, 150},	{150, 150, 150}});
	vertices.append({{1150, 570},	{150, 150, 150}});

	vertices.append({{1100, 600},	{150, 150, 150}});
	vertices.append({{925, 580},	{150, 150, 150}});

	vertices.append({{850, 475},	{150, 150, 150}});
	vertices.append({{1050, 400},	{150, 150, 150}});
	vertices.append({{1050, 127},	{150, 150, 150}});
	
	vertices.append({{500, 127},	{150, 150, 150}});
	vertices.append({{500, 275},	{150, 150, 150}});
	vertices.append({{500, 500},	{150, 150, 150}});

	vertices.append({{550, 600},	{150, 150, 150}});
	vertices.append({{450, 600},	{150, 150, 150}});
	vertices.append({{450, 400},	{150, 150, 150}});

	
	vertices.append({{400, 300},	{150, 150, 150}});
	vertices.append({{300, 300},	{150, 150, 150}});

	vertices.append({{200,  125},	{200, 50, 50}});
}
