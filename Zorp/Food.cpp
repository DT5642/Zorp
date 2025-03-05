#include "Food.h"

Food::Food() : m_healthPoints{ 10 }
{
}

Food::~Food()
{
}

int Food::GetHP()
{
	return m_healthPoints;
}