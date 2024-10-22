#ifndef DECODED_H
#define DECODED_H

#include "fstream"
#include <QProgressBar>


using std::ofstream;
using std::ifstream;

void decoded(ifstream &inFile, ofstream &outFile, QProgressBar* progress);

#endif // DECODED_H
