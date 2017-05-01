/*2_3. Тупики.
На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является
их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички
указано время ее прибытия, а также время отправления в следующий рейс. Электрички в
расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в
свободный тупик с минимальным номером. При этом если электричка из какого-то тупика
отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот
тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
Напишите программу, которая по данному расписанию определяет, какое минимальное
количество тупиков требуется для работы вокзала.
Формат входных данных. Вначале вводится n - количество электричек в расписании. Затем
вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время -
натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
Формат выходных данных. Натуральное число - минимальное количеством тупиков.
Максимальное время: 50мс, память: 5Мб.
*/
#include <iostream>
#include <cassert>
#include <cstring>

struct times
{
	int timeOfArriving;
	int timeOfDepartment;
};

class Heap
{
public:
	Heap( int n );
	~Heap();
	void Add( times& new_time );
	void ExtractMin( );
	times GetMin( );
	int GetHeapSize( );
	bool IsEmpty( );
	bool CheckSize( );
private:
	void siftDown( int i );
	void siftUp( int i );
	times last( );
	void deleteLast( );

	int heapSize;
	int memorySize;
	times* massOfTrains;

};

Heap::Heap( int n ): memorySize( n ), heapSize( 0 ), massOfTrains( new times[n] )
{}

Heap::~Heap( )
{
	delete[] massOfTrains;
}

void Heap::Add( times& newTime )
{
	massOfTrains[heapSize] = newTime;
	siftUp( GetHeapSize( ) );
	++heapSize;
}

void Heap::ExtractMin( )
{
	assert( !IsEmpty( ) );

	massOfTrains[0] = this->last( );
	this->deleteLast( );
	if( !IsEmpty( ) )
	{
		siftDown( 0 );
	}
	return ;
}

void Heap::siftDown( int i )
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if( massOfTrains[smallest].timeOfDepartment > massOfTrains[left].timeOfDepartment && left < heapSize ){
		smallest = left;
	}
	if( massOfTrains[smallest].timeOfDepartment > massOfTrains[right].timeOfDepartment && right < heapSize ){
		smallest = right;
	}
	if( smallest != i ){
		std::swap( massOfTrains[smallest], massOfTrains[i] );
		siftDown( smallest );
	}
}

void Heap::siftUp( int i )
{
	while( i > 0 )
	{
		int parent = (i - 1) / 2;
		if( massOfTrains[parent].timeOfDepartment <= massOfTrains[i].timeOfDepartment ){
			return;
		}
		std::swap( massOfTrains[parent], massOfTrains[i] );
		i = parent;
	}
}

void Heap::deleteLast( )
{
	massOfTrains[heapSize - 1].timeOfArriving = 0;
	massOfTrains[heapSize - 1].timeOfDepartment = 0;
	--heapSize;
}

times Heap::last( )
{
	return massOfTrains[heapSize - 1];
}

bool Heap::IsEmpty( )
{
	return !heapSize;
}

int Heap::GetHeapSize( )
{
	return heapSize;
}

times Heap::GetMin( )
{
	return massOfTrains[0];
}
bool Heap::CheckSize( )
{
	if( heapSize == memorySize ){
		times* newMass = new times[memorySize * 2];
		memcpy( newMass, massOfTrains, memorySize );
		memorySize *= 2;
		delete[] massOfTrains;
		massOfTrains = newMass;
	}
}


int MaxTrains( Heap* heap, int n )
{
	int max_amount_of_trains = 0;
	for( int i = 0; i < n; ++i ){
		times newTime;
		std::cin >> newTime.timeOfArriving;
		std::cin >> newTime.timeOfDepartment;

		while( !heap->IsEmpty( ) && newTime.timeOfArriving > heap->GetMin( ).timeOfDepartment ){
			heap->ExtractMin( );
		}

		heap->CheckSize( );
		heap->Add( newTime );

		if( max_amount_of_trains < heap->GetHeapSize( ) ){
			max_amount_of_trains = heap->GetHeapSize( );
		}
	}
	return max_amount_of_trains;
}

int main()
{
	int n = 0;
	std::cin >> n;

	Heap heap1( n );
	std::cout << MaxTrains( &heap1, n );

	return 0;
}
