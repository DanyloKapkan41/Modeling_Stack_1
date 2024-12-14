#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;



bool isValid(string s) {
    stack<char> stack;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        }
        else {
            if (stack.empty()) return false;

            char top = stack.top();
            stack.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }

    return stack.empty();
}

void handleValidateParentheses() {
    string s;
    cout << "Enter a string of parentheses: ";
    cin >> s;

    if (isValid(s)) {
        cout << "Output: true" << endl;
    }
    else {
        cout << "Output: false" << endl;
    }
}


struct tree {
    int x;
    tree* l;
    tree* r;
};

void Add(int x, tree** Node) {
    if ((*Node) == nullptr) {
        (*Node) = new tree;
        (*Node)->l = (*Node)->r = nullptr;
        (*Node)->x = x;
    }
    else if (x < (*Node)->x) {
        Add(x, &(*Node)->l);
    }
    else {
        Add(x, &(*Node)->r);
    }
}

void print(tree* Node) {
    if (Node == nullptr) return;
    print(Node->l);
    cout << Node->x << " ";
    print(Node->r);
}

void counting(tree* Node, int& n) {
    if (Node == nullptr) return;
    counting(Node->l, n);
    n++;
    counting(Node->r, n);
}

void handleBinaryTreeTask() {
    int N, x;
    cout << "Enter number of nodes: ";
    cin >> N;

    tree* head = nullptr;
    cout << "Enter values for the tree:\n";
    for (int i = 0; i < N; i++) {
        cin >> x;
        Add(x, &head);
    }

    cout << "Tree (inorder): ";
    print(head);
    cout << endl;
}

class MinStack {
private:
    stack<int> mainStack;
    stack<int> minStack;

public:
    MinStack() {}

    void push(int val) {
        mainStack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }

    void pop() {
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }

    int top() {
        return mainStack.top();
    }

    int getMin() {
        return minStack.top();
    }
};

class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) {
        stack1.push(x);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int x = stack2.top();
        stack2.pop();
        return x;
    }

    int peek() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        return stack2.top();
    }

    bool empty() {
        return stack1.empty() && stack2.empty();
    }
private:
    stack<int> stack1, stack2;
};

void handleMinStack() {
    MinStack minStack;
    int choice, val, counter=0;
    do {
        cout << "MinStack Operations:\n1. Push\n2. Pop\n3. Top\n4. Get Min\n5. Exit\nChoose an option: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> val;
            minStack.push(val);
            counter++;
            break;
        case 2:
            if (counter != 0)
            {
                minStack.pop();
                cout << "Top element popped.\n";
                counter--;
            }
            else cout << "Stack is empty.\n";
            break;
        case 3:
            if (counter != 0)
            {
            cout << "Top element: " << minStack.top() << endl;
            }
            else cout << "Stack is empty.\n";
            break;
        case 4:
            if (counter != 0)
            {
            cout << "Minimum element: " << minStack.getMin() << endl;
            }
            else cout << "Stack is empty.\n";
            break;
        case 5:
            cout << "Exiting MinStack operations.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

void handleQueueTask() {
    MyQueue queue;
    int choice, val;

    do {
        cout << "Queue Operations (using two stacks):\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Is Empty\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> val;
            queue.push(val);
            cout << val << " pushed to the queue.\n";
            break;
        case 2:
            if (!queue.empty()) {
                val = queue.pop();
                cout << val << " popped from the queue.\n";
            }
            else {
                cout << "Queue is empty.\n";
            }
            break;
        case 3:
            if (!queue.empty()) {
                val = queue.peek();
                cout << "Front element: " << val << endl;
            }
            else {
                cout << "Queue is empty.\n";
            }
            break;
        case 4:
            cout << "Queue is " << (queue.empty() ? "empty" : "not empty") << endl;
            break;
        case 5:
            cout << "Exiting Queue operations.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

void decodeString() {
    string s;
    cout << "Enter the string: ";
    cin >> s;
    stack<pair<int, string>> stack;
    string res = "";
    int k = 0;

    for (char c : s) {
        cout << "Current character: " << c << endl;
        if (isdigit(c)) {
            k = k * 10 + (c - '0');
        }
        else if (c == '[') {
            stack.push({ k, res });
            k = 0;
            res = "";
        }
        else if (c == ']') {
            auto prev = stack.top();
            stack.pop();
            string temp = prev.second;
            for (int i = 0; i < prev.first; i++) {
                res += temp;
            }
            if (!stack.empty()) {
                stack.top().second += res;
            }
            res = "";
        }
        else {
            res += c;
        }
    }
    cout << "Final result: " << res << endl;
}

void evalRPN() {
    string token;
    stack<int> st;

    cout << "Enter the expression in reverse Polish notation(separate tokens with spaces): ";

    while (cin >> token) {
        if (token == "+") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(a + b);
        }
        else if (token == "-") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(a - b);
        }
        else if (token == "*") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(a * b);
        }
        else if (token == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(a / b);
        }
        else if (token == "=") {
            cout << "Result: " << st.top() << endl;
            return;
        }
        else {
            st.push(stoi(token));
        }
    }
    
   
}

void findLongestValidParentheses() {
    string s;

    cout << "Enter line with parentheses: ";
    cin >> s;

    int maxLen = 0;
    stack<int> st;
    st.push(-1); 

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') {
            st.push(i);
        }
        else {
            st.pop();
            if (st.empty()) {
                st.push(i);
            }
            else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }

    cout << "Longest valid parentheses: " << maxLen << endl;
}

int main() {
    int choice;
    while (1)
    {
        cout << "Choose a task to execute (1-8):\n";
        cout << "1. Validate parentheses\n";
        cout << "2. Inorder traversal of a binary tree\n";
        cout << "3. MinStack operations\n";
        cout << "4. Queue using two stacks\n";
        cout << "5. Decode string\n";
        cout << "6. Polish notation\n";
        cout << "7. Longest parentheses\n";
        cout << "8. Exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            handleValidateParentheses();
            break;
        case 2:
            handleBinaryTreeTask();
            break;
        case 3:
            handleMinStack();
            break;
        case 4:
            handleQueueTask();
            break;
        case 5:
            decodeString();
            break;
        case 6:
            evalRPN();
            break;
        case 7:
            findLongestValidParentheses();
            break;
        case 8:
            return 0;
        default:
            cout << "Invalid choice. Please select a valid task." << endl;
        }
    }

    return 0;
}
