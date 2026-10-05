#include <iostream>
#include <fstream>
#include <iomanip> 
#include <string>

using namespace std;

ifstream input_file;
ifstream dictionary_file;
ofstream output_file;

const int a = 5;
const int b = 5;
int worlds_count = 0;
int worlds_answer = 0;
string world = "";
string dictionary[50]; 
char crossword[a][b];
char decided_crossword[a][b];

void save_answer(){
    output_file.open("output.txt"); 
    if (!output_file.is_open()){
        cout << "Error opening output file!!!" << endl;
        return;
    }
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            output_file << setw(3) << decided_crossword[i][j]; 
        }
        output_file << endl;
    }
    output_file << worlds_answer;
    output_file.close();
    cout << "Answer successfully saved to output.txt!" << endl;
}

void print_record(char crosswordInput[a][b]){
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            cout << setw(3) << crosswordInput[i][j]; 
        }
        cout << endl;
    }
}

void record_dictionary(){
    dictionary_file.open("dictionary.txt");
    if (!dictionary_file.is_open()){
        cout << "Error opening dicitionary file!!!";
        return;
    }
    while (worlds_count < 50 && dictionary_file >> dictionary[worlds_count]){
        worlds_count++;
    }
    dictionary_file.close();
}

void record_crosswrd(){
    input_file.open("input.txt");
    if (!input_file.is_open()){
        cout << "Error opening input file!!!";
        return;
    }
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            input_file >> crossword[i][j];
        }
    }
    input_file.close();
}

bool is_word_in_dictionary(string target_word){
    for (int i = 0; i < size(dictionary); i++){
        if (dictionary[i] == target_word){
            return true;
        }    
    }
    return false;
}

int crossword_solution(){
    // ?? ??????????? 
    for (int i = 0; i < a; i++){
        world = ""; 
        for (int j = 0; j < b; j++){
            world += crossword[i][j]; 
            if (is_word_in_dictionary(world)){
                worlds_answer++;
                int start_j = j - world.size() + 1; 
                for (int k = 0; k < world.size(); k++) {
                    decided_crossword[i][start_j + k] = world[k];
                }
            }
        }
    }
    // ?? ?????????
    for (int j = 0; j < a; j++){
        world = ""; 
        for (int i = 0; i < b; i++){
            world += crossword[i][j]; 
            if (is_word_in_dictionary(world)){
                worlds_answer++;
                int start_i = i - world.size() + 1; 
                for (int k = 0; k < world.size(); k++) {
                    decided_crossword[start_i + k][j] = world[k];
                }
            }
        }
    }
    // ?? ?????????
    for (int start_i = 0; start_i < a; start_i++){
        for (int start_j = 0; start_j < b; start_j++){
            world = "";
            for (int k = 0; (k + start_i) < a && (k + start_j) < b; k++){
                world += crossword[k + start_i][k + start_j];
                if (is_word_in_dictionary(world)) {
                    worlds_answer++;
                    int word_len = world.size();
                    int start_word_step = k - word_len + 1;
                    for (int m = 0; m < word_len; m++) {
                        int letter_i = start_i + start_word_step + m;
                        int letter_j = start_j + start_word_step + m;
                        decided_crossword[letter_i][letter_j] = world[m];
                    }
                }
            }
        }
    }
    for (int start_i = a - 1; start_i >= 0; start_i--){ 
        for (int start_j = 0; start_j < b; start_j++){
            world = "";
            for (int k = 0; (start_i - k) >= 0 && (k + start_j) < b; k++){
                world += crossword[start_i - k][start_j + k];
                if (is_word_in_dictionary(world)) {
                    worlds_answer++;
                    int word_len = world.size();
                    int start_word_step = k - word_len + 1;
                    for (int m = 0; m < word_len; m++) {
                        int letter_i = start_i - (start_word_step + m);
                        int letter_j = start_j + (start_word_step + m);
                        decided_crossword[letter_i][letter_j] = world[m];
                    }
                }
            }
        }
    }
    return worlds_answer;
}

int main(){
    for (int i = 0; i < a; i++){
        for (int j = 0; j < a; j++){
            decided_crossword[i][j] = '*';
        }
    }

    record_crosswrd();
    record_dictionary();
    crossword_solution();
    print_record(crossword);
    print_record(decided_crossword);
    save_answer();
    cin.get();
    return 0;
}