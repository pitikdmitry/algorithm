#include <iostream>
#include <assert.h>
#include <queue>

template <typename T>
struct CNode
{
    T Data;
    CNode<T>* Left;
    CNode<T>* Right;
    CNode( ) : Data( 0 ), Left( nullptr ), Right( nullptr ) {}
    CNode( int Data ) : Data( Data ), Left( nullptr ), Right( nullptr ) {}
};

template <typename T>
class CTree
{
public:
    CTree( ) : root( nullptr ) {}
    ~CTree( );
    CNode<T>* Find( T Key );
    CNode<T>* FindMin( );
    CNode<T>* FindMax( );
    void AddNode( T Data );
    void TraverseBFS( );
    CNode<T>* GetRoot( );

private:
    CNode<T>* root;
    void deleteTree( CNode<T>* node );
};

template <typename T>
CTree<T>::~CTree( )
{
    deleteTree( root );
}

template <typename T>
void CTree<T>::deleteTree( CNode<T>* node )
{
    if( node == nullptr ){
        return;
    }
    deleteTree( node->Left );
    deleteTree( node->Right );
    delete[] node;
}

template <typename T>
CNode<T>* CTree<T>::GetRoot( )
{
    return root;
}

template <typename T>
CNode<T>* CTree<T>::Find( T Key )
{
    CNode<T>* q = root;
    if( q == nullptr ){
        return nullptr;
    }

    while( q != nullptr ){
        if( q->Data == Key ){
            return q;
        }
        if( q->Data > Key ){
            q = q->Left;
        }
        else{
            q = q->Right;
        }
    }
}

template <typename T>
CNode<T>* CTree<T>::FindMin( )
{
    assert( root != nullptr );
    CNode<T>* q = root;

    while( q->Left != nullptr ){
        q = q->Left;
    }
}

template <typename T>
CNode<T>* CTree<T>::FindMax( )
{
    assert( root != nullptr );
    CNode<T>* q = root;

    while( q->Right != nullptr ){
        q = q->Right;
    }
}

template <typename T>
void CTree<T>::AddNode( T Data )
{
    CNode<T>* q = root;
    CNode<T>* parent = q;

    if( q == nullptr ){
        root = new CNode<T>( Data );
        return;
    }

    while( q != nullptr ){
        parent = q;
        if( Data > q->Data ){
            q = q->Right;
        }
        else{
            q = q->Left;
        }
    }

    if( q == nullptr ){
        q = new CNode<T>( Data );
        if( q->Data > parent->Data ){
            parent->Right = q;
        }
        else{
            parent->Left = q;
        }
    }
    return;
}

template <typename T>
void CTree<T>::TraverseBFS( )
{
    std::queue< CNode<T>* > q;
    q.push( root );

    while( !q.empty( ) ){
        CNode<T>* node = q.front( );
        q.pop( );
        std::cout << node->Data << ' ';
        if( node->Left != nullptr ){
            q.push( node->Left );
        }
        if( node->Right != nullptr ){
            q.push( node->Right );
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;

    CTree<int> tree;

    int data = 0;
    for( int i = 0; i < n; ++i ){
        std::cin >> data;
        tree.AddNode( data );
    }

    tree.TraverseBFS( );
    return 0;
}
