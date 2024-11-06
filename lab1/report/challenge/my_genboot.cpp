#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please input the filename!" << std::endl;
		return -1;
	}
	fstream file(argv[1], ios::out | ios::binary);
	if (!file.is_open()) {
		std::cout << "Cannot open the file: " << argv[1] << " !" << std::endl;
		return -3;
	}
	file.seekp(0, file.end);
	size_t fileSize = file.tellp();
	if (fileSize > 510) {
		std::cout << "ERROR: boot block too large: " << fileSize << " bytes (max 510)\n" << std::endl;
	}
	else {
		std::cout << "OK: boot block is " << fileSize << " bytes (max 510)\n" << std::endl;
		for (size_t curr = fileSize; curr < 510; curr++) {
			file.write("\0", 1);
		}
		file.write("\x55\xaa", 2);
	}
	file.close();
	return 0;
}

