#include <iostream>
#include <deque>
#include <stack>
#include <queue>

using namespace std;

int main(int argc, char const *argv[])
{
    deque<int> transcations;      // empty deque
    transcations.push_back(100);  // add element at the end
    transcations.push_front(200); // add element at the front
    transcations.push_back(300);  // add element at the end
    transcations.push_front(400); // add element at the front

    cout << "transcations: ";
    for (auto it = transcations.begin(); it != transcations.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    for (int i = 0; i <= 3; ++i)
    {
        cout << transcations[i] << " ";
    }
    cout << endl;

    for (int i = 0; i <= 3; ++i)
    {
        cout << transcations.at(i) << " ";
    }
    cout << endl;

    //Use this or the next for front/back print/pop
    // for (int i = 0; i <=3; ++i){
    //     cout << transcations.front() << " ";
    //     transcations.pop_front();
    // }
    // cout << endl;

    for (int i = 0; i <= 3; ++i)
    {
        cout << transcations.back() << " ";
        transcations.pop_back();
    }
    cout << endl;

    //Stack
    stack<int> stk; 
    stk.push(100);
    stk.push(200);
    stk.push(300);
    stk.push(400);

    for (int i = 0; i<=3; ++i){
        cout << stk.top() << " "; 
        stk.pop(); 
    }
    cout << endl;

    //Queue
    queue<int> que; 
    que.push(100);
    que.push(200);
    que.push(300);
    que.push(400);

    for (int i = 0; i<=3; ++i){
        cout << que.front() << " ";
        que.pop(); 
        
    }
    cout << endl;

    return 0;
}
