#include "Encoder.h"

bool CheckInputDataOnCorrect(const std::vector<uint8_t> input_data)
{
	int counter = 0;
	for (int i = 0; i < input_data.size(); i++)
	{
		if (input_data.at(i) == 0 || input_data.at(i) == 1)
			continue;
		else
			counter++;
	}

	if (counter == 0)
		return true;
	else
		return false;
}

void AddingZeros(std::vector<uint8_t> &input_data)
{
	std::uint8_t zero = 0;

	if (std::fmod(input_data.size(), kNumOfInputElements) != 0)
	{
		std::cout << "Warning: the number of entered symbols is not divisible by 4. Input data will be padded with zeros." << std::endl;

		for (int i = 0; i < std::fmod(input_data.size(), kNumOfInputElements); i++)
		{
			input_data.push_back(zero);
		}
	}
}

void SerialFor(const int &it_begin, const int &it_end, const int &step, std::function<void(int)> for_function)
{
	for (int i = it_begin; i < it_end; i += step)
	{
		for_function(i);
	}
}

void ParallelFor(const std::vector<int> &parallel_iterator, const int &step, std::function<void(int)> for_function)
{
	int num_of_threads = std::thread::hardware_concurrency();
	num_of_threads = (num_of_threads > 0) ? num_of_threads : 2;	 //if num_of_threads is undefined

	int loop_size = parallel_iterator.size();
	if (loop_size < num_of_threads)
		num_of_threads = loop_size;

	int section_size = std::ceil((double)loop_size / (double)num_of_threads);

	std::vector<std::thread> threads(num_of_threads);

	for (int i = 0; i < num_of_threads; i++)
	{
		int serial_for_it_begin = parallel_iterator.at(i * section_size);
		int serial_for_it_end;

		if ((i + 1) * section_size < parallel_iterator.size())
			serial_for_it_end = parallel_iterator.at((i + 1) * section_size);
		else
			serial_for_it_end = parallel_iterator.at(parallel_iterator.size() - 1) + step;

		threads.at(i) = (std::thread(SerialFor, serial_for_it_begin, serial_for_it_end, step, for_function));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		//std::cout << "Thread number " << i << " has an id: " << threads.at(i).get_id() << std::endl;

		if (threads.at(i).joinable())
		{
			threads.at(i).join();
		}
	}
}

std::vector<uint8_t> ParallelHamming74Encode::Encode(std::vector<uint8_t> &input_data)
{
	if (CheckInputDataOnCorrect(input_data) == false)
	{
		throw "Error: invalid input data.";
	}
	else
	{
		AddingZeros(input_data);

		int num_of_redundant_symbols = ((input_data.size() / kNumOfInputElements) * kNumOfRedundantElements);
		std::vector<uint8_t> output_data(input_data.size() + num_of_redundant_symbols);
		
		std::vector<int> parallel_iterator(input_data.size() / kNumOfInputElements);
		for (int i = 0; i < parallel_iterator.size(); i++)
			parallel_iterator.at(i) = i * 4;

		ParallelFor(parallel_iterator, kNumOfInputElements, [&](int i)
		{
			int j;
			if (i != 0)
				j = i + (i * kNumOfRedundantElements / kNumOfInputElements);
			else
				j = 0;

			output_data.at(j) = input_data.at(i);
			output_data.at(j + 1) = input_data.at(i + 1);
			output_data.at(j + 2) = input_data.at(i + 2);
			output_data.at(j + 3) = input_data.at(i + 3);
			output_data.at(j + 4) = input_data.at(i) ^ input_data.at(i + 2) ^ input_data.at(i + 3);
			output_data.at(j + 5) = input_data.at(i) ^ input_data.at(i + 1) ^ input_data.at(i + 2);
			output_data.at(j + 6) = input_data.at(i + 1) ^ input_data.at(i + 2) ^ input_data.at(i + 3);
		});

		return output_data;
	}
}

std::vector<uint8_t> SerialHamming74Encode::Encode(std::vector<uint8_t> &input_data)
{
	if (CheckInputDataOnCorrect(input_data) == false)
	{
		throw "Error: invalid input data.";
	}
	else
	{
		AddingZeros(input_data);

		int num_of_redundant_symbols = ((input_data.size() / 4) * 3);
		std::vector<uint8_t> output_data(input_data.size() + num_of_redundant_symbols);

		for (int i = 0; i < input_data.size(); i += kNumOfInputElements)
		{
			int j;
			if (i != 0)
				j = i + (i * kNumOfRedundantElements / kNumOfInputElements);
			else
				j = 0;

			output_data.at(j) = input_data.at(i);
			output_data.at(j + 1) = input_data.at(i + 1);
			output_data.at(j + 2) = input_data.at(i + 2);
			output_data.at(j + 3) = input_data.at(i + 3);
			output_data.at(j + 4) = input_data.at(i) ^ input_data.at(i + 2) ^ input_data.at(i + 3);
			output_data.at(j + 5) = input_data.at(i) ^ input_data.at(i + 1) ^ input_data.at(i + 2);
			output_data.at(j + 6) = input_data.at(i + 1) ^ input_data.at(i + 2) ^ input_data.at(i + 3);
		}

		return output_data;
	}
}