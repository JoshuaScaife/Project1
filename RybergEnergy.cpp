/* 
Calculates the energy of a transition using bohr's model.  
User inputs the atomic number, initial and final quantum numbers and whether the energy should be in J or eV
Repeats given a y/n input 

Joshua Scaife 
07466213976
06/02/2025
*/ 

#include <iostream>
#include <cmath> 
#include <string>
#include <algorithm> 

const double Ryberg_energy = 13.6;
const double Electron_charge = 1.6*pow(10, -19);

bool check_positive_integer(std::string variable)
{
    /*
    Returns true if it is possible to convert in input variable (string) into a positive integer.  
    Returns false if it is not, with a sutiable error message
    */

    try {
        int integer = std::stoi(variable);
        if (integer <= 0) 
        {
            throw std::out_of_range("");
        }
    }

    // checks for non-integer/string inputs
    catch (std::invalid_argument)
    {
        std::cout << "Invalid Argument: Not an integer" << std::endl;
        return false;
    }

    // checks for non-positive inputs
    catch (std::out_of_range)
    {
        std::cerr << "Out of Range: Negative input or integer overflow" << std::endl;
        return false;
    }

    // Catch-all block for unexpected errors
    catch (...) 
    {
        std::cout << "An unknown error occurred!" << std::endl;
        return false; 
    }

    return true; 
}

int validate_integer(std::string variable)
{
    /*
    Asks the user for an input untill a sutiable positive integer is obtained
    Uses std::stoi to convert string to integer
    */

    bool valid = check_positive_integer(variable); 
    while (valid == false)
    {
        std::cout << "Please enter a valid positive integer: ";
        std::cin >> variable; 
        valid = check_positive_integer(variable); 
    }
    
    int positive_integer = std::stoi(variable);
    return positive_integer;
}

std::string remove_white_space(std::string str) 
{
    /*
    Removes trailing and leading white space from str
    */

    // Remove leading spaces
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) 
    {
        return !std::isspace(ch);
    }));

    // Remove trailing spaces
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) 
    {
        return !std::isspace(ch);
    }).base(), str.end());

    return str;
}

double calculate_energy(int atomic_number, int n_initial, int n_final)
{
    /*
    Calculates the transition energy fron n_intial to n_final in eV 
    */

    double transition_energy;
    transition_energy = Ryberg_energy*pow(atomic_number, 2)*(1/pow(n_final, 2) - 1/pow(n_initial, 2));

    return transition_energy;
}

int main() 
{
    // initialise variables 
    double transition_energy;
    std::string atomic_number, n_initial, n_final, units;
    bool repeat = true;
    std::string repeat_string = " "; 

    while (repeat==true) {

        // take user inputs and validate each indvidually 
        std::cout << std::endl << "Enter the atomic number: ";
        std::cin >> atomic_number; 
        // new integer values stored that can be used in the transiton energy equation
        int atomic_number_int = validate_integer(atomic_number);

        std::cout << "Enter the initial quantum number: ";
        std::cin >> n_initial;
        int n_initial_int = validate_integer(n_initial);

        std::cout << "Enter the final quantum number: ";
        std::cin >> n_final; 
        int n_final_int = validate_integer(n_final);

        std::cout << "Would you like the energy in J or eV? " << std::endl << "Enter 'J' or 'eV': ";
        std::cin >> units;
        
        //convert units to upper case to reduce complexity of later conditional statements
        std::transform(units.begin(), units.end(), units.begin(), ::toupper);
        // removes leading and trailing white spaces
        units = remove_white_space(units); 
        //validate unit input
        while (not((units == "J") or (units == "EV"))) 
        {
            std::cout << "Invalid Unit: please enter either 'J' or 'eV': ";
            std::cin >> units;
            std::transform(units.begin(), units.end(), units.begin(), ::toupper);
            units = remove_white_space(units); 
        } 
        
        //check n_initial > n_final and swap if not
        if (n_initial_int < n_final_int) 
        {
            int temp;
            temp = n_initial_int;
            n_initial_int = n_final_int; 
            n_final_int = temp;
            std::cout << "Initial quantum number < final quantum number so they have been swapped to give positive transtion energy" << std::endl;
        } 
        else if (n_initial_int == n_final_int)
        {
            std::cout << "Initial quantum number = final quantum number so transition energy will be zero" << std::endl;
        }

        //calculate and output transtion energy
        if (units == "EV")
        {
            transition_energy = calculate_energy(atomic_number_int, n_initial_int, n_final_int);
            std::cout << "Transition energy = " << transition_energy << " eV" << std::endl;
        } 
        else 
        {
            transition_energy = Electron_charge*calculate_energy(atomic_number_int, n_initial_int, n_final_int);
            std::cout << "Transition energy = " << transition_energy << " J" << std::endl;
        } 

        // ask the user if they want to repeat the program
        std::cout << std::endl << "Do you want to repeat? Y/N: "; 
        std::cin >> repeat_string; 
        std::transform(repeat_string.begin(), repeat_string.end(), repeat_string.begin(), ::toupper);
        repeat_string = remove_white_space(repeat_string); 
        // validate input
        while (not((repeat_string=="Y") or (repeat_string=="N"))) 
        {
            std::cout << "Invalid Input: please enter either 'Y' or 'N': ";
            std::cin >> repeat_string;
            std::transform(repeat_string.begin(), repeat_string.end(), repeat_string.begin(), ::toupper);
            repeat_string = remove_white_space(repeat_string); 
        }

        // repeat or terminate if Y/N
        if (repeat_string == "Y") 
        {
        } 
        else if (repeat_string == "N") 
        {
            std::cout << "Terminating program" << std::endl;
            repeat = false;
        }

    } 
    return 0; 
}