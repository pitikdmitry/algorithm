/*1_2. Ломаная 1.
Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую
ломаную, проходящую через все эти точки.
Указание: стройте ломаную в порядке возрастания x-координаты. Если имеются две точки с
одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.*/
#include <iostream>
struct point
{
	int x;
	int y;
};

template< typename T >
bool comparator( T& p1, T& p2 )
{
	if( p1.x < p2.x ){
		return true;
	}
	else if( p1.x == p2.x ){
		if( p1.y < p2.y ){
			return true;
		}
		else if( p1.y == p2.y ){
			return true;
		}
		else if( p1.y > p2.y ){
			return false;
		}
	}
	else if( p1.x > p2.x ){
		return false;
	}
}

void insert_sort( point* a, int n, bool (*comparator)( point& p1, point& p2 ) )
{
	for( int i = 1; i < n; ++i ){
		point tmp = a[i];
		int j = i - 1;
		for( j; j >= 0 && comparator( tmp, a[j] ); --j ){//tmp < a[j]
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
}

int main()
{
	int n = 0;
	std::cin >> n;
	point* mass_of_points = new point[n];
	for( int i = 0; i < n; ++i){
		std::cin >> mass_of_points[i].x;
		std::cin >> mass_of_points[i].y;
	}

	insert_sort( mass_of_points, n, comparator );

	point previous;
	previous.x = -1;
	previous.y = -1;
	for( int j = 0; j < n; ++j){
		if( mass_of_points[j].x != previous.x && mass_of_points[j].y != previous.y ){
			std::cout << mass_of_points[j].x << ' ';
			std::cout << mass_of_points[j].y;
			std::cout << std::endl;
		}
	}

	delete[] mass_of_points;
	return 0;
}
