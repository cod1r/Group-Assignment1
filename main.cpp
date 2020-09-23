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
    node* next = nullptr;
	~node(){
		delete next;
	}
};

void print(node **head){
	node* curr=*head;
	while(curr!=nullptr){
		cout << curr->number << " ";
		curr=curr->next;
	}
	cout << endl;
}

void createlist(node** head, int num){
	node* curr=*head;
	node*temp=new node();
	temp->number=num;
	if (*head == nullptr){
		*head = temp;
		curr = temp;
	} else {
		if (curr->number > temp->number){
			temp->next = curr;
			*head = temp;
		}
		else if (curr->next != nullptr && curr->next->number < temp->number){
			createlist(&curr->next, num);
		} else {
			node* tmp = curr->next;
			curr->next = temp;
			temp->next = tmp;
		}
	}
}

void addNode(node*& head, int num){
	node* newN = new node;
	newN->number = num;
	node* copy = head;
	if (head == nullptr){
		head = newN;
		return;
	} else {
		while(copy->next != nullptr){
			copy = copy->next;
		}
		copy->next = newN;
	}
}

void delete_invalid(int pos, node* head, int c) {
	if (head == NULL )
		return;
	if (head != NULL && c < pos) { //goes to next node recursively until position
		c++;
		delete_invalid(pos, head->next, c); //move to next node
	}
	else if (pos == c){
		node* prev = head->next->next; //set prev to the node after next node
		head->next = prev; //set prev node to next node of curr node
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
    return numbers[numbers.size()-1];
}

node* merge(node* one, node* two){
	node* ret = nullptr;
	node* head = nullptr;
	while(one != nullptr && two != nullptr){
		if (one->number < two->number){
			if (ret == nullptr){
				node* tmp = new node;
				tmp->number = one->number;
				ret = tmp;
				head = tmp;
			} else {
				node* tmp = new node;
				tmp->number = one->number;
				ret->next = tmp;
				ret = ret->next;
			}
			one = one->next;
		} else {
			if (ret == nullptr){
				node* tmp = new node;
				tmp->number = two->number;
				ret = tmp;
				head = tmp;
			} else {
				node* tmp = new node;
				tmp->number = two->number;
				ret->next = tmp;
				ret = ret->next;
			}
			two = two->next;
		}
	}
	while(one != nullptr){
		if (ret == nullptr){
			node* tmp = new node;
			tmp->number = one->number;
			ret = tmp;
			head = tmp;
		} else {
			node* tmp = new node;
			tmp->number = one->number;
			ret->next = tmp;
			ret = ret->next;
		}
		one = one->next;
	}
	while(two != nullptr){
		if (ret == nullptr){
			node* tmp = new node;
			tmp->number = two->number;
			ret = tmp;
			head = tmp;
		} else {
			node* tmp = new node;
			tmp->number = two->number;
			ret->next = tmp;
			ret = ret->next;
		}
		two = two->next;
	}
	return head;
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

void remove_opp(node*& first, vector<int>& first_v){
	// checks head for opp value
	if (first == nullptr)
		return;
	for (int x = 0; x < first_v.size(); x++){
		if (first_v[x] + first->number == 0){
			first_v.erase(first_v.begin()+x);
			first = first->next;
			break;
		}
	}
	node* headcpy = first;
	node* temp = first;
	temp = temp->next;
	// checks everything else for opp value
	while(temp != nullptr){
		bool skip = false;
		for (int x = 0; x < first_v.size(); x++){
			if (first_v[x] + temp->number == 0){
				first_v.erase(first_v.begin()+x);
				temp = temp->next;
				headcpy->next = temp;
				skip = true;
				break;
			}
		}
		if (!skip){
			temp = temp->next;
			headcpy = headcpy->next;
		}
	}
}

bool checkIn(node* head, int target){
	while(head != nullptr){
		//cout << head->number << endl;
		if (head->number == target){
			return false;
		}
		head = head->next;
	}
	return true;
}

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

	vector<int> neg_t, neg_s;
	node* travi=nullptr; //for travis
	node* orderT=nullptr;
	node* orderS=nullptr;
	node* scarlet=nullptr; //for scarlet
	node* together=nullptr; //for both

	bool travis = false, scarlett = false;
	int invalid = 0;
	string passcode;
	while(!ifs.eof()){
		string filetext="";
		string line = "";
		getline(ifs, filetext);
		if (filetext.length() == 0)
			continue;
		for (int x = 0; x < filetext.length(); x++){
			if (filetext[x] != ' ' && filetext[x] != '\n' && filetext[x] != '\t')
				line += filetext[x];
		}

		if (line.substr(0, 8) == "Passcode"){
			passcode = line.substr(9, line.length() - 9);
			break;
		}
		if (line == "Travis") { 
			travis = true; 
			scarlett = false; 
		} else if (line == "Scarlet") { 
			scarlett = true; 
			travis = false; 
		} else if (expressValid(line) && line.length() > 0 && travis){ 
			parenthesis(line);
			if(operation(line) >= 0){
				createlist(&travi, operation(line));
				addNode(orderT, operation(line));
			} else {
				neg_t.push_back(operation(line));
			}
		}
		else if(expressValid(line) && line.length() > 0 && scarlett){
			parenthesis(line);
			if (operation(line) >= 0){
				createlist(&scarlet, operation(line));
				addNode(orderS, operation(line));
			} else {
				neg_s.push_back(operation(line));
			}
		} else {
			invalid++;
		}
	}

	vector<int> neg_tc = neg_t;
	vector<int> neg_sc = neg_s;

	// attempts to remove every neg from travis vector. if the vector isn't all empty then we need to try other scarlet
	remove_opp(orderT, neg_t);
	if (neg_t.size() > 0)
		remove_opp(orderS, neg_t);

	remove_opp(orderS, neg_s);
	if (neg_s.size() > 0)
		remove_opp(orderT, neg_s);

	remove_opp(travi, neg_tc);
	if (neg_tc.size() > 0)
		remove_opp(scarlet, neg_tc);

	remove_opp(scarlet, neg_sc);
	if (neg_sc.size() > 0)
		remove_opp(travi, neg_sc);


	together = merge(travi, scarlet);
	print(&together);

	// deletes the index of invalid
	delete_invalid(invalid, together, 1);
	string t = "", s = "", decodedpass = "", actualpass = "";

	while(orderT != nullptr){
		t += to_string(orderT->number);
		if (orderT->next != nullptr)
			t += ',';
		orderT = orderT->next;
	}

	while(orderS != nullptr){
		s += to_string(orderS->number);
		if (orderS->next != nullptr)
			s += ',';
		orderS = orderS->next;
	}
	ofs << "Scarlet: [" << s << "]" << endl;
	ofs << "Travis: [" << t << "]" << endl;
	decodedpass += "|";
	while(together != nullptr){
		decodedpass += " " + to_string(together->number) + " |";
		together = together->next;
	}

	actualpass += "|";
	for (int x = 0; x < passcode.length(); x++){
		actualpass += " " + to_string(passcode[x]-'0') + " |";
	}
	ofs << "Decoded passcode: ";
	ofs << decodedpass << endl;
	ofs << "Actual passcode: ";
	ofs << actualpass << endl;
	if (actualpass == decodedpass)
		ofs << "Treasure unlocked!";
	else
		ofs << "Treasure blocked!";
	return 0;
}
