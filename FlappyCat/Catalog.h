#pragma once
//Template in care 
//Catalogul trebuie sa stocheze un tip de data, sa primeasca un fisier cu 1 sau 0 in functie daca itemul e deblocat sau nu;
// in cazul meu, voi folosi SDL_Texture in loc de T
#include "Warning.h"
#include <fstream>
//TO DO: Catalogul
template <typename T>
class Catalog
{
	T* items = nullptr;
	size_t nr_items;


public:
	size_t left, center, right;
	Catalog()
	{
		items = new T;
		nr_items = 1;
		left = 0 % nr_items;
		center = 1 % nr_items;
		right = 2 % nr_items;
	}

	Catalog(size_t n)
	{		
		nr_items = n;
		left = 0 % nr_items;
		center = 1 % nr_items;
		right = 2 % nr_items;

		items = new T[n];
		for (size_t i = 0; i < n; i++)
		{
			*(items + i) = 0;
		}
	}
	Catalog(const char* p)
	{
		//FILE* catalog_prop = nullptr;
		ifstream catalog_prop;
		catalog_prop.open(p);
		/*bool*/Uint16 state = 0; // (UN)LOCKED
		try {
			catalog_prop >> nr_items;
			if (nr_items > 100)
			{
				warning w("The file read more than 100 items in the catalog! Make sure its well formated. (100+ might be a mistake?)");
				throw w;
			}
		}
		catch (warning& w) { nr_items = 1; }; //nu cred ca e nevoie de un catch {}
		left = 0 % nr_items;
		center = 1 % nr_items;
		right = 2 % nr_items;
		items = new T[nr_items];
		for (size_t i = 0; i < nr_items; i++)
		{
			cout << "Index " << i << endl;
			catalog_prop >> state;
				*(items + i) = state;
		}
		catalog_prop.close();
	}

	~Catalog()
	{
		if (items)
			delete[] items;
	}
	T* operator[](size_t index)
	{
		return &items[index];
	}

	size_t getsize(void) const { return nr_items; }

};