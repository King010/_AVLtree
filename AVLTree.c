#pragma once
#include<iostream>
using namespace std;


template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K,V>*_pLeft;
	AVLTreeNode<K, V>*_pRight;
	AVLTreeNode<K, V>*_pParent;
	K _key;
	V _value;
	int _bf;
	AVLTreeNode(const K&key, const V&value)
		:_pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
};



template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_proot(NULL)
	{}
	AVLTree(const AVLTree<K, V>& t)
	{}
	bool Insert(const K&key,const V&value)
	{
		Node *pCur = _proot;
		Node *pParent = NULL;
		while (pCur)
		{
			if (pCur->_key > key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (pCur->_key < key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}

		pCur = new Node(key,value);

		if (pParent == NULL)
		{
			_proot = pCur;
			return true;
		}
		else
		{
			if (pParent->_key < pCur->_key)
			{
				pParent->_pRight=pCur;
				pParent->_bf ++;
			}
			else
			{
				pParent->_pLeft = pCur;
				pParent->_bf --;
			}
			pCur->_pParent = pParent;
		}

		while (pParent!=NULL)
		{
			if (pParent->_bf == 0)
				return true;
			else if (pParent->_bf == 1 || pParent->_bf == -1)
			{
				Node*ppParent = pParent->_pParent;
				if (ppParent != NULL)
				{
					if (ppParent->_pLeft == pParent)
						ppParent->_bf--;
					else
						ppParent->_bf++;
				}
				pParent = pParent->_pParent;
				pCur = pCur->_pParent;
			}
			else
			{
				if (pParent->_bf == 2)
				{
					if (pCur->_bf == 1)
						_RotateL(pParent);
					else
						_RotateRL(pParent);
				}
				else if (pParent->_bf == -2)
				{
					if (pCur->_bf == -1)
						_RotateR(pParent);
					else
						_RotateLR(pParent);
				}
				break;
			}
		}
		return true;
	}

	void Inorder()
	{
		_Inorder(_proot);
	}

	bool IsBalance()
	{
		return _IsBalace(_proot);
	}

	void Height()
	{
		return _Height(_proot);
	}

private:

	bool _IsBalace(Node*proot)
	{
		if (proot == NULL)
			return true;
		int left = _Height(proot->_pLeft);
		int right = _Height(proot->_pRight);

		if (right - left != proot->_bf || abs(right - left) > 1)
		{
			cout << endl;
			cout << proot->_key << "平衡因子出错" << endl;
			return false;
		}

		return _IsBalace(proot->_pLeft) && _IsBalace(proot->_pRight);
	}

	void _Inorder(Node*proot)
	{
		if (proot == NULL)
			return;
		_Inorder(proot->_pLeft);
		cout << proot->_key << " ";
		_Inorder(proot->_pRight);
	}

	void _RotateR(Node*parent)
	{
		Node*subL = parent->_pLeft;
		Node*subLR = subL->_pRight;

		parent->_pLeft = subLR;
		if (subLR != NULL)
			subLR->_pParent = parent;
		subL->_pRight = parent;
		subL->_pParent = parent->_pParent;
		Node*ppParent = parent->_pParent;
		parent->_pParent = subL;

		if (ppParent == NULL)
		{
			_proot = subL;
			subL->_pParent = NULL;
		}
		else
		{
			if(ppParent->_pLeft == parent)
				ppParent->_pLeft = subL;
			else
				ppParent->_pRight = subL;
			subL->_pParent = ppParent;
		}
		
		parent->_bf = subL->_bf = 0;
		parent = subL;
	}

	void _RotateL(Node*parent)
	{
		Node*subR = parent->_pRight;
		Node*subRL = subR->_pLeft;

		parent->_pRight = subRL;
		if (subRL != NULL)
			subRL->_pParent = parent;
		subR->_pLeft = parent;
		subR->_pParent = parent->_pParent;
		Node*ppParent = parent->_pParent;
		parent->_pParent = subR;

		if (ppParent == NULL)
		{
			_proot = subR;
			subR->_pParent = NULL;
		}
		else
		{
			if (ppParent->_pLeft == parent)
				ppParent->_pLeft = subR;
			else
				ppParent->_pRight = subR;
			subR->_pParent = ppParent;
		}
		parent->_bf = subR->_bf = 0;
		parent=subR;
	}

	void _RotateLR(Node* parent)
	{
		Node*subL = parent->_pLeft;
		Node*subLR = subL->_pRight;
		int bf = subLR->_bf;

		_RotateL(parent->_pLeft);
		_RotateR(parent);
		
		if (-1 == bf)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
	}

	void _RotateRL(Node* parent)
	{
		Node*subR = parent->_pRight;
		Node*subRL = subR->_pLeft;
		int bf = subRL->_bf;

		_RotateR(parent->_pRight);
		_RotateL(parent);

		if (-1 == bf)
		{
			parent->_bf = 0;
			subR->_bf = 1;
		}
		else
		{
			parent->_bf = -1;
			subR->_bf = 0;
		}
	}

	int _Height(Node*proot)
	{
		if (NULL == proot)
			return 0;
		int left = _Height(proot->_pLeft)+1;
		int right = _Height(proot->_pRight)+1;
		return left > right ? left: right;
	}

private:
	Node *_proot;

//
};
