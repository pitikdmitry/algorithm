/*4_1. ​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
реализуйте методом прохода двумя итераторами от начала массива к концу.*/
#include <iostream>

template<typename T>
int choosingPivot( T* a, int n )
{
    int first = 0;
    int last = n - 1;
    int medium = n / 2;
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
    std::swap( a[mediana], a[last] );
}

template<typename T>
int Partition( T* a, int n )
{
    if( n <= 1 ){
        return 0;
    }
    choosingPivot( a, n );

    const T& pivot = a[n - 1];
    int i = 0;
    int j = 0;

    while( j < n - 1 ){

        for( ; a[j] > pivot && j <= n - 1; ++j ){}
        for( ; a[i] <= pivot && i < j ; ++i ){}


        if( j != n - 1 ){
            std::swap( a[i++], a[j++] );
        }
    }

        std::swap( a[i], a[n - 1]);

    return i;
}

template<typename T>
int k_stat( T* a, int n, int k )
{
    int part = Partition( a, n );
    if( part == k ){
        return a[part];
    }
    if( part > k ){
        k_stat( a, part, k );
    }
    if( part < k ){
        k_stat( a + part + 1, n - (part + 1), k - ( part + 1 ) );
    }
}

int main( )
{
    int n = 0;
    int k = 0;
    std::cin >> n;
    std::cin >> k;

    long* mass = new long[n];
    int j = 0;
    j = n;
    for( int i = 0; i < n; ++i ){
         std::cin >> mass[i];
    }
    std::cout << k_stat( mass, n, k );

    delete[] mass;

    return 0;
}
