#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int knapsackDP(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W]; 
}

struct Node {
    int level, profit, weight;
    double bound;
};

double bound(Node u, int n, int W, const vector<int>& weights, const vector<int>& values) {
    if (u.weight >= W) return 0;

    double profit_bound = u.profit;
    int total_weight = u.weight;
    int j = u.level + 1;

    while (j < n && total_weight + weights[j] <= W) {
        total_weight += weights[j];
        profit_bound += values[j];
        j++;
    }

    if (j < n)
        profit_bound += (W - total_weight) * values[j] / (double)weights[j];

    return profit_bound;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    double r1 = (double)a.second / a.first;
    double r2 = (double)b.second / b.first;
    return r1 > r2;
}

int knapsackBB(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++)
        items[i] = {weights[i], values[i]};

    sort(items.begin(), items.end(), cmp);

    vector<int> sortedWeights(n);
    vector<int> sortedValues(n);
    for (int i = 0; i < n; i++) {
        sortedWeights[i] = items[i].first;
        sortedValues[i] = items[i].second;
    }

    queue<Node> Q;
    Node u, v;

    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, sortedWeights, sortedValues);
    Q.push(u);

    int maxProfit = 0;

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        v.weight = u.weight + sortedWeights[v.level];
        v.profit = u.profit + sortedValues[v.level];

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, sortedWeights, sortedValues);

        if (v.bound > maxProfit)
            Q.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, sortedWeights, sortedValues);

        if (v.bound > maxProfit)
            Q.push(v);
    }

    return maxProfit;
}

int main() {
    int W = 5; 
    vector<int> weights = {2, 3, 4, 5}; 
    vector<int> values = {3, 4, 5, 8};  
    int n = weights.size();

    cout << "Maximum value in Knapsack (DP): " << knapsackDP(W, weights, values, n) << endl;
    cout << "Maximum value in Knapsack (Branch and Bound): " << knapsackBB(W, weights, values, n) << endl;

    return 0;
}
