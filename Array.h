#ifndef ARRAY_H
#define ARRAY_H

#include<iostream>
#include<string>
#include<fstream>
#include<typeinfo>

using namespace std;


template <typename T> class Array{

private:

	int s1 = NULL;
	int s2 = NULL;
	int s3 = NULL; //Size of array 1-3 dimensional
	T* myarray;
	T** my2Darray;
	T*** my3Darray;
	T* temparray;
	T** temp2Darray;
	T*** temp3Darray;


public:

	Array(int size);
	Array(int size1, int size2);
	Array(int size1, int size2, int size3);

	~Array();

	int i1 = 0;
	int i2 = 0;
	int i3 = 0;

	Array<T> combine2DArrays();
	Array<T> combine3DArrays();

	void addEndElement(T value); //adds value to end of 1d array
	void addEndElement(int index, T value); //adds value to end of array at specified index (2d)
	void addEndElement(int index1, int index2, T value); //adds value to end of array at specified index (3d)
	void addElement(int index, T value); //adds value at index, shift rest over 1
	void addElement(int index1, int index2, T value); //adds value at 2d index, shifts rest over 1
	void addElement(int index1, int index2, int index3, T value); //adds value at 3d index, shifts rest over 1


	template<typename T>
	Array<T> operator+(const Array<T>& a);

																  //remove functions
	void removeElement(int fromIndex, int toIndex); //sets values in index range to 0, shifts rest back accordingly
	void removeElement(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2); //sets values in 2d index area to 0 and shifts s2 values back accordingly
	void removeElement(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3); //sets values in 3d index area to 0 and shifts s3 values back accordingly

																												  //edit functions
	void editElement(int index, T value); //sets contents of element at index to given value
	void editElement(int index1, int index2, T value); //same, but 2d index
	void editElement(int index1, int index2, int index3, T value); //same, but 3d index

	void exportArray(string fileName); //checks dimensions, writes array values to text file (fileName) accordingly
	void export2DArray(); //called in exportArray function if array has 2 dimensions
	void export3DArray(); //called in exportArray function if array has 3 dimensions

																   //fill functions
	void fillRange(int fromIndex, int toIndex, T value); //sets elements in range to value
	void fillRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, T value); //sets elements in area to value
	void fillRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3, T value); //sets elements in volume to value

																													   //display functions
	void displayElements(int fromIndex, int toIndex); //displays values of elements in range
	void displayElements(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2); //displays values of data-elements in 2d range
	void displayElements(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3); //displays values of data-elements in 3d range

																														//sort functions
	//void sortRange(int fromIndex, int toIndex); //sort range in 1d array in ascending order
	//void sortRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2); //sort data in range2 in each array in range1 in ascending order relative to that array
	//void sortRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3); //sort data in range3 in each array in range2 in each array in range1 in ascending order relative to that array
																														//deconstructing functions called in deconstructor
	void close(int s1, int s2); //deletes all elements in 2D array and points myarray to null
	void close(int s1, int s2, int s3);//deletes all elements in 3D array and points myarray to null
																											 
	//search functions
	void firstOpenSpace1D();
	void firstOpenSpace2D();
	void firstOpenSpace3D();
	int nextOpenSpace();
	int nextOpenSpace(int index1);
	int nextOpenSpace(int index1, int index2);
	T searchArray(int index); //search array for index, return value
	T searchArray(int index1, int index2); //search 2d array for index, return value at index
	T searchArray(int index1, int index2, int index3); //search 3d array for index, return value at index
	int searchValue1D(T value); //search array for value, return index 1D
	void searchValue2D(T value); //search array for value, return index 2D
	void searchValue3D(T value); //search array for value, return index 3D



};


template <typename T>
Array<T> operator+ (const Array<T>& a)
{
	int s1 = this->s1;
	int s1a = a.s1;
	int sumS1 = s1 + s1a;
	int s2 = this->s2;
	int s2a = a.s2;
	int s3 = this->s3;
	int s3a = a.s3;
	if (s1 != NULL && s2 == NULL)
	{
		Array<T> sumArray(sumS1);
		for (int x = 0; x < s1; x++)
		{
			sumArray.myarray[x] = this->myarray[x];
		}
		for (int x = s1; x < sumS1; x++)
		{
			sumArray.myarray[x] = a.myarray[x - s1];
		}
	}
	else if (s1 != NULL && s2 != NULL && s3 == NULL)
	{
		Array<T> sumArray(s1,s2) = combine2DArrays();
	}
	else if (s1 != NULL && s2 != NULL && s3 != NULL)
	{
		Array<T> sumArray(s1,s2,s3) = combine3DArrays();
	}
	return sumArray();
}


template <typename T>
Array<T>::Array(int size) {
	s1 = size;
	myarray = new T[s1];
	if (typeid(myarray) == typeid(string)) {
		for (int x = 0; x < s1; x++)
		{
			myarray[x] = ' ';
		}
	}
	else if (typeid(myarray) == typeid(char))
	{
		for (int x = 0; x < s1; x++)
		{
			myarray[x] = ' ';
		}
	}
	else {
		for (int x = 0; x < s1; x++)
		{
			myarray[x] = NULL;
		}
	}
}
template <typename T>
Array<T>::Array(int size1, int size2) {
	s1 = size1;
	s2 = size2;
	my2Darray = new T*[s1];
	for (int i = 0; i < s1; i++) {
		my2Darray[i] = new T[s2];
	}
	if (typeid(T) == typeid(string) || typeid(T) == typeid(char)) {
		for (int x = 0; x < s1; x++)
		{
			for (int y = 0; y < s2; y++)
			{
				my2Darray[x][y] = ' ';
			}
		}
	}
	else {
		for (int x = 0; x < s1; x++)
		{
			for (int y = 0; y < s2; y++)
			{
				my2Darray[x][y] = NULL;
			}
		}
	}
}
template <typename T>
Array<T>::Array(int size1, int size2, int size3) {
	s1 = size1;
	s2 = size2;
	s3 = size3;
	my3Darray = new T**[s1];
	for (int x = 0; x < s1; x++) {
		my3Darray[x] = new T*[s2];
		for (int y = 0; y < s2; y++) {
			my3Darray[x][y] = new T[s3];
		}
	}
	if (typeid(T) == typeid(string) || typeid(T) == typeid(char)) {
		for (int x = 0; x < s1; x++)
		{
			for (int y = 0; y < s2; y++)
			{
				for (int z = 0; z < s2; z++)
				{
					my3Darray[x][y][z] = ' ';
				}
			}
		}
	}
	else {
		for (int x = 0; x < s1; x++)
		{
			for (int y = 0; y < s2; y++)
			{
				for (int z = 0; z < s2; z++)
				{
					my3Darray[x][y][z] = NULL;
				}
			}
		}
	}
}

template<typename T>
void Array<T>::firstOpenSpace1D() {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {

		if (s1 != NULL && s2 == NULL && s3 == NULL) {

			for (int i = 0; i < s1; i++) {
				temp = myarray[i];
				if (temp == NULL) {
					i1 = i;
					break;
				}
			}

		}
	}

	else {
		for (int i = 0; i < s1; i++) {
			temp = myarray[i];
			if (temp == ' ') {
				i1 = i;
				break;
			}
		}
	}
}

template<typename T>
void Array<T>::firstOpenSpace2D() {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {
		if (s1 != NULL && s2 != NULL && s3 == NULL) {

			for (int i = 0; i < s1; i++) {
				for (int x = 0; x < s2; x++) {
					temp = my2Darray[i][x];
					if (temp == NULL) {
						i1 = i;
						i2 = x;
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < s1; i++) {
			for (int x = 0; x < s2; x++) {
				temp = my2Darray[i][x];
				if (temp == ' ') {
					i1 = i;
					i2 = x;
				}
			}
		}

	}
}

template<typename T>
void Array<T>::firstOpenSpace3D() {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {
		if (s1 != NULL && s2 != NULL && s3 != NULL) {
			for (int i = 0; i < s1; i++) {
				for (int x = 0; x < s2; x++) {
					for (int y = 0; y < s3; y++) {
						temp = my3Darray[i][x][y];
						if (temp == NULL) {
							i1 = i;
							i2 = x;
							i3 = y;
						}
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < s1; i++) {
			for (int x = 0; x < s2; x++) {
				for (int y = 0; y < s3; y++) {
					temp = my3Darray[i][x][y];
					if (temp == ' ') {
						i1 = i;
						i2 = x;
						i3 = y;
					}
				}
			}
		}
	}
}

template <typename T>
int Array<T>::nextOpenSpace() {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {
		for (int i = 0; i < s1; i++) {
			temp = myarray[i];
			if (temp == NULL) {
				return i;
			}
		}
	}
	else {
		for (int i = 0; i < s1; i++) {
			temp = myarray[i];
			if (temp == ' ') {
				return i;
			}
		}
	}
}

template <typename T>
int Array<T>::nextOpenSpace(int index1) {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {

		for (int x = 0; x < s2; x++) {
			temp = my2Darray[index][x];
			if (temp == NULL) {
				return x;
			}
		}

	}
	else {
		for (int x = 0; x < s2; x++) {
			temp = my2Darray[index][x];
			if (temp == ' ') {
				return x;
			}
		}
	}
}

template <typename T>
int Array<T>::nextOpenSpace(int index1, int index2) {

	T temp;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(bool)) {

		for (int y = 0; y < s3; y++) {
			temp = my3Darray[index1][index2][y];
			if (temp == NULL) {
				return y;
			}
		}

	}
	else {

		for (int y = 0; y < s3; y++) {
			temp = my3Darray[index1][index2][y];
			if (temp == ' ') {
				return y;
			}
		}
	}

}

template<typename T>
void Array<T>::addElement(int index, T value) {

	temparray = new T[s1];

	for (int i = index; i < s1 - 1; i++) {
		temparray[i + 1] = myarray[i];
	}
	for (int i = index - 1; i >= 0; i--) {
		temparray[i] = myarray[i];
	}
	temparray[index] = value;
	for (int i = 0; i < s1; i++) {
		myarray[i] = temparray[i];
	}
}

template<typename T>
void Array<T>::addElement(int index1, int index2, T value) {

	temp2Darray = new T*[s1];
	for (int i = 0; i < s1; i++) {
		temp2Darray[i] = new T[s2];
	}

	if(typeid(T) == typeid(char)) {
		for (int i = 0; i < s1; i++) {
			for (int x = 0; x < s2; x++) {
				temp2Darray[i][x] = ' ';
			}
		}
	}
	else if(typeid(T) == typeid(string)) {
		for (int i = 0; i < s1; i++) {
			for (int x = 0; x < s2; x++) {
				temp2Darray[i][x] = ' ';
			}
		}
	}
	else {
		for (int i = 0; i < s1; i++) {
			for (int x = 0; x < s2; x++) {
				temp2Darray[i][x] = NULL;
			}
		}
	}

	for (int x = index2 + 1; x < s2 - 1; x++) {
		temp2Darray[index1][x] = my2Darray[index1][x];
	}
	
	for (int x = index2 - 1; x > -1; x--) {
		temp2Darray[index1][x] = my2Darray[index1][x];
	}
	temp2Darray[index1][index2] = value;
	for (int x = 0; x < s2; x++) {
		my2Darray[index1][x] = temp2Darray[index1][x];
	}

}

template<typename T>
void Array<T>::addElement(int index1, int index2, int index3, T value) {

	temp3Darray = new T**[s1];
	for (int x = 0; x < s1; x++) {
		temp3Darray[x] = new T*[s2];
		for (int y = 0; y < s2; y++) {
			temp3Darray[x][y] = new T[s3];
		}
	}


	for (int y = index3; y < s3 - 1; y++) {
		temp3Darray[index1][index2][y + 1] = my3Darray[index1][index2][y];
	}

	for (int y = index3; y >= 0; y--) {
		temp3Darray[index1][index2][y] = my3Darray[index1][index2][y];
	}

	temp3Darray[index1][index2][index3] = value;

	for (int y = 0; y < s3; y++) {
		my3Darray[index1][index2][y] = temp3Darray[index1][index2][y];
	}

}

template<typename T>
void Array<T>::addEndElement(T value) {
	int nextSpace = nextOpenSpace();
	myarray[nextSpace] = value;
}

template<typename T>
void Array<T>::addEndElement(int index, T value) {
	int nextSpace = nextOpenSpace(index);
	my2Darray[index][nextSpace] = value;
}

template<typename T>
void Array<T>::addEndElement(int index1, int index2, T value) {
	int nextSpace = nextOpenSpace(index1, index2);
	my3Darray[index1][index2][nextSpace] = value;
}

template<typename T>
void Array<T>::removeElement(int fromIndex, int toIndex) {

	temparray = new T[s1];

	int amtChanged;

	if (fromIndex == toIndex) {
		amtChanged = 1;
	}
	else {
		amtChanged = toIndex - fromIndex;
	}

	for (int i = 0; i < fromIndex - 1; i++) { //fill bottom half of array
		temparray[i] = myarray[i];
	}

	for (int i = toIndex + 1; i < s1; i++) {//fill top half of array past the range being deleted
		temparray[i - amtChanged] = myarray[i]; //subtract the range amount from the index of temp array
	}

	for (int i = 0; i < s1; i++) { //rewrite to myarray
		myarray[i] = temparray[i];
	}

}

template<typename T>
void Array<T>::displayElements(int fromIndex, int toIndex) {
	for (int i = fromIndex; i <= toIndex; i++) {
		cout << myarray[i];
	}
}

template<typename T>
void Array<T>::displayElements(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2) {
	for (int i = fromIndex1; i <= toIndex1; i++) {
		for (int x = fromIndex2; x <= toIndex2; x++) {
			cout << my2Darray[i][x];
		}
	}
}

template<typename T>
void Array<T>::displayElements(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3) {
	for (int i = fromIndex1; i <= toIndex1; i++) {
		for (int x = fromIndex2; x <= toIndex2; x++) {
			for (int y = fromIndex3; y <= fromIndex3; y++) {
				cout << my3Darray[i][x][y];
			}
		}
	}
}

template<typename T>
void Array<T>::close(int s1, int s2) {
	for (int i = 0; i < s1; i++) {
		delete my2Darray[i];
		my2Darray[i] = NULL;
	}
	delete my2Darray;
	my2Darray = NULL;
}

template<typename T>
void Array<T>::close(int s1, int s2, int s3) {
	for (int i = 0; i < s1; i++) {
		for (int x = 0; x < s2; x++) {
			delete[] this->my3Darray[i][x];
			my3Darray[i][x] = NULL;
		}
	}
	delete my3Darray;
	my3Darray = NULL;
}
template<typename T>

Array<T>::~Array() {
	try {

		if (s1 != NULL && s2 == NULL && s3 == NULL) {
			delete myarray;
			myarray = NULL;
		}
		else if (s1 != NULL && s2 != NULL && s3 == NULL) {
			close(s1, s2);
		}
		else if (s1 != NULL && s2 != NULL && s3 != NULL) {
			close(s1, s2, s3);
		}
		else {
			throw "Error deconstructing array";
		}

	}
	catch (const char* msg) {
		cout << msg << endl;
	}
}

template<typename T>
T Array<T>::searchArray(int index) {
	T value;
	value = myarray[index];
	return value;
}

template<typename T>
T Array<T>::searchArray(int index1, int index2) {
	T value;
	value = my2Darray[index1][index2];
	return value;
}

template<typename T>
T Array<T>::searchArray(int index1, int index2, int index3) {
	T value;
	value = my3Darray[index1][index2][index3];
	return value;
}

template<typename T>
int Array<T>::searchValue1D(T value) {
	T temp;
	for (int i = 0; i < s1; i++) {
		temp = myarray[i];
		if (temp == value) {
			return i;
		}
	}
}

template<typename T>
void Array<T>::searchValue2D(T value) {
	T temp;
	for (int i = 0; i < s1; i++) {
		for (int x = 0; x < s2; x++) {
			temp = my2Darray[i][x];
			if (temp == value) {
				i1 = i;
				i2 = x;
			}
		}
	}
}

template<typename T>
void Array<T>::searchValue3D(T value) {
	T temp;
	for (int i = 0; i < s1; i++) {
		for (int x = 0; x < s2; x++) {
			for (int y = 0; y < s3; y++) {
				temp = my3Darray[i][x][y];
				if (temp == value) {
					i1 = i;
					i2 = x;
					i3 = y;
				}
			}
		}
	}
}

template<typename T>
void Array<T>::removeElement(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2) {

	temp2Darray = new T*[s1];
	for (int i = 0; i < s1; i++) {
		temp2Darray[i] = new T[s2];
	}

	int amtChanged;

	if (fromIndex2 == toIndex2) {
		amtChanged = 1;
	}
	else {
		amtChanged = toIndex2 - fromIndex2;
	}

	for (int x = fromIndex1; x <= toIndex1; x++) {
		for (int y = 0; y < fromIndex2; y++) { //fill bottom half of array
			temp2Darray[x][y] = my2Darray[x][y];
		}

		for (int y = toIndex2 + 1; y < s1; y++) {//fill top half of array past the range being deleted
			temp2Darray[x][y - amtChanged2] = my2Darray[x][y]; //subtract the range amount from the index of temp array
		}

		for (int y = 0; y < s1; y++) { //rewrite to myarray
			m2Dyarray[x][y] = temp2Darray[x][y];
		}
	}
}


template<typename T>
void Array<T>::removeElement(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3) {

	temp3Darray = new T**[s1];
	for (int x = 0; x < s1; x++) {
		temp3Darray[x] = new T*[s2];
		for (int y = 0; y < s2; y++) {
			temp3Darray[x][y] = new T[s3];
		}
	}

	int amtChanged;

	if (fromIndex3 == toIndex3) {
		amtChanged = 1;
	}
	else {
		amtChanged = toIndex3 - fromIndex3;
	}

	for (int x = fromIndex1; x <= toIndex1; x++) {
		for (int y = fromIndex2; y <= toIndex2; y++)
		{
			for (int z = 0; z < fromIndex3; z++) { //fill bottom half of array
				temp3Darray[x][y][z] = my3Darray[x][y][z];
			}

			for (int z = toIndex2 + 1; z < s1; z++) {//fill top half of array past the range being deleted
				temp3Darray[x][y][z - amtChanged] = my3Darray[x][y][z]; //subtract the range amount from the index of temp array
			}

			for (int z = 0; z < s1; z++) { //rewrite to myarray
				my3Darray[x][y][z] = temp3Darray[x][y][z];
			}
		}
	}
}

template<typename T>
void Array<T>::fillRange(int fromIndex, int toIndex, T value)
{
	for (int x = fromIndex; x <= toIndex; x++)
	{
		myarray[x] = value;
	}
}

template<typename T>
void Array<T>::fillRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, T value)
{
	for (int x = fromIndex1; x <= toIndex1; x++)
	{
		for (int y = fromIndex2; y <= toIndex2; y++)
		{
			my2Darray[x][y] = value;
		}
	}
}

template<typename T>
void Array<T>::fillRange(int fromIndex1, int toIndex1, int fromIndex2, int toIndex2, int fromIndex3, int toIndex3, T value)
{
	for (int x = fromIndex1; x <= toIndex1; x++)
	{
		for (int y = fromIndex2; y <= toIndex2; y++)
		{
			for (int z = fromIndex3; z <= toIndex3; z++)
			{
				my3Darray[x][y][z] = value;
			}
		}
	}
}

template<typename T>
void Array<T>::editElement(int index, T value)
{
	try {
		if (s2 == NULL)
		{
			myarray[index] = value;
		}
		else {
			throw "Too many dimensions";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

template<typename T>
void Array<T>::editElement(int index1, int index2, T value)
{
	try {
		if (s3 == NULL && s2 != NULL)
		{
			my2Darray[index1][index2] = value;
		}
		else if (s3 != NULL) {
			throw "Too many dimensions";
		}
		else if (s2 == NULL) {
			throw "Not enough dimensions";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

template<typename T>
void Array<T>::editElement(int index1, int index2, int index3, T value)
{
	try {
		if (s3 != NULL)
		{
			my3Darray[index1][index2][index3] = value;
		}
		else if (s3 == NULL) {
			throw "Not enough dimensions";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

template<typename T>
void Array<T>::exportArray(string filename)
{
	ofstream file;
	file.open(filename, ios::out, ios::app);
	try {
		if (file.is_open())
		{
			if (s1 != NULL && s2 == NULL)
			{
				for (int x = 0; x < s1; x++)
				{
					file << myarray[x];
					file << ",";
				}
				file << endl;
			}
			else if (s1 != NULL && s2 != NULL && s3 == NULL)
			{
				export2DArray();
			}
			else if (s1 != NULL && s2 != NULL && s3 != NULL)
			{
				export3DArray();
			}
			file.close();
		}
		else {
			throw "Could not open file";
		}
	}
	catch (const* char msg)
	{
		cerr << msg << endl;
	}
}

template<typename T>
void Array<T>::export2DArray()
{
	for (int x = 0; x < s1; x++)
	{
		for (int y = 0; y < s2; y++)
		{
			file << myarray[x][y];
			file << ",";
		}
		file << endl;
	}
}

template<typename T>
void Array<T>::export3DArray()
{
	for (int x = 0; x < s1; x++)
	{
		file << x << endl;
		for (int y = 0; y < s2; y++)
		{
			for (int z = 0; z < s3; z++)
			{
				file << myarray[x][y][z];
				file << ",";
			}
			file << endl;
		}
		file << endl;
	}
}
template <typename T>
Array<T> Array<T>::combine2DArrays()
{
	int newS2 = 0;
	if (s2 > s2a) {
		newS2 = s2;
	}
	else {
		newS2 = s2a;
	}
	Array<T> sumArray(sumS1, newS2);
	for (int x = 0; x < s1; x++)
	{
		for (int y = 0; y < s2; y++)
		{
			sumArray.myarray[x][y] = this->myarray[x][y];
		}
	}
	for (int x = s1; x < sumS1; x++)
	{
		for (int y = 0; y < s2a; y++)
		{
			sumArray.myarray[x][y] = a.myarray[x - s1][y];
		}
	}
	return sumArray;
}

template <typename T>
Array<T> Array<T>::combine3DArrays()
{
	int newS2 = 0;
	int newS3 = 0;
	if (s2 > s2a) {
		newS2 = s2;
	}
	else {
		newS2 = s2a;
	}
	if (s3 > s3a) {
		newS3 = s3;
	}
	else {
		newS3 = s3a;
	}
	Array<T> sumArray(sumS1, newS2, newS3);
	for (int x = 0; x < s1; x++)
	{
		for (int y = 0; y < s2; y++)
		{
			for (int z = 0; z < s3; z++)
			{
				sumArray.myarray[x][y][z] = this->myarray[x][y][z];
			}
		}
	}
	for (int x = s1; x < sumS1; x++)
	{
		for (int y = 0; y < s2a; y++)
		{
			for (int z = 0; z < s3a; z++)
			{
				sumArray.myarray[x][y][z] = a.myarray[x - s1][y][z];
			}
		}
	}
	return sumArray;
}

#endif