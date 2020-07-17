#include <iostream>
#include <vector>
using namespace std;


enum State {
	EMPTY,
	EXIST,
	DELETE
};

template<class K,class V>
struct HashNode {
	pair<K, V> _value;
	State _state;
	HashNode(const pair<K, V>& val = pair<K, V>())
		:_value(val)
		,_state(EMPTY)
	{}
};


template<class K,class V>
class hashTable {
public:
	hashTable(size_t n = 10) {
		_table.resize(n);
		_size = 0;
	}

	bool insert(const pair<K, V>& value) {
		//检查容量
		checkcipacity();
		int idx = value.first%_table.size();
		while (_table[idx]._state == EXIST) {
			if (_table[idx]._value.first == value.first)
				return false;
			++idx;
			if (idx == _table.size())
				idx = 0;
		}
		//插入
		_table[idx]._value = value;
		_table[idx]._state = EXIST;
		_size++;
		return true;
	}
	//增容:
	void checkcipacity() {
		if (_size * 10 / _table.size() >= 7) {
			hashTable<K,V> tmp(2 * _table.size());

		}
		for (int i = 0; i < _table.size(); ++i) {
			if (_table[i]._state == EXIST) {
				tmp.insert(_table[i]._value);
			}
		}
		swap(_table, tmp._table);
	}


	//查找:
	hashNode<K, V>* find(const K& key) {
		int idx = key % _table.size();
		while (_table[idx]._state != EMPTY) {
			if (_table[idx]._state == EXIST && _table[idx]._value.first == key) {
				return &_table[idx];
			}
			++idx;
			if (idx == _table.size())
				idx = 0;
		}
		return nullptr;
	}
	//删除:
	bool erase(const K& key) {
		hashNode<K, V>* ptr = find(key);
		if (ptr) {
			ptr->_state == DELETE;
			_size--;
			return true;
		}
		return false;
	}

private:
	vector<hashNode<K, V>> _table;
	size_t _size;
};


void testHT()
{
	hashTable<int, int> ht();
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(11, 1));
	ht.insert(make_pair(21, 1));
	ht.insert(make_pair(2, 1));
	ht.insert(make_pair(9, 1));
	ht.insert(make_pair(15, 1));
	ht.insert(make_pair(13, 1));
	ht.insert(make_pair(28, 1));
	ht.insert(make_pair(72, 1));
	ht.insert(make_pair(99, 1));
	ht.insert(make_pair(56, 1));

	hashNode<int, int>* ptr = ht.find(99);
	cout << ptr->_value.first << "--->" << ptr->_value.second << endl;
	ptr = ht.find(100);
	cout << ptr << endl;

	bool ret = ht.erase(72);
	ret = ht.erase(35);

}

int main()
{
	testHT();
	return 0;
}