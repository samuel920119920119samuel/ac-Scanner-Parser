//
//  main.cpp
//  ac Scanner & Parser
//
//  Created by 王瑞安 on 29/03/2018.
//  Copyright © 2018 RyanWang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Error(){
    cout<<"error"<<endl;
    return 0;
}

void Match(string inputToken, string correctToken){
    if( inputToken != correctToken )    Error();
    else cout<<inputToken<<" "<<correctToken<<" are the same"<<endl;
}

//void Expr(vector<string>::iterator it){
//    if(
//}

void Val(vector<string>::iterator &it){
    if(*it == "id")     Match(*it, "id");
    else if(*it == "inum")     Match(*it, "inum");
    else if(*it == "fnum")     Match(*it, "fnum");
    else    Error();
}

void Stmt(vector<string>::iterator &it){
    if(*it == "id"){
        Match(*it, "id");   it++;
        Match(*it, "assign");   it++;
        Val(it);
        //        Expr(it++);
    }
    else if(*it == "print"){
        Match(*it, "print");    it++;
        Match(*it, "id");
    }
    else    Error();
}

void Stmts(vector<string>::iterator &it){
    if(*it == "id" || *it == "print"){
        Stmt(it);   it++;
        Stmts(it);
    }
    else{
        if(*it == "$")  cout<<"$ done"<<endl;//do nothing
        else    Error();
    }
    
}


int main(int argc, const char * argv[]) {
    vector<string> ts = {"id", "assign", "inum", "$"};
    vector<string>::iterator it = ts.begin();
    Stmts(it);
    cout<<"all done"<<endl;
    return 0;
}
