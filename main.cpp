#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;


// Lena's linkedlist shit here

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
		else if (expressValid(line) && line.length() > 0){ 
			valid = true; 
		}

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

	// remember to delete index (amount of invalid) if greater than zero
	return 0;
}
