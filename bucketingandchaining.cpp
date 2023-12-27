#include<iostream>
using namespace std;

struct node {
    int data;
    node* next;
    node(int d) : data(d), next(nullptr) {}
};

class Hash {
    int numofelements;
    static const int size = 15;
    node* hashtable[size];
    int sizeofbucket;
    int numofbuckets;
    int** bucket;

public:
    Hash() {
        numofelements = 0;
        numofbuckets = 15;
        sizeofbucket = 4;
        bucket = new int* [numofbuckets];
        for (int i = 0; i < numofbuckets; i++) {
            bucket[i] = new int[sizeofbucket];
        }
        // Initialize hashtable
        for (int i = 0; i < size; i++) {
            hashtable[i] = nullptr;

        }
        for (int i = 0; i < numofbuckets; i++) {
            for (int j = 0; j < sizeofbucket; j++) {
                bucket[i][j] = 0;
            }
        }
    }

    int getindexforbuckets(int data) {
        return data % numofbuckets;
    }

    void inserinbucket(int data) {
        int index = getindexforbuckets(data);
        int i = 0;
        while (i < sizeofbucket && bucket[index][i] != 0) {
            i++;
        }
        if (bucket[index][i] == 0) {
            bucket[index][i] = data;
        }
        else {
            rehashing();
        }
    }

    void rehashing() {
        int oldsize = numofbuckets;
        numofbuckets *= numofbuckets;
        int** newbucket = new int* [numofbuckets];
        for (int i = 0; i < numofbuckets; i++) {
            newbucket[i] = new int[sizeofbucket];
        }
        for (int i = 0; i < numofbuckets; i++) {
            for (int j = 0; j < sizeofbucket; j++) {
                newbucket[i][j] = 0;
            }
        }
        for (int i = 0; i < oldsize; i++) {
            for (int j = 0; j < sizeofbucket; j++) {
                if (bucket[i][j] != 0) {
                    int data = bucket[i][j];
                    int index = getindexforbuckets(data);
                    int k = 0;
                    while (newbucket[index][k] != 0) {
                        k++;
                    }
                    if (newbucket[index][k] == 0) {
                        newbucket[index][k] = data;
                    }
                }
            }
        }

        for (int i = 0; i < oldsize; i++) {
            delete[] bucket[i];
        }
        delete[] bucket;
        bucket = newbucket;
    }

    void deleteiteminbucket(int data) {
        int index = getindexforbuckets(data);
        int i = 0;
        while (i != sizeofbucket && bucket[index][i] != data) {
            i++;
        }
        if (bucket[index][i] == data) {
            cout << "Element deleted";
            bucket[index][i] = -1;
        }
        else {
            cout << "Element not found";
        }
    }

    int getindex(int data) {
        return data % size;
    }

    void insert(int data) {
        int index = getindex(data);
        if (hashtable[index] == nullptr) {
            hashtable[index] = new node(data);
        }
        else {
            node* newnode = new node(data);
            newnode->next = hashtable[index];
            hashtable[index] = newnode;
        }
    }

    void deleteitem(int data) {
        int index = getindex(data);
        if (hashtable[index] == nullptr) {
            cout << "No value found";
        }
        else {
            node* temp = hashtable[index];
            node* prev = nullptr;
            while (temp != nullptr) {
                if (temp->data == data) {
                    if (prev == nullptr) {
                        hashtable[index] = temp->next;
                        delete temp;
                        cout << "Value is deleted";
                        return;
                    }
                    else {
                        prev->next = temp->next;
                        delete temp;
                        cout << "Value is deleted";
                        return;
                    }
                }
                prev = temp;
                temp = temp->next;
            }
            cout << "Value not found";
        }
    }

    bool search(int data) {
        int index = getindex(data);
        if (hashtable[index] == nullptr) {
            return false;
        }
        else {
            node* temp = hashtable[index];
            while (temp != nullptr) {
                if (temp->data == data) {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
    }
};
int main() {
    int choice, data;
    Hash h, bucketHash; // Assuming you have an instance of the Hash class

    do {
        cout << "\n\n1. Chaining";
        cout << "\n2. Buckets";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Chaining functionality
            do {
                cout << "\n\n1. Insert";
                cout << "\n2. Search";
                cout << "\n3. Delete";
                cout << "\n4. Display";
                cout << "\n5. Go back to the main menu";
                cout << "\nEnter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "\nEnter data to be inserted and -1 to stop: ";
                    cin >> data;
                    while (data != -1) {
                        h.insert(data);
                        cin >> data;
                    }
                    break;
                case 2:
                    cout << "\nEnter item to search: ";
                    cin >> data;
                    if (h.search(data))
                        cout << "\nItem found!";
                    else
                        cout << "\nItem not found!";
                    break;
                case 3:
                    cout << "\nEnter item to delete: ";
                    cin >> data;
                    h.deleteitem(data);
                    break;
                case 4:
                    // Assuming you have a display function in your Hash class
                    cout << "\nDisplaying hash table:\n";
                    // Add a display function in your Hash class and call it here
                    // h.display();
                    break;
                case 5:
                    cout << "\nReturning to the main menu...";
                    break;
                default:
                    cout << "\nInvalid choice! Please enter a valid option.";
                }
            } while (choice != 5);
            break;

        case 2: // Bucket functionality
            do {
                cout << "\n\n1. Insert";
                cout << "\n2. Rehashing";
                cout << "\n3. Delete";
                cout << "\n4. Go back to the main menu";
                cout << "\nEnter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "\nEnter data to be inserted and -1 to stop: ";
                    cin >> data;
                    while (data != -1) {
                        bucketHash.inserinbucket(data);
                        cin >> data;
                    }

                    break;
                case 2:
                    cout << "\nPerforming rehashing...";
                    bucketHash.rehashing();
                    break;
                case 3:
                    cout << "\nEnter item to delete: ";
                    cin >> data;
                    bucketHash.deleteiteminbucket(data);
                    break;
                case 4:
                    cout << "\nReturning to the main menu...";
                    break;
                default:
                    cout << "\nInvalid choice! Please enter a valid option.";
                }
            } while (choice != 4);
            break;

        case 3: // Exit
            cout << "\nExiting program...";
            break;

        default:
            cout << "\nInvalid choice! Please enter a valid option.";
        }

    } while (choice != 3);

    return 0;
}