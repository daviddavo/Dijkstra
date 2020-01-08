#pragma once

#include <assert.h>

class EmptyHeapException {};
class KeyGreaterException {};

template <class K, class V>
class SkewHeap {
	/* Node _root */

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
            assert(_root->_up == nullptr);
            assert(_root->_left == nullptr || _root->_left->_up == _root);
            assert(_root->_right == nullptr || _root->_right->_up == _root);
        	return _root;
        }

        void deleteMin() {
            if (_root == nullptr) throw EmptyHeapException();
        	auto aux = _root;

        	if (_root->esHoja()) {
        		_root = nullptr;
        	} else {
        		if (aux->_left != nullptr) aux->_left->_up = nullptr;
        		if (aux->_right != nullptr) aux->_right->_up = nullptr;
        		_root = join(aux->_left, aux->_right);
        		_root->_up = nullptr;
        	}

        	aux->_left = aux->_right = nullptr;
        	delete aux;

        	assert(_root == nullptr || _root->_up == nullptr);
        	assert(_root == nullptr || _root->_left == nullptr || _root->_left->_up == _root);
			assert(_root == nullptr || _root->_right == nullptr || _root->_right->_up == _root);
        }

        Node * insert(K key, V val) {
            Node * n = new Node(key, val);

        	_root = join(_root, n);
            _root->_up = nullptr;

			assert(_root->_left == nullptr || _root->_left->_up == _root);
			assert(_root->_right == nullptr || _root->_right->_up == _root);
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

            auto & up = node->_up;
            node->_key = newKey;

            // If node->_up is nullpointer, then it's the root
            // we don't have to do anything
            assert(up != nullptr || node == _root);
            if (up != nullptr) {
                if (node != up->_right)
                    std::swap(up->_left, up->_right);

                assert(up->_right == node || up->_left == node);
                up->_right = nullptr;
                node->_up = nullptr;

                _root = join(_root, node);
                _root->_up = nullptr;

				assert(_root->_left == nullptr || _root->_left->_up == _root);
				assert(_root->_right == nullptr || _root->_right->_up == _root);
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
				std::swap(n2, n1);

			assert(n1->_up == nullptr || n1->_up->_left == n1 || n1->_up->_right == n1);
			assert(n1->_left == nullptr || n1->_left->_up == n1);
			assert(n1->_right == nullptr || n1->_right->_up == n1);
			assert(n2->_up == nullptr || n2->_up->_left == n2 || n2->_up->_right == n2);
			assert(n2->_left == nullptr || n2->_left->_up == n2);
			assert(n2->_right == nullptr || n2->_right->_up == n2);

            std::swap(n1->_left, n1->_right);
            n1->_left = join(n1->_left, n2);
            n1->_left->_up = n1;

            assert(n1->_left->_up == n1);
            assert(n1->_right == nullptr || n1->_right->_up == n1);
            assert(n1->_up == nullptr || n1->_up->_left == n1 || n1->_up->_right == n1);
            assert(n2->_up == nullptr || n2->_up->_left == n2 || n2->_up->_right == n2);
			assert(n2->_left == nullptr || n2->_left->_up == n2);
			assert(n2->_right == nullptr || n2->_right->_up == n2);

			return n1;
		}

        static void inorder(std::vector<Node *> & vector, Node * n) {
        	if (n == nullptr) return;
        	inorder(vector, n->_left);
        	vector.push_back(n);
        	inorder(vector, n->_right);
        }
};
