#include <vector>
using namespace std;

template <class Comparable> 
void insertionSort(vector<Comparable> &v)
{
    for (unsigned int p = 1; p < v.size(); p++)
    {
    	Comparable tmp = v[p];
	    int j;
	    for(j = p; j > 0 && tmp < v[j-1]; j--)
    	   v[j] = v[j-1];
    	v[j] = tmp;
    } 
}
template <class Comparable>
void bubbleSort(vector<Comparable> &v){
    bool trade;
    Comparable tmp;
    for (unsigned int p = v.size() - 1; p > 0; p--) {
        trade = false;
        for (unsigned int q = 0; q < p; q++)
            if(v[q] > v[q+1]){
                tmp = v[q];
                v[q] = v[q+1];
                v[q+1] = tmp;
            }
        if(!trade) break;
    }

}

