#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

static void race_track(int car_index)
{
    constexpr static float s_TrackLength = 1e6;
    float progress = 0.0f;

    while (progress < s_TrackLength)
    {
        progress += sqrtf(2.0f);
    }
    std::cout << car_index + 1 << "\n";
    return;
}

static std::vector<int> generate_numeric_sequence(size_t sequence_length)
{
   std::vector<int> sequence(sequence_length);
   for (size_t i = 0; i < sequence_length; ++i)
   {
      sequence[i] = i;
   }
   return sequence;
}

static void threads_qualifying(std::vector<int>& thread_indices)
{
    // Why is this needed? Threads have an advantage depending
    // on the order of which they are started.
    // Therefore, the starting order is randomized.
    std::random_device random_device;
    std::mt19937 mersenne_twister(random_device());

    std::shuffle(thread_indices.begin(), thread_indices.end(), mersenne_twister);
    std::cout << "==== [QUALIFYING RESULTS] ====\n";
    for (size_t i = 0; i < thread_indices.size(); ++i)
    {
        std::cout << i + 1 << ": " << thread_indices[i] + 1 << "\n";
    }
}

int main()
{
    unsigned int thread_max = std::thread::hardware_concurrency();
    std::cout << "Your machine is able to race at maximum " << thread_max << " threads.\n";
    std::cout << "How many threads should compete?: ";

    int n_threads = 0;
    std::cin >> n_threads;

    if (n_threads <= 0 || n_threads > thread_max)
    {
        std::cout << "Error! Invalid number provided.\n";
        return 1;
    }

    std::vector<int> thread_indices = generate_numeric_sequence(n_threads);
    threads_qualifying(thread_indices);

    std::vector<std::thread> threads(n_threads);

    for (int i = 0; i < n_threads; ++i)
    {
        int thread_to_start_index = thread_indices[i];
        std::cout << "Starting thread: " << thread_to_start_index + 1 << "\n";
        threads[thread_to_start_index] = std::thread(race_track, thread_to_start_index);
    }
    for (std::thread& thread : threads)
    {
        thread.join();
    }
}
