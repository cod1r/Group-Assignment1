#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
    int number;
    node *next;
};

node *split(node *);
node *merge(node *, node *);
node *mergesort(node *);

void parenthesis(string &);
int useOp(int, int, char);
int operation(string);

int main()
{
    node *list_node = new node();
	node* test_node = new node();
    string test = "8-{{(1-[0+4]+8)}}";
	string test2 = "8-(9+4)+5";
    parenthesis(test);
	parenthesis(test2);
    list_node -> number = operation(test);
	test_node -> number = operation(test2);
    list_node->next = nullptr;
	test_node->next = nullptr;
    cout << list_node->number << endl;
	cout << test_node->number << endl;
    return 0;
}

node *mergesort(node *start)
{
    if (start == nullptr || start->next == nullptr) //recursion condition, and checks if list has 1-no nodes
    {
        return start;
    }

    node *head = start;
    node *a;
    node *b;

    node *middle = split(start); //splits list to 2 and assign the right pointers
    node *middle1 = middle->next;
    middle->next = nullptr;

    node *left = mergesort(start); //splits the pieces even more to 2 units and compares them
    node *right = mergesort(middle1);

    return merge(left, right); //puts the list together recursively
}

node *split(node *list)
{
    node *slow; //slow goes 1 unit, and fast goes 2
    node *fast;
    slow = fast = list;

    while (fast->next != nullptr && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

node *merge(node *left, node *right) //compares and puts it back together
{
    node *temp = new node();
    node *res = temp;

    while (left != nullptr && right != nullptr)
    {
        if (left->number < right->number)
        {
            res->next = left;
            left = left->next;
        }
        else
        {
            res->next = right;
            right = right->next;
        }
        res = res->next;
    }
    if (left != nullptr)
    {
        res->next = left;
    }
    if (right != nullptr)
    {
        res->next = right;
    }

    return temp->next;
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

int operation(string expression) //does math and returns it as a node with data
{
    vector<int> numbers;
    vector<char> operators;

    for (char i : expression)
    {
		//checks for number
        if (i == '(')
        {
            operators.push_back(i);
        } 
		//checks for open brace
        else if (isdigit(i))
        {
            numbers.push_back(i - 48);
        } 
        else if (i == ')')
        {
            //if loop finds closing brace, uses all numbers inside brace to evaluate
			//prioritizes parenthesis
            while (!operators.empty() && operators.back() != '(')
            {
                int a = numbers.back();
                numbers.pop_back();

                int b = numbers.back();
                numbers.pop_back();

                char op = operators.back();
                operators.pop_back();

                numbers.push_back(useOp(a, b, op));
            }

            if (!operators.empty()) //gets rid of open brace
                operators.pop_back();
        }
        else //loop finds a regular operator and evaluates it
        {
            while (!operators.empty() && operators.back() != '(')
            {
                int a = numbers.back();
                numbers.pop_back();

                int b = numbers.back();
                numbers.pop_back();

                char op = operators.back();
                operators.pop_back();

                numbers.push_back(useOp(a, b, op));
            }
            operators.push_back(i);
        }
    }

    //apply the rest of the operators
    while (!operators.empty())
    {
        int a = numbers.back();
        numbers.pop_back();

        int b = numbers.back();
        numbers.pop_back();

        char op = operators.back();
        operators.pop_back();

        numbers.push_back(useOp(a, b, op));
    }

    return numbers.back();
}

int useOp(int left, int right, char op)
{
    switch (op)
    {
    case '+':
        return left + right;
        break;
    case '-':
        return right - left;
        break;
    default:
        return 0;
    }
    return 0;
}
