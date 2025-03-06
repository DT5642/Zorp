#include "Food.h"
#include "GameDefines.h"
#include <fstream>
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

void Food::Save(std::ofstream& out)
{
	if (!out.is_open())
	{
		return;
	}

	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_healthPoints << "\n";
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