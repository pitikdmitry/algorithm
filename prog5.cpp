#include <iostream>
#include <assert.h>

struct Rectangle
{
    Rectangle( ) : Width( 0 ), Height( 0 ) {}
    Rectangle( int width, int height ) : Width( width ), Height( height ) {}
    int Width;
    int Height;
};

int Square( int width, int height )
{
    return width * height;
}

int Square( Rectangle rect )
{
    return Square( rect.Width, rect.Height );
}

class CStack
{
public:
    CStack( int bufferSize );
    ~CStack( );
    void Push( Rectangle& other );
    Rectangle Pop( );
    Rectangle& Back( ) const;
    int GetTopIndex( ) const;
    Rectangle& GetElement( int index );
    int GetBufferSize( ) const;
    bool IsEmpty( ) const;

private:
    Rectangle* buffer;
    int bufferSize;
    int top;//индекс верхнего элемента
};

CStack::CStack( int bufferSize ) : bufferSize( bufferSize ), top( -1 )
{
    buffer = new Rectangle[bufferSize];
}

CStack::~CStack( )
{
    delete[] buffer;
}

void CStack::Push( Rectangle& other )
{
    assert( top + 1 < bufferSize );
    buffer[++top] = other;
}

Rectangle CStack::Pop( )
{
    assert( top != -1 );
    return buffer[top--];
}

bool CStack::IsEmpty( ) const
{
    return top == -1;
}

Rectangle& CStack::Back( ) const
{
    assert( top != -1 );
    return buffer[top];
}

Rectangle& CStack::GetElement( int index )
{
    assert( index > -1 && index < bufferSize );
    return buffer[index];
}

int CStack::GetTopIndex( ) const
{
    return top;
}

int CStack::GetBufferSize( ) const
{
    return bufferSize;
}

void biggestSquare( Rectangle current, CStack& stack, int& maxSquare, bool& last )
{
    Rectangle previous;
    if( !stack.IsEmpty( ) ){
        previous = stack.Back( );
    }

    if( current.Height < previous.Height ){//если меньший
        int tempTop = stack.GetTopIndex( );
        int summaryWidth = 0;
        int previousHeight = 0;

        while( tempTop != -1 ){//идем до самого начала и считаем макс площадь
            Rectangle& tempRect = stack.GetElement( tempTop );
            summaryWidth += tempRect.Width;

            if( Square( summaryWidth, tempRect.Height ) > maxSquare ){
                maxSquare = Square( summaryWidth, tempRect.Height );
            }

            if( tempRect.Height > current.Height ){//подрезаем
                tempRect.Height = current.Height;
            }
            --tempTop;
        }
    }
    if( stack.GetTopIndex( ) < stack.GetBufferSize( ) - 1 ){//добавляем здесь и большой и маленький
        stack.Push( current );
    }

    if( ( stack.GetTopIndex( ) == stack.GetBufferSize( ) - 1 ) && last == false ){//обрабатываем последний
        Rectangle afterLast;//присылаем нулевой прямоугольник который буде после последнего, в стек его класть не будем
        last = true;
        return biggestSquare( afterLast, stack, maxSquare, last );
    }
}

int main()
{
    int n;
    std::cin >> n;
    CStack stack( n );
    int maxSquare = 0;
    bool last = false;
    Rectangle current;
    for( int i = 0; i < n; ++i ){
        std::cin >> current.Width;
        std::cin >> current.Height;
        biggestSquare( current, stack, maxSquare, last );
    }
    std::cout << maxSquare;

    return 0;
}
