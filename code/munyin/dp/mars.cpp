#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

// Define a large constant for infinity
const int INF = numeric_limits<int>::max() / 2;

/**
 * @brief Calculates the minimum drops needed to change one wheel from character 'from' to 'to'.
 * The alphabet is circular (A-Z).
 * @param from The current character (e.g., 'A').
 * @param to The target character (e.g., 'Z').
 * @return int The minimum number of steps (drops).
 */
int get_min_drops(char from, char to) {
    int start = from - 'A'; // 0-25
    int end = to - 'A';     // 0-25
    int diff = abs(start - end);
    
    // The alphabet has 26 characters (0-25).
    // The minimum distance is either the direct difference or moving the other way around the circle.
    return min(diff, 26 - diff);
}

/**
 * @brief Solves the Mars keyboard problem using Dynamic Programming.
 * @param password The input string.
 * @return int The minimum total number of water drops required.
 */
int solve_mars(const string& password) {
    if (password.empty()) return 0;

    int len = password.length();

    // DP table: dp[i][j] = minimum drops to type password[0...i], 
    // where char 'A' + j is the character on the UNUSED wheel.
    // i: index of character being typed (0 to len-1)
    // j: index of the character on the unused wheel (0 to 25, 'A' to 'Z')
    vector<vector<int>> dp(len, vector<int>(26, INF));

    // --- Base Case: Typing the first character (password[0]) ---
    char target0 = password[0];

    // The initial state is: Left='A', Right='A'.
    
    // We must use one of the wheels to type target0. The other wheel remains at 'A'.
    // The unused wheel must be 'A' (index 0).
    for (int unused_char_idx = 0; unused_char_idx < 26; ++unused_char_idx) {
        char unused_char = 'A' + unused_char_idx;
        
        // Cost to type target0 on the Left Wheel (Right Wheel is unused, showing 'A')
        // Left wheel moves from 'A' to target0. Unused wheel (Right) is 'A'.
        int cost_L = get_min_drops('A', target0);
        dp[0][0] = min(dp[0][0], cost_L); // Unused wheel shows 'A' (index 0)

        // Cost to type target0 on the Right Wheel (Left Wheel is unused, showing 'A')
        // Right wheel moves from 'A' to target0. Unused wheel (Left) is 'A'.
        int cost_R = get_min_drops('A', target0);
        dp[0][0] = min(dp[0][0], cost_R); // Unused wheel shows 'A' (index 0)
    }
    // Since both options result in the unused wheel being 'A', the base case simplifies greatly:
    // The minimum cost to type the first char is min_drops('A' -> target0).
    dp[0][target0 - 'A'] = get_min_drops('A', target0); // Error in initial thought, this should be the char on the used wheel!
    // Correct Base Case:
    // Min cost to type P[0] is always moving A -> P[0]. The unused wheel is the one that stays at 'A'.
    // The used wheel now shows P[0].
    dp[0][0] = get_min_drops('A', target0); // The unused wheel is 'A' (index 0)

    // --- DP Transition: From password[i-1] to password[i] ---
    for (int i = 1; i < len; ++i) {
        char target_i = password[i]; // The character to type now
        char target_prev = password[i - 1]; // The character typed previously

        // current_unused_idx is the index of the character on the wheel NOT used to type target_i
        for (int current_unused_idx = 0; current_unused_idx < 26; ++current_unused_idx) {
            char current_unused_char = 'A' + current_unused_idx;
            
            // --- Option 1: Use the Left Wheel to type target_i ---
            // If the Left Wheel types target_i:
            // 1. The Right Wheel (current_unused_char) is the UNUSED wheel in the final state.
            // 2. The Right Wheel must have been the UNUSED wheel in the PREVIOUS state (i-1)
            //    OR the wheel used to type target_prev.
            //
            // Let's simplify: We must transition from a valid state DP[i-1][prev_unused_idx].
            
            for (int prev_unused_idx = 0; prev_unused_idx < 26; ++prev_unused_idx) {
                if (dp[i-1][prev_unused_idx] == INF) continue; // Skip unreachable previous states

                char prev_unused_char = 'A' + prev_unused_idx;
                
                // *** CASE A: Use the Left Wheel to type target_i ***
                
                // 1. Determine the character on the Left Wheel just before typing target_i.
                //    - The previous char (target_prev) must have been typed by the Right Wheel.
                //    - Therefore, the Left Wheel must have been the UNUSED wheel in state (i-1), showing prev_unused_char.
                char L_prev = prev_unused_char; 
                char R_prev = target_prev;

                // 2. Calculate the cost to move Left Wheel: L_prev -> target_i.
                int cost_L_move = get_min_drops(L_prev, target_i);

                // 3. The new state: Left wheel shows target_i (used); Right wheel shows R_prev (unused).
                //    The character on the UNUSED wheel is R_prev (index R_prev - 'A').
                int final_unused_idx = R_prev - 'A';
                
                int total_cost_A = dp[i-1][prev_unused_idx] + cost_L_move;
                
                dp[i][final_unused_idx] = min(dp[i][final_unused_idx], total_cost_A);


                // *** CASE B: Use the Right Wheel to type target_i ***

                // 1. Determine the character on the Right Wheel just before typing target_i.
                //    - The previous char (target_prev) must have been typed by the Left Wheel.
                //    - Therefore, the Right Wheel must have been the UNUSED wheel in state (i-1), showing prev_unused_char.
                char R_start = prev_unused_char;
                char L_start = target_prev;

                // 2. Calculate the cost to move Right Wheel: R_start -> target_i.
                int cost_R_move = get_min_drops(R_start, target_i);

                // 3. The new state: Right wheel shows target_i (used); Left wheel shows L_start (unused).
                //    The character on the UNUSED wheel is L_start (index L_start - 'A').
                final_unused_idx = L_start - 'A';

                int total_cost_B = dp[i-1][prev_unused_idx] + cost_R_move;
                
                dp[i][final_unused_idx] = min(dp[i][final_unused_idx], total_cost_B);
            }
        }
    }

    // --- Find the Minimum Final Cost ---
    int min_drops = INF;
    // The password is fully typed at state dp[len-1].
    // The final total cost is the minimum value across all possible unused wheel characters (j=0 to 25).
    for (int j = 0; j < 26; ++j) {
        min_drops = min(min_drops, dp[len - 1][j]);
    }

    return min_drops;
}


int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    if (!(cin >> test_cases)) return 0;

    for (int i = 1; i <= test_cases; ++i) {
        string password;
        if (!(cin >> password)) break;

        int result = solve_mars(password);

        cout << "Case #" << i << ": " << result << "\n";
    }

    return 0;
}