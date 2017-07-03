#include <iostream>
#include <assert.h>
#include <queue>

struct CNode
{
    int Data;
    unsigned int Height;//1 для заполненного 0 для нет

    CNode* Left;
    CNode* Right;

    CNode( ) : Data( 0 ), Left( nullptr ), Right( nullptr ), Height( 0 ) {}
    CNode( int Data ) : Data( Data ), Left( nullptr ), Right( nullptr ), Height( 1 ) {}
};

class CTree
{
public:
    CTree( ) : root( nullptr ) {}
    ~CTree( );

    //add node
    CNode* AddNode( CNode*& node, int Data, int& position );
    //remove node from tree
    CNode* Delete( CNode*& node, int value );
    //

    //basic binary tree methods
    CNode*& GetRoot( );
    CNode* FindMin( CNode* node );
    CNode* FindMax( CNode* node );
    CNode* Find( int Key );

    //methods for Balancing tree
    unsigned int Height( CNode* node );
    int BFactor( CNode* node );
    void FixHeight( CNode* node );
    CNode* RotateLeft( CNode* a );
    CNode* RotateRight( CNode* a );
    //

    void TraverseBFS( );
    void inorder( CNode *node, int value, int& position, bool& found );
    void display(CNode* ptr, int level);
private:
    CNode* root;

    void deleteTree( CNode* node );//called by destructor
    CNode* balance( CNode* a );
};

//deleting tree
//-------------------------------------------------
CTree::~CTree( )
{
    deleteTree( root );
    root = nullptr;
}

void CTree::deleteTree( CNode* node )
{
    if( node != nullptr ){
        deleteTree( node->Left );
        deleteTree( node->Right );

        delete[] node;
    }
}
//-------------------------------------------------

//methods for balancing tree
//-------------------------------------------------
unsigned int CTree::Height( CNode* node )//возвращает высоту заполненного поддерева
{
    return ( node != nullptr ) ? node->Height : 0;
}

//баланс для данного узла
int CTree::BFactor( CNode* node )
{
    return Height( node->Right ) - Height( node->Left );
}

void CTree::FixHeight( CNode* node )//высота максимального поддерева для данного узла + 1
{
    unsigned int hleft = Height( node->Left );
    unsigned int hright = Height( node->Right );
    node->Height = ( hleft > hright ? hleft : hright ) + 1;
}

CNode* CTree::RotateLeft( CNode* a )
{
    CNode* b = a->Right;
    a->Right = b->Left;
    b->Left = a;

    FixHeight( a );
    FixHeight( b );

    return b;
}

CNode* CTree::RotateRight( CNode* a )
{
    CNode* b = a->Left;
    a->Left = b->Right;
    b->Right = a;

    FixHeight( a );
    FixHeight( b );

    return b;
}

CNode* CTree::balance( CNode* a )
{
    FixHeight( a );

    if( BFactor( a ) == 2 ){

        if( BFactor( a->Right ) < 0 ){
            a->Right = RotateRight( a->Right );
        }

        return RotateLeft( a );
    }

    if( BFactor( a ) == -2 ){
        if( BFactor( (a)->Left ) > 0 ){
            (a)->Left = RotateLeft( (a)->Left );
        }
        return RotateRight( a );
    }

    return a;
}

//basic binary tree methods
//-------------------------------------------------------
CNode*& CTree::GetRoot( )
{
    return root;
}

CNode* CTree::Find( int Key )
{
    CNode* q = root;
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

CNode* CTree::FindMin( CNode* node )
{
    assert( node != nullptr );
    CNode* q = node;

    while( q->Left != nullptr ){
        q = q->Left;
    }
    return q;
}

CNode* CTree::FindMax( CNode* node )
{
    assert( node != nullptr );
    CNode* q = node;

    while( q->Right != nullptr ){
        q = q->Right;
    }
    return q;
}
//---------------------------------------------------

//adding node
//---------------------------------------------------
CNode* CTree::AddNode( CNode*& node, int Data, int& position )
{
    if( node == nullptr ){
        node = new CNode( Data );
        return node;
    }
    else if( Data < node->Data  ){
        position += Height(node->Right) + 1;
        node->Left = AddNode( node->Left, Data, position );
    }
    else{
        node->Right = AddNode( node->Right, Data, position );
    }

    node = balance( node );
    return node;
}
//--------------------------------------------------

//Deleting node + Balance
//--------------------------------------------------
CNode* CTree::Delete( CNode*& node, int value )
{
    if( node == nullptr ){
        return nullptr;
    }
    if( value < node->Data ){
        return Delete( node->Left, value );
    }
    else if( value > node->Data ){
        return Delete( node->Right, value );
    }
    else{

        if( node->Left == 0 ){

            CNode* right = node->Right;
            delete node;
            node = right;

        }else if( node->Right == 0 ){

            CNode* left = node->Left;
            delete node;
            node = left;

        }
        else{
            CNode* temp = FindMin( node->Right );
            node->Data = temp->Data;
            node->Right = Delete( node->Right, temp->Data );
        }
    }
    if( node == nullptr ){
        return node;
    }
    return balance( node );
}
//----------------------------------------------------

int main()
{
    int n = 0;
    std::cin >> n;

    CTree tree;

    int operation = 0;
    int height = 0;
    for( int i = 0; i < n; ++i ){
        std::cin >> operation;
        std::cin >> height;
        switch( operation ){
            case 1:{
                int position = 0;
                tree.AddNode( tree.GetRoot( ), height, position );
                // bool found = false;
                // tree.inorder( tree.GetRoot( ), height, position, found );
                std::cout<<  position << ' ';
                break;
            }
            case 2:
                tree.Delete( tree.GetRoot( ), height );
                break;
            default:
                break;
        }
        // tree.display( tree.GetRoot( ), 1 );
    }

    return 0;
}

void CTree::inorder( CNode *node, int value, int& position, bool& found )
{

    if (node == nullptr){
        return;
    }

    inorder (node->Right, value, position, found );
    if( node->Data != value && found == false ){
        ++position;
        inorder (node->Left,value, position, found);
    }
    else{
        found = true;
        return;
    }

}

void CTree::TraverseBFS( )
{
    std::queue< CNode* > q;
    q.push( root );

    while( !q.empty( ) ){
        CNode* node = q.front( );
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


void CTree::display(CNode* ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {

        display(ptr->Right, level + 1);

        // printf("\n");
        std::cout<<std::endl;

        if (ptr == root)

        std::cout<<"Root -> ";

        for (i = 0; i < level && ptr != root; i++)

            std::cout<<"        ";

        std::cout<<ptr->Data;

        display(ptr->Left, level + 1);

    }
}
// void CTree::DeleteNode( CNode*& node )
// {
//     if( node->Left == 0 ){
//         CNode* right = node->Right;
//         delete node;
//         node = right;
//     }else if( node->Right == 0 ){
//         CNode* left = node->Left;
//         delete node;
//         node = left;
//     }else{
//         CNode* minParent = node;
//         CNode* min = node->Right;
//         while( min->Left != 0 ){
//             minParent = min;
//             min = min->Left;
//         }
//         ( minParent->Left == min ? minParent->Left : minParent->Right ) = min->Right;
//         node->Data = min->Data;
//         delete min;
//         // return Balance( minParent->Left );
//     }
//     // return node;
//     return;
// }
