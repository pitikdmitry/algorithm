#include <iostream>
#include <assert.h>
#include <queue>

struct CNode
{
    int Data;
    unsigned int Height;//1 для заполненного 0 для нет
    CNode* Left;
    CNode* Right;
    CNode* Parent;
    CNode( );
    CNode( int Data );
};

CNode::CNode( int Data ) : Data( Data ), Left( nullptr ), Right( nullptr ), Parent( nullptr ), Height( 1 )
{ }

CNode::CNode( ) : Data( 0 ), Left( nullptr ), Right( nullptr ), Parent( nullptr ), Height( 0 )
{ }

unsigned int Height( CNode* node )//возвращает высоту заполненного поддерева
{
    return ( node != nullptr ) ? node->Height : 0;
}

int BFactor( CNode* node )//баланс для данного узла
{
    return Height( node->Right ) - Height( node->Left );
}

void FixHeight( CNode* node )//высота максимального поддерева для данного узла
{
    unsigned int hleft = Height( node->Left );
    unsigned int hright = Height( node->Right );
    node->Height = ( hleft > hright ? hleft : hright ) + 1;
}

CNode* RotateLeft( CNode* a )//возвращаем новую вершину
{
    CNode* b = (a)->Right;
    (a)->Right = b->Left;
    b->Left = (a);
    FixHeight( a );
    FixHeight( b );
    return b;
}

CNode* RotateRight( CNode* a )
{
    CNode* b = (a)->Left;
    (a)->Left = b->Right;
    b->Right = (a);
    FixHeight( a );
    FixHeight( b );
    return b;
}

class CTree
{
public:
    CTree( );
    CNode* Find( int Key );
    CNode* FindMin( );
    CNode* FindMax( );
    // CNode*& AddNode( CNode*& node, int Data );
    CNode* AddNode( CNode*& node, int Data );
    void TraverseBFS( );
    void DeleteTree( CNode* node );
    CNode*& GetRoot( );
    CNode* Balance( CNode* a );
    void inorder( CNode *node, int value, int& position, bool& found );
    void display(CNode* ptr, int level);
    // CNode* Delete( CNode*& node, int value );
    // CNode* DeleteNode( CNode*& node );
    CNode* findmin(CNode*& p);
    CNode* removemin(CNode*& p);
    CNode* remove(CNode*& p, int k);
private:
    CNode* root;
    int treeSize;
};

CTree::CTree( ) : root( nullptr ), treeSize( 0 )
{ }

CNode* CTree::Balance( CNode* a )
{

    FixHeight( a );
    if( BFactor( a ) > 1 ){
        if( BFactor( (a)->Right ) < 0 ){
            a->Right = RotateRight( (a)->Right );
        }
        (a) = RotateLeft( a );
    }

    if( BFactor( a ) < -1 ){
        if( BFactor( (a)->Left ) >= 0 ){
            (a)->Left = RotateLeft( (a)->Left );
        }
        (a) =  RotateRight( a );
    }

    return a;
  // return Balance( a->Parent );//noBalance
}


CNode*& CTree::GetRoot( )
{
    return root;
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

CNode* CTree::FindMin( )
{
    assert( root != nullptr );
    CNode* q = root;

    while( q->Left != nullptr ){
        q = q->Left;
    }
    return q;
}

CNode* CTree::FindMax( )
{
    assert( root != nullptr );
    CNode* q = root;

    while( q->Right != nullptr ){
        q = q->Right;
    }
    return q;
}

CNode* CTree::AddNode( CNode*& node, int Data )
{
    if( node == nullptr ){
        node = new CNode( Data );
        ++treeSize;
        return (node);
    }
    // CNode* tmp = (*node);

    if( Data < (node)->Data  ){
        (node)->Left = AddNode( (node)->Left, Data );
        node = Balance( node );
    }
    else{
        (node)->Right = AddNode( (node)->Right, Data );
        node = Balance( node );
    }

    return node;
}

CNode* CTree::findmin(CNode*& p) // поиск узла с минимальным ключом в дереве p
{
	return p->Left?findmin(p->Left):p;
}

CNode* CTree::removemin(CNode*& p) // удаление узла с минимальным ключом из дерева p
{
	if( p->Left==0 )
		return p->Right;
	p->Left = removemin(p->Left);
	return Balance(p);
}

CNode* CTree::remove(CNode*& p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->Data )
		p->Left = remove(p->Left,k);
	else if( k > p->Data )
		p->Right = remove(p->Right,k);
	else //  k == p->key
	{
		CNode* q = p->Left;
		CNode* r = p->Right;
		delete p;
		if( !r ) return q;
		CNode* min = findmin(r);
		min->Right = removemin(r);
		min->Left = q;
		return Balance(min);
	}
	return Balance(p);
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


void CTree::DeleteTree( CNode* node )
{
    if( node == nullptr ){
        return;
    }
    DeleteTree( node->Left );
    DeleteTree( node->Right );
    delete[] node;
}

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
                tree.AddNode( tree.GetRoot( ), height );
                int position = 0;
                bool found = false;
                // tree.inorder( tree.GetRoot( ), height, position, found );
                // std::cout<<  position << ' ';
                break;
            }
            case 2:
                tree.remove(  tree.GetRoot( ), height );
                // tree.Delete( tree.GetRoot( ), height );
                break;
            default:
                break;
        }
    }
    // // tree.Delete( tree.GetRoot( ), 3 );
    //
    // // tree.TraverseBFS( );
    // // tree.inorder( tree.GetRoot( ));
    tree.display( tree.GetRoot( ), 1);

    tree.DeleteTree( tree.GetRoot( ) );
    return 0;
}
