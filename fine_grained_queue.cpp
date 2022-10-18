#include <iostream>
#include <mutex>
#include "fine_grained_queue.h"

void printQueue(FineGrainedQueue &queue)
{
	Node *node = queue._head;

	while(node)
	{
		std::cout << node->value;
		node = node->next;

		if(node)
		{
			std::cout << "\t";
		}
	}

	std::cout << std::endl;
}

FineGrainedQueue::FineGrainedQueue():_head(nullptr)
{
}

FineGrainedQueue::~FineGrainedQueue()
{
	Node *node = _head;

	while(node)
	{
		Node *next = node->next;
		delete node;
		node = next;
	}
}

void FineGrainedQueue::insertIntoMiddle(const int value, const size_t pos)
{
	Node *node = new Node();
	node->value = value;
	node->next = nullptr;

	Node *currentNode = nullptr;
	size_t currentPos = 0;

	_queue_mutex.lock();
	if(!_head)
	{
		_head = node;
	}
	else if(!pos)
	{
		_head->node_mutex.lock();
		node->next = _head;
		_head = node;
		_head->next->node_mutex.unlock();
	}
	else
	{
		_head->node_mutex.lock();
		currentNode = _head;
	}
	_queue_mutex.unlock();

	while(currentNode && currentPos < pos)
	{
		++currentPos;
		Node *nextNode = currentNode->next;
		if(nextNode)
		{
			nextNode->node_mutex.lock();
		}

		if(currentPos == pos || !nextNode)
		{
			node->node_mutex.lock();
			currentNode->next = node;
			node->next = nextNode;
			node->node_mutex.unlock();

			if(nextNode)
			{
				nextNode->node_mutex.unlock();
			}
		}

		currentNode->node_mutex.unlock();
		currentNode = nextNode;
	}
}
