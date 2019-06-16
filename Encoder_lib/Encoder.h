#pragma once 

#include <iostream>
#include <vector>
#include <cstdint>
#include <thread>
#include <algorithm>
#include <mutex>

const int kNumOfInputElements = 4;
const int kNumOfOutputElements = 7;
const int kNumOfRedundantElements = kNumOfOutputElements - kNumOfInputElements;

bool CheckInputDataOnCorrect(const std::vector<uint8_t> input_data);
void AddingZeros(std::vector<uint8_t> &input_data);
void SerialFor(const int &it_begin, const int &it_end, const int &step, std::function<void(int)> for_function);
void ParallelFor(const std::vector<int> &parallel_iterator, const int &step, std::function<void(int)> for_function);

class IEncode 
{
public:
	~IEncode() {}

	virtual std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) = 0;
};

class SerialHamming74Encode : public IEncode
{
public:
	~SerialHamming74Encode() {}

	std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) override;
};

class ParallelHamming74Encode : public IEncode
{
public:
	~ParallelHamming74Encode() {}

	std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) override;
};