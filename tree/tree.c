#include "tree.h"
#include "deque.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void make_empty(BSTree *t)
{
    if (t) {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }
}

//printing tree in ascii

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
    asciinode * left, *right;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right   
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];

    Color color;
};


#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left and right nodes
int gap = 3;

//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;

static int MIN(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

static int MAX(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

asciinode *build_ascii_tree_recursive(BSTree *t)
{
    asciinode *node;

    if (t == NULL) return NULL;

    node = malloc(sizeof(asciinode));
    node->left = build_ascii_tree_recursive(t->left);
    node->right = build_ascii_tree_recursive(t->right);

    if (node->left != NULL) {
        node->left->parent_dir = -1;
    }

    if (node->right != NULL) {
        node->right->parent_dir = 1;
    }

    node->color = t->color;
    sprintf(node->label, "%d", t->element);
    node->lablen = strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
asciinode *build_ascii_tree(BSTree *t)
{
    asciinode *node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
    if (node == NULL) return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and 
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL) {
        node->edge_length = 0;
    } else {
        if (node->left != NULL) {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        } else {
            hmin = 0;
        }
        if (node->right != NULL) {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2 
        if (((node->left != NULL && node->left->height == 1) ||
            (node->right != NULL && node->right->height == 1)) && delta>4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->left != NULL) {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL) {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level)
{
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;

#ifdef _WIN32
        HANDLE hd = NULL;
        if (node->color == Red) {
            hd = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_INTENSITY);
        } else if (node->color == Black) {
            //
        }
        printf("%s", node->label);
        SetConsoleTextAttribute(hd, FOREGROUND_RED |
                                FOREGROUND_GREEN |
                                FOREGROUND_BLUE);

#else
        if (node->color == Red) {
            printf("\033[31m%s\033[0m", node->label);
        } else {
            printf("%s", node->label);
        }
#endif

        print_next += node->lablen;
    } else if (node->edge_length >= level) {
        if (node->left != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
void print_ascii_tree(BSTree *t)
{
    asciinode *proot;
    int xmin, i;
    if (t == NULL) return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

int height(BSTree *t)
{
    if (!t)
        return 0;

    return MAX(height(t->left), height(t->right)) + 1;
}

BSTree *getNode(int value)
{
    BSTree *new_node = (BSTree *)malloc(sizeof(BSTree));

    if (new_node) {
        new_node->element = value;
        new_node->height = 1;
        new_node->color = None;
        new_node->left = new_node->right = new_node->parent = NULL;
    }

    return new_node;
}

bool check_sorted(BSTree *t)
{
    bool stat = true;

    if (t) {
        stat &= check_sorted(t->left);
        stat &= check_sorted(t->right);
    }

    return stat;
}

bool check_balanced(BSTree *t)
{
    bool stat = true;
    int lh, rh;
    int diff;

    if (t) {
        lh = height(t->left);
        rh = height(t->right);
        diff = abs(lh - rh);
        if (diff > 1) {
            stat = false;
        } else {
            stat &= check_balanced(t->left);
            stat &= check_balanced(t->right);
        }
    }

    return stat;
}

BSTree *grandparent(BSTree *t)
{
    if (!t)
        return NULL;
    if (!t->parent)
        return NULL;
    return t->parent->parent;
}

BSTree *uncle(BSTree *t)
{
    if (!t)
        return NULL;
    if (!t->parent)
        return NULL;
    if (!t->parent->parent)
        return NULL;
    return (t->parent == t->parent->parent->left ? t->parent->parent->right : t->parent->parent->left);
}

bool check_rb_black_num(BSTree *t)
{
    int lnum, rnum;

    if (!t)
        return true;

    lnum = get_bnode_num(t->left);
    rnum = get_bnode_num(t->right);
    if (lnum != rnum)
        return false;

    return check_rb_black_num(t->left) & check_rb_black_num(t->right);
}

int get_bnode_num(BSTree *t)
{
    int num = 0;
    int lnum, rnum;

    if (!t)
        return 0;

    if (t->color == Black)
        ++num;

    lnum = get_bnode_num(t->left);
    rnum = get_bnode_num(t->right);
    num += (lnum > rnum ? lnum : rnum);
    return num;
}

bool check_rb_red(BSTree *t)
{
    BSTree *lnode, *rnode;

    if (!t)
        return true;
    if (t->color != Red && t->color != Black)
        return false;

    lnode = t->left;
    rnode = t->right;

    if (t->color == Red) {
        if (lnode && lnode->color == Red)
            return false;
        if (rnode && rnode->color == Red)
            return false;
    }

    return check_rb_red(lnode) & check_rb_red(rnode);
}

bool check_rb_tree(BSTree *t)
{
    if (!t)
        return true;
    if (t->color != Black)
        return false;
    return check_rb_red(t) & check_rb_black_num(t);
}

void preorder_travel_recur(BSTree *t, UserFunc func, void *udata)
{
    if (!t)
        return;

    func(t, udata);
    preorder_travel_recur(t->left, func, udata);
    preorder_travel_recur(t->right, func, udata);
}

void inorder_travel_recur(BSTree *t, UserFunc func, void *udata)
{
    if (!t)
        return;

    inorder_travel_recur(t->left, func, udata);
    func(t, udata);
    inorder_travel_recur(t->right, func, udata);
}

void postorder_travel_recur(BSTree *t, UserFunc func, void *udata)
{
    if (!t)
        return;

    postorder_travel_recur(t->left, func, udata);
    postorder_travel_recur(t->right, func, udata);
    func(t, udata);
}

void preorder_travel_stack(BSTree *t, UserFunc func, void *udata)
{
    Deque *dq = NULL;
    BSTree *cur_node;

    if (!t)
        return;
    if (!(dq = new_deque()))
        return;

    push_back(dq, t, BSTree *);
    while (!is_empty(dq)) {
        cur_node = back(dq, BSTree *);
        func(cur_node, udata);
        pop_back(dq);
        if (cur_node->right)
            push_back(dq, cur_node->right, BSTree *);
        if (cur_node->left)
            push_back(dq, cur_node->left, BSTree *);
    }

    delete_deque(dq);
}

void inorder_travel_stack(BSTree *t, UserFunc func, void *udata)
{
    Deque *dq = NULL;
    BSTree *cur_node = NULL;

    if (!t)
        return;
    if (!(dq = new_deque()))
        return;

    cur_node = t;

    while (!is_empty(dq) || cur_node) {
        if (cur_node) {
            push_back(dq, cur_node, BSTree *);
            cur_node = cur_node->left;
        } else {
            cur_node = back(dq, BSTree *);
            func(cur_node, udata);
            pop_back(dq);
            cur_node = cur_node->right;
        }
    }

    delete_deque(dq);
}

void postorder_travel_stack(BSTree *t, UserFunc func, void *udata)
{
    Deque *dq = NULL;
    BSTree *cur_node = NULL;
    BSTree *pre_node = NULL;
    BSTree *p = t;

    if (!t)
        return;
    if (!(dq = new_deque()))
        return;

    while (!is_empty(dq) || p) {
        if (p) {
            push_back(dq, p, BSTree *);
            p = p->left;
        } else {
            cur_node = back(dq, BSTree *);
            if (cur_node->right && pre_node != cur_node->right) {
                p = cur_node->right;
            } else {
                func(cur_node, udata);
                pop_back(dq);
                pre_node = cur_node;
            }
        }
    }

    delete_deque(dq);
}

void levelorder_trabel(BSTree *t, UserFunc func, void *udata)
{
    Deque *dq = NULL;
    BSTree *cur_node = NULL;

    if (!t)
        return;
    if (!(dq = new_deque()))
        return;

    push_back(dq, t, BSTree *);

    while (!is_empty(dq)) {
        cur_node = front(dq, BSTree *);
        func(cur_node, udata);
        if (cur_node->left)
            push_back(dq, cur_node->left, BSTree *);
        if (cur_node->right)
            push_back(dq, cur_node->right, BSTree *);
        pop_front(dq);
    }

    delete_deque(dq);
}
