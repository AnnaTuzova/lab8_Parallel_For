#include "../Encoder_lib/Encoder.h"
#include <windows.h>
#include <gtest/gtest.h>
#include <time.h> 
#include <cstdlib>

TEST(ParallelTest, ParallelEncodingTest)
{
	std::vector<uint8_t> input_data{ 0,0,0,0,
									 0,0,0,1,
									 0,0,1,0,
									 0,0,1,1,
									 0,1,0,0,
									 0,1,0,1,
									 0,1,1,0,
									 0,1,1,1,
									 1,0,0,0,
									 1,0,0,1,
									 1,0,1,0,
									 1,0,1,1,
									 1,1,0,0,
									 1,1,0,1,
									 1,1,1,0,
									 1,1,1,1 };

	std::vector<uint8_t> expected_output_result{ 0,0,0,0,0,0,0,
											   0,0,0,1,1,0,1,
											   0,0,1,0,1,1,1,
											   0,0,1,1,0,1,0,
											   0,1,0,0,0,1,1,
											   0,1,0,1,1,1,0,
											   0,1,1,0,1,0,0,
											   0,1,1,1,0,0,1,
											   1,0,0,0,1,1,0,
											   1,0,0,1,0,1,1,
											   1,0,1,0,0,0,1,
											   1,0,1,1,1,0,0,
											   1,1,0,0,1,0,1,
											   1,1,0,1,0,0,0,
											   1,1,1,0,0,1,0,
											   1,1,1,1,1,1,1 };

	ParallelHamming74Encode parallel_encode;
	std::vector<uint8_t> actual_data = parallel_encode.Encode(input_data);
	ASSERT_EQ(actual_data, expected_output_result);
}

TEST(ParallelTest, SpeedTest)
{
	size_t input_data_size = 10000000;
	std::vector<uint8_t> input_data(input_data_size);

	for (int i = 0; i < input_data_size; i++)
		input_data.at(i) = std::rand() % 2;

	ParallelHamming74Encode parallel_encode;
	SerialHamming74Encode serial_encode;

	clock_t parallel_start = clock();
	std::vector<uint8_t> parallel_output_data = parallel_encode.Encode(input_data);
	clock_t parallel_end = clock();
	double parallel_seconds = (double)(parallel_end - parallel_start) / CLOCKS_PER_SEC;

	clock_t serial_start = clock();
	std::vector<uint8_t> serial_output_data = serial_encode.Encode(input_data);
	clock_t serial_end = clock();
	double serial_seconds = (double)(serial_end - serial_start) / CLOCKS_PER_SEC;

	std::cout << "Serial encoding took " << serial_seconds << " seconds to complete." << std::endl;
	std::cout << "Parallel encoding took " << parallel_seconds << " seconds to complete." << std::endl;

	ASSERT_TRUE(parallel_seconds < serial_seconds);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}