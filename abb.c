#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

static bool elem_eq(abb_elem a, abb_elem b)
{
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b)
{
    return a < b;
}


//---- Invariant
static bool check_greater (abb_elem e, abb tree){
    bool greater = true;
    if(tree != NULL){
        greater = elem_less(tree->elem, e) && check_greater(e, tree->left)
                                           && check_greater(e, tree->right);
    }

    return greater;
}

static bool check_smaller (abb_elem e, abb tree){
    bool smaller = true;
    if(tree != NULL){
        smaller = elem_less(e, tree->elem) && check_smaller(e, tree->left) 
                                           && check_smaller(e, tree->right);
    }
    return smaller;
}

static bool invrep(abb tree){
    bool valid = true;
    if(tree == NULL){
        valid = true;
    } else {
        valid = check_greater(tree->elem, tree->left) &&
                check_smaller(tree->elem, tree->right) &&
                invrep(tree->left) && invrep(tree->right);
    }

    return valid;
}





abb abb_empty(void){
    abb tree;

    tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}


abb abb_add(abb tree, abb_elem e){
    assert(invrep(tree));

    if(tree == NULL){
        abb newTree;
        newTree = malloc(sizeof(struct _s_abb));
        newTree->elem = e;
        newTree->left = NULL;
        newTree->right = NULL;
        tree = newTree;

    } else {
        if(elem_less(e, tree->elem)){
            tree->left = abb_add(tree->left, e); 

        } else if (elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right, e);
        }
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree)
{
    bool is_empty = false;
    assert(invrep(tree));

    is_empty = (tree == NULL);

    return is_empty;
}

bool abb_exists(abb tree, abb_elem e)
{
    bool exists = false;
    assert(invrep(tree));

    exists = (tree!=NULL) && ((elem_eq(e, tree->elem)) || 
             (elem_less(tree->elem, e) && abb_exists(tree->right, e)) ||
             (elem_less(e, tree->elem) && abb_exists(tree->left, e)));

    return exists;
}

unsigned int abb_length(abb tree){
     
    unsigned int length = 0;
    assert(invrep(tree));
    
    if(tree != NULL){
        length += abb_length(tree->left);
        length++;
        length += abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e)
{
    assert(invrep(tree));

    if(tree==NULL){
        return NULL;
    }

    /*busco el elemento*/
    if (elem_less(e, tree->elem)){
        tree->left = abb_remove(tree->left, e);

    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_remove(tree->right, e);
    }


    else{
        //leafs
        if (tree->left == NULL && tree->right == NULL){
            free(tree);
            tree = NULL;
            return tree;
        }


        else if (tree->left == NULL || tree->right == NULL){
            abb temp;
            if (tree->left == NULL){
                temp = tree->right;

            } else {
                temp = tree->left;

            }
            free(tree);
            tree = NULL;
            return temp;
        }

            
        else{
            
            abb_elem sucesor = abb_min(tree->right);
            tree->elem = sucesor;
            tree->right = abb_remove(tree->right,sucesor);
        }

    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree)
{
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));

    root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree){
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    while(tree->right!=NULL){
        tree = tree->right;
    }

    max_e = tree->elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree){
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    while(tree->left!=NULL){
        tree = tree->left;
    }

    min_e = tree->elem;

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree){
    assert(invrep(tree));
    if (tree != NULL){
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree){
    assert(invrep(tree));
    if(tree!=NULL){
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}
