#include "pch.h"

#include <list>

#include "../PathGenerator.h"

PathGenerator* pathgenerator;
std::vector<PathGenerator::Cell*> path;

class PathGeneratorTestClass : public ::testing::Test
{
protected:
	void SetUp() override
	{
		srand((unsigned)time(NULL));
		std::vector<std::vector<int>> grid = generateGrid(rand() % 100, rand() % 100);
		pathgenerator = new PathGenerator(grid);
	}
};

TEST_F(PathGeneratorTestClass, TestAStar) {
	path = pathgenerator->aStar(false);
}

TEST_F(PathGeneratorTestClass, TestEmptyGrid)
{
	
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

std::vector<std::vector<int>> generateGrid(int gridWidth, int gridHeight) {
	std::vector<std::vector<int>> grid;
	for (int i = 0; i < gridWidth; i++)
	{
		std::vector<int> columns;
		for (int j = 0; j < gridHeight; j++)
		{
			columns.push_back(0);
		}
		grid.push_back(columns);
	}
	return grid;
}