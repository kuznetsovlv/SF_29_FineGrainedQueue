#include <chrono>
#include <thread>
#include <ctime>
#include <random>
#include <vector>
#include "fine_grained_queue.h"

int main()
{
	srand(time(nullptr));

	FineGrainedQueue queue;
	std::vector<std::thread> threads;

	for(int i = 0; i < 100; ++i)
	{
		threads.push_back(std::thread([&queue, &i](){
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3000));
			queue.insertIntoMiddle(rand() % 20, rand() % i);
		}));
	}

	for(size_t i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	printQueue(queue);

	return 0;
}
