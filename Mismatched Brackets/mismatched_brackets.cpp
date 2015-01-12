/* the link of the problem statement :
    https://algospot.com/judge/problem/read/BRACKETS2
 */

#include <iostream>
#include <stack>
#include <string.h>

#define MAXLEN 10000

using namespace std;

int n;
char input_str[MAXLEN + 2];

void input_n()
{
    cin >> n;
}

bool solve()
{
    cin >> input_str;
    int len = (int)strlen(input_str);
    stack<char> st;
    
    for (int i = 0; i < len; ++ i)
    {
        char ch = input_str[i];
        
        if (ch != '[' && ch != ']' && ch != '{' && ch != '}' && ch != '(' && ch != ')')
            continue;
        
        while (!st.empty() &&
               ((st.top() == '[' && ch == ']') ||
               (st.top() == '(' && ch == ')') ||
               (st.top() == '{' && ch == '}')))
        {
            st.pop();
            
            if (!st.empty())
            {
                ch = st.top();
                st.pop();
            }
            else
                ch = 0;
        }
        
        if (ch)
            st.push(ch);

    }
    
    return (st.empty());
}

int main(int argc, const char * argv[])
{
    input_n();
    
    while (n > 0)
    {
        if (solve())
            cout << "YES" << endl << flush;
        else
            cout << "NO" << endl << flush;
        -- n;
    }
    
    return 0;
}
