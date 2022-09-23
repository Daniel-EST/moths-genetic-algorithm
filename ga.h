#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


extern const int POPULATION;
extern const int MAX_ITER;

struct Moth {
    Moth(int r, int g,  int b);
    int get_fit();
    int r, g, b;
    int x, y;
};

std::vector<Moth*> initialization(const int population_size, std::random_device* generator);

Moth* selection(std::vector<Moth*> population, std::random_device* generator);

Moth* crossover(Moth* moth1, Moth* moth2, std::random_device* generator);

int clamp(int num);

Moth* mutation(Moth* moth, std::random_device* generator);
