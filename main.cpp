#include "ga.h"
#include <raylib.h>
#include <random>

// static void OnUpdate(void);
// static void Render(void);

int main() 
{
    std::random_device generator;
    std::vector<Moth*> population = initialization(POPULATION, &generator);
    std::vector<Moth*> new_population;
    Moth* parent1;        
    Moth* parent2;
    
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Genetic Algorithms");

    int generation{ 1 };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for(auto it = population.begin(); it != population.end(); ++it) {
                std::uniform_int_distribution<int> generate_x(0, screenWidth);
                std::uniform_int_distribution<int> generate_y(0, screenHeight);
                Color color{(unsigned char) (255 - (*it)->r), (unsigned char) (255 - (*it)->g), (unsigned char) (255 - (*it)->b), 255};
                DrawCircle((*it)->x, (*it)->y, 5.0f, color);
            }

            DrawFPS(10, 10);
            DrawText(TextFormat("Generation %d", generation), 10, 40, 20, RAYWHITE);
            DrawText(TextFormat("Press \"ENTER\" to continue.", generation), 10, 420, 20, RAYWHITE);

        EndDrawing();

        if(IsKeyDown(KEY_ENTER)) {
            for(auto it = population.begin(); it != population.end(); ++it) 
            {
                parent1 = selection(population, &generator);
                parent2 = selection(population, &generator);
                new_population.push_back(mutation(crossover(parent1, parent2, &generator), &generator));
            }

            for(size_t i{}; i < population.size(); i++) 
            {
                delete population[i];
                population[i] = new_population[i];
            }

            new_population.clear();
            generation++;
        }
    }

    CloseWindow();

    return 0;
}
