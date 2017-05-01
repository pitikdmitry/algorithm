/*6_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел.
Отсортировать массив методом MSD по битам (бинарный QuickSort).*/
#include <iostream>
#include "assert.h"
#include <stdio.h>
#include <stdint.h>
#define bitsInWord 63

bool digit( unsigned long long num, int w )
{
    return num & ( ( unsigned long long int )1 << w );

}

//со старшего бита
void binaryQuickSort( unsigned long long *a, int l, int r, int w )
{
	if( r <= l || w < 0 ){
		return;
    }
    int i = l;
    int j = r;

	while( i != j ){
		while ( digit( a[i], w ) == 0 && i < j ) ++i;
		while ( digit( a[j], w ) != 0 && j > i ) --j;
		std::swap( a[i] , a[j] );
	}
	if ( digit( a[r], w ) == 0 ){
        ++j;
    }

    binaryQuickSort(a, l, j - 1, w - 1);
	binaryQuickSort(a, j, r, w - 1);
}

int main()
{
	int n;
	std::cin >> n;
	assert( n > 0 );
	unsigned long long *mass = new unsigned long long[n];

	for (int i = 0; i < n; ++i){
		std::cin >> mass[i];
	}

	binaryQuickSort( mass, 0, n - 1, bitsInWord );

	for( int i = 0; i < n; ++i ){
		std::cout << mass[i] << ' ';
	}

	delete[] mass;
}
