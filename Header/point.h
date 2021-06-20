#include <math.h>
#pragma once
#ifndef  POINT_H
#define POINT_H

/**
 * \brief Point class than consists Key, xCor, yCor values.
 */
class Point {

	private:
		float xCor = 0;
		float yCor = 0;
		int key = 0;

	public: 
		/**
		 * \brief C-Tor of a Point
		 * 
		 * \param x: X value to be setted.
		 * \param y: Y value to be setted.
		 * \param key: Key value to be setted
		 */
		Point(float x, float y, int key);

		/**
		 * D-Tor
		 * 
		 */
		~Point();

		/**
		 * \brief Sets x value of Point
		 * \param x:  x point as float
		 */
		void setX(float x);

		/**
		 * \brief Sets y value of Point
		 * \param y: y point as float
		 */
		void setY(float y);

		/**
		 * \brief Sets key of Point
		 * \param x : key number as integer
		 */
		void setKey(int key);

		/**
		 * \brief returns x value of Point
		 * \return x value as float.
		 */
		float getX();

		/**
		 * \brief Returns y value of Point
		 * \return y value as float.
		 */
		float getY();

		/**
		 * \brief Returns Key of Point
		 * \return key value as integer.
		 */
		int getKey();
};
#endif // ! POINT_H