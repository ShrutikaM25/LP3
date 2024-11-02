#include <iostream>
using namespace std;

class Fibonacci {
public:
     long long fibonacciIterative(int n) {
        if (n <= 1)
            return n;

        long long prev2 = 0, prev1 = 1;
        long long current = 0;

        for (int i = 2; i <= n; ++i) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }

        return current;
    }

     long long fibonacciRecursive(int n) {
        if (n <= 1)
            return n;
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Fibonacci calc;

    cout << "Fibonacci (Iterative) of " << n << " is: " << calc.fibonacciIterative(n) << endl;
    cout << "Fibonacci (Recursive) of " << n << " is: " << calc.fibonacciRecursive(n) << endl;

    return 0;
}
