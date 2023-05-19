#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

class PathGenerator
{
public:
	PathGenerator(std::vector<std::vector<int>> *startGrid);
	~PathGenerator();

	struct Cell
	{
		int row;
		int col;
		int totCost;
		int costStartToCurrent;
		int heuristicCostCurrentToGoal;
		Cell* parent;

		Cell(int r, int c) : row(r), col(c), totCost(0), costStartToCurrent(0), heuristicCostCurrentToGoal(0), parent(nullptr) {}

		void calculateHeuristic(const Cell& goal)
		{
			heuristicCostCurrentToGoal = std::abs(row - goal.row) + std::abs(col - goal.col);
		}
	};
	Cell* start;
	Cell* goal;

	struct CompareCells
	{
		bool operator()(const Cell* leftHs, const Cell* rightHs) const
		{
			return leftHs->totCost > rightHs->totCost;
		}
	};

	std::vector<std::vector<int>> *grid;

	bool isValidCell(const std::vector<std::vector<int>>& grid, int row, int col);
	bool isGoalCell(const Cell& cell, const Cell& goal);

	std::vector<Cell*> tracePath(Cell* goal);

	std::vector<Cell*> aStar();
	void printGrid();
	void printPath(const std::vector<Cell*>& path);
};