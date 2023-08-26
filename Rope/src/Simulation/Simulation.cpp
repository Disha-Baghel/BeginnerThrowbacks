#include "Simulation.h"

Simulation* Simulation::Instance = nullptr;

Simulation::Simulation(){
    CreateCanvas(800,500,"Rope Simulation");
}

void Simulation::Update(){

}
float time = 0;
void Simulation::Draw(){
    translate(150,250);
    float x = 0;
    float y = 0;

    for(int i=0;i<10;i++){

        float prevx = x;
        float prevy = y;

        int n = i*n + 1;

        float radius = 75 * (4/(n*3.14));

        x += radius * SDL_cos(n * time);
        y += radius * SDL_sin(n * time);

        Ellipse(prevx,prevy,radius);
        Line(x,y,prevx,prevy);
    }
    wave.push_front(y);

    translate(400,250);
    Line(x-250,y,0,wave[0]);

    for(int i=1;i<wave.size();i++){
        Line(i-1,wave[i-1],i,wave[i]);
    }

    time += 0.05;

    if(wave.size()>400){
        wave.pop_back();
    }
}



void Simulation::Event(){

}
