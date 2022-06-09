#pragma once

//Author Ilya Ovsyannikov
//task 2
/*Implement a function that returns the i-th prime number (for example, the millionth prime
number is 15485863). Calculations are implemented in a secondary thread. Display in console
calculation progress (on the main thread).*/

using namespace std;

//Integer detection function(if the number is an integer it returns true)
bool isWhole(uint32_t result)
{
	if (result == 1) return false;
	for (size_t i = 2; i < sqrt(result); i++)
	{
		if (result % i == 0)
		{
			return false;
		}
	}
	return true;
}

//Prime number return function
void whole(uint32_t index, uint32_t& result, uint32_t& counter, bool& ready)
{
	while (counter < index)
	{
		result++;
		if (isWhole(result))
		{
			counter++;
		}
	}
	ready = true;
}

//We implement the calculation in the secondary thread and output to the console
uint32_t wholeNumber(uint32_t index)
{
	uint32_t result = 0;
	uint32_t counter = 0;
	bool ready = false;
	thread t2{ whole, ref(index), ref(result), ref(counter), ref(ready) };
	while(!ready)
	{
		system("cls");
		cout << "Progressive: " << counter / (index / 100.0) << "%" << endl;
		this_thread::sleep_for(100ms);
	}
	t2.join();
	system("cls");
	cout << "Progressive: " << counter / (index / 100.0) << "%" << endl;
	return result;

}