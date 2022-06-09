#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
#include <chrono>
#include"Task_2.h"
#include "Task_3.h"

//Author Ilya Ovsyannikov

//Task_1
/*Create a thread-safe wrapper around the cout object. Name it pcout. Necessary,
so that multiple threads can access pcout and output information to the console.
Demonstrate how pcout works.*/

using namespace std;
mutex m;

template<typename T>
void pCout(T& info)
{
	lock_guard lg(m);
	cout << "start thead " << info << endl;
	this_thread::sleep_for(0.1s);

}


int main()
{
	cout << "_______________Task_1_______________" << endl;
	setlocale(LC_ALL, "Russian");
	int b = 0;
	for (size_t i = 0, length = 5; i < length; i++)
	{
		this_thread::sleep_for(1s);
		std::thread th1([&]() {pCout("1"); });
		std::thread th2([&]() {pCout("2"); });
		std::thread th3([&]() {pCout("3"); });
		th1.join();
		th2.join();
		th3.join();

		std::cout << std::endl;
	}

	
	cout << "_______________Task_2_______________" << endl;

	uint32_t num = 1000000;
	uint32_t pNum = wholeNumber(num);
	cout << num << "-th prime number = " << pNum << endl;
	cout << endl;


	this_thread::sleep_for(4s);
	cout << "_______________Task_3_______________" << endl;
	vector<int> things = { 95,126,42,84 };
	thread masterThread(master, ref(things));
	thread theifThread(thief, ref(things));
	masterThread.join();
	theifThread.join();
	cout << "A thief has stolen things in your house!" << endl;
	return 0;
}




