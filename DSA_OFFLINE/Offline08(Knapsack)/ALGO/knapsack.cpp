#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#define INFINTY INT16_MAX
using namespace std;
class knapsack
{
    int itemCount;
    int capacity;
    vector<vector<int>> OPT;
    int maxValue;
    // map<int, int> storeMap;
    map<int, pair<int, int>> weightMap;
    map<int, pair<int, int>> InitialweightMap;
    map<int, pair<int, int>> weightMap1;
    long double theta = 1.0;
    int initialbactrack;
    int initilaVmax;
    int AnswerOfOriginalInstance;
    vector<int> selectedItems;

public:
    knapsack(int itemCount, int capacity)
    {
        this->itemCount = itemCount;
        this->capacity = capacity;
        this->maxValue = INT16_MIN;
        // vector<vector<int>> matrix(itemCount+1, vector<int>());
        for (int i = 1; i <= itemCount; i++)
        {
            int value, weight;
            cin >> value >> weight;
            // storeMap[weight] = value;
            weightMap[i].first = weight;
            weightMap[i].second = value;
            InitialweightMap[i].first = weight;
            InitialweightMap[i].second = value;
            if (value > maxValue)
            {
                this->maxValue = value;
            }
        }

        int rows = itemCount + 1;
        int cols = itemCount * maxValue + 1;

        OPT.resize(rows, vector<int>(cols));
        InitializeOPT();

        weightMap1 = weightMap;
        this->initilaVmax = maxValue;

        // answer();
        // PrintOPT();
        printAnswer(1);
        // ReducedInstanceAnswer();
        // cout << this->itemCount << " " << this->capacity << " " << maxValue << endl;
    }
    void InitializeOPT()
    {
        int rows = itemCount + 1;
        int cols = itemCount * maxValue + 1;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (j == 0)
                {
                    OPT[i][j] = 0;
                }
                else if (i == 0 && j != 0)
                {
                    OPT[i][j] = INT16_MAX;
                }
                else
                {
                    if (j - weightMap[i].second < 0)
                    {
                        OPT[i][j] = OPT[i - 1][j];
                        continue;
                    }
                    OPT[i][j] = min(OPT[i - 1][j], weightMap[i].first + OPT[i - 1][j - weightMap[i].second]);
                }
                // else{
                //     OPT[i][j]=0;
                // }
            }
        }
    }
    int Count(vector<int> &selectedItems)
    {
        int ans = 0;
        for (int i = 0; i < selectedItems.size(); i++)
        {
            // ans+=OPT[selec][]
            ans += (InitialweightMap[selectedItems[i]].second);

            // cout << selectedItems[i] << " ";
        }
        // cout<<ans;
        return ans;
    }
    void answer()
    {
        int rows = itemCount + 1;
        int cols = itemCount * maxValue + 1;
        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                if (j - weightMap[i].second < 0)
                {
                    OPT[i][j] = OPT[i - 1][j];
                    continue;
                }
                OPT[i][j] = min(OPT[i - 1][j], weightMap[i].first + OPT[i - 1][j - weightMap[i].second]);
            }
        }
    }
    void printAnswer(int choice)
    {
        int cols = itemCount * maxValue + 1;
        // vector<pair<int,int>> valueweight;
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> Q;

        for (int j = 1; j < cols; ++j)
        {
            if (OPT[itemCount][j] <= capacity)
            {
                Q.push({j, OPT[itemCount][j]});
            } // OPT[i][j] = min(OPT[i - 1][j], weightMap[i] + OPT[i - 1][j - storeMap[weightMap[i]]]);
        }
        /*
        Answer of reduced instance: 1514
        Answer of reduced instance multiplied by theta: 12724.809523809525
        Indices: 41 39 27 24 19 12 11 10 4
        Answer of original instance (rounded up): 12680
        Used Weight: 649
        Ratio: 1.0016561514195583
        */
        if (choice == 1)
        {
            AnswerOfOriginalInstance = Q.top().first;
            cout << "Original Instance:" << endl;
            cout << "Answer: " << Q.top().first << endl;
            cout << "Used Weight: " << Q.top().second << endl;
            selectedItems.clear();
            initialbactrack = backtrack(Q.top().first, selectedItems);
            print_backtrack(selectedItems);
        }
        else if (choice == 2)
        {
            cout << "Theta:" << theta << endl;
            selectedItems.clear();
            double temp = backtrack(Q.top().first, selectedItems) * theta;
            cout << "Answer of reduced instance: " << Q.top().first << endl;
            cout << "Answer of reduced instance multiplied by theta: " << static_cast<double>(theta) * 1.0 * static_cast<double>(Q.top().first)
                 << endl;
            int ans1 = Count(selectedItems);
            print_backtrack(selectedItems);
            cout << "Answer of original instance (rounded up): " << ans1 << endl;
            // Count(selectedItems);
            // cout << endl;
            cout << "Used Weight: " << Q.top().second << endl;
            cout << "Ratio: " << (double)AnswerOfOriginalInstance / (double)ans1 << endl;
            cout << endl
                 << endl
                 << endl;
        }

        // cout << "weight: " << Q.top().second << " value: " << Q.top().first << endl;
        //  cout<<OPT[itemCount][262]<<endl;
    }
    double backtrack(int capacity, vector<int> &selectedItems)
    {
        int remainingCapacity = capacity;
        // vector<int> selectedItems;
        double ans = 0;

        for (int i = itemCount; i >= 1; --i)
        {
            if (OPT[i][remainingCapacity] != OPT[i - 1][remainingCapacity])
            {
                selectedItems.push_back(i);
                // ans += (theta*OPT[i][remainingCapacity]);
                remainingCapacity -= weightMap[i].second;
            }
        }

        // cout << "Indices: ";
        //  for (int i = 0; i < selectedItems.size(); i++)
        //  {
        //      // ans+=OPT[selec][]
        //      ans += (weightMap[selectedItems[i]].second);

        //     cout << selectedItems[i] << " ";
        // }
        // cout << endl;
        // cout<<ans<<endl;
        return ans;
    }
    void print_backtrack(vector<int> &selectedItems)
    {
        cout << "Indices: ";
        for (int i = 0; i < selectedItems.size(); i++)
        {
            // ans+=OPT[selec][]
            // ans += (weightMap[selectedItems[i]].second);

            cout << selectedItems[i] << " ";
        }
        cout << endl;
    }
    void ReducedInstanceAnswer(long double precisionParameter)
    {
        theta = (precisionParameter * 1.0 * initilaVmax) / (2.0 * itemCount);
        maxValue = INT16_MIN;
        weightMap1 = weightMap;

        for (int i = 1; i <= itemCount; i++)
        {
            weightMap[i].second = ceil(weightMap[i].second / theta);
            // cout << weightMap[i].second << endl;
            if (weightMap[i].second > maxValue)
            {
                maxValue = weightMap[i].second;
            }
        }
        int rows = itemCount + 1;
        int cols = itemCount * maxValue + 1;
        OPT.clear();

        OPT.resize(rows, vector<int>(cols));

        InitializeOPT();
        cout << "Rounded Instance with Eps: " << precisionParameter << endl;
        printAnswer(2);
        weightMap = weightMap1;
    }

    void PrintOPT()
    {
        int rows = itemCount + 1;
        int cols = itemCount * maxValue + 1;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (OPT[i][j] == INT16_MAX)
                {
                    cout << INFINTY << " ";
                    continue;
                }
                cout << OPT[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    knapsack k(n, m);
    // vector<double> arr;
    //  for(int i=0;i<4;i++)
    //  {
    //      arr.push_back()
    //  }
    double arr[] = {0.5, 0.2, 0.1, 0.05};
    // for (auto v : arr)
    // {
    //     cout << v << " ";
    // }
    cout << endl
         << endl;
    for (int i = 0; i < 4; i++)
    {
        k.ReducedInstanceAnswer(arr[i]);
    }

    cout << "Aal is well" << endl;
    return 0;
}