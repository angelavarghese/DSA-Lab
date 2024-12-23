#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int ipAdd;
    int dataPacket;
    struct node *left;
    struct node *right;
    struct node *parent;
} * NODE;

typedef struct splay_tree
{
    NODE root;
} * SPLAY_TREE;

NODE new_node(int ipAdd)
{
    NODE n = malloc(sizeof(struct node));
    if (n == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    n->ipAdd = ipAdd;
    n->dataPacket = 0;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

SPLAY_TREE new_splay_tree()
{
    SPLAY_TREE t = malloc(sizeof(struct splay_tree));
    if (t == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

NODE maximum(NODE x)
{
    while (x->right != NULL)
        x = x->right;
    return x;
}

void left_rotate(SPLAY_TREE t, NODE x)
{
    NODE y = x->right;
    if (!y)
        return;

    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        t->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(SPLAY_TREE t, NODE x)
{
    NODE y = x->left;
    if (!y)
        return;

    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        t->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void splay(SPLAY_TREE t, NODE n)
{
    while (n->parent != NULL)
    {
        if (n->parent == t->root)
        {
            if (n == n->parent->left)
            {
                right_rotate(t, n->parent);
            }
            else
            {
                left_rotate(t, n->parent);
            }
        }
        else
        {
            NODE p = n->parent;
            NODE g = p->parent;
            if (n == p->left && p == g->left)
            {
                right_rotate(t, g);
                right_rotate(t, p);
            }
            else if (n == p->right && p == g->right)
            {
                left_rotate(t, g);
                left_rotate(t, p);
            }
            else if (n == p->right && p == g->left)
            {
                left_rotate(t, p);
                right_rotate(t, g);
            }
            else if (n == p->left && p == g->right)
            {
                right_rotate(t, p);
                left_rotate(t, g);
            }
        }
    }
}

void insert(SPLAY_TREE t, NODE n)
{
    NODE y = NULL;
    NODE temp = t->root;
    while (temp != NULL)
    {
        y = temp;
        if (n->ipAdd < temp->ipAdd)
            temp = temp->left;
        else
            temp = temp->right;
    }
    n->parent = y;
    if (y == NULL)
        t->root = n;
    else if (n->ipAdd < y->ipAdd)
        y->left = n;
    else
        y->right = n;
    splay(t, n);
}

NODE search(SPLAY_TREE t, NODE n, int x)
{
    if (n == NULL || x == n->ipAdd)
    {
        if (n)
            splay(t, n);
        return n;
    }
    if (x < n->ipAdd)
        return search(t, n->left, x);
    else
        return search(t, n->right, x);
}

void inorder(NODE n, const char *cmn)
{
    if (n != NULL)
    {
        inorder(n->left, cmn);
        printf("%s%d -> %d\n", cmn, n->ipAdd, n->dataPacket);
        inorder(n->right, cmn);
    }
}

int main()
{
    const char *cmn = "192.168.3.";
    SPLAY_TREE t = new_splay_tree();

    NODE nodes[11];
    int ips[11] = {104, 112, 117, 124, 121, 108, 109, 111, 122, 125, 129};

    for (int i = 0; i < 11; i++)
    {
        nodes[i] = new_node(ips[i]);
        insert(t, nodes[i]);
    }

    srand(time(NULL));
    for (int i = 0; i < 11; i++)
    {
        int data = rand() % 200;
        NODE temp = search(t, t->root, ips[i]);
        if (temp != NULL)
        {
            temp->dataPacket = data;
        }
    }

    printf("IP ADDRESS -> DATA PACKET\n");
    inorder(t->root, cmn);

    // Free memory
    for (int i = 0; i < 11; i++)
    {
        free(nodes[i]);
    }
    free(t);

    return 0;
}
