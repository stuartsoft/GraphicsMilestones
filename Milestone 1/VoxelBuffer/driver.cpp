/**
NOTE: The test results are accurate to within 0.001.

The code below uses == for comparing floating point values.  You need to fix that to provide proper floating point comparisons.

*/

#include "VoxelBuffer.h"
#include <string>
#include <iostream>

#define EPSILON 0.001f

using namespace std;

VoxelBuffer* subject0;
VoxelBuffer* subject1;
VoxelBuffer* subject2;
VoxelBuffer* subject3;

int runTotalTests(void);
int runPlaneTests(void);
int runLineTests(void);

bool compareEpsilon(float a, float b){
	float c = a - b;
	return (c > - EPSILON && c < EPSILON);
}


int main(int argc, char** argv) {
	cout << "***** Constructing Test Buffers *****" << endl;
	subject1 = VoxelBuffer::factory("test1.txt");
	cout << "********  Buffer 1 Finished  ********" << endl;
	subject2 = VoxelBuffer::factory("test2.txt");
	cout << "********  Buffer 2 Finished  ********" << endl;
	subject3 = VoxelBuffer::factory("test3.txt");
	cout << "********  Buffer 3 Finished  ********\n\n";

	cout << "***** Testing Total Density of Buffers *****" << endl;
	cout << "***********  " << runTotalTests() << " out of 3 correct  ***********\n\n";
	
	cout << "***** Testing Plane Density of Buffers *****" << endl;
	cout << "***********  " << runPlaneTests() << " out of 9 correct  ***********\n\n";
	
	cout << "***** Testing Line Density of Buffers ******" << endl;
	cout << "***********  " << runLineTests() << " out of 9 correct  ***********\n\n";

	delete subject1;
	delete subject2;
	delete subject3;

	system("pause");
	return 0;
}

int runPlaneTests() {
	int correct = 0;

	ivec3 indices;
	indices.x = 25;
	float total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			total += subject1->densityRead(subject1->getVoxelCenter(indices));
		}
	}

	float expected = 702.0f;
	bool result = compareEpsilon(total,expected);
	cout << "Plane density test1 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 38;
	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject1->densityRead(subject1->getVoxelCenter(indices));
		}
	}

	expected = 1812.0f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test2 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.z = 15;
	total = 0.0f;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject1->densityRead(subject1->getVoxelCenter(indices));
		}
	}

	expected = 0.0f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test3 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 35;
	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			total += subject2->densityRead(subject2->getVoxelCenter(indices));
		}
	}

	expected = 1057.187f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test4 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 56;
	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject2->densityRead(subject2->getVoxelCenter(indices));
		}
	}

	expected = 1401.439f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test5 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.z = 46;
	total = 0.0f;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject2->densityRead(subject2->getVoxelCenter(indices));
		}
	}

	expected = 1475.349f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test6 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 70;
	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			total += subject3->densityRead(subject3->getVoxelCenter(indices));
		}
	}

	expected = 328.300f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test7 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 27;
	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject3->densityRead(subject3->getVoxelCenter(indices));
		}
	}

	expected = 1464.0f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test8 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.z = 59;
	total = 0.0f;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		for(indices.x = 0; indices.x < 100; indices.x++) {
			total += subject3->densityRead(subject3->getVoxelCenter(indices));
		}
	}

	expected = 48.651f;
	result = compareEpsilon(total,expected);
	cout << "Plane density test9 " << (result ? "passed" : "failed") << endl;
	correct += result;

	return correct;
}

int runLineTests() {
	int correct = 0;

	ivec3 indices;
	indices.x = 35;
	indices.y = 35;
	float total = 0;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		total += subject1->densityRead(subject1->getVoxelCenter(indices));
	}

	float expected = 33.0f;
	bool result = compareEpsilon(total,expected);
	cout << "Line density test1 " << (result ? "passed" : "failed") << endl;
	correct += result;
	

	indices.x = 69;
	indices.y = 56;
	total = 0;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		total += subject1->densityRead(subject1->getVoxelCenter(indices));
	}

	expected = 33.0f;
	result = compareEpsilon(total,expected);
	cout << "Line density test2 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 63;
	indices.y = 46;
	total = 0;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		total += subject1->densityRead(subject1->getVoxelCenter(indices));
	}

	expected = 40.5f;
	result = compareEpsilon(total,expected);
	cout << "Line density test3 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 70;
	indices.z = 11;
	total = 0;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		total += subject2->densityRead(subject2->getVoxelCenter(indices));
	}

	expected = 0.0f;
	result = compareEpsilon(total,expected);
	cout << "Line density test4 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 20;
	indices.z = 68;
	total = 0;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		total += subject2->densityRead(subject2->getVoxelCenter(indices));
	}

	expected = 3.015f;
	result = compareEpsilon(total,expected);
	cout << "Line density test5 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.x = 28;
	indices.z = 59;
	total = 0;
	for(indices.y = 0; indices.y < 100; indices.y++) {
		total += subject2->densityRead(subject2->getVoxelCenter(indices));
	}

	expected = 15.148f;
	result = compareEpsilon(total,expected);
	cout << "Line density test6 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 25;
	indices.z = 30;
	total = 0;
	for(indices.x = 0; indices.x < 100; indices.x++) {
		total += subject3->densityRead(subject3->getVoxelCenter(indices));
	}

	expected = 36.0f;
	result = compareEpsilon(total,expected);
	cout << "Line density test7 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 38;
	indices.z = 40;
	total = 0;
	for(indices.x = 0; indices.x < 100; indices.x++) {
		total += subject3->densityRead(subject3->getVoxelCenter(indices));
	}

	expected = 21.0f;
	result = compareEpsilon(total,expected);
	cout << "Line density test8 " << (result ? "passed" : "failed") << endl;
	correct += result;

	indices.y = 15;
	indices.z = 20;
	total = 0;
	for(indices.x = 0; indices.x < 100; indices.x++) {
		total += subject3->densityRead(subject3->getVoxelCenter(indices));
	}

	expected = 34.5f;
	result = compareEpsilon(total,expected);
	cout << "Line density test9 " << (result ? "passed" : "failed") << endl;
	correct += result;

	return correct;
}

int runTotalTests() {
	int correct = 0;

	ivec3 indices;
	float total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			for(indices.x = 0; indices.x < 100; indices.x++) {
				total += subject1->densityRead(subject1->getVoxelCenter(indices));
			}
		}
	}

	float expected = 84828.000f;
	bool result = compareEpsilon(total,expected);
	cout << "Total density test1 " << (result ? "passed" : "failed") << endl;
	correct += result;

	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			for(indices.x = 0; indices.x < 100; indices.x++) {
				total += subject2->densityRead(subject2->getVoxelCenter(indices));
			}
		}
	}

	expected = 60316.843f;
	result = compareEpsilon(total,expected);
	cout << "Total density test2 " << (result ? "passed" : "failed") << endl;
	correct += result;

	total = 0.0f;
	for(indices.z = 0; indices.z < 100; indices.z++) {
		for(indices.y = 0; indices.y < 100; indices.y++) {
			for(indices.x = 0; indices.x < 100; indices.x++) {
				total += subject3->densityRead(subject3->getVoxelCenter(indices));
			}
		}
	}

	expected = 56855.187f;
	result = compareEpsilon(total,expected);
	cout << "Total density test3 " << (result ? "passed" : "failed") << endl;
	correct += result;
	
	return correct;
}
