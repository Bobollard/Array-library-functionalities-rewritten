#include"Array.h"

int main() {

	Array<int> exArray(4);
	exArray.fillRange(0, 3, 8); 
	exArray.displayElements(0, 3);

	cout << endl;
	cout << endl;
	

	Array<int> exArray2D(2, 2);
	for (int i = 0; i < 2; i++) {
		for (int z = 0; z < 2; z++) {
			exArray2D.addElement(i, z, 4);
		}
	}
	exArray2D.displayElements(0, 1, 0, 1);
	
	cout << endl;
	cout << endl;

	int nextspot = exArray.nextOpenSpace();

	system("pause");

	return 0;
}