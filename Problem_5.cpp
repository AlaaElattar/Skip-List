#include <iostream>
#include <stack>
using namespace std;

/**
 * Alaa Mahmoud Ebrahim 20190105
 * Rana Ihab Ahmed 20190207
 * Omar Khaled Al Haj 20190351
 * */


class Skiplist {
private :
    struct Node {
        Node* next;
        Node* down;
        int val;
        Node(int val1, Node* next1=nullptr, Node* down1=nullptr) : val(val1), next(next1), down(down1){}
    };

public:

    Node* head;
    int numlevels = 1;
    int numcount = 0;
    stack<Node*> stk;           // using stack to assign down pointer after they have all been created


    Skiplist() {
        // keeping -1 as the first element in all levels
        head = new Node(-1);

    }

    bool search(int target) {
        Node* ptr = head;
        while(ptr)
        {
            while(ptr->next && ptr->next->val < target)
                ptr = ptr->next;

            if(ptr->next && ptr->next->val == target) return true;
            ptr = ptr->down;
        }
        return false;
    }

    // get the number of levels for new element
    int getLevel(){
        int ans = 1;
        while(rand()%2 && ans < numlevels)
            ans++;
        return ans;
    }

    void insert(int num) {

        // move down till the last level where we will insert the new element
        int maxlev = getLevel();
        Node* ptr=head;
        for(int i=0; i<numlevels-maxlev; i++)
            ptr = ptr->down;

        while(ptr)
        {
            while( ptr->next && ptr->next->val < num)
                ptr = ptr->next;

            ptr->next = new Node(num,ptr->next,nullptr);
            stk.push(ptr->next);
            ptr = ptr->down;
        }

        Node* prevNode = stk.top(); stk.pop();
        while(!stk.empty())
        {
            stk.top()->down = prevNode;
            prevNode = stk.top();
            stk.pop();
        }

        // keeping the logarithmic bound
        numcount++;
        if(numcount > (1<<(numlevels-1)))
        {
            head = new Node(-1,nullptr,head);
            numlevels++;
        }

    }

    int getlayers()
    {
        cout << numlevels-1<<endl;
    }

    int printLayer(int layer){
        if (layer <= 0){
            cout<<"Wrong Input"<<endl;
            return -1;
        }else if (layer>=numlevels){
            return -1;
        }
        int levels = numlevels;
        Node* ptr=head;

        while (levels != layer){
            levels--;
            ptr = ptr->down;
        }

        ptr = ptr->next;
        while (ptr){
            cout<<ptr->val<<" ";
            ptr = ptr->next;
        }
        cout<<endl;
    }
};

int main()
{
    Skiplist skipList;

    skipList.insert(2);
    skipList.insert(10);
    skipList.insert(15);
    skipList.insert(16);
    skipList.insert(31);
    skipList.insert(71);
    skipList.insert(89);
    skipList.insert(91);
    skipList.insert(96);

    skipList.getlayers();

    skipList.printLayer(1);



}