/* probID: W9-A1-Rotation */
// struct node
// {
//     char c;
//     int pri, l_sz, r_sz;
//     // pri, size of left child and right child
//     node *lc, *rc, *p;
//     // pointer to left child, right child, parent
// };
node *rotate_dir(node *r, bool dir)
{
    if (dir)
    { // right rotation
        node *leftNode = r->lc;
        r->lc = leftNode->rc;
        if (leftNode->rc)
            leftNode->rc->p = r;

        leftNode->p = r->p;
        if (r->p)
        {
            if (r->p->lc == r)
                r->p->lc = leftNode;
            else
                r->p->rc = leftNode;
        }

        leftNode->rc = r;
        r->p = leftNode;

        // update size
        r->l_sz = (r->lc) ? r->lc->l_sz + r->lc->r_sz + 1 : 0;
        leftNode->r_sz = r->l_sz + r->r_sz + 1;

        return leftNode;
    }
    else
    { // left rotation
        node *rightNode = r->rc;
        r->rc = rightNode->lc;
        if (rightNode->lc)
            rightNode->lc->p = r;

        rightNode->p = r->p;
        if (r->p)
        {
            if (r->p->lc == r)
                r->p->lc = rightNode;
            else
                r->p->rc = rightNode;
        }

        rightNode->lc = r;
        r->p = rightNode;

        // update size

        return rightNode;
    }
}

/*
修改說明
右旋轉 (dir 為 true):
指標調整:
將 r->lc 設為 leftNode->rc。
如果 leftNode->rc 存在，將其父指標設為 r。
更新 leftNode->p 為 r->p。
如果 r 有父節點，根據 r 是左子節點還是右子節點，將父節點的相應子指標指向 leftNode。
將 leftNode->rc 設為 r，並更新 r->p 為 leftNode。
大小更新:
更新 r->l_sz 為左子樹的大小。
更新 leftNode->r_sz 為 r 的新左子樹和右子樹的大小加上 r 本身。
左旋轉 (dir 為 false):
指標調整:
將 r->rc 設為 rightNode->lc。
如果 rightNode->lc 存在，將其父指標設為 r。
更新 rightNode->p 為 r->p。
如果 r 有父節點，根據 r 是左子節點還是右子節點，將父節點的相應子指標指向 rightNode。
將 rightNode->lc 設為 r，並更新 r->p 為 rightNode。
大小更新:
更新 r->r_sz 為右子樹的大小。
更新 rightNode->l_sz 為 r 的新左子樹和右子樹的大小加上 r 本身。
其他注意事項
父節點檢查： 確保在更新父節點指向時，檢查 r->p 是否為 nullptr，避免空指標訪問。
大小更新： 根據實際情況，l_sz 和 r_sz 應該反映子樹的總大小（包括所有後代節點），而不僅僅是子節點的數量。在此實現中，假設 l_sz 和 r_sz 表示左子樹和右子樹的總節點數。
記憶體安全： 確保所有指標在旋轉後都被正確更新，避免指向錯誤的節點，這是防止運行時錯誤的關鍵。
*/