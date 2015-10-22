    #include <iostream>
    #include <stdio.h>
    #include <string.h>
    #include "Vector.h"
    using namespace std;
    bool more(int a, int b)
    {
        return a > b;
    }
    int main() {
        Vector <int> * v = new Vector<int>();
        Vector <int> * v2 = new Vector<int>(1);
        v->add(4);
        v2->add(0);
        v2->add(1);
        v2->add(14, 0);
        cout << "here" << endl;
        v2->sort(&more);
        cout << "here" << endl;
        for(int i = 0; i < v2->length(); i++)
        {
            cout << v2->get(i);
        }
        //cout << v2->get(0) << ", " << v2->get(1) << ", " << v2->get(2);
        //cout << endl << v2->contains(4) << ", " << v2->contains(0);

        /*Empty <int> * emp = new Empty<int>();
        List <int> * l1 = new Cons<int>(2, new Cons<int>(3, emp));
        cout << l1->get(1);
        Deque <int> * d1 = new Deque<int>();
        d1->push_back(3);
        d1->push_back(4);
        cout << endl << d1->get(2);
        return 1;*/
    }
