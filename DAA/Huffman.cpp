#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};


struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; 
    }
};

void printCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) { 
        huffmanCodes[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (const auto& pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* internalNode = new Node('\0', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top(); 
}

unordered_map<char, string> huffmanEncoding(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    Node* root = buildHuffmanTree(freq);

    unordered_map<char, string> huffmanCodes;
    printCodes(root, "", huffmanCodes);

    return huffmanCodes;
}

string encodeText(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedText;
    for (char ch : text) {
        encodedText += huffmanCodes.at(ch);
    }
    return encodedText;
}

int main() {
    string text = "this is an example for huffman encoding";

    unordered_map<char, string> huffmanCodes = huffmanEncoding(text);

    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    string encodedText = encodeText(text, huffmanCodes);
    cout << "\nEncoded Text:\n" << encodedText << endl;

    return 0;
}
