/* 
	2nd homework I use SA to solve the TSP 
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

double** dist;
int city_num;
int* current_solution;

void swap(int& a, int& b) {
    int c = a; a = b; b = c;
}

double rand01() { // generate randomized double between 0 and 1
    return rand() / (double) RAND_MAX;
}

double evaluate(int* solution) { // calculate f(i)
    double result = 0;
    for (int i = 0; i < city_num - 1; ++i) {
        result += dist[solution[i]][solution[i + 1]];
    }
    result += dist[solution[city_num - 1]][solution[0]];
    return result;
}

void generate_neighbour(int* cs) { // randomly generate a neighbour of a state
    int swap_start = 0;
    int swap_end = 0;
    while (swap_start >= swap_end) {
        swap_start = rand() % (city_num - 1) + 1;
        swap_end = rand() % (city_num - 1) + 1;
    }
    for (int i = 0; (swap_start + i) < (swap_end - i); ++i) {
        swap(cs[swap_start + i], cs[swap_end - i]);
    }
}

void load_file() {
    cin >> city_num;
    double** temp = new double*[city_num];
    dist = new double*[city_num];
    current_solution = new int[city_num];
    for (int i = 0; i < city_num; ++ i) {
        char title; cin >> title;
        temp[i] = new double[2];
        dist[i] = new double[city_num];
        cin >> temp[i][0]; cin >> temp[i][1];
        current_solution[i] = i;
    }
    for (int i = 0; i < city_num; ++ i)
        for (int j = 0; j < city_num; ++ j) {
            if (i == j)
                dist[i][j] = 0.0f;
            else {
                double dx = temp[i][0] - temp[j][0];
                double dy = temp[i][1] - temp[j][1];
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
    for (int i = 0; i < city_num; ++ i)
        delete[] temp[i];
    delete[] temp;
}

void tsp() {
    double temperature = 280.0f;
    int loop_max = 100 * city_num;
    double last_solution = -1;
    while (true) {
        double this_solution = evaluate(current_solution);
        for (int i = 0; i < loop_max; ++ i) {
            int* new_solution = new int[city_num];
            memcpy(new_solution, current_solution, sizeof(int) * city_num);
            generate_neighbour(new_solution);
            double neigh_res = evaluate(new_solution);
            if (neigh_res < this_solution || 
                rand01() < exp((this_solution - neigh_res) / temperature)) { // acceptable solution.
                memcpy(current_solution, new_solution, sizeof(int) * city_num);
                this_solution = neigh_res;
            }
            delete[] new_solution;
        }

        for (int i = 0; i < city_num; ++ i) {
            cout << char('A' + current_solution[i]) << ' ';
        }
        cout << this_solution << endl;

        if (abs(this_solution - last_solution) < 1e-6)
            break;
        last_solution = this_solution;
        temperature = temperature * 0.92;
    }
    // current_solution is the final answer.
}

int main(int argc, char const *argv[])
{
    if (argc != 3) return 1;
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    srand((int)time(0));
    load_file();
    tsp();
    
    for (int i = 0; i < city_num; ++ i)
        delete[] dist[i];
    delete[] dist;
    delete[] current_solution;
    return 0;
}
