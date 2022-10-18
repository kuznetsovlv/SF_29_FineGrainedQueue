#pragma once
#include <mutex>

class FineGrainedQueue;
void printQueue(FineGrainedQueue&);

struct Node
{
	int value;
	Node *next;
	std::mutex node_mutex;
};

class FineGrainedQueue
{
	private:
	Node *_head;
	std::mutex _queue_mutex;

	public:
	FineGrainedQueue();
	FineGrainedQueue(FineGrainedQueue&) = delete;
	FineGrainedQueue(FineGrainedQueue&&) = delete;
	~FineGrainedQueue();

	void insertIntoMiddle(const int, const size_t);

	FineGrainedQueue& operator=(FineGrainedQueue&) = delete;
	FineGrainedQueue& operator=(FineGrainedQueue&&) = delete;

	friend void printQueue(FineGrainedQueue&);
};
