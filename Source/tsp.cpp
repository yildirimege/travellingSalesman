#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <iostream>

#include "tsp.h"
#include "point.h"
#include "functions.h"

/**
 * \brief Prints Consecutive Asterix (*) signs to increase visuality of output.
 */
void printAsterix()
{
	std::cout << "**********************************************************************" << '\n' << '\n';
}

/**
 * \brief Splits string by delimeter space. In the data strings are in order as: key, xCor, yCor
 * \param str: String to be splitted (a single line from data)
 * \param delim: Delimeter which is used to split (Space character in our case.)
 * \param out: Vector of strings which contains key, xCor and yCor in order.
 */
void splitString(std::string const& str, const char delim, std::vector<std::string> out)
{
	std::stringstream ss(str);
	std::string s;
	while (std::getline(ss, s, delim))
	{
		out.push_back(s);
	}
}

/**
 * \param beststart: refference to previous best starting point.
 * \param numPoints: Number of points (Or size of pointsVec.)
 * \param points: Pre-initialized points in order to use in NN algorithm.
 * \param path: Refference to the path vector that will be modified inside the function
 */
void findBestStart(int& beststart, int numPoints, int** points, std::vector<int>& path)
{
	std::vector < int > bestPath;

	int nnCurrent = MAX_NUMBER;
	int nnBest = MAX_NUMBER;
	int nearest_neighbor_dist = 0;
	int prevPath = MAX_NUMBER;
	int nnResult = 0;
	int bestStartKey = 0;
	int** G = 0;
	G = new int* [numPoints];

	for (int i = 0; i < numPoints; i++)
	{
		path.clear();
		nearest_neighbor_dist = NearestNeighbor::NearestNeighbour(G, numPoints, i, path);
		bestPath = path;
		if (nearest_neighbor_dist < prevPath)
		{
			nnResult = nearest_neighbor_dist;
			bestStartKey = i;
		}

		for (int i = 0; i < numPoints; i++)
		{
			nnCurrent = NearestNeighbor::NearestNeighbour(points, numPoints, i, path);
			if (nnCurrent < nnBest)
			{
				beststart = i;
			}
		}
	}
}

/**
 * \brief Reads from the .tsp data and initializes the Points vector.
 * \return  Returns the Point vector which contains Point object with key, xCor and yCor values.
 */
std::vector <Point> initializePoints()
{
	std::ifstream reader("ca4663.tsp");
	std::vector < Point > pointsVec;
	std::vector< std::vector< std::string> > out;
	std::vector<std::string> tmp;

	std::string line, str;
	std::stringstream ss;

	while (std::getline(reader, line, '\n')) {
		if (line.size() <= 4) //Break the loop if length of the line string is smaller than accepted.
		{
			break;
		}
		ss.str(line);
		while (ss >> str)
		{
			tmp.push_back(str);
		}
		out.push_back(tmp);
		tmp.clear();
		ss.clear();
		pointsVec.push_back(Point(std::stod(out[0][1]), std::stod(out[0][2]), std::stoi(out[0][0])));
		out.clear();
	}
	return pointsVec;
}

/**
 * Main Run.
 */
void main() {
	std::vector < int > path;
	std::vector<float> distanceVec;
	std::vector< std::vector< std::string> > out;
	std::vector<std::string> tmp;

	printAsterix();
	std::cout << "Initializing Points Vector..." << '\n' << '\n';
	std::vector < Point > pointsVec = initializePoints();

	int x = 0, y = 0, key = 0;
	int numPoints = pointsVec.size();

	std::string line, str;
	std::stringstream ss;
	
	int** G = 0;
	G = new int* [numPoints];

	for (int i = 0; i < numPoints; i++)
	{
		G[i] = new int[numPoints];
		for (int j = 0; j < numPoints; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = Function::findEucDistance(pointsVec[i], pointsVec[j]);
			}
		}
	}
	printAsterix();
	clock_t greedyStart = clock();

	/* GREEDY */
	std::cout << "Starting Greedy Algorithm" << '\n' << '\n';
	std::cout << std::fixed << "Greedy Tour Length: " << Greedy::greedyMethod(pointsVec, pointsVec.at(0), path) << '\n' << '\n';
	float greedy_duration = (clock() - greedyStart) / (double)CLOCKS_PER_SEC;
	std::cout << "Time Taken by Greedy: " << greedy_duration << '\n' << '\n';

	printAsterix();

	/*Divide And Conquer*/
	clock_t divide_Start = clock();
	std::cout << "Starting Divide and Conquer Algorithm" << '\n' << '\n';
	std::cout << "Divide and Conquer Tour Length: " << DivideAndConquer::divideAndConquer(pointsVec, pointsVec.at(0)) << '\n' << '\n';
	float divide_duration = (clock() - divide_Start) / (double)CLOCKS_PER_SEC;
	std::cout << "Time taken By Nearest Neighbor: " << divide_duration << '\n' << '\n';

	printAsterix();

	/*Nearest Neighbor*/
	clock_t NNstart = clock();
	std::cout << "Starting Nearest Neighbor Algorithm" << '\n' << '\n';
	std::cout << "Nearest Neighbor Tour Length: " << NearestNeighbor::NearestNeighbour(G, numPoints, 4662, path) << '\n' << '\n';
	float duration = (clock() - NNstart) / (double)CLOCKS_PER_SEC;
	std::cout << "Time taken By Nearest Neighbor: " << duration << '\n' <<'\n';

	printAsterix();
}