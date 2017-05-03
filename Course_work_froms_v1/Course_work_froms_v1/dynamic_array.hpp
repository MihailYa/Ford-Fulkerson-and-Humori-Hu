#pragma once

/**
* Create dynamic array n x m
* @n rows
* @m cols
* @return pointer on array
*/
template<typename T>
T** create_array(int n, int m)
{
	T **temp;
	temp = new T*[n];
	for (int i = 0; i < n; i++)
		temp[i] = new T[m];

	return temp;
}

/**
* Delete dynamic array n x m
* @ar array n x m
* @n rows
* @return pointer on array
*/
template<typename T>
void delete_array(T **ar, int n)
{
	for (int i = 0; i < n; i++)
		delete[] ar[i];
	delete[] ar;
}