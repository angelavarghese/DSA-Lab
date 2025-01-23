#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <bitset>
#include <cstring> // For memset

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

void buildCodeTable(Node* root, const string& str, string huffmanCode[]) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[(unsigned char)root->ch] = str;
    }

    buildCodeTable(root->left, str + "0", huffmanCode);
    buildCodeTable(root->right, str + "1", huffmanCode);
}

Node* buildHuffmanTree(int freqArray[]) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < 256; ++i) {
        if (freqArray[i] > 0) {
            pq.push(new Node((char)i, freqArray[i]));
        }
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    return pq.empty() ? nullptr : pq.top();
}

void buildFrequencyArray(const string& inputFilePath, int freqArray[]) {
    ifstream inputFile(inputFilePath, ios::binary);
    char ch;

    while (inputFile.get(ch)) {
        freqArray[(unsigned char)ch]++;
    }

    inputFile.close();
}

long getFileSize(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) return -1;

    long size = 0;
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        size += file.gcount();
    }
    size += file.gcount(); // Add remaining bytes
    file.close();
    return size;
}

void writeCompressedFile(const string& inputFilePath, const string& outputFilePath, const string huffmanCode[]) {
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);

    string encodedData = "";
    char ch;

    while (inputFile.get(ch)) {
        encodedData += huffmanCode[(unsigned char)ch];
    }

    int padding = 8 - (encodedData.size() % 8);
    for (int i = 0; i < padding; i++) {
        encodedData += "0";
    }

    outputFile.put((char)padding);

    for (size_t i = 0; i < encodedData.size(); i += 8) {
        bitset<8> byte(encodedData.substr(i, 8));
        outputFile.put((char)byte.to_ulong());
    }

    inputFile.close();
    outputFile.close();
}

void readCompressedFile(const string& compressedFilePath, const string& decompressedFilePath, Node* root) {
    ifstream inputFile(compressedFilePath, ios::binary);
    ofstream outputFile(decompressedFilePath, ios::binary);

    char paddingChar;
    inputFile.get(paddingChar);
    int padding = (int)paddingChar;

    string encodedData = "";
    char byte;

    while (inputFile.get(byte)) {
        bitset<8> bits((unsigned char)byte);
        encodedData += bits.to_string();
    }

    encodedData = encodedData.substr(0, encodedData.size() - padding);

    Node* current = root;
    for (char bit : encodedData) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            outputFile.put(current->ch);
            current = root;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    cout << "WELCOME TO FILE COMPRESSION USING HUFFMAN CODING!" << endl;
    cout << "Enter the path of the file you want to compress: ";
    string inputFilePath;
    cin >> inputFilePath;
    string compressedFilePath = inputFilePath + ".compressed";
    string decompressedFilePath = "output_decompressed.txt";

    long originalSize = getFileSize(inputFilePath);

    int freqArray[256] = {0}; // Frequency array for all ASCII characters
    buildFrequencyArray(inputFilePath, freqArray);

    Node* root = buildHuffmanTree(freqArray);

    string huffmanCode[256]; // Huffman codes for all ASCII characters
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
