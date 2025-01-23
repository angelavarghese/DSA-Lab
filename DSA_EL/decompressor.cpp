#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void buildCodeTable(Node* root, const string& str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    buildCodeTable(root->left, str + "0", huffmanCode);
    buildCodeTable(root->right, str + "1", huffmanCode);
}

Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    return pq.top();
}

unordered_map<char, int> buildFrequencyMap(const string& inputFilePath) {
    ifstream inputFile(inputFilePath, ios::binary);
    unordered_map<char, int> freqMap;
    char ch;

    while (inputFile.get(ch)) {
        freqMap[ch]++;
    }

    inputFile.close();
    return freqMap;
}

long getFileSize(const string& filePath) {
    ifstream file(filePath, ios::binary | ios::ate);
    return file.tellg();
}

void writeCompressedFile(const string& inputFilePath, const string& outputFilePath, const unordered_map<char, string>& huffmanCode) {
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);

    string encodedData = "";
    char ch;

    while (inputFile.get(ch)) {
        encodedData += huffmanCode.at(ch);
    }

    int padding = 8 - (encodedData.size() % 8);
    for (int i = 0; i < padding; i++) {
        encodedData += "0";
    }

    outputFile.put(static_cast<char>(padding));

    for (size_t i = 0; i < encodedData.size(); i += 8) {
        bitset<8> byte(encodedData.substr(i, 8));
        outputFile.put(static_cast<char>(byte.to_ulong()));
    }

    inputFile.close();
    outputFile.close();
}

void readCompressedFile(const string& compressedFilePath, const string& decompressedFilePath, Node* root) {
    ifstream inputFile(compressedFilePath, ios::binary);
    ofstream outputFile(decompressedFilePath, ios::binary);

    char paddingChar;
    inputFile.get(paddingChar);
    int padding = static_cast<int>(paddingChar);

    string encodedData = "";
    char byte;

    while (inputFile.get(byte)) {
        bitset<8> bits(static_cast<unsigned char>(byte));
        encodedData += bits.to_string();
    }

    encodedData = encodedData.substr(0, encodedData.size() - padding);

    Node* current = root;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            outputFile.put(current->ch);
            current = root;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main(int argc, char *argv[]) {
    string inputFilePath = "input.txt";
    string compressedFilePath = "input.txt.compressed";
    string decompressedFilePath = "input_decompressed.txt";

    long originalSize = getFileSize(inputFilePath);

    unordered_map<char, int> freqMap = buildFrequencyMap(inputFilePath);

    Node* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCode;
    buildCodeTable(root, "", huffmanCode);

    writeCompressedFile(inputFilePath, compressedFilePath, huffmanCode);

    long compressedSize = getFileSize(compressedFilePath);

    cout << "Original file size: " << originalSize << " bytes" << endl;
    cout << "Compressed file size: " << compressedSize << " bytes" << endl;

    readCompressedFile(compressedFilePath, decompressedFilePath, root);

    long decompressedSize = getFileSize(decompressedFilePath);

    cout << "Decompressed file size: " << decompressedSize << " bytes" << endl;
    cout << "File decompressed successfully: " << decompressedFilePath << endl;

    return 0;
}
