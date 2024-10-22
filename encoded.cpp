#include "encoded.h"
#include <cstring>
#include <climits>
#include <string>
#include <bitset>
#include "functions.h"
#include "algorithm"

using namespace std;

void make_code(Node::pointer& node, std::string str, std::vector<std::string>& codes) {
    if (node->left != nullptr) {
        make_code(node->left, str + "0", codes);
    }
    if (node->right != nullptr) {
        make_code(node->right, str + "1", codes);
    }

    if (node->left == nullptr && node->right == nullptr){
        node->code(str);
        codes[node->get_byte()] = str;
    }
}


string message2code(ifstream& ifs, const vector<string>& codes) {
    string msg;
    if (!ifs) {
        cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
        return msg;
    }
    while(true) {
        char c;
        ifs.read(&c, 1);
        if (ifs.eof()) {
            break;
        }
        msg += codes[static_cast<uchar>(c)];
    }
    return msg;
}

void write_file(ofstream& ofs, vector<long long int>& frequency, const string& message) {
    if(!ofs) {
        cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
        return;
    }

    uchar count = count_if(frequency.begin(), frequency.end(), [](const int& value) {
        return value != 0;
    });
    ofs.write(reinterpret_cast<char*>(&count), sizeof(count));
    uchar index{0};
    for_each(frequency.begin(), frequency.end(), [&index, &ofs](long long int& value) {
        if (value != 0){
            ofs.write(reinterpret_cast<char*>(&index), sizeof(index));
            ofs.write(reinterpret_cast<char*>(&value), sizeof(value));
        }
        ++index;
    });

    int byte_count = message.size() / CHAR_BIT;
    uchar modulo = message.size() % CHAR_BIT;

    ofs.write(reinterpret_cast<char*>(&byte_count), sizeof(byte_count));
    ofs.write(reinterpret_cast<char*>(&modulo), sizeof(modulo));
    int i = 0;
    for(; i < byte_count; ++i){
        std::bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, CHAR_BIT));
        auto value = static_cast<uchar>(b.to_ulong());
        ofs.write(reinterpret_cast<char*>(&value), sizeof(value));
    }
    if (modulo != 0){
        std::bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, modulo));
        auto value = static_cast<uchar>(b.to_ulong());
        ofs.write(reinterpret_cast<char*>(&value), sizeof(value));
    }
}


void encoded(ifstream &inFile, ofstream &outFile, QProgressBar* progress) {
    if (!inFile || !outFile) {
        cerr << __PRETTY_FUNCTION__ << strerror(errno);
        return;
    }
    const int totalSteps = 6;
    int step = 0;
    vector<long long int> frequency(0x100, 0);
    while(true) {
        char s;
        inFile.read(&s, 1);
        if (inFile.eof()) {
            break;
        }
        frequency[static_cast<unsigned char>(s)]++;
    }

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    queue_t queue;

    fill_queue(frequency, queue);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    build_tree(queue);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    vector<std::string> codes(0x100, "");
    Node::pointer root = queue.top();

    make_code(root, "", codes);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    inFile.clear();
    inFile.seekg(0);

    string message = message2code(inFile, codes);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;

    write_file(outFile, frequency, message);

    progress->setValue((step + 1) * 100 / totalSteps);
    ++step;
}
