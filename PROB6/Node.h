#ifndef __1352847_NODE_H__
#define __1352847_NODE_H__

#include <string>
#include <vector>
#include <regex>
#include <set>

using std::string;
using std::vector;
using std::regex;
using std::set;

const regex OP_PATTERN("[ABCDE]");
const regex UINT_PATTREN("[0-9]+");

static set<string> nameUsed;

bool checkRepeat(const string& _name)
{
	if (nameUsed.count(_name) == 1) {
		return true;
	}
	return false;
}

typedef struct _Node
{
	_Node()
	{
		this->parent = nullptr;
		this->children = {};
		this->name = "";
		nameUsed.insert(this->name);
	}

	_Node(const string& _name)
	{
		this->parent = nullptr;
		this->children = {};
		this->name = _name;
		nameUsed.insert(_name);
	}

	~_Node()
	{
		for (int i = 0; i < this->children.size(); i++) {
			children[i]->~_Node();
		}
		nameUsed.erase(this->name);
	}

	_Node* find(const string& _name)
	{
		if (this->name == _name) {
			return this;
		}
		else {
			for (int i = 0; i < this->children.size(); i++) {
				auto ptr = children[i]->find(_name);
				if (ptr != nullptr) {
					return ptr;
				}
			}
			return nullptr;
		}
	}

	bool addChild(const string& _name)
	{
		if (checkRepeat(_name)) {
			return false;
		}
		this->children.push_back(new _Node(_name));
		return true;
	}

	bool deleteChild(const string& _name)
	{
		if (!checkRepeat(_name)) {
			return false;
		}
		if (this->name == _name) {
			this->~_Node();
			return true;
		}
		for (int i = 0; i < children.size(); i++) {
			this->children[i]->deleteChild(_name);
			if (this->children[i] == nullptr) {
				this->children.erase(this->children.begin() + i);
				break;
			}
		}
		return true;
	}

	bool editChild(const string& _name, const string& _changeName)
	{
		if ( (!checkRepeat(_name)) || (checkRepeat(_changeName)) ) {
			return false;
		}
		if (this->name == _name) {
			this->name = _changeName;
			nameUsed.erase(_name);
			nameUsed.insert(_changeName);
			return true;
		}
		for (int i = 0; i < children.size(); i++) {
			this->children[i]->editChild(_name, _changeName);
		}
		return true;
	}

	_Node* parent;
	vector<_Node*> children;
	string name;
} Node;

#endif