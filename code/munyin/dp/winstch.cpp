#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 1. Define the structure for a job request
struct Job
{
    int id; // Original index/ID for output
    long long start;
    long long finish;
    long long weight;
};

// Comparison function to sort jobs by finish time
bool compareJobs(const Job &a, const Job &b)
{
    return a.finish < b.finish;
}

// 2. Function to find p(j) using Binary Search
// Finds the index of the latest non-overlapping job before job j.
int findLatestNonOverlapping(const vector<Job> &jobs, int j)
{
    long long current_start_time = jobs[j].start;
    int low = 0;
    int high = j - 1;
    int result = 0; // Index 0 represents the imaginary DP[0] base case

    // Binary search for the latest job i where jobs[i].finish <= current_start_time
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (jobs[mid].finish <= current_start_time)
        {
            // This job is compatible, try to find a later one
            result = mid + 1; // Store 1-based index (for DP array)
            low = mid + 1;
        }
        else
        {
            // This job finishes too late
            high = mid - 1;
        }
    }
    return result;
}

// Global vectors to store DP table and predecessors for backtracking
vector<long long> DP;
vector<int> Predecessor; // To store the index p(j)

void solve()
{
    int N;
    cin >> N;

    vector<Job> jobs(N);
    for (int i = 0; i < N; ++i)
    {
        jobs[i].id = i + 1;
        cin >> jobs[i].start >> jobs[i].finish >> jobs[i].weight;
    }

    // 1. Sort the jobs by finish time
    sort(jobs.begin(), jobs.end(), compareJobs);

    // Initialize DP array (size N+1) and Predecessor array
    // DP[0] is the base case (value 0)
    DP.resize(N + 1, 0);
    Predecessor.resize(N + 1, 0);

    // 2. Fill DP table
    for (int j = 1; j <= N; ++j)
    {
        // Find p(j) (The index of the latest non-overlapping job)
        int p_j = findLatestNonOverlapping(jobs, j - 1); // j-1 is the 0-based index

        // Value if we EXCLUDE job j:
        long long exclude_val = DP[j - 1];

        // Value if we INCLUDE job j:
        long long include_val = jobs[j - 1].weight + DP[p_j];

        // 3. DP Recurrence
        if (include_val > exclude_val)
        {
            DP[j] = include_val;
            Predecessor[j] = p_j; // Store predecessor index p(j) for backtracking
        }
        else
        {
            DP[j] = exclude_val;
            Predecessor[j] = j - 1; // Store predecessor index j-1 for backtracking
        }
    }

    // --- Output ---

    // 1. Maximum Value
    cout << DP[N] << endl;

    // 2. Backtracking to find the set of requests
    vector<int> solution_set;
    int current_index = N;

    while (current_index > 0)
    {
        // If the path came from p(j), the job was included
        if (Predecessor[current_index] == findLatestNonOverlapping(jobs, current_index - 1))
        {
            solution_set.push_back(jobs[current_index - 1].id);
            current_index = Predecessor[current_index]; // Jump back to p(j)
        }
        else
        {
            // If the path came from j-1, the job was excluded
            current_index = Predecessor[current_index]; // Jump back to j-1
        }
    }

    // 2. Number of requests
    cout << solution_set.size() << endl;

    // 3. List of requests (must be sorted arbitrarily)
    sort(solution_set.begin(), solution_set.end());
    for (size_t i = 0; i < solution_set.size(); ++i)
    {
        cout << solution_set[i] << (i == solution_set.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main()
{
    // Optional: for faster I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}