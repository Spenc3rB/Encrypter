#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void get_blocks(string& input_lines, vector<string>& blocks){
    for(int i = 0; i < input_lines.length(); i+=16){
        blocks.push_back(input_lines.substr(i, 16));
    }
    // Check last block
    string last_block = blocks[blocks.size()-1];
    while(last_block.size() < 16){
        last_block += char(0x81); // --> Padding character
    }
    blocks[blocks.size()-1] = last_block; // swap in last block
}

string swap(string in, string key){
    int end = in.length() - 1;
    int start = 0;
    int count = 0;

    while (start != end) {

        if (((int)key[count]) % 2 == 1) {
            char hold = in[start];
            in[start] = in[end];
            in[end] = hold;
            end -= 1;
        }

        if (end != start) {
            start++;
        }

        if (count == key.length() - 1) {
            count = 0;
        } else {
            count++;
        }

    }
    return in;
}


void blockCipherD(ifstream& in, ofstream& out, string key){
    vector<string> blocks;
    string input_lines;
    char c;
    while(in.get(c)){
        input_lines += c;
    }

    input_lines = swap(input_lines, key);

    get_blocks(input_lines, blocks);

    // bitwise xor operations
    for(int i = 0; i < blocks.size(); i++){
        string block = blocks[i];
        string XOR = "";

        for(int i = 0; i < block.size(); i++){
            XOR += block[i] ^ key[i];
        }
        blocks[i] = XOR;
    }

    input_lines = "";
    for(string s: blocks){
        input_lines += s;
    }

    input_lines.erase(remove(input_lines.begin(), input_lines.end(), char(0x81)), input_lines.end());

    out << input_lines;

}

void blockCipherE(ifstream& in, ofstream& out, string key){
    vector<string> blocks;
    string input_lines;
    char c;
    while(in.get(c)){
        input_lines += c;
    }
    // get blocks in vectors of size 16
    get_blocks(input_lines, blocks);

    // bitwise xor operations
    for(int i = 0; i < blocks.size(); i++){
        string block = blocks[i];
        string XOR = "";

        for(int i = 0; i < block.size(); i++){
            XOR += block[i] ^ key[i];
        }
        blocks[i] = XOR;
    }

    input_lines = "";
    for(int i = 0; i < blocks.size(); i++){
        input_lines += blocks[i];
    }

    out << swap(input_lines, key);
    
}

bool is_emp(ifstream& file){
    return file.peek() == ifstream::traits_type::eof();
}

int main(int argc, char *argv[]) {

    ifstream in(argv[2]);
    ifstream key(argv[4]);
    ofstream out(argv[3]);

    // flags
    bool block = false;
    bool stream = false;
    bool decryption = false;
    bool encryption = false;

    // Is file empty?
    if(is_emp(in)){
        out << "";
        return -1;
    }

    // Argument # checking
    if(argc != 6){
        cerr << "Please enter exactly five arguments.\nExiting... ";
        return -1;
    }

    // Block or stream argument
    if(strcmp(argv[1], "B") == 0){
        block = true;
    }
    else if(strcmp(argv[1], "S") == 0){
        stream = true;
    }
    else {
        cerr << "Please enter a \'B\' for Block Cipher or \'S\' for Stream Cipher.\nExiting... ";
        return -1;
    }

    // File to encrypt argument
    if(!in.is_open()){
        cerr << "Please enter the correct filename to encrypt.\nExiting... ";
        return -1;
    }
    
    // Keyfile and keystring extraction
    string keystring;
    if(key.is_open()){
        string line;
        while(getline(key, line)){
            keystring += line;
        }
        key.close();
    }
    else {
        cerr << "Unable to produce encrypted file. Please check your keyfile.\nExiting... ";
        return -1;
    }

    // Encryption or decryption arguments
    if(strcmp(argv[5], "E") == 0){
        encryption = true;
    }
    else if(strcmp(argv[5], "D") == 0){
        decryption = true;
    }
    else {
        cerr << "Please enter a \'E\' for Encryption or \'D\' for Decryption.\nExiting... ";
        return -1;
    }

    // functions called per input
    if(block && encryption){
        blockCipherE(in, out, keystring);
    }
    else if (block && decryption){
        blockCipherD(in, out, keystring); 
    }
    else if (stream){
        string input_lines;
        string output_lines;
        char c;
        while(in.get(c)){
            input_lines += c;
        }

        int count = 0;
        for (int i = 0; i < input_lines.length(); i++) {
            if (count == keystring.length()) {
            count = 0;
            }
            output_lines += input_lines[i] ^ keystring[count];
            count++;
        }
        out << output_lines;
    }
}