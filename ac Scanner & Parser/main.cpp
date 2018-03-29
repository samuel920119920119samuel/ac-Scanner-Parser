//
//  main.cpp
//  ac Scanner & Parser
//
//  Created by 王瑞安 on 29/03/2018.
//  Copyright © 2018 RyanWang. All rights reserved.
//

// this version can only parse "Stmts $"
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// whever meets terminal, iterator move to the next token in ts

void Error(string term){
    cout<<term<<" error"<<endl;
    exit(EXIT_SUCCESS);
}

void Match(string inputToken, string correctToken){
    if(inputToken != correctToken)    Error("Match");
    else cout<<inputToken<<" "<<correctToken<<" are the same"<<endl;
}

void Val(vector<string>::iterator &it){
    if(*it == "id")            {Match(*it, "id");   it++;}
    else if(*it == "inum")     {Match(*it, "inum"); it++;}
    else if(*it == "fnum")     {Match(*it, "fnum"); it++;}
    else    Error("Val");
}

void Expr(vector<string>::iterator &it){
    if(*it == "plus"){
        Match(*it, "plus");     it++;
        Val(it);
        Expr(it);
    }
    else if(*it == "minus"){
        Match(*it, "minus");    it++;
        Val(it);
        Expr(it);
    }
    else if(*it == "$"){
        cout<<"Expr $ done"<<endl;
    }
    else    ;   // lamda, go to next token
}

void Stmt(vector<string>::iterator &it){
    if(*it == "id"){
        Match(*it, "id");       it++;
        Match(*it, "assign");   it++;
        Val(it);
        Expr(it);
    }
    else if(*it == "print"){
        Match(*it, "print");    it++;
        Match(*it, "id");       it++;
    }
    else    Error("Stmt");
}

void Stmts(vector<string>::iterator &it){
    if(*it == "id" || *it == "print"){
        Stmt(it);
        Stmts(it);
    }
    // only Stmts in ac will end with $
    else if(*it == "$"){
        cout<<"Stmts $ done"<<endl;
    }
    else    Error("Stmts");
}

////////////////////////// Scanner //////////////////////////
set<char> numSet = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
set<char> idSet = {'a','b','c','d','e','g','h','j','k','l','m','n','o','q','r','s','t','u','v','w','x','y','z'};

struct token{
    string type;
    string value;
};
token makeToken(string type, string value){
    token thisToken = {type, value};
    return thisToken;
}

token ScanDigits(string::iterator &it){
    string type, val;
    while(numSet.count(*it)){
        val = val + *it;
        it++;
    }
    if(*it != '.')  type = "inum";
    else{   //*it == '.'
        type = "fnum";
        val = val + '.';
        it++;
        while(numSet.count(*it)){
            val = val + *it;
            it++;
        }
    }
    return makeToken(type, val);
}

vector<token> Scanner(string code){
    vector<token> ans;
    for(string::iterator it=code.begin(); it!=code.end()+1; ++it){
        while(*it == ' ')   it++;
        if(it == code.end())   ans.push_back(makeToken("$", "$"));
        else if(numSet.count(*it))  ans.push_back(ScanDigits(it));
        else{
            if(idSet.count(*it)) {
                string idStr; idStr = idStr + *it;
                ans.push_back(makeToken("id", idStr));
            }
            else if(*it == 'p') ans.push_back(makeToken("print", "p"));
            else if(*it == '=') ans.push_back(makeToken("assign", "="));
            else if(*it == '+') ans.push_back(makeToken("plus", "+"));
            else if(*it == '-') ans.push_back(makeToken("minus", "-"));
            else    Error("lexical");
        }
    }
    return ans;
}
////////////////////////// Scanner //////////////////////////

int main(int argc, const char * argv[]) {
    // Scanner
    string code;
    getline(cin, code);
    vector<token> ts = Scanner(code);
    
    // Parser
    // extract type in ts and store in tsToken
    // cuz we only need type for parser
    vector<string> tsToken;
    for(vector<token>::iterator it=ts.begin(); it!=ts.end(); it++){
        tsToken.push_back(it->type);
    }
    vector<string>::iterator itToken = tsToken.begin();
    Stmts(itToken);
    cout<<"all done"<<endl;
    
    return 0;
}
