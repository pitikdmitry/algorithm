/*3_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться
вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не
исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество
современников. В день 18летия человек уже может принимать участие в собраниях, а в день
80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях
принимать участие в собраниях он не мог.
*/
#include <iostream>
#include <cstdlib>



struct date
{
	int day;
	int month;
	int year;
	bool is_born;
	bool is_dead;
	date( );
	date( int day, int month, int year );
	bool operator>=( date other );
	bool operator<( date other );
};
void input_date_of_start( date& );
void input_date_of_end( date& date_of_birth );

date::date( )
{
	day = 0;
	month = 0;
	year = 0;
	is_born = false;
}

date::date( int day, int month, int year ): day( day ), month( month ), year( year )
{
	is_born = false;
}

void input_date_of_start( date& date_of_birth )
{
	std::cin >> date_of_birth.day;
	std::cin >> date_of_birth.month;
	std::cin >> date_of_birth.year;
	date_of_birth.is_born = false;
	date_of_birth.is_dead = false;
}

void input_date_of_end( date& date_of_birth, date& date_of_death )
{
	date_of_death.is_born = false;
	date_of_death.is_dead = false;
	int temp_dead_day = 0;
	int temp_dead_month = 0;
	int temp_dead_year = 0;
	std::cin >> temp_dead_day;
	std::cin >> temp_dead_month;
	std::cin >> temp_dead_year;

	date temp_dead( temp_dead_day, temp_dead_month, temp_dead_year );

	date date18( date_of_birth.day, date_of_birth.month, date_of_birth.year + 18 );
	date date80( date_of_birth.day, date_of_birth.month, date_of_birth.year + 80 );

	if( date18 < temp_dead ){
		date_of_birth.is_born = true;
		date_of_birth.is_dead = false;
		date_of_birth.year += 18;
	}

	if( date80 < temp_dead && date_of_birth.is_born == true ){
		date_of_death.is_dead = true;
		date_of_death.is_born = false;
		date_of_death.day = date80.day - 1;
		date_of_death.month = date80.month;
		date_of_death.year = date80.year;
	}
	else if( date80 >= temp_dead && date_of_birth.is_born == true ){
		date_of_death.is_dead = true;
		date_of_death.is_born = false;
		date_of_death.day = temp_dead.day - 1;
		date_of_death.month = temp_dead.month;
		date_of_death.year = temp_dead.year;
	}
}

bool date::operator<( date other )
{
	if( year < other.year ){
		return true;
	}
	else if( year == other.year ){
		if( month < other.month ){
			return true;
		}
		else if( month == other.month ){
			if( day < other.day ){
				return true;
			}
			else if( day >= other.day ){
				return false;
			}
		}
		else if( month > other.month ){
			return false;
		}
	}
	else if( year > other.year ){
		return false;
	}
}

bool date::operator>=( date other )
{
	if( this->year > other.year ){
		return true;
	}
	else if( year == other.year ){
		if( month > other.month ){
			return true;
		}
		else if( month == other.month ){
			if( day >= other.day ){
				return true;
			}
			else if( day < other.day ){
				return false;
			}
		}
		else if( month < other.month ){
			return false;
		}
	}
	else if( year < other.year ){
		return false;
	}
}

template<typename T>
void BuildHeap( T* a, int heap_size );

template<typename T>
void HeapSort( T* a, int n );

template<typename T>
void SiftDown( T* a, int i, int heap_size );

template<typename T>
void BuildHeap( T* a, int heap_size )
{
	int parent = ( heap_size - 2 ) / 2;
	for( int i = parent; i >= 0; --i ){
		SiftDown( a, i, heap_size);
	}
}

template<typename T>
void HeapSort( T* a, int n )
{
	int heap_size = n;
	BuildHeap( a, heap_size );

	while( heap_size > 1 ){
		std::swap( a[0], a[heap_size - 1] );
		--heap_size;
		SiftDown( a, 0, heap_size );
	}
}

template<typename T>
void SiftDown( T* a, int i, int heap_size )
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if( left < heap_size && a[smallest] < a[left] ){
		smallest = left;
	}
	if( right < heap_size && a[smallest] < a[right] ){
		smallest = right;
	}
	if( smallest != i ){
		std::swap( a[smallest], a[i] );
		SiftDown( a, smallest, heap_size );
	}
}

template<typename T>
int max_modernists( T* a, int size )
{
	int current_max = 0;
	int max = current_max;
	for( int i = 0; i < size; ++i ){
		if( a[i].is_born == true && a[i].is_dead == false ){
			++current_max;
			if( current_max > max ){
				max = current_max;
			}
		}
		else if( a[i].is_born == false && a[i].is_dead == true ){
			--current_max;
		}
	}
	return max;
}

int main()
{
	int n = 0;
	std::cin >> n;

	int size = 2 * n;
	date* all_dates = new date[size];
	for( int i = 0; i < size; ++i ){
		input_date_of_start( all_dates[i] );
		if( i < size ){
			++i;
			input_date_of_end( all_dates[i - 1], all_dates[i] );
		}
	}

	HeapSort( all_dates, size );

	std::cout << max_modernists( all_dates, size );

	delete[] all_dates;
	return 0;
}
