#pragma once

#include <assert.h>

class EmptyHeapException {};
class KeyGreaterException {};

template <class K, class V>
class SkewHeap {
    public:
        class Node {
            K _key;
            V _val;
            Node * _up;
            Node * _left;
            Node * _right;

            friend class SkewHeap;

            public:
            	Node(K key, V val) :
            		_key(key), _val(val), _up(nullptr), _left(nullptr), _right(nullptr) {}

                K getKey() const { return _key; }
                V getVal() const { return _val; }

                bool esHoja() const {
                	return _left == nullptr && _right == nullptr;
                }
        };

        SkewHeap() : _root(nullptr) {}

        ~SkewHeap() {
            if (_root != nullptr) {
                deleteHeap(_root);
                _root = nullptr;
            }
        }

        Node * getMin() const {
            if (_root == nullptr) throw EmptyHeapException();
        	return _root;
        }

        void deleteMin() {
            if (_root == nullptr) throw EmptyHeapException();
        	auto aux = _root;
            _root = aux->esHoja()?nullptr:join(aux->_left, aux->_right);
            if (_root != nullptr) _root->_up = nullptr;
        	delete aux;

        	assert(_root == nullptr || _root->_up == nullptr);
        }

        Node * insert(K key, V val) {
            Node * n = new Node(key, val);

        	_root = join(_root, n);
            _root->_up = nullptr;
            return n;
        }

        bool empty() const {
            return _root == nullptr;
        }

        const std::vector<Node *> inorder() const {
        	auto vector = std::vector<Node*>();
        	inorder(vector, _root);
        	return vector;
        }
        
        void decreaseKey(Node * node, K newKey) {
            if (_root == nullptr) throw EmptyHeapException();
            if (node == nullptr) throw std::invalid_argument("Can't decrease nullptr");
            if (newKey > node->_key) throw KeyGreaterException();

            auto up = node->_up;
            node->_key = newKey;

            if (node->_up != nullptr) {
                if (node == up->_left)
                    up->_left = nullptr;
                else
                    up->_right = nullptr;

                node->_up = nullptr;
                _root = join(_root, node);
                _root->_up = nullptr;
            }
        }
    private:
        Node * _root;

        static void deleteHeap(Node * node) {
            if (node->_left != nullptr) deleteHeap(node->_left);
            if (node->_right != nullptr) deleteHeap(node->_right);
            node->_left = node->_right = nullptr;
            node->_up = nullptr;
            
            delete node;
        }

        static Node * join(Node * n1, Node * n2) {
			if (n1 == nullptr) return n2;
			if (n2 == nullptr) return n1;

			if (n1->_key > n2->_key)
				return join(n2, n1);

            std::swap(n1->_left, n1->_right);
            n1->_left = join(n2, n1->_left);
            n1->_left->_up = n1;

            assert(n1->_left->_up == n1);
            if (n1->_right != nullptr)
                printf("0x%08x, 0x%08x\n", n1->_right, n1->_right->_up);
            assert(n1->_right == nullptr || n1->_right->_up == n1);

			return n1;
		}

        static void inorder(std::vector<Node *> & vector, Node * n) {
        	if (n == nullptr) return;
        	inorder(vector, n->_left);
        	vector.push_back(n);
        	inorder(vector, n->_right);
        }
};
