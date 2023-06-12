#include "PathGenerator.h"
#include <fstream>

PathGenerator::PathGenerator(std::vector<std::vector<int>> startGrid) : grid(startGrid)
{
	start = new Cell(0, 0);
	goal = new Cell(grid.size() - 1, grid.size() - 1);
}

PathGenerator::~PathGenerator()
{
}

bool PathGenerator::isValidCell(const std::vector<std::vector<int>>& grid, int row, int col)
{
	int numRows = grid.size();
	int numCols = grid[0].size();
	return (row >= 0 && row < numRows&& col >= 0 && col < numCols&& grid[row][col] == 0);
}

bool PathGenerator::isGoalCell(const Cell& cell, const Cell& goal)
{
	return (cell.row == goal.row && cell.col == goal.col);
}

std::vector<PathGenerator::Cell*> PathGenerator::tracePath(Cell* goal)
{
	std::vector<Cell*> path;
	Cell* current = goal;
	while (current != nullptr)
	{
		path.push_back(current);
		current = current->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

/*
 * Generates the shortest path with the given grid to the goal cell, using the A* method.
 * If the bool parameter is set to true it will instead read a path from the Path.txt file.
 */
std::vector<PathGenerator::Cell*> PathGenerator::aStar(bool readFromFile)
{
	if (readFromFile)
	{
		std::vector<Cell*> path;
		std::fstream inputFile;
		inputFile.open("Path.txt");
		if (inputFile.is_open())
		{
			char delimiter;
			int x, y;
			while (inputFile >> delimiter >> x >> delimiter >> y >> delimiter >> delimiter)
			{
				Cell* cell = new Cell(x, y);
				path.push_back(cell);
			}
			inputFile.close();
			return path;
		}

		std::cout << "Could not open the path.txt file." << std::endl;
		return std::vector<Cell*>();
	}

	if (!isValidCell(grid, start->row, start->col) || !isValidCell(grid, goal->row, goal->col))
	{
		std::cout << "Invalid start or goal cell" << "\n";
		return std::vector<Cell*>();
	}

	std::priority_queue<Cell*, std::vector<Cell*>, CompareCells> openSet;
	openSet.push(new Cell(start->row, start->col));

	std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

	start->costStartToCurrent = 0;
	start->calculateHeuristic(*goal);
	start->totCost = start->costStartToCurrent + start->heuristicCostCurrentToGoal;

	while (!openSet.empty())
	{
		Cell* current = openSet.top();
		openSet.pop();

		if (isGoalCell(*current, *goal))
		{
			return tracePath(current);
		}

		int row = current->row;
		int col = current->col;

		visited[row][col] = true;

		const std::vector<int> dr = { -1, 0, 1, 0 };
		const std::vector<int> dc = { 0, 1, 0, -1 };
		for (int i = 0; i < 4; i++)
		{
			int newRow = row + dr[i];
			int newCol = col + dc[i];

			if (newRow < 0 || newCol < 0 || newRow > grid.size() - 1 || newCol > grid[0].size() - 1)
				continue;

			if (isValidCell(grid, newRow, newCol) && !visited[newRow][newCol])
			{
				auto neighbor = new Cell(newRow, newCol);
				neighbor->parent = current;

				neighbor->costStartToCurrent = current->costStartToCurrent + 1;

				neighbor->calculateHeuristic(*goal);

				neighbor->totCost = neighbor->costStartToCurrent + neighbor->heuristicCostCurrentToGoal;

				openSet.push(neighbor);

				visited[newRow][newCol] = true;
			}
		}
	}

	std::cout << "No path found" << std::endl;
	return std::vector<Cell*>();
}

void PathGenerator::printGrid()
{
	for (const auto& row : grid)
	{
		for (auto cell : row)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}
}

void PathGenerator::printPath(const std::vector<Cell*>& path)
{
	for (const Cell* cell : path)
	{
		std::cout << "(" << cell->row << ", " << cell->col << ")";
	}
	std::cout << "\n";
}

void PathGenerator::writePathToFile(const std::vector<Cell*>& path)
{
	std::fstream outPutFile;
	outPutFile.open("Path.txt");
	for (const Cell* cell : path)
	{
		outPutFile << "(" << cell->row << ", " << cell->col << "), ";
	}
	outPutFile.close();
}