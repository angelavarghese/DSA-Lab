#include <bits/stdc++.h>
using namespace std;
# define n 100


class Stack{
    char op[n];
    int topn;
    public:
    Stack(){
        topn = -1;
    }
    char top(){
        if (topn == n)
            return '\0';
        return op[topn];
    }
    void push(char c){
        if(topn == n)
            return;
        topn++;
        op[topn] = c;
        return;
    }
    void pop(){
        if(topn == -1)
            return;
        topn--;
    }
    bool empty(){
        return topn==-1;
    }
};


int prec(char c){
    switch(c){
        case '^': return 6;
        case '%': return 5;
        case '/': return 4;
        case '*': return 3;
        case '+': return 2;
        case '-': return 1;
        default: return 0;
    }
}


string postfix(string s){
    string postfix, token;
    Stack st;
    string res;
    char c;
    s = '('+ s +')';
    for (int i = 0; i < s.length(); i++) {
        c = s[i];
        if(isspace(c) || c == ',')
            continue;
        if(isalpha(c) || isdigit(c)) {
            res += c;
        }
        else if (c == '(') {
            res+= " ";
            st.push(c);
        }
        else if (c == ')') {
            res+= " ";
            while (!st.empty() && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            if (! st.empty()) {
                st.pop(); // pop the '('
            }
        }
        else {
            res+= " ";
            if(s[i] == '^'){
                while ((prec(st.top()) >= prec(c))) {
                    res += st.top();
                    st.pop();
                }
            }
            else{
                while ((prec(st.top()) > prec(c))) {
                    res += st.top();
                    st.pop();
                }
            }
            st.push(c);  
            }
        }
    while (!st.empty()) {
        res+= " ";
        res += st.top();
        st.pop();
    }
    return res;
}
string prefix(string s){
    reverse(s.begin(), s.end());
    Stack st;
    string res;
    char c;


    s = ')'+ s +'(';
    for (int i = 0; i < s.length(); i++) {
        c = s[i];
        if(isspace(c) || c == ',')
            continue;
        else if (isalpha(c)) {
            res += c;
            continue;
        }
        else if (c == ')') {
            st.push(c);
        }
        else if (c == '(') {
            while (!st.empty() && st.top() != ')') {
                res += st.top();
                st.pop();
            }
            if (!st.empty()) {
                st.pop(); // pop the ')'
            }
        }
        else {
            if(c == '^'){
                while ((prec(st.top()) >= prec(c))) {
                    res += st.top();
                    st.pop();
                }
            }
            else{
                while ((prec(st.top()) > prec(c))) {
                    res += st.top();
                    st.pop();
                }
            }
            st.push(c);  
            }
        }
        while(! st.empty()){
            res += st.top();
            st.pop();
        }
    reverse(res.begin(), res.end());
    return res;
}


int main(){
    cout << "Infix to postfix conversion\n\n";
    string exp;
    cout << "ENTER YOUR EXPRESSION: ";
    cin >> exp;

    // 12 13 + 14 11 / * 124 -
    // (13 + (14 - 15)) * 16/17 + 18
    cout << "\nInfix: " << exp << "\nPostfix: " << postfix(exp) << endl;
   // need to make prefix work too
    return 0;
}