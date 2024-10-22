//
// Created by sorbo on 26.04.2024.
//
#include "decoded.h"
#include "cstring"
#include "bitset"
#include <algorithm>
#include <climits>
#include "functions.h"

using namespace std;

void read_decoding_file(ifstream& ifs, vector<long long int>& frequency, string& message){
    if(!ifs) {
        cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
        return;
    }
    uchar count = 0;
    ifs.read(reinterpret_cast<char*>(&count), sizeof count);

    int i = 0;
    while(i < count) {
        uchar ch;
        ifs.read(reinterpret_cast<char*>(&ch), sizeof ch);
        long long int f = 0;
        ifs.read(reinterpret_cast<char*>(&f), sizeof f);
        frequency[ch] = f;
        ++i;
    }

    int byte_count = 0;
    uchar modulo = 0;
    ifs.read(reinterpret_cast<char *>(&byte_count), sizeof byte_count);
    ifs.read(reinterpret_cast<char *>(&modulo), sizeof modulo);


    i = 0;
    for(; i < byte_count; ++i){
        uchar byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        bitset<CHAR_BIT> b(byte);
        message += b.to_string();
    }

    if(modulo > 0){
        uchar byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        bitset<CHAR_BIT> b(byte);
        message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
    }
}

void make_char(Node::pointer& root, const string& message, string& text) {
    Node::pointer node = root;

    auto found_the_letter = [&text, &root](Node::pointer& n){
        text += n->get_byte();
        n = root;
    };

    for (char ch : message){
        if (ch == '0') {
            if (node->left != nullptr) {
                node = node->left;
                if (node->is_leaf()) {
                    found_the_letter(node);
                }
            }
        }
        else if (ch == '1'){
            if (node->right != nullptr) {
                node = node->right;
                if (node->is_leaf()) {
                    found_the_letter(node);
                }
            }
        }
    }
}

void decoded(ifstream &inFile, ofstream &outFile, QProgressBar* progress) {
    vector<long long int> frequency(0x100, 0);

    const int totalSteps = 5;
    int step = 0;

    string message;
    read_decoding_file(inFile, frequency, message);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    queue_t queue;
    fill_queue(frequency, queue);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    build_tree(queue);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    Node::pointer root = queue.top();
    string text;
    make_char(root, message, text);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    outFile << text;

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;
}
