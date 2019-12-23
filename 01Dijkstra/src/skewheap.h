#pragma once
#include <iterator>

template <class K, class V>
class SkewHeap {
    public:
        class Node {
            K _key;
            V _val;
            Node * _left;
            Node * _right;

            friend class SkewHeap;

            public:
            	Node(K key, V val) :
            		_key(key), _val(val), _left(nullptr), _right(nullptr) {}

            	~Node() {
            		if (_left != nullptr) delete _left;
            		if (_right != nullptr) delete _right;
            		_left = _right = nullptr;
            	}

                K getKey() const { return _key; }
                V getVal() const { return _val; }

                bool esHoja() const {
                	return _left == nullptr && _right == nullptr;
                }
        };

        SkewHeap() : _root(nullptr) {}

        ~SkewHeap() {
        	delete _root;
        	_root = nullptr;
        }

        Node * getMin() const {
        	return _root;
        }

        void deleteMin() {
        	auto aux = _root;
        	_root = join(aux->_left, aux->_right);
        	delete aux;
        }

        void insert(K key, V val) {
        	_root = join(_root, new Node(key, val));
        }

        const std::vector<Node *> inorder() const {
        	auto vector = std::vector<Node*>();
        	inorder(vector, _root);
        	return vector;
        }
    private:
        Node * _root;

        static Node * join(Node * n1, Node * n2) {
			if (n1 == nullptr) return n2;
			if (n2 == nullptr) return n1;

			// We avoid writing two if's
			if (n1->_key > n2->_key)
				std::swap(n1, n2);

			std::swap(n1->_left, n1->_right);

			n1->_left = join(n2, n1->_left);

			return n1;
		}

        static void inorder(std::vector<Node *> & vector, Node * n) {
        	if (n == nullptr) return;
        	inorder(vector, n->_left);
        	vector.push_back(n);
        	inorder(vector, n->_right);
        }
};
