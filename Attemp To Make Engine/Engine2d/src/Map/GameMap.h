#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap{

    public:
        void Render(){
            for(unsigned int i=0;i<MapLayer.size();i++){
                MapLayers[i]->Render();
            }
        }

        void Update(){
            for(unsigned int i=0;i<MapLayer.size();i++){
                MapLayers[i]->Update();
            }
        }

        std::vector<Layer*> GetMapLayer(){return MapLayers;}


    private:
        std::vector<Layer*> MapLayers;
};

#endif // GAMEMAP_H
