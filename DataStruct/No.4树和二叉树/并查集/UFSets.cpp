#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int parent; // 双亲结点的下标
    int rank; // 树的高度（秩）
} Set;

// 初始化并查集
void MakeSet(Set* S, int n)
{
    for (int i = 0; i < n; i++) {
        S[i].parent = -1; // 初始时每个元素都是一个单独的集合，其双亲结点为-1
        S[i].rank = 0; // 初始时每个元素的树高为0
    }
}

// 查找元素所在的集合的根结点
int Find(Set* S, int x)
{
    if (S[x].parent == -1) { // 如果双亲结点为-1，说明该元素是一个单独的集合，其本身就是根结点
        return x;
    }
    else {
        // 路径压缩，将查找路径上的所有结点的双亲结点都设置为根结点
        S[x].parent = Find(S, S[x].parent);
        return S[x].parent;
    }
}

/*实现路径压缩的方法是在查找元素所在的集合的根结点时，
将查找路径上的所有结点的双亲结点都设置为根结点。
具体来说，我们可以在查找根结点的过程中，将每个结点的双亲结点都设置为根结点，
这样就可以将查找路径上的所有结点都直接连接到根结点上，从而形成一棵更加扁平的树。
这样做的好处是，下一次查找同一个集合的根结点时，
就可以直接找到根结点，而不需要再遍历整个查找路径，从而加速了查找操作。*/

// 查找元素所在的集合的根结点
int Find_non_recursion(Set* S, int x)
{
    int root = x;
    while (S[root].parent != -1) { // 如果双亲结点不为-1，说明该结点不是根结点
        root = S[root].parent; // 继续向上查找双亲结点
    }
    // 路径压缩，将查找路径上的所有结点的双亲结点都设置为根结点
    while (x != root) {
        int parent = S[x].parent; //指向x的父节点
        S[x].parent = root; //x的父节点直接指向根节点
        x = parent;
    }
    return root;
}
// 合并两个集合
void Union(Set* S, int x, int y)
{
    int root1 = Find(S, x); // 查找x所在的集合的根结点
    int root2 = Find(S, y); // 查找y所在的集合的根结点
    if (root1 != root2) { // 如果两个元素不在同一个集合中
        if (S[root1].rank > S[root2].rank) { // 将rank较小的集合合并到rank较大的集合中
            S[root2].parent = root1;
        }
        else if (S[root1].rank < S[root2].rank) {
            S[root1].parent = root2;
        }
        else {
            S[root2].parent = root1;
            S[root1].rank++; // 如果两个集合的rank相等，将其中一个集合的rank加1
        }
    }
}
/*需要注意的是，rank并不是树的深度，而是树的高度（秩），
即从根结点到最远叶子结点的距离。在合并两个集合时，我们需要比较它们的rank大小，而不是树的深度大小。*/

/*初始化并查集：O(n)，其中n为元素个数，需要遍历所有元素进行初始化。

  查找元素所在的集合的根结点：O(log n)，其中n为元素个数，最坏情况下需要遍历整个查找路径，
  查找路径的长度为树的高度，树的高度最坏情况下为log n。

  合并两个集合：O(log n)，其中n为元素个数，需要先查找两个元素所在的集合的根结点，
  然后将rank较小的集合合并到rank较大的集合中，合并操作的时间复杂度为O(1)，
  但是需要保证合并后的树的高度不会过高，因此需要进行路径压缩和rank优化，这两个操作的时间复杂度均为O(log n)。*/

int main()
{
    Set S[MAX_SIZE];
    int n = 10; // 元素个数
    MakeSet(S, n); // 初始化并查集
    Union(S, 0, 1); // 合并元素0和元素1所在的集合
    Union(S, 2, 3); // 合并元素2和元素3所在的集合
    Union(S, 4, 5); // 合并元素4和元素5所在的集合
    Union(S, 6, 7); // 合并元素6和元素7所在的集合
    Union(S, 0, 2); // 合并元素0所在的集合和元素2所在的集合
    Union(S, 4, 6); // 合并元素4所在的集合和元素6所在的集合
    Union(S, 0, 4); // 合并元素0所在的集合和元素4所在的集合
    for (int i = 0; i < n; i++) {
        printf("%d ", Find(S, i)); // 输出每个元素所在的集合的根结点
    }
    printf("\n");
    return 0;
}