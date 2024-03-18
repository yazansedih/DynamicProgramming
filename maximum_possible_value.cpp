#include <iostream>
#include <vector>

using namespace std;

void maximum_possible_value(int boxs[], int start, int end, int day, int& max_value) {
    if (start > end)
        return;

    if (boxs[start] >= boxs[end]) { 
        // if start > end ==> max += stat; ==> end++ on day++;
        max_value += boxs[end] * day;
        maximum_possible_value(boxs, start, end - 1, day + 1, max_value);
    } else {  
        // else max += end; ==> start++ on day++;
        max_value += boxs[start] * day;
        maximum_possible_value(boxs, start + 1, end, day + 1, max_value);
    }
    // cout << "\tDay: " << day << "\tMax value: " << max_value << endl;
}

int main() {
    int size;
    cin >> size;

    int boxs[size];
    int day = 1;

    for (int i = 0; i < size; i++)
        cin >> boxs[i];

    int maximum = 0;
    maximum_possible_value(boxs, 0, size - 1, day, maximum);
    cout << maximum << endl;

    return 0;
}
