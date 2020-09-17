#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
    int number;
    node* next;
};

node* split(node*);
node* merge(node*, node*);
node* mergesort(node*);

void parenthesis(string &);
int useOp(int, int, char);
node* operation(string);

int main()
{
    node* list_node = new node();
    string test = "2+{[(6-9)+9]-4}";
    parenthesis(test);
    list_node = operation(test);
    list_node -> next = nullptr;
    cout << list_node -> number;
    return 0;
}


node* mergesort(node* start)
{
    if (start == nullptr || start -> next == nullptr)//recursion condition, and checks if list has 1-no nodes
    {
        return start;
    }

    node* head = start;
    node* a;
    node* b;

    node* middle = split(start);//splits list to 2 and assign the right pointers
    node* middle1 = middle -> next;
    middle -> next = nullptr;

    node* left = mergesort(start);//splits the pieces even more to 2 units and compares them
    node* right = mergesort(middle1);

    return merge(left, right);//puts the list together recursively

}

node* split(node* list)
{
    node* slow;//slow goes 1 unit, and fast goes 2
    node* fast;
    slow = fast = list;

    while (fast -> next != nullptr && fast -> next -> next)
    {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}

node* merge(node* left, node* right) //compares and puts it back together
{
    node* temp = new node();
    node* res = temp;

    while (left != nullptr && right != nullptr)
    {
        if (left -> number < right -> number)
        {
            res -> next = left;
            left = left -> next;
        }
        else
        {
            res -> next = right;
            right = right -> next;
        }
        res = res -> next;
    }
    if (left != nullptr){res -> next = left;}
    if (right != nullptr){res -> next = right;}

    return temp -> next;
}

void parenthesis(string &s) //replaces the brackets and squiggly brackets with parenthesis to operate
{
    int count = 0;
    for (char c : s)
    {
        if (c == '[' || c == '{')
        {
            s.replace(count, 1, "(");
        }
        else if (c == ']' || c == '}')
        {
            s.replace(count, 1, ")");
        }
        count++;
    }
    return;
}

node* operation (string expression)//does math and returns it as a node with data
{
    node* result = new node();
    int total = 0;
    vector<int> numbers;
    vector<char> operators;

    for (char i : expression)
    {
    if(i == '(') {operators.push_back(i);}//checks for open brace
    else if (isdigit(i)){numbers.push_back(i - 48);}//checks for number
    else if (i == ')')
    {
        //if loop finds closing brace, uses all numbers inside brace to evaluate
        while(!operators.empty() && operators.back() != '(')
        {
        int a = numbers.back();
        numbers.pop_back();
        
        int b = numbers.back();
        numbers.pop_back();

        char op = operators.back();
        operators.pop_back();

        numbers.push_back(useOp(a, b, op));
        }
    }
    else//loop finds a regular operator and evaluates it
    {
        while(!operators.empty())
        {
            int a = numbers.back();
            numbers.pop_back();
        
            int b = numbers.back();
            numbers.pop_back();

            char op = operators.back();
            operators.pop_back();

            numbers.push_back(useOp(a, b, op));
        }
    
    }
}


//apply the rest of the operators
while(!operators.empty())
{
    int a = numbers.back();
    numbers.pop_back();
        
    int b = numbers.back();
    numbers.pop_back();

    char op = operators.back();
    operators.pop_back();

    numbers.push_back(useOp(a, b, op));
}
    total = numbers.back();
    result -> number = total;

    return result;

}

int useOp (int left, int right, char op)
{
    switch (op)
    {
        case '+' : return left + right; break;
        case '-' : return left - right; break;
        default : return 0;
    }
    return 0;
}



















