#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// A Huffman tree node
struct Node {
    char ch;
    int freq;
    int left, right;
    
    Node(char c, int f) : ch(c), freq(f), left(-1), right(-1) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.freq > b.freq;
    }
};

class Graph {
private:
    vector<Node> nodes;
    unordered_map<char, string> huffmanCodes;
    
    void generateHuffmanCodes(int index, string code) {
        if (index == -1) return;
        
        if (nodes[index].left == -1 && nodes[index].right == -1) {
            huffmanCodes[nodes[index].ch] = code;
        }
        
        generateHuffmanCodes(nodes[index].left, code + "0");
        generateHuffmanCodes(nodes[index].right, code + "1");
    }
    
public:
    void buildHuffmanTree(vector<pair<char, int>>& charFreqs) {
        priority_queue<Node, vector<Node>, Compare> minHeap;
        
        for (auto &p : charFreqs) {
            minHeap.push(Node(p.first, p.second));
        }
        
        while (minHeap.size() > 1) {
            Node left = minHeap.top(); minHeap.pop();
            Node right = minHeap.top(); minHeap.pop();
            
            nodes.push_back(left);
            int leftIndex = nodes.size() - 1;
            
            nodes.push_back(right);
            int rightIndex = nodes.size() - 1;
            
            nodes.emplace_back('\0', left.freq + right.freq);
            nodes.back().left = leftIndex;
            nodes.back().right = rightIndex;
            
            minHeap.push(nodes.back());
        }
        
        generateHuffmanCodes(nodes.size() - 1, "");
    }
    
    void printHuffmanCodes() {
        cout << "Huffman Codes:\n";
        for (auto &p : huffmanCodes) {
            cout << p.first << " : " << p.second << endl;
        }
    }
};

int main() {
    vector<pair<char, int>> charFreqs = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    
    Graph huffmanGraph;
    huffmanGraph.buildHuffmanTree(charFreqs);
    huffmanGraph.printHuffmanCodes();
    
    return 0;
}
