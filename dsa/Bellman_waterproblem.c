// This doesn't use graphs to solve the problem
// It uses Bellman's Principle of Optimality. Do not study this for exam, you may not get marks

#include <stdio.h>

struct statecarrier {
    int a;
    int b;
    int c;
};

int maxcap[] = {10, 7, 4};

// Tracking globally
int visited[11][8][5] = {0};

// Action function
struct statecarrier pour(int action[], int state[]) {
    int availCap = maxcap[action[1]] - state[action[1]];
    if (availCap > state[action[0]]) {
        availCap = state[action[0]];
    } 
    int newState[3] = {state[0], state[1], state[2]};
    newState[action[0]] -= availCap;
    newState[action[1]] += availCap;

    struct statecarrier temp = {newState[0], newState[1], newState[2]};
    return temp;
}

int R(int state[]) {
    return (state[1] == 2 || state[2] == 2);
}

int V(int state[]) {
    
    // If target is acquired
    if (R(state)) {
        return 1;
    }

    // Checking for visited states
    if (visited[state[0]][state[1]][state[2]]) {
        return 0;
    }

    visited[state[0]][state[1]][state[2]] = 1;

    int actionspace[6][2] = {
        {0, 1}, {1, 0},
        {0, 2}, {2, 0},
        {1, 2}, {2, 1}
    };

    for (int i = 0; i < 6; i++) {
        struct statecarrier t = pour(actionspace[i], state);
        int nextState[3] = {t.a, t.b, t.c};
        if (V(nextState)) {
            return 1;
        }
    }
    return 0; // no solution
}

// Main function
int main() {
    int state[3] = {0, 7, 4};
    if (V(state)) {
        printf("Solution exists!\n");
    } else {
        printf("No solution.\n");
    }
    return 0;
}
