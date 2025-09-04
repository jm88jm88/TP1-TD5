#include "BacktrackingSolver.h"
#include <vector>
#include <set>
#include <limits>

void backtrack(
    const Instance& instance,
    int idx,
    int N,
    int M,
    int totalCost,
    std::set<int>& coveredSegments,
    std::vector<int>& selectedInfluencers,
    int& minCost,
    std::vector<int>& bestSelected
) {
    // Poda por optimalidad
    if (totalCost >= minCost) return;

    // Solución completa
    if (coveredSegments.size() == N) {
        minCost = totalCost;
        bestSelected = selectedInfluencers;
        return;
    }

    // Sin más influencers
    if (idx == M) return;

    // Poda por factibilidad (simple): si no hay suficientes influencers para cubrir lo que falta, corta
    // (puedes mejorar esto con una unión de segmentos como en tu versión avanzada)

    // 1) No incluir influencer idx
    backtrack(instance, idx + 1, N, M, totalCost, coveredSegments, selectedInfluencers, minCost, bestSelected);

    // 2) Incluir influencer idx
    {
        const std::vector<int>& segmentos = instance.getInfluencerSegments(idx);
        int prevSize = coveredSegments.size();
        for (int s : segmentos) coveredSegments.insert(s);
        selectedInfluencers.push_back(idx);

        backtrack(instance, idx + 1, N, M, totalCost + instance.getInfluencerCost(idx),
                  coveredSegments, selectedInfluencers, minCost, bestSelected);

        selectedInfluencers.pop_back();
        // Deshacer los segmentos agregados
        for (int s : segmentos) {
            if (coveredSegments.size() > prevSize) coveredSegments.erase(s);
        }
    }
}

Solution BacktrackingSolver::solve(const Instance& instance) {
    int N = instance.getNumSegments();
    int M = instance.getNumInfluencers();

    int minCost = std::numeric_limits<int>::max();
    std::vector<int> bestSelected;
    std::set<int> coveredSegments;
    std::vector<int> selectedInfluencers;

    backtrack(instance, 0, N, M, 0, coveredSegments, selectedInfluencers, minCost, bestSelected);

    Solution bestSolution(M);
    if (minCost < std::numeric_limits<int>::max()) {
        bestSolution.setCost(minCost);
        bestSolution.setSelectedInfluencers(bestSelected);
    } else {
        bestSolution.setCost(-1);
        bestSolution.setSelectedInfluencers({});
    }
    return bestSolution;
}