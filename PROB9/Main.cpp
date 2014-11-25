#include <string>
#include <sstream>
#include "RedBlackTree.h"

using namespace std;

int main(int argc, char* argv[])
{
	/* Welcome */
	cout << "**               红黑树               **" << endl;
	cout << "=======================================" << endl;
	cout << "**             1 - 建立树             **" << endl;
	cout << "**            2 - 插入元素            **" << endl;
	cout << "**            3 - 查询元素            **" << endl;
	cout << "**            4 - 退出程序            **" << endl;
	cout << "=======================================" << endl;

	string input;
	RBTree<int> *treeptr = nullptr;

	while (true) {
		cout << "Please Select: ";
		cin >> input;

		if (input == "1") {
			if (treeptr == nullptr) {
				treeptr = new RBTree<int>;
				cout << "Please input number of initial elements:" << endl;
				int num;
				cin >> num;
				cout << "Please input the elements:" << endl;
				int tmp;
				for (int i = 0; i < num; i++) {
					cin >> tmp;
					if (treeptr->count(tmp) == 0)
						treeptr->insert(tmp);
					else
						cout << "Element " << tmp << " has already been inserted in the tree." << endl;
				}
				cout << "Current elements: ";
				treeptr->print();
				cout << endl;
			} else {
				cout << "Red-black tree has been established. Operation cancelled." << endl;
			}
		}
		else if (input == "2") {
			if (!treeptr) {
				cout << "Tree not found." << endl;
				continue;
			}
			cout << "Please input the element: " << endl;
			int tmp;
			cin >> tmp;
			if (treeptr->count(tmp) == 0)
				treeptr->insert(tmp);
			else
				cout << "Element " << tmp << " has already been inserted in the tree." << endl;
		}
		else if (input == "3") {
			if (!treeptr) {
				cout << "Tree not found." << endl;
				continue;
			}
			cout << "Please input the element: " << endl;
			int tmp;
			cin >> tmp;
			if (treeptr->count(tmp) == 1)
				cout << "Search success!" << endl;
			else
				cout << "Not found element " << tmp << "."<< endl;
		}
		else if (input == "4") {
			cout << "Bye!" << endl;
			system("pause");
			break;
		}
		else {
			cout << "Invalid input." << endl;
		}
	}

	return 0;
}