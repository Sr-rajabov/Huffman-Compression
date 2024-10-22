#ifndef ENCODED_H
#define ENCODED_H

#include "fstream"
#include <QProgressBar>

using std::ifstream;
using std::ofstream;


void encoded(ifstream &inFile, ofstream &outFile, QProgressBar* progress);
#endif // ENCODED_H
