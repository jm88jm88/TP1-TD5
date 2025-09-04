#include "Instance.h"
#include "Solution.h"
#include <vector>
#include <limits>

// Esta clase resuelve el problema usando programación dinámica con máscaras de bits
class DynamicProgrammingSolver {
public:
    Solution solve(const Instance& instance) {
        int N = instance.getNumSegments();      
        int M = instance.getNumInfluencers();   

        int FULL_MASK = (1 << N) - 1;           // Mascara con todos los segmentos cubiertos

        // estado[mask]: costo minimo para cubrir los segmentos indicados por mask
        std::vector<int> estado(1 << N, std::numeric_limits<int>::max());
        estado[0] = 0; 
        // selected[mask]: influencers usados para llegar a ese mask
        std::vector<std::vector<int>> selected(1 << N);


        for (int mask = 0; mask <= FULL_MASK; ++mask) {
            // Si este estado no es alcanzable -> lo salto
            if (estado[mask] == std::numeric_limits<int>::max()) continue;

            // Pruebo agregar cada influencer
            for (int i = 0; i < M; ++i) {
                int newMask = mask;

                // Para cada segmento que cubre el influencer, activo el bit correspondiente
                const std::vector<int>& segmentos = instance.getInfluencerSegments(i);
                for (size_t j = 0; j < segmentos.size(); ++j) {
                    int seg = segmentos[j]; // Número de segmento cubierto por el influencer
                    // Los segmentos empiezan en 1, así que resto 1 para el bit
                    int bit = seg - 1;
                                                        // Activo el bit correspondiente en la máscara: 1 << bit crea un numero binario donde solo el bit en la posición bit está en 1
                    newMask = newMask | (1 << bit);      // El operador | (OR bit a bit) combina newMask con ese número, poniendo en 1 el bit correspondiente al segmento.
                    
                                                                
                }                                           


                int newCost = estado[mask] + instance.getInfluencerCost(i);
                // Si es mejor que lo que tenía antes, actualizo
                if (newCost < estado[newMask]) {
                    estado[newMask] = newCost;
                    selected[newMask] = selected[mask];
                    selected[newMask].push_back(i);
                }
            }
        }

        // Armo la solución final
        Solution sol(M);
        if (estado[FULL_MASK] < std::numeric_limits<int>::max()) {
            sol.setCost(estado[FULL_MASK]);
            sol.setSelectedInfluencers(selected[FULL_MASK]);
        } else {
            sol.setCost(-1); // No se pudo cubrir todos los segmentos
            sol.setSelectedInfluencers({});
        }
        return sol;
    }
};