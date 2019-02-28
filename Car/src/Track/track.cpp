#include "track.h"

Track::Track():
	vertices(sf::LineStrip, 20)
{
	// Outer
	vertices[0]  = {{50, 50},		{150, 150, 150}};
	vertices[1]  = {{450, 50},		{150, 150, 150}};
	vertices[2]  = {{850, 150},		{150, 150, 150}};
	vertices[3]  = {{1200, 350},	{150, 150, 150}};
	vertices[4]  = {{1200, 650},	{150, 150, 150}};
	vertices[5]  = {{1100, 650},	{150, 150, 150}};
	vertices[6]  = {{1000, 600},	{150, 150, 150}};
	vertices[7]  = {{450, 600},		{150, 150, 150}};
	vertices[8]  = {{50, 300},		{150, 150, 150}};
	vertices[9]  = {{50, 50},		{250, 50, 50}};

	// 9 - 10 = finish line

	// TODO: Make new vertex array for inner
	// Inner
	vertices[10]  = {{150, 150},	{250, 50, 50}};
	vertices[11]  = {{450, 150},	{150, 150, 150}};
	vertices[12]  = {{850, 250},	{150, 150, 150}};
	vertices[13]  = {{1100, 450},	{150, 150, 150}};
	vertices[14]  = {{1100, 550},	{150, 150, 150}};
	vertices[15]  = {{1100, 550},	{150, 150, 150}};
	vertices[16]  = {{1000, 500},	{150, 150, 150}};
	vertices[17]  = {{450, 500},	{150, 150, 150}};
	vertices[18]  = {{150, 200},	{150, 150, 150}};
	vertices[19]  = {{150, 150},	{150, 150, 150}};
}
