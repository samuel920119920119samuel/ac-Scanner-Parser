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
using namespace std;

// whever meets terminal, iterator move to the next token in ts

void Error(string term){
    cout<<term<<" error"<<endl;
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


int main(int argc, const char * argv[]) {
    vector<string> ts = {"id", "assign", "inum", "id", "assign", "id", "plus", "fnum", "print", "id", "$"};
    vector<string>::iterator it = ts.begin();
    Stmts(it);
    cout<<"all done"<<endl;
    return 0;
}
