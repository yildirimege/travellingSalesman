#include "point.h"

Point::Point(float x, float y, int key)
{
    setKey(key);
    setX(x);
    setY(y);
}

Point::~Point()
{
}

void Point::setX(float x)
{
    this->xCor = x;
}

void Point::setY(float y)
{
    this->yCor = y;
}

void Point::setKey(int key)
{
    this->key = key;
}

float Point::getX()
{
    return this->xCor;
}

float Point::getY()
{
    return this->yCor;
}

int Point::getKey()
{
    return this->key;
}