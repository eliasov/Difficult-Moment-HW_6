#pragma once
#include <sstream>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

//Author Ilya Ovsyannikov
//task 3
/* Simulate the following situation. There are two people (2 threads): the owner and the thief. The owner
brings things home (a function that adds a random number to a vector at intervals of 1
times per second). At the same time, each thing has its own value. The thief takes things (function,
which finds the largest number and removes from the vector with a frequency of 1 time in 0.5
seconds), takes the item with the highest value each time.*/

mutex mutexHouse;

//Fu-tion adding things to the house
void master(vector<int>& things)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(1, 100);
	while (!things.empty())
	{
		mutexHouse.lock();
		int new_thing = dis(generator);
		things.push_back(new_thing);
		cout << "There was a thing in the house worth " << new_thing << endl;
		cout << "The cost of things in the house : " << endl;
		for (const auto& t : things)
		{
			cout << t << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(1000ms);
	}
}
//The function finds a larger number and removes from the vector
void thief(vector<int>& things)
{
	while (!things.empty())
	{
		mutexHouse.lock();
		vector<int>::iterator high_price = max_element(things.begin(), things.end());
		cout << "A thief broke into the house and stole things worth: " << *high_price << endl;
		things.erase(high_price);
		cout << "Remaining items for the price : " << endl;
		for (const auto& n : things)
		{
			cout << n << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(0.5s);
	}
}