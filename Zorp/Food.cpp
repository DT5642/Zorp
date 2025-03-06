#include "Food.h"
#include "GameDefines.h"
#include <iostream>

using std::cout;
using std::cin;

Food::Food() : m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

Food::Food(Point2D position) : GameObject{ position }, m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

Food::~Food()
{
}

int Food::GetHP()
{
	return m_healthPoints;
}

void Food::Draw()
{
	cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ]";
}

void Food::DrawDescription()
{
	cout << INDENT << "You smell a recently extinguished campfire, perhaps left by a previous traveller.\n";
}

void Food::LookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here. It should be edible.\n";
}