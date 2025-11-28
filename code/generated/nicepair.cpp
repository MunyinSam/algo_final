#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// The core data structure: 
// Key: Weight (W_i)
// Value: A map where Key: Color (C_i: 1, 2, or 3), Value: Count
typedef map<long long, map<int, long long>> WeightToColorCounts;

void solve() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, L;
    if (!(cin >> N >> L)) return;

    // Stores the counts of each (Weight, Color) combination.
    WeightToColorCounts counts_map;

    // 1. Read input and populate the map
    for (int i = 0; i < N; ++i) {
        long long W;
        int C; // Color is small (1, 2, or 3)
        cin >> W >> C;
        // Increment the count for this (W, C) pair
        counts_map[W][C]++;
    }

    // Variable to store the final answer
    long long total_nice_pairs = 0;

    // 2. Iterate through the unique weights (W_i) in the map
    // Use an iterator to process the map and prevent double counting.
    for (auto it_i = counts_map.begin(); it_i != counts_map.end(); ++it_i) {
        long long W_i = it_i->first;
        const map<int, long long>& Colors_i = it_i->second;
        
        // Calculate the required complementary weight W_j
        long long W_j = L - W_i;

        // --- Check for valid pairs ---

        // Case A: W_i < W_j (Pairing distinct weight groups)
        // This ensures we only count the pair (W_i, W_j) once (when W_i is the smaller weight).
        if (W_i < W_j) {
            
            // Try to find the complement weight W_j in the map
            auto it_j = counts_map.find(W_j);

            if (it_j != counts_map.end()) {
                const map<int, long long>& Colors_j = it_j->second;

                // Calculate total count of pieces in group i and j
                long long total_i = 0;
                for (auto const& [C, count] : Colors_i) {
                    total_i += count;
                }

                long long total_j = 0;
                for (auto const& [C, count] : Colors_j) {
                    total_j += count;
                }

                // Total possible pairs (ignoring color constraints): |P_i| * |P_j|
                long long total_pairs = total_i * total_j;

                // Count bad pairs (pairs with the same color: (1,1), (2,2), (3,3))
                long long bad_pairs = 0;
                
                // Iterate through the three possible colors (1, 2, 3)
                for (int C = 1; C <= 3; ++C) {
                    long long count_i = 0;
                    if (Colors_i.count(C)) {
                        count_i = Colors_i.at(C);
                    }
                    
                    long long count_j = 0;
                    if (Colors_j.count(C)) {
                        count_j = Colors_j.at(C);
                    }
                    
                    bad_pairs += count_i * count_j;
                }

                // Nice pairs = Total pairs - Bad pairs
                total_nice_pairs += (total_pairs - bad_pairs);
            }
        } 
        
        // Case B: W_i = W_j (Pairing within the same weight group: W_i = L/2)
        // This only happens when L is even.
        else if (W_i * 2 == L) {
            
            // Calculate total count of pieces in this weight group
            long long total_i = 0;
            for (auto const& [C, count] : Colors_i) {
                total_i += count;
            }

            // Total possible distinct pairs (ignoring color constraints): |P_i| * (|P_i| - 1) / 2
            // We calculate |P_i| * (|P_i| - 1) first and divide by 2 later.
            long long total_combinations = total_i * (total_i - 1);
            
            // Count bad pairs (pairs with the same color)
            long long bad_combinations = 0;
            
            for (int C = 1; C <= 3; ++C) {
                if (Colors_i.count(C)) {
                    long long count_c = Colors_i.at(C);
                    // Pairs of same color: count_c * (count_c - 1)
                    bad_combinations += count_c * (count_c - 1);
                }
            }

            // Nice pairs = Total combinations - Bad combinations (all divided by 2)
            // Note: total_combinations and bad_combinations are always even, so division by 2 is safe.
            total_nice_pairs += (total_combinations - bad_combinations) / 2;
        }
        
        // Case C: W_i > W_j (already handled when we processed W_j in the earlier part of the loop)
    }

    // 3. Output the result
    cout << total_nice_pairs << "\n";
}

int main() {
    solve();
    return 0;
}