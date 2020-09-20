#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;


// Lena's linkedlist shit here
struct node
{
    int number;
    node* next;
};

void createlist(node** head, int num){
	node* curr=*head;
	node*temp=new node();
	temp->number=num;
	temp->next=nullptr;
	if(*head == nullptr){
		*head=temp;
		temp=nullptr;
	}
	else{
		
		if(curr->next!=nullptr){	//goes to next node recursively
			createlist(&curr->next, num);
		}
		else
			curr->next=temp;
	}
	
}

void deletepos_neg(node**head , node**head2, int x) { //delete pose/neg pairs
	node* prev = nullptr; //create prev node
	node* curr = *head; //create current node
	node* prev2 = nullptr;
	node* curr2 = *head2;
	int i=0 ,j=0, c=0;
	if (curr == nullptr )
		return;
	while (curr != nullptr){
		if ((curr->number == x || curr->number + x == 0) && i<2 ) //compare
		{
			c++;
			i++;
			if (curr==*head) { //if it's the first node, set to next node
				*head=(*head)->next;
				curr = *head;
				prev = *head;
			}
			else { //if not first node, skip the number
				prev->next = curr->next; 
				curr = curr->next;
			}
		}
		else {
			prev = curr; //if curr->id is not line, then set curr node to prev
			curr = curr->next; //go to next node
			
		}
	}
	//return if found pair
	if (curr2 == nullptr || i==2)
		return;
	//if have not found pair yet, check second list
	while (curr2 != NULL){
			if ((curr2->number == x || curr2->number + x == 0) && j < 1 && c <= 1) 
			{	
				c++;
				j++;
				if (curr2 == *head2) {
					*head2 = (*head2)->next;
					curr2 = *head2;
					prev2 = *head2;
				}
				else {
					prev2->next = curr2->next; 
					curr2 = curr2->next;
				}
			}
			else {
				prev2 = curr2; 
				curr2 = curr2->next; 
			}
		
		}
}

void checkneg(node**head, node**head2){ //check for negatives in each list. if negative then call delete function
node*curr=*head;
node*curr2=*head2;
while(curr != nullptr){
	if(curr->number<0)
		deletepos_neg(&*head, &*head2,curr->number);
	curr=curr->next;
	
 	}
while(curr2!=nullptr){
	if(curr2->number<0)
		deletepos_neg(&*head2, &*head, curr2->number);
	curr2=curr2->next;
 	}
}

void delete_invalid(int pos, node** head, int c) {
		node* curr = *head; //create current node and set head to curr
		if (curr == NULL )
			return;
		if (curr!= NULL && c < pos) { //goes to next node recursively until position
			c++;
			delete_invalid(pos,&curr->next, c); //move to next node
		}
		else{
			node* prev = curr->next->next; //set prev to the node after next node
			delete curr->next; //free memory
			curr->next = prev; //set prev node to next node of curr node
		}
	}

void print(node **head){
	node* curr=*head;
	while(curr!=nullptr){
		cout<<curr->number<<" ";
		curr=curr->next;
	}
}

// jason's expression validator
bool expressValid(string expression){
	string brackets = "";
	for (int x = 0; x < expression.length(); x++){
		if (expression[x] != '(' && expression[x] != ')' && expression[x] != '[' && expression[x] != ']' && expression[x] != '{' && expression[x] != '}'){
			continue;
		}
		brackets += expression[x];
	}

	if (brackets.length() == 0)
		return true;

	int count = 0;
	vector<char> p;
	for (int x = 0; x < brackets.length(); x++){
		if (p.size() > 0 && p[p.size()-1] == '(' && brackets[x] == ')'){
			p.erase(p.begin()+p.size()-1);
			count++;
		}
		else if (p.size() > 0 && p[p.size()-1] == '{' && brackets[x] == '}'){
			p.erase(p.begin()+p.size()-1);
			count++;
		}
		else if (p.size() > 0 && p[p.size()-1] == '[' && brackets[x] == ']'){
			p.erase(p.begin()+p.size()-1);
			count++;
		}
		if (brackets[x] != ')' && brackets[x] != ']' && brackets[x] != '}')
			p.push_back(brackets[x]);
	}
	if ((float)count == (float)brackets.length()/2.0)
		return true;
	return false;
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
// jason's future merge function


// nathan's output to file function

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "Not enough arguments" << endl;
		return 0;
	}
	// argument manager stuff
	 ArgumentManager am(argc, argv);
	 string input = am.get("input");
	 string output = am.get("output");
	 ifstream ifs(input);
	 ofstream ofs(output);

	// ifstream ifs("input11.txt");
	// ofstream ofs("output.txt");

	node *travi=nullptr; //for travis
	node *scarlet=nullptr; //for scarlet
	node* together=nullptr; //for both

	string line="";
	bool travis = false, scarlett = false, valid = false;
	int invalid = 0;
	while(!ifs.eof()){
		getline(ifs, line);
		cout << line << endl;
		// if the line equal travis then we keep on adding to travis until it is scarlett
		if (line == "Travis") { travis = true; scarlett = false; }
		else if (line == "Scarlet") { scarlett = true; travis = false; }
		// if the line is not a name then we check if it is invalid or not. if it is valid then we set valid to true which allows us to add to linkedlists
		else if (expressValid(line) && line.length() > 0 && travis){ 
			valid = true; 
			//createlist(&travi, operation(line));
		}
		else if(expressValid(line) && line.length() > 0 && scarlett)
			//createlist(&scarlet, operation(line));

		if (travis && valid){
			// add to travis
		}
		if (scarlett && valid){
			// add to scarlett
		} else if(!expressValid(line)){
			// incrementing invalid count
			invalid++;
		}
	}
	cout << "Invalid: " << invalid << endl;

	
	//testing deletion of negative/positive pairs
	string s="6 8 9 3 7 9 2 -6 4 8";
	stringstream b(s);
	string u;
	while(b){
		getline(b, u, ' ');
		createlist(&scarlet, stoi(u));
		if(b.eof())
			break;
	}
	string t= "-9 4 9 4 -8 -3 7 2 3";
	stringstream ss(t); 
	string m;
	while(ss){
		getline(ss, m, ' ');
		createlist(&together, stoi(m));
		if(ss.eof())
			break;
	}
	checkneg(&together, &scarlet);
	
	// remember to delete index (amount of invalid) if greater than zero
	int count=1; //to set counter for delete at pos (basically set position at 1)
	delete_invalid(2, &together, count);

	cout<<"Scarlet: ";
	print(&scarlet);
	cout<<endl;
	cout<<"Travis:";
	print(&travi);
	cout<<endl<<"together: ";
	print(&together);
	return 0;
}
