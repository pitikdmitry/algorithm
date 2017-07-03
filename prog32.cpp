#include <iostream>
#include <assert.h>
#include <queue>
using namespace std;

//Node
//-----------------------------------------------------
template <typename T>
struct CNode
{
    T Data;
    int Priority;
    CNode<T>* Left;
    CNode<T>* Right;
    CNode( ) : Data( 0 ), Priority( 0 ), Left( nullptr ), Right( nullptr ) {}
    CNode( T Data, int priority = 0 ) : Data( Data ), Priority( priority ), Left( nullptr ), Right( nullptr ) {}
};
//-----------------------------------------------------
//end node

//BinaryTree
//------------------------------------------------------
template <typename T>
class CTree
{
public:
    CTree( ) : root( nullptr ) {}
    ~CTree( );
    void AddNode( T Data );
    CNode<T>* GetRoot( );
    void TraverseBFS( );

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
void CTree<T>::AddNode( T data )
{
    CNode<T>* q = root;
    CNode<T>* parent = q;

    if( q == nullptr ){
        root = new CNode<T>( data );
        return;
    }

    while( q != nullptr ){
        parent = q;
        if( data > q->Data ){
            q = q->Right;
        }
        else{
            q = q->Left;
        }
    }

    if( q == nullptr ){
        q = new CNode<T>( data );
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
//End BinaryTree
//-------------------------------------------------------

//Treap
//-------------------------------------------------------
template <typename T>
class CTreap
{
public:
    CTreap( ) : root( nullptr ) {}
    ~CTreap( );
    void AddNode( T Data, int priotity );
    void Split( CNode<T>* node, int value, CNode<T>*& left, CNode<T>*& right );
    CNode<T>* GetRoot( );
    void TraverseBFS( );

private:
    CNode<T>* root;
    void deleteTree( CNode<T>* node );
};

template <typename T>
CTreap<T>::~CTreap( )
{
    deleteTree( root );
}

template <typename T>
void CTreap<T>::deleteTree( CNode<T>* node )
{
    if( node == nullptr ){
        return;
    }
    deleteTree( node->Left );
    deleteTree( node->Right );
    delete[] node;
}

template <typename T>
CNode<T>* CTreap<T>::GetRoot( )
{
    return root;
}

template <typename T>
void CTreap<T>::Split( CNode<T>* node, int data, CNode<T>*& left, CNode<T>*& right )
{
    if( node == nullptr ){
        left = nullptr;
        right = nullptr;
    }
    else if( node->Data <= data ){
        Split( node->Right, data, node->Right, right );
        left = node;
    }
    else{
        Split( node->Left, data, left, node->Left );
        right = node;
    }
}

template <typename T>
void CTreap<T>::AddNode( T data, int priority )
{
    CNode<T>* q = root;
    CNode<T>* parent = q;
    CNode<T>* newNode = new CNode<T>( data, priority );

    if( q == nullptr ){
        root = newNode;
        return;
    }

    while( q != nullptr && priority <= q->Priority ){
        parent = q;
        if( data > q->Data ){
            q = q->Right;
        }
        else{
            q = q->Left;
        }
    }

    Split( q, data, parent->Left, parent->Right );

    q = newNode;

    return;
}

template <typename T>
void CTreap<T>::TraverseBFS( )
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
//End Treap
//--------------------------------------------------------




int main()
{
    int n = 0;
    std::cin >> n;

    CTree<int> binaryTree;
    CTreap<int> treeHeap;

    int data = 0;
    int priority = 0;

    for( int i = 0; i < n; ++i ){
        std::cin >> data;
        std::cin >> priority;

        treeHeap.AddNode( data, priority );
        binaryTree.AddNode( data );
    }

    std::cout<<"binary: " << std::endl;
    binaryTree.TraverseBFS();
    std::cout<<std::endl;

    std::cout<<"treeHeap: " << std::endl;
    treeHeap.TraverseBFS();
    std::cout<<std::endl;

    return 0;
}
