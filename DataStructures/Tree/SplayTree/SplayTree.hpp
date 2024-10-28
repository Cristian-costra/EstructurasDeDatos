#include <iostream>
#include "Node.hpp"

template <class T>
class SplayTree{
    public: 
        SplayTree();
        SplayTree(std::initializer_list<T> list);
        SplayTree(const SplayTree<T> &otherTree);
        const SplayTree<T> operator=(const SplayTree<T> &otherTree);
        ~SplayTree();

        void splay(T data);

        void insert(T data);
        int search(T data);
        void deleteN(T data);

        void preOrder();
        void inOrder();
        void postOrder();
        void inReverseOrder();

        void preOrder(Node<T>* root);
        void inOrder(Node<T>* root);
        void postOrder(Node<T>* root);
        void inReverseOrder(Node<T>* root);
    private: 
        Node<T>* root; 
        // Node<T>* lastAccess; // Posible optimización
};

template <class T>
SplayTree<T>::SplayTree(){
    root = nullptr;
}

template <class T>
SplayTree<T>::SplayTree(std::initializer_list<T> list){
    for(const auto &element:list){
        insert(element);
    }
}

template <class T>
void SplayTree<T>::splay(T data){
    if(root == nullptr){
        throw(std::runtime_error("El árbol está vacío"));
    } else if (root->getData() == data){
        return;
    }
    Node<T> *temp = root;
    bool cond = (data < root->getData()) ? (root->getLeft() != nullptr) : (root->getRight() != nullptr); // original >, cambie a < FAVOR DE CORREGIR
    while (cond){
        if(data < root -> getData()){
            temp = root;
            T rootLeftData = root->getLeft() ? root->getLeft()->getData() : data; // Modificación anti Segmentation Fault. FAVOR DE CORREGIR
            if(data < rootLeftData && root->getLeft()->getLeft() != nullptr){
                // rotación zig zig
                root = root->getLeft()->getLeft();
                temp->getLeft()->setLeft(root->getRight());
                root->setRight(temp);
            } else if(data > rootLeftData && root->getLeft()->getRight() != nullptr){
                // realiza el movimiento zig zag
                root = root->getLeft()->getRight();
                temp->getLeft()->setRight(root -> getLeft());
                root->setLeft(temp->getLeft());
                temp->setLeft(root->getRight());
                root->setRight(temp);
            } else{
                // zig y break
                root = root->getLeft() ? root->getLeft() : root;
                temp->setLeft(root->getRight());
                root->setRight(temp);
                break;
            }
        } else if (data > root->getData()){ // No necesito checar si es null porque en el cond ya garanticé que no.
            if(data > root->getRight()->getData() && root->getRight()->getRight() != nullptr){
                // zig zig 
                root= root->getRight()->getRight();
                temp->getRight()->setRight(root->getLeft());
                root->setLeft(temp);
            } else if(data < root->getRight()->getData() && root->getRight()->getLeft() != nullptr){
                // zig zag 
                root = root->getRight()->getLeft();
                temp -> getRight() -> setLeft(root -> getRight());
                root -> setRight(temp->getRight());
                temp -> setRight(root->getLeft());
                root -> setLeft(temp);
            } else{
                // zig y break
                root = root -> getRight();
                temp -> setRight(root -> getLeft());
                root -> setLeft(temp);
                break;
            }
        } else{
            break; // No debería ser necesario este break por la formulación del cond
        }
        cond = (data > root->getData()) ? (root -> getLeft() != nullptr) : (root -> getRight() != nullptr && root-> getData() != data);
    }
}

template <class T>
void SplayTree<T>::insert(T data){
    if(root == nullptr){
        root = new Node<T>(data);
        return;
    }

    splay(data);
    if(root -> getData() == data){
        return;
    }
    Node<T> *temp= root;
    root = new Node<T>(data);
    if(data < temp -> getData()){
        root -> setRight(temp);
        root -> setLeft(temp->getLeft());
    } else{
        root -> setLeft(temp);
        root -> setRight(temp->getRight());
    }
}

template <class T>
int SplayTree<T>::search(T data){
    splay(data);

    return (root->getData() == data) ? 1 : 0;
}

// template <class T>
// void SplayTree<T>::deleteN(T data){
//     if(root == nullptr){
//         throw(std::runtime_error("El árbol está vacío"));
//     }

//     if (search(data)){
//         Node<T> *subRootL = root->getLeft();
//         if(root->getLeft() != nullptr){
//             root = root -> getLeft();
//             if (temp->getRight() != nullptr){
//                 root -> setRight(temp -> getRight());
//             }
//         } else if (root->getRight() != nullptr){
//             root = root -> getRight();
//             if (temp -> getRight){
                
//             }
//         }
//         delete temp;
//     } else{
//         return;
//     }

// }


//MUY MAAAAAL
template <class T>
SplayTree<T>::~SplayTree(){
    if(root != nullptr){
        delete root;
    }
}

template <class T>
void SplayTree<T>::inOrder(){
    if(root != nullptr){
        inOrder(root);
    }
}

template <class T>
void SplayTree<T>::inOrder(Node<T>* root){
    if(root != nullptr){
        inOrder(root->getLeft());
        std::cout << root->getData() << "\n";
        inOrder(root->getRight());
    }
}

template <class T>
void SplayTree<T>::preOrder(){
    if(root != nullptr){
        preOrder(root);
    }
}

template <class T>
void SplayTree<T>::preOrder(Node<T>* root){
    if(root != nullptr){
        std::cout << root->getData() << "\n";
        preOrder(root->getLeft());
        preOrder(root->getRight());
    }
}

template <class T>
void SplayTree<T>::postOrder(){
    if(root != nullptr){
        postOrder(root);
    }
}

template <class T>
void SplayTree<T>::postOrder(Node<T>* root){
    if(root != nullptr){
        postOrder(root->getLeft());
        postOrder(root->getRight());
        std::cout << root->getData() << "\n";
    }
}

template <class T>
void SplayTree<T>::inReverseOrder(){
    if(root != nullptr){
        inReverseOrder(root);
    }
}

template <class T>
void SplayTree<T>::inReverseOrder(Node<T>* root){
    if(root != nullptr){
        inReverseOrder(root->getRight());
        std::cout << root->getData() << "\n";
        inReverseOrder(root->getLeft());
    }
}