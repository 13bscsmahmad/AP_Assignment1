#include "Header.h"

using namespace std;

class testClass {

public:
	
	int test() {

		owned::StringBuffer *newString1 = new owned::StringBuffer;

		newString1->reserve(1);
		/*int length = newString1->length();

		if (length != 1) {
			cout << "Test failed" << endl;
			return 1;
		}*/
		newString1->append('e');
		if (newString1->charAt(0) != 'e') {
			cout << "Test failed" << endl;
			return 1;
		}
		
		copied::StringBuffer *newString3 = new copied::StringBuffer;

		newString3->reserve(1);
		/*int length3 = newString3->length();
		if (length3 != 1) {
		cout << "Test failed" << endl;
		return 1;
		}*/

		newString3->append('e');
		if (newString3->charAt(0) != 'e') {
			cout << "Test failed" << endl;
			return 1;
		}

		refcount::StringBuffer *newString2 = new refcount::StringBuffer;

		newString2->reserve(1);
		/*int length2 = newString2->length();

		if (length2 != 1) {
			cout << "Test failed" << endl;
			return 1;
		}*/

		newString2->append('e');
		if (newString2->charAt(0) != 'e') {
			cout << "Test failed" << endl;
			return 1;
		}

		

		return 0;

	}
	
};


int main(void) {

	testClass test1;
	
	if (test1.test() == 0) {
		cout << "Done" << endl;
	}
}