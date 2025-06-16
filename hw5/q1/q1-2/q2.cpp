/* probID: W9-A2-Insertion */
#include <iostream>
using namespace std;
void BST_insert_after(node *r, int pos, node *nde)
{
    if (pos < r->l_sz)
    { // put to left
        BST_insert_after(r->lc, pos, nde);
    }
    else if (pos > r->l_sz + 1)
    {
        BST_insert_after(r->rc, pos, nde);
    }
    else
    {
        if (r->rc->pri >= nde->pri) // r.right > nde
        {
            // set r.right to nde.right and update parent
            nde->rc = r->rc;
            r->rc->p = nde;

            // update size
            nde->l_sz = 0;
            nde->r_sz = r->r_sz + 1;
            r->r_sz += 1;
        }
        else // r.right < nde
        {
            // set r.right to nde.left and update parent
            nde->lc = r->lc;
            r->lc->p = nde;

            // update size
            nde->r_sz = 0;
            nde->l_sz = r->r_sz + 1;
            r->r_sz += 1;
        }

        r->rc = nde;
        nde->p = r;
    }
}

void BST_insert_before(node *r, int pos, node *nde)
{
    if (pos < r->l_sz)
    { // put to left
        BST_insert_before(r->lc, pos, nde);
    }
    else if (pos > r->l_sz + 1)
    {
        BST_insert_before(r->rc, pos, nde);
    }
    else
    {
        if (r->lc->pri >= nde->pri) // r.left > nde
        {
            // set r.left to nde.right and update parent
            nde->rc = r->lc;
            r->lc->p = nde;

            // update size
            nde->l_sz = 0;
            nde->r_sz = r->l_sz + 1;
        }
        else // r.left < nde
        {
            // set r.left to nde.left and update parent
            nde->lc = r->lc;
            r->lc->p = nde;

            // update size
            nde->r_sz = 0;
            nde->l_sz = r->l_sz + 1;
        }

        r->rc = nde;
        nde->p = r;
        r->l_sz += 1;
    }
}
