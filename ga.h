//Cody Herberholz
//10/25/16
//CS441
//Lab 2


#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;


const int POP = 10; //holds initial population size
const int NEWPOP = 20; //holds total population size with siblings added


//holds fitness, value, and 10 bit encoding for x, y, and z
struct variable
{
    int var[10];
    int fitness;
    int value;
};


//struct that acts as framework for the equation as a whole
struct individual
{
    variable x;
    variable y;
    variable z;
    int sum_fitness;
};


//Genetic Algorithm ADT, holds operations needed in order to minimize the given 
//function and keeps all the work hidden from the client
class GA
{
    public:
        GA(); //initialize population
        int evaluate();
        int selection(int left, int right);
        int crossover();
        int mutation();
        int replace();
        void exchange(int i, int j, int k);
        int fitness(int val);
        int gen_fitness();
        void display(); //displays random population and fitness of each individual

    private:
        int initialized; //keeps track of whether original population was evalutated
        individual pop[NEWPOP]; //array of individual equations
};

