#include <iostream>
#include <string>
#include <cstdlib>

#define INIT_SIZE 8
#define HASH_1 17
#define HASH_2 19
#define REHASH 0.75

int hash1( const std::string& other, int memorySize );
int hash2( const std::string& other, int memorySize );

enum status { NIL, deleted, filled };

struct CNode
{
    std::string Str;
    status Status;

    CNode( ) : Str(), Status( NIL ) {}
};

class CHashTable
{
public:
    CHashTable( int size );
    ~CHashTable( );
    bool Add( std::string& other );
    bool Remove( std::string& other );
    bool Has( std::string& other, int& index );

private:
    CNode* mass;
    int memorySize;
    int amountOfElements;

    void createNode( std::string& other, int index );
    void resize( );
};

CHashTable::CHashTable( int size ) : memorySize( size ), amountOfElements( 0 )
{
    mass = new CNode[size];
}

CHashTable::~CHashTable( )
{
    delete[] mass;
}

void CHashTable::createNode( std::string& other, int index )
{
    mass[index].Str = other;
    mass[index].Status = filled;
}

bool CHashTable::Add( std::string& other )
{
    if( ( static_cast<double>(amountOfElements) / static_cast<double>(memorySize) ) >= REHASH ){
        resize( );
    }

    int hash_1 = hash1( other, memorySize );
    int hash_2 = hash2( other, memorySize );
    int double_hash = hash_1;

    int deletedIndex = -1;
    int i = 0;
    while( mass[double_hash].Status == filled && i < memorySize ){
        //что такой есть
        if( mass[double_hash].Str == other ){
            return false;
        }

        double_hash = ( hash_1 + i * hash_2 ) % memorySize;
        ++i;
    }

    createNode( other, double_hash );
    ++amountOfElements;

    return true;
}

void CHashTable::resize( )
{
    CNode* oldMass = mass;
    int oldMemorySize = memorySize;

    memorySize = 2 * memorySize;
    CNode* newMass = new CNode[memorySize];
    mass = newMass;
    amountOfElements = 0;//при новом добавлении будет увеличиваться

    for( int i = 0; i < oldMemorySize; ++i ){
        //если заполнен и не удаленный
        if( oldMass[i].Status == filled ){
            Add( oldMass[i].Str );
        }
    }

    delete[] oldMass;
}

bool CHashTable::Has( std::string& other, int& index )
{
    int hash_1 = hash1( other, memorySize );
    int hash_2 = hash2( other, memorySize );
    int double_hash = hash_1;

    int i = 0;
    while( mass[double_hash].Status != NIL && i < memorySize ){
        if( mass[double_hash].Str == other && mass[double_hash].Status == filled ){
            index = double_hash;
            return true;
        }

        double_hash = ( hash_1 + i * hash_2 ) % memorySize;
        ++i;
    }

    return false;
}

bool CHashTable::Remove( std::string& other )
{
    int index = -1;
    if( Has( other, index ) ){
        --amountOfElements;
        mass[index].Status = deleted;
        mass[index].Str.clear( );
        return true;
    }

    return false;
}

int hash1( const std::string& other, int memorySize )
{
    int hash = 0;

    for( int i = 0; i < other.size( ); ++i ){
        hash = ( hash * HASH_1 + other[i] ) % memorySize;
    }

    return hash;
}

int hash2( const std::string& other, int memorySize )
{
    int hash = 0;

    for( int i = 0; i < other.size( ); ++i ){
        hash = ( hash * HASH_2 + other[i] ) % memorySize;
    }

    return ( 2 * hash + 1 ) % memorySize;
}

int main( )
{
    CHashTable table( INIT_SIZE );

    while( true ){
        char command;
        std::string str;

        std::cin >> command >> str;

        if( std::cin.fail( ) ){
            break;
        }

        switch( command ){
            case '+':
                table.Add( str ) ?( std::cout << "OK" << std::endl ) : ( std::cout << "FAIL" << std::endl );
                break;

            case '-':
                table.Remove( str ) ?( std::cout << "OK" << std::endl ) : ( std::cout << "FAIL" << std::endl );
                break;

            case '?':
            {
                int index = -1;
                table.Has( str, index ) ?( std::cout << "OK" << std::endl ) : ( std::cout << "FAIL" << std::endl );
                break;
            }

        default:
            break;
        }
    }
    return 0;
}
