#define _CRT_SECURE_NO_WARNINGS 1
#include"AVLTree.h"
#include<iostream>
using namespace std;

void Test1()
{
	AVLTree<int, int>t;
	t.Insert(50,50);
	t.Insert(40,40);
	t.Insert(70,70);
	t.Insert(65,65);
	t.Insert(80,80);
	//t.Insert(90,90);
	t.Insert(68, 68);
	t.Inorder();
	t.Remove(68);
	cout<<t.IsBalance()<<endl;

}

int main()
{
	Test1();
	system("pause");
	return 0;
}
