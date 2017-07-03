#include <algorithm>

class CAVLTree {
public:
    CAVLTree();
    ~CAVLTree();

    void Add( int key );
    void Remove( int key );
    bool Has( int key );

private:
    struct CAVLNode {
        int Key;
        int Depth;
        CAVLNode* Left;
        CAVLNode* Right;
        explicit CAVLNode( int key ) : Key( key ), Depth( 1 ), Left( 0 ), Right( 0 ) {}
    };
    CAVLNode* root;

    // Безопасное вычисление глубины поддерева.
    static int depth( CAVLNode* node ) { return node == 0 ? 0 : node->Depth; }
    void add( int key, CAVLNode*& node );
    void balance( CAVLNode*& node );
    void rotateLeft( CAVLNode*& node );
    void rotateRight( CAVLNode*& node );
    void fixDepth( CAVLNode*& node );
};

void CAVLTree::Add( int key )
{
    add( key, root );
}

// Рекурсивный метод добавления элемента в поддерево.
void CAVLTree::add( int key, CAVLNode*& node )
{
    if( node == 0 ) {
        node = new CAVLNode( key );
        return;
    }
    if( node->Key > key ) {
        add( key, node->Left );
    } else {
        // Больше или равные ключи добавляем вправо.
        add( key, node->Right );
    }
    balance( node );
}

// Восстановление балансировки при необходимости с помощью поворотов.
void CAVLTree::balance( CAVLNode*& node )
{
    if( depth( node->Left ) - depth( node->Right ) == 2 ) {
        if( depth( node->Left->Left ) - depth( node->Left->Right ) == -1 ) {
            rotateLeft( node->Left );
        }
        rotateRight( node );
    } else if( depth( node->Left ) - depth( node->Right ) == -2 ) {
        if( depth( node->Right->Left ) - depth( node->Right->Right ) == 1 ) {
            rotateRight( node->Right );
        }
        rotateLeft( node );
    }
    fixDepth( node );
}

// Левый малый поворот.
void CAVLTree::rotateLeft( CAVLNode*& node )
{
    CAVLNode* tmp = node->Right;
    node->Right = tmp->Left;
    tmp->Left = node;
    node = tmp;
    fixDepth( node->Left );
    fixDepth( node );
}

// Правый малый поворот.
void CAVLTree::rotateRight( CAVLNode*& node )
{
    CAVLNode* tmp = node->Left;
    node->Left = tmp->Right;
    tmp->Right = node;
    node = tmp;
    fixDepth( node->Right );
    fixDepth( node );
}

// Обновление поля Depth в узле node.
void CAVLTree::fixDepth( CAVLNode*& node )
{
    node->Depth = std::max( depth( node->Left ), depth( node->Right ) ) + 1;
}

int main()
{
    return 0;
}
