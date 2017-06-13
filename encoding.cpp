// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.

#include "encoding.h"
#include "pqueue.h"

// TODO: include any other headers you need
PriorityQueue<HuffmanNode*> pqueue;
void encodeMapHelper (Map<int, string>& encodingMap, HuffmanNode* encodingTree, string path);

Map<int, int> buildFrequencyTable(istream& input) {

    Map<int, int> freqTable;

    while (true) {

        int nextChar = (int)input.get();
        if (nextChar == EOF) {

            freqTable[PSEUDO_EOF] = 1;
            break;
        }

        if (nextChar != EOF) {

            if (freqTable.containsKey(nextChar)){

                freqTable[nextChar]++;
            } else {

                freqTable[nextChar] = 1;
            }
        }
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {

    //PriorityQueue<HuffmanNode*> pqueue;
    Vector<int> keys = freqTable.keys();

    for (int i = 0; i < freqTable.size(); i++) {                    //Stuff it all in

        HuffmanNode* nodePointer = new HuffmanNode;
        nodePointer->character = keys[i];

        nodePointer->count = freqTable[keys[i]];
        nodePointer->one = NULL;
        nodePointer->zero = NULL;
        pqueue.enqueue(nodePointer, nodePointer->count);
    }


    HuffmanNode* huffTree = treeHelper(pqueue);


    return huffTree;   // this is just a placeholder so it will compile
}

HuffmanNode* treeHelper(PriorityQueue<HuffmanNode*>& pqueue){

    if (pqueue.size() == 1){

        return pqueue.dequeue();

    } else {
        HuffmanNode* pop1 = pqueue.dequeue();
        HuffmanNode* pop2 = pqueue.dequeue();
        HuffmanNode* newNode = new HuffmanNode;
        newNode->character = NOT_A_CHAR;
        newNode->count = pop1->count + pop2->count;
        newNode->one = pop2;
        newNode->zero = pop1;
        pqueue.enqueue(newNode, newNode->count);

        return treeHelper(pqueue);
    }

}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {

    Map<int, string> encodingMap;
    string path = "";
    encodeMapHelper(encodingMap, encodingTree, path);

    return encodingMap;
}

void encodeMapHelper (Map<int, string>& encodingMap, HuffmanNode* encodingTree, string path) {

    if (encodingTree->one == NULL) {

        encodingMap[encodingTree->character] = path;
    } else {

        encodeMapHelper(encodingMap, encodingTree->zero, path + "0");
        encodeMapHelper(encodingMap, encodingTree->one, path + "1");
    }

}

//string encodeHelper()

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {

    string toBeCut = "";

    while (true) {

        int c = input.get();
        toBeCut += encodingMap[c];

        if (c == EOF){
            break;
        }
    }

    cout << "toBeCut = " << toBeCut << endl;

    for (int i = 0; i < toBeCut.length(); i++) {
        string s = toBeCut.substr(i, 1);
        output.writeBit(stringToInteger(s));
    }

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
