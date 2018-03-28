//Cody Herberholz
//10/25/16
//CS441
//Lab 2


#include "ga.h"


//Initializes the array of struct individual
GA::GA()
{
    srand(time(NULL));
    cout << "Starting Population" << endl;

    for(int i = 0; i < NEWPOP; ++i)
    {
        pop[i] = {};
        if(i < POP)
        {
            for(int j = 0; j < 10; ++j)
            {
                pop[i].x.var[j] = rand() % 2;
                pop[i].y.var[j] = rand() % 2;
                pop[i].z.var[j] = rand() % 2;
            }
        }
    }
    initialized = 0; //shows that it still needs evaluation
}


//Goes through and calculates the value and then fitness based off the value
int GA::evaluate()
{
    int size = 0;
    int x_val;
    int y_val;
    int z_val;
    int exp;
    int start;

    //If this is first time running evaluation set size to original population size
    //otherwise increase to new population size to include offspring
    if(initialized)
    {
        size = NEWPOP;
        start = POP;
    }
    else
    {
        size = POP;
        start = 0;
    }
    for(int i = start; i < size; ++i)
    {
        x_val = 0;
        y_val = 0;
        z_val = 0;
        exp = 9;

        //These three conditionals check if there is a sign bit in front
        if(pop[i].x.var[0])
        {
            x_val += pow(2, exp);
            x_val *= -1;
        }
        if(pop[i].y.var[0])
        {
            y_val += pow(2, exp);
            y_val *= -1;
        }
        if(pop[i].z.var[0])
        {
            z_val += pow(2, exp);
            z_val *= -1;
        }

        --exp;

        //For loop calculates the value by adding 2^exp for each bit with a 1
        //starting at element 1 since element zero was already checked
        for(int j = 1; j < 10; ++j)
        {
            if(pop[i].x.var[j])
                x_val += pow(2, exp);
            if(pop[i].y.var[j])
                y_val += pow(2, exp);
            if(pop[i].z.var[j])
                z_val += pow(2, exp);
            --exp;
        }
        pop[i].x.value = x_val;
        pop[i].y.value = y_val;
        pop[i].z.value = z_val;
        
        //calls function to determin fitness based off value and then stores the
        //equation fitness
        pop[i].x.fitness = fitness(x_val);
        pop[i].y.fitness = fitness(y_val);
        pop[i].z.fitness = fitness(z_val);
        pop[i].sum_fitness = pop[i].x.fitness + pop[i].y.fitness + pop[i].z.fitness;
    }

    //after first evaluation initialized is set to one
    if(!initialized)
        initialized = 1;

    return 0;
}

//Use Quicksort to put pop array in order from most fit(closest to zero) to least fit
int GA::selection(int left, int right)
{
    int i, j;
    int mid = left + (right - left)/2;
    //int pivot = pop[(left + right) / 2].sum_fitness;
    int pivot = pop[mid].sum_fitness;
    i = left;
    j = right;
    individual temp;


    while(i <= j)
    {
        while(pop[i].sum_fitness < pivot)
            ++i;
        while(pop[j].sum_fitness > pivot)
            --j;
        
        //swap both elements
        if(i <= j)
        {
            temp = pop[i];
            pop[i] = pop[j];
            pop[j] = temp;
            ++i;
            --j;
        }
    }
    if(left < j)
        selection(left, j);
    if(i < right)
        selection(i, right);

    return pop[0].sum_fitness;
}


//Randomly selects a split and creates offspring by crossing over parts of each 
//bit string 
int GA::crossover()
{
    int i = 0;
    int k = POP;
    int flip = 0; //helps keep track of when to move i forward and backward
    int split = rand() % 6 + 2; //Splits between elements 2 - 7

    while(i < POP)
    {
        for(int j = 0; j < 10; ++j)
        {
            //Half way through switch to next individual in order crossover
            if(j == split && flip == 0)
            {
                ++i;
                flip = 1;
            }
            else if(j == split)
            {
                --i;
                flip = 0;
            }

            //checks to see if x,y,z are zero and then uses them to create offspring
            exchange(i,j,k);

        }
        ++k;
        if(!flip)
            i += 2;
    }
    return 0;
}


//Goes through the new population created from crossover and flips a bit randomly
//for x, y, and z in each new individual
int GA::mutation()
{
    int random = 0;

    for(int i = POP; i < NEWPOP; ++i)
    {
        random = rand() % 10;
        
        if(pop[i].x.var[random])
            pop[i].x.var[random] = 0;
        else
            pop[i].x.var[random] = 1;
        
        
        if(pop[i].y.var[random])
            pop[i].y.var[random] = 0;
        else
            pop[i].y.var[random] = 1;
        
        
        if(pop[i].z.var[random])
            pop[i].z.var[random] = 0;
        else
            pop[i].z.var[random] = 1;
    }
 
    return 0;
}


//After selection takes place the last half of the array is wiped to get rid of 
//weakest links
int GA::replace()
{
    for(int i = POP; i < NEWPOP; ++i)
    {
        pop[i] = {};
    }
 
    return 0;
}


//Used by crossover to do swapping of values. If a curtain variable is doing well
//fitness wise then that 10 bit encoding is used to improve upon the other variables
void GA::exchange(int i, int j, int k)
{
    
    int x = pop[i].x.fitness;
    int y = pop[i].y.fitness;
    int z = pop[i].z.fitness;
    int min = 0;

    //finds fitness closest to zero
    if(x <= y && x <= z)
        min = x;
    else if(y <= x && y <= z)
        min = y;
    else if(z <= x && z <= y)
        min = z;
    else
        cout << "ERROR: No Min" << endl;

    if(min == x)
    {
        pop[k].x.var[j] = pop[i].x.var[j];
        pop[k].y.var[j] = pop[i].x.var[j];
        pop[k].z.var[j] = pop[i].x.var[j];
    }
    else if(min == y)
    {
        pop[k].x.var[j] = pop[i].y.var[j];
        pop[k].y.var[j] = pop[i].y.var[j];
        pop[k].z.var[j] = pop[i].y.var[j];
    }
    else if(min == z)
    {
        pop[k].x.var[j] = pop[i].z.var[j];
        pop[k].y.var[j] = pop[i].z.var[j];
        pop[k].z.var[j] = pop[i].z.var[j];
    }
    else
    {
        pop[k].x.var[j] = pop[i].x.var[j];
        pop[k].y.var[j] = pop[i].y.var[j];
        pop[k].z.var[j] = pop[i].z.var[j];
    }
}


//Uses a condition in order to determine the fitness based on binary value
int GA::fitness(int val)
{
    int result = 0;

    //first check sets result to zero if there are all 1s or 0s
    //result then increases as the range of the value increases
    if(val == -1 || val == 0) 
        result = 0;
    else if(val >= -15 && val <= 15)
        result = 1;
    else if(val >= -50 && val <= 50)
        result = 2;
    else if(val >= -100 && val <= 100)
        result = 3;
    else if(val >= -150 && val <= 150)
        result = 4;
    else if(val >= -200 && val <= 200)
        result = 5;
    else if(val >= -250 && val <= 250)
        result = 6;
    else if(val >= -250 && val <= 250)
        result = 7;
    else if(val >= -300 && val <= 300)
        result = 8;
    else if(val >= -350 && val <= 350)
        result = 9;
    else if(val >= -400 && val <= 400)
        result = 10;
    else if(val >= -450 && val <= 450)
        result = 11;
    else if(val >= -500 && val <= 500)
        result = 12;
    else if(val >= -512 && val <= 512)
        result = 13;
    else
        cout << "Not a valid value" << endl;

    return result;
}


//Used to return the Total fitness of the current generation
int GA::gen_fitness()
{
    int fitness = 0; //Generation fitness
   
    for(int i = 0; i < POP; ++i)
        fitness += pop[i].sum_fitness;

    return fitness;
}


//Displays the random population, fitness of each individual, and overall fitness of 
//the population at each generation
void GA::display()
{

    for(int i = 0; i < POP; ++i)
    {
        cout << "\t\tIndividual Fitness: " << pop[i].sum_fitness << endl; 

        //Displays x values
        cout << "x: ";
        for(int j = 0; j < 10; ++j)
            cout << pop[i].x.var[j];
        cout << "\tFitness x: " << pop[i].x.fitness;
        cout << "\tx = " << pop[i].x.value << endl;

        //Displays y values
        cout << "y: ";
        for(int p = 0; p < 10; ++p)
            cout << pop[i].y.var[p];
        cout << "\tFitness y: " << pop[i].y.fitness;
        cout << "\ty = " << pop[i].y.value << endl;
        
        //Displays z values
        cout << "z: ";
        for(int k = 0; k < 10; ++k)
            cout << pop[i].z.var[k]; 
        cout << "\tFitness z: " << pop[i].z.fitness;
        cout << "\tz = " << pop[i].z.value << endl << endl;
    }
}
