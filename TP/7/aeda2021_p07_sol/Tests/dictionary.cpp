#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

//to provide
BST<WordMeaning> Dictionary::getWords() const {
	return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
     return word < wm1.word;
}

bool WordMeaning::operator == (const WordMeaning &wm1) const {
     return word == wm1.word;
}


void Dictionary::readDictionary(ifstream &f)
{
     string word1,mean1;
     while (!f.eof())
     {
           getline(f,word1);
           getline(f,mean1);
           WordMeaning wm1(word1,mean1);
           words.insert(wm1);
     }
}


string Dictionary::searchFor(string word) const
{
    WordMeaning wm1(word,"");
    WordMeaning wmx=words.find(wm1);
    WordMeaning wmNotFound("","");
    if (wmx==wmNotFound)
    {
        BSTItrIn<WordMeaning> it(words);
        string wBef="",mBef="";
        while (!it.isAtEnd() && it.retrieve()<wm1)
        {
            wBef=it.retrieve().getWord();
            mBef=it.retrieve().getMeaning();
            it.advance();
        }
        string wAft="",mAft="";
        if (!it.isAtEnd())
        {
            wAft=it.retrieve().getWord();
            mAft=it.retrieve().getMeaning();
        }
        throw WordInexistent(wBef,mBef,wAft,mAft);
    }
    else
        return wmx.getMeaning();
}

bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning wDic = words.find(WordMeaning(word,""));
    if (wDic==WordMeaning("","")) {
        words.insert(WordMeaning(word,newMeaning));
        return false;
    }
    else {
        words.remove(WordMeaning(word,""));
        wDic.setMeaning(newMeaning);
        words.insert(wDic);
        return true;
    }

}

void Dictionary::print() const
{
    BSTItrIn<WordMeaning> it(words);
    while (!it.isAtEnd())
    {
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }

    cout << "novo iterador"<< endl;
    iteratorBST<WordMeaning> it2 = words.begin();
    while (it2!=words.end()) {
         cout << (*it2).getWord() << endl << (*it2).getMeaning() << endl;
         it2++;
    }

}

