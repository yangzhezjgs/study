
typedef enum { RED, BLACK } color_t;

typedef struct node_t {
    struct node_t *parent;
    struct node_t *left;
    struct node_t *right;
    int key;
    color_t color;
} node_t;

typedef struct tree_t {
    node_t *root;
    node_t *nil;
} tree_t;

tree_t *
make_rbt(void)
{
    tree_t *tree;

    tree = malloc(sizeof(tree_t));
    tree->root = tree->nil;
    tree->nil->left = tree->nil->right = NULL;
    tree->nil->key = 0;
    tree->nil->color = BLACK;
    tree->nil->parent = tree->root;

    return tree;
}

/* 假设x->right != tree->nil */
void
left_rotate(tree_t *tree, node_t *x)
{
    node_t *y;

    y = x->right;
    x->right = y->left;
    if (y->left != tree->nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/* 假设x->left != tree->nil */
void
right_rotate(tree_t *tree, node_t *y)
{
    node_t *x;

    x = y->left;
    y->left = x->right;
    if (x->right != tree->nil)
        x->right->parent = y;

    x->parent = y->parent;
    if (x->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void
rb_insert_fixup(tree_t *tree, node_t *z)
{
    node_t *y;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color == BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (z == z->parent->right) {
                z = z->parent;
                left_rotate(tree, z);
            } else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (z == z->parent->left) {
                z = z->parent;
                right_rotate(tree, z);
            } else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->color = BLACK;
}




void
rb_insert(tree_t *tree, node_t *z)
{
    node_t *x;
    node_t *y;

    y = tree->nil;
    x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (x->key < z->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    rb_insert_fixup(tree, z);
}

void
rb_transplant(tree_t *tree, node_t *u, node_t *v)
{
    if (u->parent == tree->nil)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void
rb_delete_fixup(tree_t *tree, node_t *x)
{
    node_t *w;

    while (x == tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                right_rotate(tree, w);
                w = x->parent->right;
            } else {
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                left_rotate(tree, w);
                w = x->parent->left;
            } else {
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}
                

}

node_t *
tree_minimum(tree_t *tree, node_t *x)
{
    while (x->left != tree->nil)
        x = x->left;

    return x;
}

void
rb_delete(tree_t *tree, node_t *z)
{
    node_t *x;
    node_t *y;
    color_t y_original_color;

    y = z;
    y_original_color = z->color;
    if (z->left == tree->nil) {
        x = z->right;
        rb_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rb_transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
        rb_transplant(tree, z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        rb_delete_fixup(tree, x);
}

