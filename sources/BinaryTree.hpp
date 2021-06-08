#pragma once
#include <queue>
#include <string>
#include <memory>
#include <stack>
#include <iostream>

#define preorder 1
#define inorder 2
#define postorder 3
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        struct Node
        {

            T valy;
            Node *left;
            Node *right;
            Node *parent;
            Node(T v, Node *nodeL = nullptr, Node *nodeR = nullptr, Node *nodeP = nullptr) : valy(v), left(nodeL), right(nodeR), parent(nodeP) {}
        };

        Node *root;

    public:
          BinaryTree<T>() : root(nullptr){};
        ~BinaryTree<T>(){};

        BinaryTree &add_root(T valy)
        {
            //check if there is no root and create new one, otherwise replace the current 
            if(root == nullptr){
                    this->root = new Node(valy)
            }
              else{
                        root->valy = valy;
              }      
            return *this;
        }
        BinaryTree<T> &add_left(T parent, T left)
        {
            return *this;
        }
        BinaryTree<T> &add_right(T parent, T right)
        {
            Node *found = found_node(this->root, parent);
            if (found == nullptr) // if we didnt found
            {
                throw std::invalid_argument("No value found");
            }
            if (found->right == nullptr) //If he has no right son
            {
                found->right = new Node(right);
                found->right->parent = found; // Updating his parent
            }
            else // If he has a son
            {
                found->right->data = right;
            }
            return *this;
        }
        
           friend std::ostream &operator<<(std::ostream &os, const BinaryTree &trees)
        {
            return os;
        };
       

        class Iterator
        {
            Node *curr;
            int kind;
            std::stack<Node *> stack;

        public:
            // constrctor
            Iterator() : curr(nullptr){};
            Iterator(const int kind, Node *node=nullptr) : curr(node) ,kind(typekind){
                init_Stack(node);
                if (!stack.empty())
                {

                    curr = stack.top();
                    stack.pop();
                }
            }

            Node *get_current()
            {
                return curr;
            }

            void init_Stack(Node *node)
            {
                if (node == nullptr)
                        return;
                
              
                if (kind == preorder)
                {
                    init_Stack(node->right);
                    init_Stack(node->left);
                    stack.push(node);
                }
                else   if (kind == inorder)
                {

                    init_Stack(node->right);
                    stack.push(node);
                    init_Stack(node->left);
                }
                else 
                {
                    stack.push(node);
                    init_Stack(node->right);
                    init_Stack(node->left);
                }
            }
            
            Iterator &operator++()
            {
                if (stack.empty())
                    curr = nullptr;
                
                else{
                    curr = stack.top();
                    stack.pop(); }

                return *this;
            }
           
            Iterator operator++(int)
            {

                Iterator tmp = *this;
                if (stack.empty())
                {
                    curr = nullptr;
                }
                else
                {
                    curr = stack.top();
                    stack.pop();
                }
                return tmp;
            }

            T &operator*() const
            {
                return curr->data;
            }

            T *operator->() const
            {
                return &(curr->data);
            }
            bool operator==(const Iterator &other) const
            {
                return curr == other.curr;
            }

            bool operator!=(const Iterator &other) const
            {
                return !(*this == other);
            }
        };
    public:
        BinaryTree<T>() : root(nullptr)
        {
        };

        void copy_ctor(Node *nd, const Node *other_nd)
        {
            if (other_nd->left != nullptr)
            {
                nd->left = new Node(other_nd->left->data);
                copy_ctor(nd->left, other_nd->left);
            }
            if (other_nd->right != nullptr)
            {
                nd->right = new Node(other_nd->right->data);
                copy_ctor(nd->right, other_nd->right);
            }
        }

        BinaryTree<T> &operator=(const BinaryTree<T> &bt)
        {
            if (this == &bt)
            {
                return *this;
            }
            if (root != nullptr)
            {
                delete root;
            }
            if (bt.root != nullptr)
            {
                root = new Node{bt.root->data};
                copy_ctor(root, bt.root);
            }
            return *this;
        }

        BinaryTree<T>(const BinaryTree<T> &bt)
        { //copy ctor
            if (bt.root != nullptr)
            {
                this->root = new Node(bt.root->data);
                copy_ctor(root, bt.root);
            }
        }
        BinaryTree<T> &operator=(BinaryTree<T> &&bt) noexcept // move opertor
        {
            if (root)
            {
                delete root;
            }
            root = bt.root;
            bt.root = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree<T> &&bt) noexcept // move constructor
        {
            this->root = bt.root;
            bt.root = nullptr;
        }
        //-------------//

        ~BinaryTree<T>()
        {
            if (root)
            {
                for (auto it = (*this).begin_postorder(); it != (*this).end_postorder(); ++it)
                {
                    delete it.get_current();
                }
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree)
        {
            os << tree.root->data;
            return os;
        }
        BinaryTree<T> &add_root(T data)
        {
            if (root != nullptr) // There is already a root just need to update a value
            {
                root->data = data;
            }
            else // We will create a new one
            {
                this->root = new Node(data);
            }
            return *this;
        }

        Node *found_node(Node *node, T value)
        {
            if (node == nullptr) //Basic
            {
                return nullptr;
            }
            for (auto it = begin_inorder(); it != end_inorder(); ++it)
            {
                if (*it == value)
                {
                    return it.get_current();
                }
            }
            return nullptr;
        }

        BinaryTree<T> &add_left(T parent_val, T child_val)
        {
            Node *found = found_node(this->root, parent_val);
            if (found == nullptr) // if we didnt found
            {
                throw std::invalid_argument("No value found");
            }

            if (found->left == nullptr) //If he has no left son
            {
                found->left = new Node(child_val);
                found->left->parent = found; // Updating his parent
            }
            else // If he has a son
            {
                found->left->data = child_val;
            }
            return *this;
        }


        Iterator begin()
        {
            return Iterator{inorder,root};
        };
        Iterator end()
        {
            return Iterator{};
        };
        Iterator end_preorder()
        {

            return Iterator{};
        }
        Iterator begin_preorder()
        {
            return Iterator{preorder,root};
        }
        Iterator end_inorder()
        {

            return Iterator{};
        }
        Iterator begin_inorder()
        {
            return Iterator{inorder, root};
        }
        Iterator end_postorder()
        {
            return Iterator{};
        }
        Iterator begin_postorder()
        {
            return Iterator{ postorder, root};
        }
    };

//  class Preorder_iter
//         {
//         private:
//             Node *current;

//         public:
//             Preorder_iter(Node *ptr = nullptr) : current(ptr){};
//             Preorder_iter(): current(nullptr){}

//             T &operator*() const
//             {
//                 return current->valy;
//             }

//             T *operator->() const
//             {
//                 return &(current->valy);
//             }
//             Preorder_iter &operator++()
//             {
//                 return *this;
//             }
//             const Preorder_iter operator++(int)
//             {
//                 return *this;
//             }
//             bool operator==(const Preorder_iter &other) const
//             {
//                 return false;
//             }

//             bool operator!=(const Preorder_iter &other) const
//             {
//                 return false;
//             }
//         };
//          Preorder_iter end_preorder()
//         {
//             return Preorder_iter(nullptr);
//         }
//         Preorder_iter begin_preorder()
//         {
//             return Preorder_iter(root);
//         }
 

//         class Inorder_iter
//         {
//         private:
//             Node *current;

//         public:
//             Inorder_iter(Node *ptr = nullptr) : current(ptr){};
//             Inorder_iter(): current(nullptr){}


//             T &operator*() const
//             {
//                 return current->valy;
//             }

//             T *operator->() const
//             {
//                 return &(current->valy);
//             }
//             Inorder_iter &operator++()
//             {
//                 return *this;
//             }
//             const Inorder_iter operator++(int)
//             {
//                 return *this;
//             }
//             bool operator==(const Inorder_iter &other) const
//             {
//                 return false;
//             }

//             bool operator!=(const Inorder_iter &other) const
//             {
//                 return false;
//             }
//         };
//                Inorder_iter end_inorder()
//         {
//             return Inorder_iter(nullptr);
//         }
//         Inorder_iter begin_inorder()
//         {
//             return Inorder_iter(root);
//         }

 
//         class Postorder_iter
//         {
//         private:
//             Node *current;

//         public:
//             Postorder_iter(Node *ptr = nullptr) : current(ptr){};
//             Postorder_iter():current(nullptr){}


//             T &operator*() const
//             {
//                 return current->valy;
//             }

//             T *operator->() const
//             {
//                 return &(current->valy);
//             }
//             Postorder_iter &operator++()
//             {
//                 return *this;
//             }
//             const Postorder_iter operator++(int)
//             {
//                 return *this;
//             }
//             bool operator==(const Postorder_iter &other) const
//             {
//                 return false;
//             }

//             bool operator!=(const Postorder_iter &other) const
//             {
//                 return false;
//             }
//         };

//         Inorder_iter begin()
//         {
//             return begin_inorder();
//         };
//         Inorder_iter end()
//         {
//             return end_inorder();
//         };
    
//         Postorder_iter end_postorder()
//         {
//             return Postorder_iter(root);
//         }
//         Postorder_iter begin_postorder()
//         {
//             return Postorder_iter(nullptr);
//         }
//     };
}





