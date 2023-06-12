#include "pch.h"
#include <list>
#include "../PathGenerator.cpp"

std::vector<PathGenerator::Cell*> path;
std::string resultsPath = "../TestResults.txt";

class PathGeneratorTestClass : public ::testing::Test
{
protected:
	std::vector<std::vector<int>> grid;
	PathGenerator* pathgenerator;

	void SetUp() override
	{
		grid = {
			{0, 0, 0, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 1, 0, 1, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0}
		};

		pathgenerator = new PathGenerator(grid);
	}
};

TEST_F(PathGeneratorTestClass, TestAStar)
{
	path = pathgenerator->aStar(false);

	ASSERT_FALSE(path.empty());

	writeTestResults("TestAStar", "PathGeneratorTestClass", (path[0]->row == 0));
	writeTestResults("TestAStar", "PathGeneratorTestClass", (path[0]->col == 0));
	writeTestResults("TestAStar", "PathGeneratorTestClass", (path[path.size() - 1]->row == grid.size() - 1));
	writeTestResults("TestAStar", "PathGeneratorTestClass", (path[path.size() - 1]->col == grid.size() - 1));

	EXPECT_EQ(path[0]->row, 0);
	EXPECT_EQ(path[0]->col, 0);
	EXPECT_EQ(path[path.size() -1]->row, grid.size() - 1);
	EXPECT_EQ(path[path.size() -1]->col, grid.size() - 1);

	for (const auto& cell : path) {
		delete cell;
	}
}

TEST_F(PathGeneratorTestClass, PathFileRead)
{
	std::ofstream outputFile("Path.txt");
	outputFile << "(0, 0), (0, 1), (0, 2), (1, 2), (1, 3), (1, 4), (2, 4),";
	outputFile.close();

	std::vector<PathGenerator::Cell*> path = pathgenerator->aStar(true);

	ASSERT_FALSE(path.empty());

	writeTestResults("PathFileRead", "PathGeneratorTestClass", (path[0]->row == 0));
	writeTestResults("PathFileRead", "PathGeneratorTestClass", (path[0]->col == 0));
	writeTestResults("PathFileRead", "PathGeneratorTestClass", (path[path.size() - 1]->row == 2));
	writeTestResults("PathFileRead", "PathGeneratorTestClass", (path[path.size() - 1]->col == 4));

	EXPECT_EQ(path[0]->row, 0);
	EXPECT_EQ(path[0]->col, 0);
	EXPECT_EQ(path[path.size() - 1]->row, 2);
	EXPECT_EQ(path[path.size() - 1]->col, 4);

	for (const auto& cell : path) {
		delete cell;
	}
}

TEST_F(PathGeneratorTestClass, PathFileWrite)
{
	std::vector<PathGenerator::Cell*> path;
	path.push_back(new PathGenerator::Cell(0, 0));
	path.push_back(new PathGenerator::Cell(0, 1));
	path.push_back(new PathGenerator::Cell(0, 2));
	path.push_back(new PathGenerator::Cell(1, 2));
	path.push_back(new PathGenerator::Cell(1, 3));
	path.push_back(new PathGenerator::Cell(1, 4));
	path.push_back(new PathGenerator::Cell(2, 4));

	pathgenerator->writePathToFile(path);

	std::ifstream inputFile("Path.txt");
	std::string pathString;
	std::getline(inputFile, pathString);
	inputFile.close();

	writeTestResults("PathFileWrite", "PathGeneratorTestClass", (pathString == "(0, 0), (0, 1), (0, 2), (1, 2), (1, 3), (1, 4), (2, 4), "));

	EXPECT_EQ(pathString, "(0, 0), (0, 1), (0, 2), (1, 2), (1, 3), (1, 4), (2, 4), ");

	for (const auto& cell : path) {
		delete cell;
	}
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	std::ofstream file(resultsPath, std::ios::trunc);

	if (file.is_open())
	{
		file.close();
	}
	else
	{
		std::cout << "Could not open the file\n";
	}

	int result = RUN_ALL_TESTS();

	return result;
}

void writeTestResults(const std::string& testName, const std::string& testClass, bool succes) 
{
	std::ofstream resultFile;
	resultFile.open(resultsPath, std::ios_base::app);

	if (resultFile.is_open())
	{
		resultFile << '(' << testClass << "." << testName << ") = " << (succes ? "Passed" : "Failed") << "\n";
		resultFile.close();
	}
	else
	{
		std::cout << "Unable to open results file at: " << resultsPath << "\n";
	}
} 