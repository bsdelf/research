#include <iostream>
#include <fstream>
#include <string>
#include "scx/ColStr.hpp"
using namespace std;
using namespace scx;

struct Table
{
    size_t row;
    size_t column;
    string name;
    int** p;

    Table(size_t row, size_t col, const string& str):
	row(row),
	column(col),
	name(str),
	p(NULL)
    {
	if (row != 0)
	{
	    p = new int*[row];
	}

	for (size_t i = 0; i < row; i++)
	{
	    if (column != 0)
	    {
		p[i] = new int[column];
	    }

	    for (size_t j = 0; j < column; j++)
	    {
		p[i][j] = 0;
	    }
	}
    }

    ~Table()
    {
	if (row != 0)
	{
	    for (size_t i = 0; i < row; ++i)
	    {
		if (column != 0)
		    delete[] p[i];
	    }
	    delete[] p;
	}
    }
};

void create(Table*& refpTable, int row, int column, const string& name)
{
    refpTable = new Table(row, column, name);

    cout << YellowStr("create done!") << endl;
}

void print(Table* pTable)
{
    cout << pTable->name << ":" << endl;
    for (size_t i = 0; i < pTable->row; i++)
    {
	for (size_t j = 0; j < pTable->column; j++)
	{
	    cout << pTable->p[i][j] << '\t';
	}
	cout << endl;
    }

    cout << YellowStr("print done!") << endl;
}

void set(Table* pTable, int row, int column, int value)
{
    if (row < pTable->row && column < pTable->column)
	pTable->p[row][column] = value;
    else
	cout << RedStr("set error!") <<endl;
}

void copy(Table* pSrc,Table* pDest)
{
    size_t row = std::min(pSrc->row, pDest->row);
    size_t column = std::min(pSrc->column, pDest->column);

    for (size_t i = 0; i < row; ++i)
    {
	for (size_t j = 0; j < column; ++j)
	{
	    pDest->p[i][j] = pSrc->p[i][j];
	}
    }

    cout << YellowStr("copy done!") << endl;
}
 
void remove(Table*& pTable)
{
    delete pTable;
    pTable = NULL;

    cout << YellowStr("remove done!") << endl;
}

void resize(Table*& pOldTable, int row, int column)
{
    Table* pNewTable;
    create(pNewTable, row, column, pOldTable->name);
    copy(pOldTable, pNewTable); 
    remove(pOldTable);
    pOldTable = pNewTable;

    cout << YellowStr("resize done!") << endl;
}
 
void load(Table*& pTable, const string& path)
{
    ifstream infile(path.c_str(), ios::in | ios::binary);

    if (infile.is_open())
    {
	size_t row = 0;
	size_t column = 0;
	size_t namelen = 0;
	char* pname = NULL; 

	infile.read((char*)&row, sizeof(size_t));
	infile.read((char*)&column, sizeof(size_t));
	infile.read((char*)&namelen, sizeof(size_t));

	pname = new char[namelen];
	infile.read(pname, namelen);
	string name(pname, namelen);
	delete[] pname;

	create(pTable, row, column, name);

	for (size_t i = 0; i < row; ++i)
	{
	    for (size_t j = 0; j < column; ++j)
	    {
		infile.read((char*)&pTable->p[i][j], sizeof(int));
	    }
	}

	cout << YellowStr("load finished!") << endl;
    }
    else
    {
	pTable = NULL;
	cout << RedStr("load failed, can't open!") << endl;
    }

    infile.close();
}

void save(Table* pTable, const string& path)
{
    ofstream outfile(path.c_str(), ios::out | ios::binary);

    if (outfile.is_open())
    {
	size_t row = pTable->row;
	size_t column = pTable->column;
	size_t namelen = pTable->name.size();
	string name(pTable->name);

	outfile.write((const char*)&row, sizeof(size_t));
	outfile.write((const char*)&column, sizeof(size_t));
	outfile.write((const char*)&namelen, sizeof(size_t));
	outfile.write(name.data(), name.size());

	for (size_t i = 0; i < row; ++i)
	{
	    for (size_t j = 0; j < column; ++j)
	    {
		outfile.write((char*)&pTable->p[i][j], sizeof(int));
	    }
	}

	cout << YellowStr("save finished!") << endl;
    }
    else
    {
	cout << RedStr("save failed! can't open!") << endl;
    }

    outfile.close();
}

int main(int argc, char** argv)
{
   Table* pTable = NULL;
   string cmd;

   while (true)
   {
       cout << BlueStr("enter cmd: ");
       cin >> cmd;

       if (cmd == "create")
       {   
	   size_t row;
	   size_t column;
	   string name;
	   cin >> row >> column >> name;
	   create(pTable, row, column, name);
       }
       else if (cmd == "print")
       {
	   print(pTable);
       }
       else if (cmd == "set")
       {
	   size_t row;
	   size_t column;
	   int value;
	   cin >> row >> column >> value;
	   set(pTable, row, column, value);
       }
       else if (cmd == "resize")
       {
	   size_t row;
	   size_t column;
	   cin >> row >> column ;
	   resize(pTable, row, column);
       }
       else if (cmd == "remove")
       {
	   remove(pTable);
       }
       else if (cmd == "load")
       {
	   string path;
	   cin >> path;
	   remove(pTable);
	   load(pTable, path);
       }
       else if (cmd == "save")
       {
	   string path;
	   cin >> path;
	   save(pTable, path);
       }
       else if (cmd == "quit")
       {
	   break;  
       }
   }

   if (pTable != NULL)
   {
       delete pTable;
   }

   return 0;
}
