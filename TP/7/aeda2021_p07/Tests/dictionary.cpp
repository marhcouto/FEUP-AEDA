#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}


bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

bool WordMeaning::operator==(const WordMeaning &wm1) const {
    return word == wm1.getWord();
}


void Dictionary::readDictionary(ifstream &f)
{
    while (!f.eof()) {
        std::string word, meaning;
        std::getline(f, word);
        std::getline(f, meaning);
        WordMeaning element (word, meaning);
        words.insert(element);
    }
}


string Dictionary::searchFor(string word) const
{
    WordMeaning w(word, "");
    WordMeaning w2 = words.find(w);
    WordMeaning wordNotFound("", "");

    if (w2 == wordNotFound) {
        std::string wa, wb, ma, mb;
        iteratorBST<WordMeaning> it;
        for (it = words.begin(); it != words.end(); it++) {
            if (*it < w) {
                wb = (*it).getWord();
                mb = (*it).getMeaning();
            }
            else {
                wa = (*it).getWord();
                ma = (*it).getMeaning();
                break;
            }
        }
        throw WordInexistent(wb, wa, mb, ma);
    }
    else return w2.getMeaning();
}


bool Dictionary::correct(string word, string newMeaning)
{
    if (words.find(WordMeaning(word, newMeaning)) == WordMeaning("", "")) {
        words.insert(WordMeaning(word, newMeaning));
        return false;
    }
    else {
        words.remove(WordMeaning(word, ""));
        words.insert(WordMeaning(word, newMeaning));
        return true;
    }
}


void Dictionary::print() const
{
    iteratorBST<WordMeaning> it = words.begin();
    while (it != words.end()) {
        std::cout << (*it).getWord() << "\n" << (*it).getMeaning() << "\n";
        it++;
    }
}

