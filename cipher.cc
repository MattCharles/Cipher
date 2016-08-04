#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char* argv[]){
	unsigned int LOWEST_ASCII = 32;
	unsigned int HIGHEST_ASCII = 126;
	//take an input file, an output file and a word
	if(argc > 5 || argc < 3){
		std::cout << "Usage: " << argv[0] << " [input file] " << "[keyword] " << "[output file (optional)] " << "-d (decrypt, optional)";
		return 0;
	}

	std::ofstream inFile;
	std::ofstream outFile;
	std::string codeword;
	char c;
	unsigned int char_num = 0;
	char raw_char;
	char new_c;
	bool encrypt_mode;

	if(strcmp("-d", argv[4]) == 0 || strcmp("-d", argv[5]) == 0){					//decrypt mode
		encrypt_mode = false;
	} else {															//could just be an outfile
		encrypt_mode = true;
	}

	inFile.open(argv[2]);
	codeword = argv[3];
	
	std::map <char, unsigned int> alpha;
	for(int letter = LOWEST_ASCII; letter < HIGHEST_ASCII; letter++){	//initialize 'alphabet'
		alpha[letter] = 0;
	}

	if(argv[4] && strcmp("-d", argv[4]) == 0 ){
		outFile.open(argv[4]);
	} else {
		outFile.open("output.txt");
	}

	if(!inFile.is_open() || !outFile.is_open()){
		std::cout << "Error opening a file.";
		return -1;
	}
	if(encrypt_mode){

		while(inFile >> c){
			raw_char = c + codeword[char_num % codeword.length()];
			new_c = alpha[raw_char % (alpha.size())];
			alpha[new_c]++;
			char_num++;
		}

		std::cout << "COUNTS:";
		for(auto i : alpha)
			std::cout << i.first << ": " << i.second << std::endl;

	}
}