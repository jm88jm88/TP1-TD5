#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

class Instance {
private:
    int N; // Numero de segmentos
    int M; // Numero de influencers
   
    std::vector<int> influencerCosts; // Costos de cada influencer
    std::vector<std::vector<int>> influencerSegments; // Segmentos cubiertos por cada influencer


public:
    // Constructor
    Instance();
    
    // Cargar instancia desde archivo
    bool loadFromFile(const std::string& filename);
    
    // Getters
    int getNumSegments() const;
    int getNumInfluencers() const;

    // Getters para costos y segmentos
    int getInfluencerCost(int idx) const { return influencerCosts[idx]; }
    const std::vector<int>& getInfluencerSegments(int idx) const { return influencerSegments[idx]; }
    
    // Mostrar informacion de la instancia
    void printInstance() const;

};

#endif // INSTANCE_H
