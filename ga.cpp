#include "ga.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

const int POPULATION = 100;
const int MAX_ITER = 1000;

Moth::Moth(int r, int g,  int b) : r{ r }, g{ g }, b{ b } 
{
    static std::random_device generator;

    std::uniform_int_distribution<int> generate_x(10, 790);
    std::uniform_int_distribution<int> generate_y(10, 440);
    x = generate_x(generator);
    y = generate_y(generator);
}
int Moth::get_fit() { return r + g + b; }

std::vector<Moth*> initialization(const int population_size, std::random_device* generator)
{
    std::vector<Moth*> population;
    std::uniform_int_distribution<int> distribution(0, 255);

    for(int i{}; i < population_size; i++)
    {
        population.push_back(new Moth{ distribution(*generator), distribution(*generator), distribution(*generator) });
    }

    return population;
}

Moth* selection(std::vector<Moth*> population, std::random_device* generator) {
    int pop_fit{};

    for(auto it = population.begin(); it != population.end(); ++it) 
    {
        pop_fit += (*it)->get_fit();
    }

    std::uniform_int_distribution<int> distribution(0, pop_fit);

    int weight = distribution(*generator);
    for(auto it = population.begin(); it != population.end(); ++it)
    {
        if(weight < (*it)->get_fit())
        {
            return *it;
        }

        weight -= (*it)->get_fit();
    }
    return *population.begin();
}

Moth* crossover(Moth* moth1, Moth* moth2, std::random_device* generator)
{
    
    std::uniform_real_distribution<float> distribution(0, 1);
    int r =  distribution(*generator) > 0.5 ? moth1->r : moth2->r;
    int g =  distribution(*generator) > 0.5 ? moth1->g : moth2->b;
    int b =  distribution(*generator) > 0.5 ? moth1->b : moth2->g;
    
    Moth* child = new Moth{ r, g, b };
    return child;
}

int clamp(int num)
{
    num = num < 0 ? 0 : num;
    num = num > 255 ? 255 : num;
    return num;
}

Moth* mutation(Moth* moth, std::random_device* generator)
{
    std::uniform_real_distribution<float> distribution(0, 1);
    std::uniform_int_distribution<int> mutation(-15, 15);

    if(distribution(*generator) < 0.15)
    {
        moth->r = clamp(moth->r + mutation(*generator));
        moth->g = clamp(moth->g + mutation(*generator));
        moth->b = clamp(moth->b + mutation(*generator));
    }
    
    return moth;
}

// int main() {
//     std::random_device generator;
//     std::vector<Moth*> population = initialization(POPULATION, &generator);
//     std::vector<Moth*> new_population;

//     Moth* parent1;        
//     Moth* parent2;
//     for(int i{}; i < MAX_ITER; i++){
//         for(auto it = population.begin(); it != population.end(); ++it) {
            
//             std::cout << (*it)->r << " " << (*it)->g << " " << (*it)->b << " - " << (*it)->get_fit() << std::endl;
//             parent1 = selection(population, &generator);
//             parent2 = selection(population, &generator);
//             new_population.push_back(mutation(crossover(parent1, parent2, &generator), &generator));
//         }

//         for(auto it = population.begin(); it != population.end(); ++it) {
//             delete *it;
//         }

//         population = new_population;
//         new_population.clear();

//         std::cout << std::endl;
//     }

//     return 0;
// }