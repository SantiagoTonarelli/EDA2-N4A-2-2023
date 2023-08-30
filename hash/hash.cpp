#include <iostream>
using namespace std;

template<class T>
class ClosedHash {
private:
    T** hashTable;
    int length;
    int maxElements;
    int (*hashFunc)(T);

    bool isPrime(int num) {
        if(num <= 1) {
            return false;
        } else {
            for (int i = 2; i <= num/2; i++) {
                if(num % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    int nextPrime(int num) {
        while(!isPrime(++num));
        return num;
    }

public:
    ClosedHash(int maxElements, int (*hashFunc)(T)) {
        this->maxElements = nextPrime(maxElements);
        this->length = 0;
        this->hashTable = new T*[this->maxElements];
        for (int i = 0; i < this->maxElements; i++) {
            this->hashTable[i] = NULL;
        }
        this->hashFunc = hashFunc;
    }

    void add(T data) {
        // if this->length / this->maxElements > 0.5 then resize vec
        int position = this->hashFunc(data) % this->maxElements;
        while(this->hashTable[position]) {
            position = (position+1) % this->maxElements;
        }
        this->hashTable[position] = &data;
    }

    bool exists(T data) {
        int position = this->hashFunc(data) % this->maxElements;
        int initialPosition = position;
        while (this->hashTable[position] != NULL) {
            if (*this->hashTable[position] == data) {
                return true;
            }
            position = (position + 1) % this->maxElements; // Linear, DON'T USE THIS
            
            // If we've checked all positions and circled back, break to avoid infinite loop
            if(position == initialPosition) {
                break;
            }
        }
        return false;
    }

    ~ClosedHash() {
        for (int i =0 ; i< this->maxElements ; i++){
            if(hashTable[i]){
                delete hashTable[i];
                hashTable[i] = NULL;
            }
        }
        delete[] hashTable;
    }
};

// DON'T USE THIS
int simpleHash(int data) {
    return data;
}

int main() {
    ClosedHash<int>* hash = new ClosedHash<int>(10, simpleHash);

    hash->add(3);
    
    cout << "Does '3' exist? " << (hash->exists(3) ? "Yes" : "No") << endl;  // Expected: Yes
    
    delete hash;
    return 0;
}
