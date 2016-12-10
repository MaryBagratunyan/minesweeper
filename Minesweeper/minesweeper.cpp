#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <assert.h>

typedef std::vector<char> row;
typedef std::vector<row> matrix;

const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

std::pair<int,int> random_coordinate(int);
matrix generate_board(int);
bool check(std::pair<int,int>,int);
void print_board(const matrix&);

int main()
{
	srand(time(NULL));
	print_board(generate_board(10));
}

matrix generate_board(int n)
{
	matrix board(n, row(n, '0'));

	std::vector<std::pair<int,int>> coords;
	for(int i = 0; i < n;)
	{
		std::pair<int,int> x = random_coordinate(n);
		if(board[x.first][x.second] == '0')
		{
			board[x.first][x.second] = '*';
			coords.push_back(x);
			++i;
		}
	}

	// Just to be sure :)
	assert(coords.size() == n);

	for(int i = 0; i < coords.size(); ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			std::pair<int,int> new_coord;
			new_coord.first = dx[j] + coords[i].first;
			new_coord.second = dy[j] + coords[i].second;

			if(check(new_coord, n) && 
				board[new_coord.first][new_coord.second] != '*')
			{
				++board[new_coord.first][new_coord.second];
			}
		}
	}

	return board;
}

std::pair<int,int> random_coordinate(int n)
{
	std::pair<int, int> coordinate;
	coordinate.first = rand() % n;
	coordinate.second = rand() % n;

	return coordinate;
	
}

bool check(std::pair<int,int> coord,int n)
{
	return (coord.first >= 0 && coord.first < n && 
			coord.second >= 0 && coord.second < n);
}

void print_board(const matrix& board)
{
	for(int i = 0; i < board.size(); ++i)
	{
		for(int j = 0; j < board.size(); ++j)
			std::cout << board[i][j] << ' ';
		std::cout << std::endl;
	}
}