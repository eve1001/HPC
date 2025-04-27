// Parallel BFS, DFS

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class TreeNode
{
    public:
        TreeNode *left;
        TreeNode *right;
        int data;
        TreeNode(int x)
        {
            data = x; left = right = NULL;
        }
};

class Tree
{
    public:
        TreeNode *root;
        Tree(){root = NULL;}

        void insert(int x)
        {
            TreeNode *n = new TreeNode(x);
            if(root == NULL)    
                root = n;
            else
            {
                queue<TreeNode *> q;
                q.push(root);

                int flag = 0;

                while(!q.empty() && !flag)
                {
                    for(int i=0; i<q.size(); i++)
                    {
                        TreeNode *temp = q.front();
                        q.pop();
                        
                        if(temp->left == NULL)
                        {
                            temp->left = n;
                            flag = 1;
                        }
                        else 
                        {
                            q.push(temp->left);
                            if(temp->right == NULL)
                            {
                                temp->right = n;
                                flag = 1;
                            }
                            else
                                q.push(temp->right);
                        }
                    }
                }
            }
        }
        
        void bfs()
        {
            queue<TreeNode *> q;
            q.push(root);

            while(! q.empty())
            {
                int n = q.size();

                #pragma omp parallel for
                for(int i=0; i<n; i++)
                {
                    TreeNode *temp;

                    #pragma omp critical
                    {
                        temp = q.front();
                        q.pop();
                        cout<<temp->data<<" | ";
                    }
                    if(temp->left != NULL)
                        q.push(temp->left);
                    if(temp->right != NULL)
                        q.push(temp->right);    
                }
            }
            cout<<endl;
        }
        
        void dfs()
        {
            TreeNode *temp = root;
            stack<TreeNode *> s;
            s.push(root);
            while(! s.empty())
            {
                int n = s.size();

                #pragma omp parallel for
                for(int i=0; i<n; i++)
                {
                    #pragma omp critical
                    {
                        while(temp!=NULL)
                        {
                            temp = temp->left;
                            if(temp!=NULL)
                                s.push(temp);
                        }
                        temp = s.top();
                        s.pop();

                        cout<<temp->data<<" | ";

                        if(temp->right!=NULL)
                            s.push(temp->right);
                        temp=temp->right;
                    }
                }
            }
            cout<<endl;
        }
};

int main()
{
    Tree *t = new Tree();
    while(true)
    {
        int ch;
        cout<<"Enter 1-Insert | 2-BFS | 3-DFS | 0-Exit : ";
        cin>>ch;
        
        if(ch==1)
        {
            cout<<"Enter a number : ";
            cin>>ch;
            t->insert(ch);
        }
        else if(ch==2)
            t->bfs();
        else if(ch==3)
            t->dfs();
        else if(ch==0)
        {
            cout<<"Exited successfully."<<endl;
            break;
        }
        else
            cout<<"Invalid Input."<<endl;
    }

    return 0;
}


/*Of course! ??  
Let’s go **line by line** in **very simple words** so you fully understand:

---

```cpp
// Parallel BFS, DFS
```
- This is a comment. It tells us that the program is about **parallel** versions of **BFS** and **DFS** tree traversal.

---
```cpp
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
```
- We include:
  - `iostream` for `cin` and `cout`.
  - `stack` to use the **Stack** data structure (needed for DFS).
  - `queue` to use the **Queue** data structure (needed for BFS).
- `using namespace std;` avoids typing `std::` again and again.

---

### Class: TreeNode
```cpp
class TreeNode
{
    public:
        TreeNode *left;
        TreeNode *right;
        int data;
```
- A **TreeNode** represents a **single node** in a tree.
- It has:
  - `data` (value stored)
  - pointer to the `left` child
  - pointer to the `right` child

---
```cpp
TreeNode(int x)
{
    data = x; 
    left = right = NULL;
}
```
- **Constructor**: When you create a new node, it sets its `data` and both `left` and `right` to **NULL**.

---

### Class: Tree
```cpp
class Tree
{
    public:
        TreeNode *root;
```
- The **Tree** class represents the **whole tree**.
- It stores a pointer called `root` (top node).

---
```cpp
Tree(){root = NULL;}
```
- **Constructor**: When a new tree is created, `root` is initially **NULL** (empty tree).

---

### Insert function
```cpp
void insert(int x)
```
- Adds a new node with value `x` to the tree.

---
```cpp
TreeNode *n = new TreeNode(x);
```
- Create a new node with the given data.

---
```cpp
if(root == NULL)
    root = n;
```
- If the tree is empty, make the new node the `root`.

---
Else:
- If tree is **not empty**,
- Use a **queue** to do a **level-wise** insertion:
  - Check each node one by one.
  - If the `left` child is missing, insert there.
  - Else check `right` child.
  - If both children exist, **push** them into the queue and continue checking deeper.

---
```cpp
int flag = 0;
```
- A flag to indicate whether **insertion is done**.

---

### BFS (Breadth-First Search)
```cpp
void bfs()
```
- This function prints the tree using **BFS** (level by level).

---
```cpp
queue<TreeNode *> q;
q.push(root);
```
- Start from the **root** and add it to the queue.

---
```cpp
while(!q.empty())
```
- While there are nodes to process:
  
---
```cpp
int n = q.size();
```
- Count how many nodes are there at this level.

---
```cpp
#pragma omp parallel for
for(int i=0; i<n; i++)
```
- Use **OpenMP** to **parallelize** visiting nodes at the same level.

---
Inside the loop:
```cpp
#pragma omp critical
{
    temp = q.front();
    q.pop();
    cout<<temp->data<<" | ";
}
```
- In the `critical` section (one thread at a time):
  - Get a node.
  - Print its data.
  - Remove it from the queue.

---
```cpp
if(temp->left != NULL)
    q.push(temp->left);
if(temp->right != NULL)
    q.push(temp->right);
```
- If the node has a **left** child, add it to the queue.
- If the node has a **right** child, add it too.

---
Finally:
```cpp
cout<<endl;
```
- Move to the next line after BFS is complete.

---

### DFS (Depth-First Search)
```cpp
void dfs()
```
- This function prints the tree using **DFS** (go deep down before moving sideways).

---
```cpp
TreeNode *temp = root;
stack<TreeNode *> s;
s.push(root);
```
- Start with the `root` and push it into a **stack**.

---
```cpp
while(!s.empty())
```
- While there are nodes to process:

---
```cpp
int n = s.size();
```
- Get the current number of nodes in stack.

---
```cpp
#pragma omp parallel for
for(int i=0; i<n; i++)
```
- Use **OpenMP** to **parallelize** DFS processing.

---
Inside the loop:
```cpp
#pragma omp critical
{
    while(temp!=NULL)
    {
        temp = temp->left;
        if(temp!=NULL)
            s.push(temp);
    }
    temp = s.top();
    s.pop();
```
- Go **all the way left** (deep into left side).
- Push nodes onto the stack while moving left.

---
```cpp
cout<<temp->data<<" | ";
```
- Print the node's data.

---
```cpp
if(temp->right!=NULL)
    s.push(temp->right);
temp=temp->right;
```
- If the node has a **right** child, push it into the stack.
- Move `temp` to the right node.

---
Finally:
```cpp
cout<<endl;
```
- Move to next line after DFS is complete.

---

### Main function
```cpp
int main()
```
- Start of the program.

---
```cpp
Tree *t = new Tree();
```
- Create a new Tree object.

---
Infinite loop:
```cpp
while(true)
```
- Keep asking the user what they want to do:

---
```cpp
cout<<"Enter 1-Insert | 2-BFS | 3-DFS | 0-Exit : ";
cin>>ch;
```
- Show a menu:
  - 1 ? Insert a node
  - 2 ? Print BFS
  - 3 ? Print DFS
  - 0 ? Exit

---
Based on user input:
- If **1**, ask for a number and insert it into the tree.
- If **2**, call `bfs()`.
- If **3**, call `dfs()`.
- If **0**, print exit message and break the loop.
- Else print "Invalid Input."

---
```cpp
return 0;
```
- End the program properly.

---

# ?? In Short:
- This program lets you **build** a **binary tree**.
- You can **insert** numbers, then **display** the tree using:
  - **BFS** (level-by-level)
  - **DFS** (deep first)
- Both traversals are made **parallel** using **OpenMP** to make them faster.

---

Would you also like me to quickly show how **parallel BFS and DFS** actually run differently compared to normal ones? ?? (like a small example tree ??)  
It'll make it super easy for you to imagine! ??
*/
