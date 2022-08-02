#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();

	//getters
	int getX();
	int getY();

	//setters
	void setX(int x);
	void setY(int y);

private:
	int m_x;
	int m_y;

};

