#include "Vector2D.h"

// Initialise constructor
Vector2D::Vector2D()
{
	m_x = 0;
	m_y = 0;

}

// Constructor with parameters
Vector2D::Vector2D(int x, int y)
{
	m_x = x;
	m_y = y;
}

// Destructor
Vector2D::~Vector2D()
{
}

// Setters
void Vector2D::setX(int x)
{
	m_x = x;
}
void Vector2D::setY(int y)
{
	m_y = y;
}

// Getters
int Vector2D::getX()
{
	return m_x;
}
int Vector2D::getY()
{
	return m_y;
}
