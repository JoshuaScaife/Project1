/* 
Calculates the energy of a transition using bohr's model.  
User inputs the atomic number, initial and final quantum numbers and whether the energy should be in J or eV
Repeats given a y/n input 

Joshua Scaife 
07466213976
03/02/2025
*/ 


#include <iostream>
#include <cmath>  

int main() 
{
    const double Ryberg_energy = 13.6;
    double energy;
    int atomic_number, n_initial, n_final;
    char units;


    std::cout << "Enter the atomic number: ";
    std::cin >> atomic_number; 
    std::cout << "Enter the initial quantum number: ";
    std::cin >> n_initial; 
    std::cout << "Enter the final quantum number: ";
    std::cin >> n_final; 
    std::cout << "Would you like the energy in J or eV " << std::endl << "Please enter J or eV: ";
    std::cin >> units;

    energy = Ryberg_energy*pow(atomic_number, 2)*(1/pow(n_final, 2) - 1/pow(n_initial, 2));
    std::cout << energy;

    /* 
    Test line 
    */
}