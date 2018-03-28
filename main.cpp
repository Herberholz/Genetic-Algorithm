//Cody Herberholz
//10/25/16
//CS441
//Lab 2


#include "ga.h"


//main controls the flow of the genetic algorithm. It leaves the loop and finds
//a solution when the first element found in the array has a fitness of zero.
//this indicates the min was found and the generation with that min is displayed 
//as the solution
int main ()
{

    int fitness = 0; //when zero, will indicate minimum has been found
    int gen_fit = 0; //keeps track of generation fitness
    int count = 1;   //keeps track of generations

    cout << "\nThe purpose of this program is to minimize the function "
            "\nf(x,y,z) = x^2 + y^2 + z^2 using a simple genetic algorithm" << endl;

    GA function;

    function.evaluate();
    fitness = function.selection(0, POP - 1);
    
    //stops loop once an individual fitness is found to be 0
    while(fitness)
    {
        gen_fit = function.gen_fitness();    
        
        cout << "\nFitness: Generation " << count << " = " << gen_fit << "\n\n";
        function.display();
    
        function.crossover(); //mate and create new population
        function.mutation();  //flip bit
        function.evaluate(); //find fitness values of new pop
  
        fitness = function.selection(0, NEWPOP - 1); //sorts array to put most fit first
        function.replace();   //eliminates last half of array to get rid of weakest links
        ++count; 

    }

    cout << "\n\n\nSolution Found!" << endl;
    cout << "Fitness: Generation " << count << " = " << gen_fit << "\n\n";
    function.display();
    

    return 0;
}



