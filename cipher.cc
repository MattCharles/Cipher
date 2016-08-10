#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char** argv){
	unsigned int LOWEST_ASCII = 32;
	unsigned int HIGHEST_ASCII = 126;
	//take an input file, an output file and a word

	if(argc > 5 || argc < 3){
		cout << "Usage: " << argv[0] << " [input file] " << "[keyword] " << "[output file (optional)] " << "-d (decrypt, optional)\n";
		return 0;
	}

	ifstream inFile;
	FILE * outFile;
	string codeword;
	char c;
	unsigned int char_num = 0;
	char raw_char;
	char new_c;
	bool encrypt_mode;

	for(int i = 0; i < argc; i++){
		cout << argv[i] << "\n";
	}

	if(argc >= 4 && (strcmp("-d", argv[3]) == 0 || strcmp("-d", argv[4]) == 0)){					//decrypt mode
		encrypt_mode = false;
	} else {															//could just be an outfile
		encrypt_mode = true;
	}

	inFile.open(argv[1]);
	codeword = argv[2];
	
	map <char, unsigned int> alpha;
	for(char letter = LOWEST_ASCII; letter < HIGHEST_ASCII; letter++){	//initialize 'alphabet'
		alpha[letter] = 0;
		cout << letter << "\t";
		if(letter % 5 == 0) cout << endl;
	}

	if(argv[4] && strcmp("-d", argv[4]) == 0 ){
		outFile = fopen(argv[3], "w");
	} else {
		outFile = fopen("output.txt", "w");
	}

	if(!inFile.is_open() || outFile == NULL){
		cout << "Error opening a file.\n";
		!inFile.is_open() ? cout << "it was in.\n" : cout << "it was out.\n";
		return -1;
	}
	if(encrypt_mode){
		while(inFile.get(c)){
			raw_char = c + codeword[char_num % codeword.length()];
			new_c = raw_char % alpha.size();
			alpha[new_c] = alpha[new_c] + 1;
			cout << new_c << "\n";
			char_num++;
			fputc(new_c, outFile);
		}

		cout << "COUNTS:";
		for(auto i : alpha){
			cout << i.first << ": " << i.second << endl;
		}
	} else {
		//TODO: implement decryption?
		while(inFile.get(c)){
			raw_char = c - codeword[char_num % codeword.length()];
			new_c = raw_char % alpha.size();
			alpha[new_c] = alpha[new_c] + 1;
			cout << new_c << "\n";
			char_num++;
			fputc(new_c, outFile);
		}
	}
	fclose(outFile);
}
