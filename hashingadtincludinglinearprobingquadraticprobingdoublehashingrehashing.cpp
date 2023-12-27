#include<iostream>
using namespace std;

class Hash {
	int* arr;
	int size;
	int numberofelements;
	int** newarray;
public:
	Hash() {
		numberofelements = 0;
		size = 15;
		arr = new int[size];
		newarray = new int* [size];
		for (int i = 0; i < size; i++) {
			newarray[i] = new int[size];
			arr[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				newarray[i][j] = 0;
			}
		}
	}
	int getindex(int key) {
		return (key % size);
	}
	int get2ndindex(int key) {
		return 13 - (key % 13);
	}
	void insertitemforlinearprobing(int data) {
		int location;
		location = getindex(data);
		float loadfactor = numberofelements / size;
		if (loadfactor > 0.7) {
			cout << "Hash table is almost full. Performing rehashing..." << endl;
			rehashingforlinearandquadratic();
		}
		while (arr[location] != 0) {
			location = (location + 1) % size;
		}
		arr[location] = data;
		numberofelements++;
	}
	bool recieveitemforlinearprobing(int item) {
		int location;
		int startlocation = getindex(item);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == item || arr[location] == 0) {
				search = false;
			}
			else {
				location = (location + 1) % size;
			}
		} while (location != startlocation && search);

		search = (arr[location] == item);
		return search;
	}
	bool deleteanitemforlinearprobing(int item) {
		int location;
		int startlocation = getindex(item);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == item) {
				search = false;
			}
			else if (arr[location] == 0) {
				search = false;
			}
			else {
				location = (location + 1) % size;
			}
		} while (location != startlocation && search);
		if (!search) {
			arr[location] = -1;
			return true;
		}
		else {
			return false;
		}
	}
	void rehashingforlinearandquadratic() {
		int data, location;
		int oldsize = size;
		int* arr1;
		size *= 2; // Double the size for rehashing
		arr1 = new int[size];
		for (int i = 0; i < size; i++) {
			arr1[i] = 0;
		}
		for (int i = 0; i < oldsize; i++) {
			if (arr[i] != 0 && arr[i] != -1) {
				data = arr[i];
				location = getindex(data);
				while (arr1[location] != 0) {
					location = (location + 1) % size;
				}
				arr1[location] = data;
				numberofelements++;  // Update the count
			}
		}

		delete[] arr;
		arr = arr1;
	}

	void insertitemforquadraticprobing(int data) {
		int location;
		location = getindex(data);
		int i = 0;
		float loadfactor = numberofelements / size;
		if (loadfactor > 0.7) {
			cout << "Hash table is almost full. Performing rehashing..." << endl;
			rehashingforlinearandquadratic();
		}
		while (arr[location] != 0)
		{
			location = (getindex(data) + i * i) % size;
			if (arr[location] != 0) {
				location = (getindex(data) - i * i) % size;
				if (location < 0) {
					location = (location + size) % size;
				}
			}
			i++;
		}
		arr[location] = data;
		numberofelements++;
	}
	bool recieveitemforquadraticprobing(int data) {
		int location, i = 0;
		int startlocation = getindex(data);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == data || arr[location] == 0) {
				search = false;
			}
			else {
				location = (getindex(data) + i * i) % size;
				if (arr[location] != 0) {
					location = (getindex(data) - i * i) % size;
					if (location < 0) {
						location = (location + size) % size;
					}
				}
				i++;
			}
		} while (location != startlocation && search);
		search = (arr[location] == data);
		if (search) {
			return true;
		}
		else {
			return false;
		}
	}
	bool deleteanitemforquadraticprobing(int data) {
		int location, i = 0;
		int startlocation = getindex(data);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == data || arr[location] == 0) {
				search = false;
			}
			else {                           
				location = (getindex(data) + i * i) % size;
				if (arr[location] != 0) {
					location = (getindex(data) - i * i) % size;
					if (location < 0) {
						location = (location + size) % size;
					}
				}
				i++;
			}
		} while (location != startlocation && search);
		search = (arr[location] == data);
		if (search) {
			arr[location] = -1;
			return true;
		}
		else {
			return false;
		}
	}

	bool recieveitemfordoublehashing(int data) {
		int location, startlocation, i = 0;
		startlocation = getindex(data);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == data || arr[location] == 0) {
				search = false;
			}
			else {
				location = (getindex(data) + i * get2ndindex(data)) % size;
			}
		} while (location != startlocation && search);
		search = (arr[location] == data);
		return search;
	}
	bool full() {
		return (numberofelements == size);
	}
	void doublehasinginsertion(int data) {
		int location, i = 0;
		location = getindex(data);
		float loadfactor = static_cast<float> (numberofelements) / size;
		if (loadfactor > 0.7) {
			cout << "Hash table is almost full. Performing rehashing..." << endl;
			rehashingfordoublehashing();
		}
		while (arr[location] != 0) {
			location = (getindex(data) + i * get2ndindex(data)) % size;
			i++;
		}
		arr[location] = data;
		numberofelements++;
	}
	void rehashingfordoublehashing() {
		int data, location;
		int oldsize = size;
		int j = 0;
		int* arr1;
		size *= 2; // Double the size for rehashing
		arr1 = new int[size];
		for (int i = 0; i < size; i++) {
			arr1[i] = 0;
		}
		for (int i = 0; i < oldsize; i++) {
			int j = 0;
			if (arr[i] != 0 && arr[i] != -1) {
				data = arr[i];
				location = getindex(data);
				while (arr1[location] != 0) {
					location = (getindex(data) + j * get2ndindex(data)) % size;
					j++;
				}
				arr1[location] = data;
				numberofelements++;  // Update the count
			}
		}

		delete[] arr;
		arr = arr1;
	}
	bool deleteanitemfordoublehashing(int data) {
		int location, startlocation, i = 0;
		startlocation = getindex(data);
		location = startlocation;
		bool search = true;
		do {
			if (arr[location] == data || arr[location] == 0) {
				search = false;
			}
			else {
				location = (getindex(data) + i * get2ndindex(data)) % size;
			}
		} while (location != startlocation && search);

		search = (arr[location] == data);
		if (search) {
			arr[location] = -1;
			return true;
		}
		else {
			return false;
		}
	}
};

int main() {
	int choice, data, size;
	Hash h;

	do {
		cout << "\n\n1. Linear Probing";
		cout << "\n2. Quadratic Probing";
		cout << "\n3. Double Hashing";
		cout << "\n4. Exit";
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			// Linear Probing functionality
			// Implement the linear probing operations here
			do {
				cout << "\n\n1. Insert an item";
				cout << "\n2. Check if an item exists";
				cout << "\n3. Delete an item";
				cout << "\n4. Exit";
				cout << "\nEnter your choice: ";
				cin >> choice;

				switch (choice) {
				case 1:
					cout << "\nEnter data to be inserted: ";
					cin >> data;
					h.insertitemforlinearprobing(data);
					break;
				case 2:
					cout << "\nEnter item to check: ";
					cin >> data;
					if (h.recieveitemforlinearprobing(data))
						cout << "\nItem found!";
					else
						cout << "\nItem not found!";
					break;
				case 3:
					cout << "\nEnter item to delete: ";
					cin >> data;
					if (h.deleteanitemforlinearprobing(data))
						cout << "\nItem deleted!";
					else
						cout << "\nItem not found!";
					break;
				case 4:
					cout << "\nExiting program...";
					break;
				default:
					cout << "\nInvalid choice! Please enter a valid option.";
				}
			} while (choice != 4);

			break;
		case 2:
			do {
				cout << "\n\n1. Insert an item";
				cout << "\n2. Check if an item exists";
				cout << "\n3. Delete an item";
				cout << "\n4. Exit";
				cout << "\nEnter your choice: ";
				cin >> choice;

				switch (choice) {
				case 1:
					cout << "\nEnter data to be inserted: ";
					cin >> data;
					h.insertitemforquadraticprobing(data);
					break;
				case 2:
					cout << "\nEnter item to check: ";
					cin >> data;
					if (h.recieveitemforquadraticprobing(data))
						cout << "\nItem found!";
					else
						cout << "\nItem not found!";
					break;
				case 3:
					cout << "\nEnter item to delete: ";
					cin >> data;
					if (h.deleteanitemforquadraticprobing(data))
						cout << "\nItem deleted!";
					else
						cout << "\nItem not found!";
					break;
				case 4:
					cout << "\nExiting program...";
					break;
				default:
					cout << "\nInvalid choice! Please enter a valid option.";
				}
			} while (choice != 4);

			break;
		case 3:
			do {
				cout << "\n\n1. Insert an item";
				cout << "\n2. Check if an item exists";
				cout << "\n3. Delete an item";
				cout << "\n4. Exit";
				cout << "\nEnter your choice: ";
				cin >> choice;

				switch (choice) {
				case 1:
					cout << "\nEnter data to be inserted: ";
					cin >> data;
					while (data != -1) {
						h.doublehasinginsertion(data);
						cin >> data;
					}

					break;
				case 2:
					cout << "\nEnter item to check: ";
					cin >> data;
					if (h.recieveitemfordoublehashing(data))
						cout << "\nItem found!";
					else
						cout << "\nItem not found!";
					break;
				case 3:
					cout << "\nEnter item to delete: ";
					cin >> data;
					if (h.deleteanitemfordoublehashing(data))
						cout << "\nItem deleted!";
					else
						cout << "\nItem not found!";
					break;
				case 4:
					cout << "\nExiting program...";
					break;
				default:
					cout << "\nInvalid choice! Please enter a valid option.";
				}
			} while (choice != 4);

			break;
		case 4:
			cout << "\nExiting program...";
			break;
		default:
			cout << "\nInvalid choice! Please enter a valid option.";
		}
	} while (choice != 4);

	return 0;
}
