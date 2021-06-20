#pragma once
#include <iostream>
#include <vector>
#ifndef FUNCTIONS_H

/**
 *\brief Maximum Value that an integer can take. Used to initialize best / minimum values in comparative functions.
 */
static int MAX_NUMBER = std::numeric_limits<int>::max();

/**
 * \brief Function class that consists three different algorithm and assistant functions..
 */
class Function
{
public:
	/**
	 * \brief C-Tor
	 * 
	 */
	Function();

	/**
	 * \brief D-Tor.
	 * 
	 */
	~Function();

	/**
	 * .
	 * 
	 * \param First Point
	 * \param Second Point
	 * \return Returns the Euclidian Distance Between Two Points.
	 */
	static float findEucDistance(Point p1, Point p2)
	{
		return sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
	}
};


/**
 *\brief Nearest Neighbor class which is inherited from Function class.
 */
class NearestNeighbor: public Function
{
public:
	/**
	* .
	* \brief Finds the distance of shortest tour between points using Nearest Neighbor Approach, whish is also a greedy algorithm.
	* \param pointsVec: Vector Of Point Objects
	* \param startPoint: Starting Point of tour
	* \param path: Path vector that visited nodes will be pushed back.
	* \return : Returns shortest path length as float.
	*/
	static float NearestNeighbour(int** points, int numPoints, int start, std::vector < int >& path)
	{
		int* visitedList = nullptr;
		visitedList = new int[numPoints];
		memset(visitedList, 0, numPoints * sizeof(int));

		int curPoint = start;
		int closestPoint = 0;
		float totalDist = 0;
		int counter = 0;
		int minimumDistance = MAX_NUMBER;

		visitedList[start] = true;
		path.clear();
		path.push_back(start);

		while (counter < numPoints - 1)
		{
			minimumDistance = MAX_NUMBER;
			for (int j = 0; j < numPoints; j++)
			{
				if (!visitedList[j])
				{
					if (points[curPoint][j] < minimumDistance)
					{
						minimumDistance = points[curPoint][j];
						closestPoint = j;
					}
				}
			}

			if (!visitedList[closestPoint])
			{
				path.push_back(closestPoint);
				totalDist += minimumDistance;
				visitedList[closestPoint] = true;
				curPoint = closestPoint;
				counter++;
			}
		}

		minimumDistance = points[curPoint][start];
		path.push_back(start);
		totalDist += minimumDistance;

		delete[] visitedList;

		return totalDist;
	}
};

/**
 *\brief Greedy class which is inherited from Function class.
 */
class Greedy:public Function
{
public:
	/**
	 * .
	 * \brief Finds the distance of shortest tour between points using Greedy Approach
	 * \param pointsVec: Vector Of Point Objects
	 * \param startPoint: Starting Point of tour
	 * \param path: Path vector that visited nodes will be pushed back.
	 * \return : Returns shortest path length as float.
	 */
	static float greedyMethod(std::vector < Point > pointsVec, Point startPoint, std::vector<int>& path)
	{
		int numPoints = pointsVec.size();

		std::vector < int> distanceVec;
		int* visitedList = nullptr;
		visitedList = new int[numPoints];
		memset(visitedList, 0, numPoints * sizeof(int));

		int curPos = startPoint.getKey();
		int nextPos = 0;

		visitedList[startPoint.getKey()] = true;

		path.push_back(startPoint.getKey());

		int closestCityKey = 0;
		int totalDistance = 0;
		int counter = 0;
		int minDistance = MAX_NUMBER;
		int curDistance = 0;

		while (counter < numPoints - 1)
		{
			int minDistance = MAX_NUMBER;

			for (int i = 0; i < numPoints; i++)
			{
				if (!visitedList[i])
				{
					curDistance = findEucDistance(startPoint, pointsVec.at(i));

					if (curDistance < minDistance) {
						closestCityKey = i;
						minDistance = curDistance;
					}
				}
			}
			path.push_back(closestCityKey);
			visitedList[closestCityKey] = true;
			startPoint = pointsVec.at(closestCityKey);
			totalDistance += minDistance;
			counter++;
		}
	return totalDistance;
	}
};

/**
 *\brief Divide and Conquer class which is inherited from Function class.
 */
class DivideAndConquer :public Function
{
public:
	/**
	 * \brief Finds the distance of shortest tour between points using Divide and Conquer Approach.
	 * \param pointsVec: Vector Of Point Objects.
	 * \param startPoint: Starting Point of tour.
	 * \return Returns shortest tour length as float.
	 */
	static float divideAndConquer(std::vector < Point > pointsVec, Point startPoint)
	{
		std::vector<int> leftPath;
		std::vector<int> rightPath;

		float leftTour, rightTour, totalTour;

		std::size_t const half_size = pointsVec.size() / 2;

		std::vector <Point> left(pointsVec.begin(), pointsVec.begin() + half_size);
		std::vector <Point> right(pointsVec.begin() + half_size, pointsVec.end());

		Point leftEnd(0, 0, 0);
		Point rightBegin(0, 0, 0);

		leftTour = Greedy::greedyMethod(left, left.at(0), leftPath);
		leftEnd = left.at(*leftPath.end());

		rightTour = Greedy::greedyMethod(right, right.at(0), rightPath);
		rightBegin = right.at(0);

		totalTour = leftTour + rightTour + findEucDistance(leftEnd, rightBegin);

		return totalTour;
	}
};
#endif // !FUNCTIONS_H
