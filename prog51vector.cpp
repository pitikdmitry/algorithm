/*5_1. Первые k элементов длинной последовательности.
Дана очень длинная последовательность целых чисел длины n. Требуется вывести в
отсортированном виде её первые k элементов. Последовательность может не помещаться в
память. Время работы O(n * log(k)). Память O(k). Использовать слияние.
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <assert.h>


struct HeapElement
{
    HeapElement( ) {}
    HeapElement( int Number, int ElementIndex, int MassIndex );
    int Number;
    int ElementIndex;
    int MassIndex;
    bool operator<( HeapElement& other );
    bool operator>( HeapElement& other );
    bool operator<=( HeapElement& other );
};

HeapElement::HeapElement( int Number, int ElementIndex, int MassIndex ): Number( Number ),
                                ElementIndex( ElementIndex), MassIndex( MassIndex )
{}

bool HeapElement::operator<( HeapElement& other )
{
    if( Number < other.Number ){
        return true;
    }
    return false;
}

bool HeapElement::operator>( HeapElement& other )
{
    if( Number > other.Number ){
        return true;
    }
    return false;
}

bool HeapElement::operator<=( HeapElement& other )
{
    if( Number <= other.Number ){
        return true;
    }
    return false;
}

template< class T >
class Heap
{
public:
	Heap( int n );
	~Heap();
	void Add( T& newElement );
	T ExtractMin( );
	int GetHeapSize( );
	bool IsEmpty( );
    void DeleteLast( );
private:
	void siftDown( int i );
	void siftUp( int i );
	T last( );

	int heapSize;
	int memorySize;
	T* mass;

};

template< class T >
Heap< T >::Heap( int n ): memorySize( n ), heapSize( 0 ), mass( new T[n] )
{}

template< class T >
Heap< T >::~Heap( )
{
	delete[] mass;
}

template< class T >
void Heap< T >::Add( T& newElement )
{
	mass[heapSize] = newElement;
	siftUp( GetHeapSize( ) );
	++heapSize;
}

template< class T >
T Heap< T >::ExtractMin( )
{
	assert( !IsEmpty( ) );
    T temp = mass[0];

	mass[0] = this->last( );
	this->DeleteLast( );
	if( !IsEmpty( ) )
	{
		siftDown( 0 );
	}
	return temp;
}

template< class T >
void Heap< T >::siftDown( int i )
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if( mass[smallest] > mass[left] && left < heapSize ){
		smallest = left;
	}
	if( mass[smallest] > mass[right] && right < heapSize ){
		smallest = right;
	}
	if( smallest != i ){
		std::swap( mass[smallest], mass[i] );
		siftDown( smallest );
	}
}

template< class T >
void Heap< T >::siftUp( int i )
{
    while( i > 0 )
	{
		int parent = (i - 1) / 2;
		if( mass[parent] <= mass[i] ){
			return;
		}
		std::swap( mass[parent], mass[i] );
		i = parent;
	}
}

template< class T >
void Heap< T >::DeleteLast( )
{
	--heapSize;
}

template< class T >
T Heap< T >::last( )
{
	return mass[heapSize - 1];
}

template< class T >
bool Heap< T >::IsEmpty( )
{
	return !heapSize;
}

template< class T >
int Heap< T >::GetHeapSize( )
{
	return heapSize;
}

//обычное слияние двух массивов для обычной сортировки слиянием
void merge( const int* a, int aLen, const int* b, int bLen, int* c )
{
    int i = 0;
    int j = 0;
    for( ; i < aLen && j < bLen; ){
        if( a[i] <= b[j] ){
            c[i + j] = a[i];
            ++i;
        }
        else{
            c[i + j] = b[j];
            ++j;
        }
    }

    if( i == aLen ){
        for( ; j < bLen; ++j ){
            c[i + j] = b[j];
        }
    }
    else{
        for( ; i < aLen; ++i ){
            c[i + j] = a[i];
        }
    }
}

//обычная сортировка слиянием
void mergeSort( int* a, int aLen )
{
    if( aLen <= 1 ){
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    mergeSort( a, firstLen );
    mergeSort( a + firstLen, secondLen );
    int* c = new int[aLen];
    merge( a, firstLen, a + firstLen, secondLen, c );
    memcpy( a, c, sizeof( int ) * aLen );
    delete[] c;
}

//слияние первых элдементов отсортированных массивов
void mergeK( std::vector< std::vector< int > >& mass, int k, std::vector< int >& result )
{
    //заполняем кучу первыми элементами массива
    int amountOfArrays = mass.size( );
    //в каждом элементе кучи хранимп число, индекс элемента в массиве, индекс массива
    Heap<HeapElement> heap( amountOfArrays ) ;
    for( int i = 0; i < amountOfArrays; ++i ){
        HeapElement num1( mass[i][0], 0, i );
        heap.Add( num1 );
    }

    int amountOfMins = 0;
    while( amountOfMins < k ){

        HeapElement temp = heap.ExtractMin( );
        result.push_back( temp.Number );

        //если один из массивов кончился уменьшаем размер кучи
        if( temp.ElementIndex >= ( mass[temp.MassIndex].size( ) - 1 ) ){
            heap.DeleteLast( );
        }//если нет добавляем в кучу следующий элемент массива
        else{
            HeapElement num1( mass[temp.MassIndex][temp.ElementIndex + 1], temp.ElementIndex + 1, temp.MassIndex );
            heap.Add( num1 );
        }
        ++amountOfMins;

    }
}

int main()
{
    int n = 0;
    int k = 0;
    std::cin >> n;
    std::cin >> k;

    int amountOfArrays = 0;
    int elementsEntered = 0;
    if( n % k == 0 ){
        amountOfArrays = n / k;
    }
    else{
        amountOfArrays = n / k + 1;
    }

    //заполняем массивы пока не закончится ввод
    int temp = 0;
    std::vector< std::vector< int > > mass( amountOfArrays );
    for( int i = 0; i < amountOfArrays && elementsEntered < n; ++i ){
        for( int j = 0; j < k && elementsEntered < n; ++j, ++elementsEntered ){
            std::cin >> temp;
            mass[i].push_back( temp );
        }
    }

    //отсортируем каждый из массивов отдельно
    for( auto it = mass.begin( ); it != mass.end( ); ++it ){
        mergeSort( it->data( ), it->size( ) );
    }

    std::vector< int > result;
    //ищем К первых элементов
    mergeK( mass, k, result );
    for( auto it = result.begin( ); it != result.end( ); ++it ){
        std::cout << ( *it ) << ' ';
    }

    return 0;
}
