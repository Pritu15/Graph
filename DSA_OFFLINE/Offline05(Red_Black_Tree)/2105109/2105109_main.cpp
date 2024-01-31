#include "2105109.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string type;
    int i = 1;
    Map<int, string> m;
    int key;
    string value;
    vector<int> keyStore;
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
    while (cin >> type)
    {
        if (type == "I")
        {

            cin >> key >> value;
            keyStore.push_back(key);
            cout << "Cmd " << i++ << ": I " << key << " " << value << endl;
            m.insert(key, value);
            // cout << endl;
        }
        else if (type == "E")
        {
            cin >> key;
            cout << "Cmd " << i++ << ": E " << key << endl;
            m.Erase(key);
        }
        else if (type == "Em")
        {
            cout << "Cmd " << i++ << ": Em " << endl;
            m.Empty();
        }
        else if (type == "S")
        {
            cout << "Cmd " << i++ << ": S " << endl;
            m.size();
        }
        else if (type == "F")
        {
            cin >> key;

            cout << "Cmd " << i++ << ": F " << key << endl;
            m.Find(key);
        }
        else if (type == "Itr")
        {
            cout << "Cmd " << i++ << ": Itr " << endl;

            m.Iteration();
        }
        else if (type == "Clr")
        {
            // for(auto v:keyStore)
            // {
            //     m.Erase(v);
            // }
            cout << "Cmd " << i++ << ": Clr " << endl;
            // cout << "unsuccessful" << endl;
            m.clear();
        }
        cout << endl;
        cout << endl;
    }
    fclose(stdin);
    fclose(stdout);

    return 0;
}