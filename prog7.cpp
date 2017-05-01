/*7. Быстрейшая сортировка.
Отсортировать массив целых чисел.
Последовательность случайная, максимальный размер 25000000.
Вывести каждое десятое число в отсортированном массиве.
За основу должен быть взят алгоритм быстрой сортировки.
Набор оптимизаций, который необходимо реализовать:
1. Оптимизация выбора опорного элемента.
2. Оптимизация Partition.
3. Оптимизация концевой рекурсии – гибридная сортировка с использованием InsertionSort.
4. Написать без рекурсии.
*/
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <vector>

int getPivotPosition( int left, int right )
{
    return left + rand() % (right - left + 1);
}

template<typename T>
int choosingPivot( T* a, int first, int last )
{
    int medium = ( first + last ) / 2;
    int mediana = medium;

    if( ( a[first] <= a[last] && a[first] >= a[medium] ) || ( a[first] <= a[medium] && a[first] >= a[last] ) ){
        mediana = first;
    }
    else if( ( a[medium] <= a[last] && a[medium] >= a[first] ) || ( a[medium] <= a[first] && a[medium] >= a[last] ) ){
        mediana = medium;
    }
    else{
        mediana = last;
    }
    return mediana;
}

template<class T>
void insertion_sort( T *a, int l, int r, bool ( *comparator )( const T &, const T & ) ) {
    assert( a );
    for( int i = l; i < r; i++ ){
        T x = a[i];
        int j = i;
        while( j > 0 && comparator( x, a[j - 1] ) ){
            a[j] = a[j - 1];
            j--;
        }
        a[j] = x;
    }
}

template <class T>
int partition( T* a, int left, int right, bool ( *comparator )( const T &, const T & ) )
 {

    int pivotPosition = choosingPivot( a, left, right );
    std::swap( a[right], a[pivotPosition] );
    const T& pivot = a[right];

    int i = left;
    int j = right - 1;

    while ( i <= j ) {
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= left && !( comparator( a[j], pivot ) ); --j ) {}

        if( i < j ){
            std::swap( a[i++], a[j--] );
        }
    }

    std::swap( a[i], a[right] );
    return i;
}

bool my_cmp(const int &s1, const int &s2) {
    return s1 < s2;
}

bool comparator(const int &p1, const int &p2) {
    return p1 < p2;
}

template <class T>
void quick_sort(T* a, int n, bool (*comparator)(const T &, const T &))
{
    int left = 0;
    int right = n - 1;
    std::stack<std::pair<int, int> > stack;
    stack.push(std::make_pair(left, right));

    while (!stack.empty()){

        std::pair<int, int> top = stack.top();
        left = top.first;
        right = top.second;
        stack.pop();

        if( right - left <= 10 ){
            insertion_sort( a, left, right + 1, comparator );
            continue;
        }

        int part = partition( a, left, right, comparator );

        if( part - 1 > left ){
            stack.push( std::make_pair( left, part - 1 ) );
        }
        if( part + 1 < right ){
            stack.push( std::make_pair( part + 1, right ) );
        }
    }
}

int main() {

    int* a = new int[25000000];

    int i = 0;
    int temp = 0;
    while(!feof(stdin))
    {
        scanf ("%d %d %d %d %d %d %d %d %d %d ",
                &a[i], &a[i+1], &a[i+2], &a[i+3], &a[i+4], &a[i+5],
                &a[i+6], &a[i+7], &a[i+8], &a[i+9]);
        i += 10;
    }

    quick_sort( &a[0], i, comparator );

    for (int j = 9; j < i; j+=10) {
        std::cout << a[j] << ' ';
    }
    delete[] a;
    return 0;
}
