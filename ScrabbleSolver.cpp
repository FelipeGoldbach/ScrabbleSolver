/* scrabble.cpp
   CSC 116 - Fall 2018
   
   Complete the implementations of each of the functions below (declared in scrabble.hpp)

   Felipe Goldbach - 10/26/2018
*/

#include <iostream>
#include <set> 
#include "scrabble.hpp"
#include <vector>
#include <algorithm>


ScrabbleSolver::ScrabbleSolver(){
	std::vector <std::string> dictionary {};
}

void ScrabbleSolver::add_word( std::string const& word ){
	try{
		for(unsigned i{}; i<dictionary.size(); i++){
			if(word == dictionary.at(i)){
				throw std::runtime_error("Word is already present in dictionary");
			}
		}
	dictionary.push_back(word);
	}
	catch(std::exception const& e){
		std::cout<<e.what()<<std::endl;
	}
}

ScoreMap ScrabbleSolver::get_score_map(){
	std::map< std::string, int > scores;
	for(unsigned j{}; j<dictionary.size(); j++){
		scores[dictionary.at(j)] = compute_score(dictionary.at(j));
	}
	return scores;
}

ScoreMap ScrabbleSolver::find_words( TileSet const& tiles ){
	std::map< std::string, int > possible_words;
	for(unsigned x{}; x<dictionary.size(); x++){
		int count{0};
		for(unsigned y{}; y<dictionary.at(x).size(); y++){
			if(tiles.find(dictionary.at(x).at(y)) == tiles.end()){
				count++;
			}
		}
		if(count < 1 && can_make_word(dictionary.at(x), tiles)){
			possible_words[dictionary.at(x)] = compute_score(dictionary.at(x));
		}
	}
	return possible_words;
}

ScoreMap ScrabbleSolver::find_best_words( TileSet const& tiles ){
	int high_score {};
	std::map< std::string, int > all_words;
	std::map<std::string, int> high_words;
	std::vector<int> vec_scores;
	std::vector<std::string> vec_words;
	for(unsigned w{}; w<dictionary.size(); w++){
		int count{0};
		for(unsigned q{}; q<dictionary.at(w).size(); q++){
			if(tiles.find(dictionary.at(w).at(q)) == tiles.end()){
				count++;
			}
		}
		if(count < 1 && can_make_word(dictionary.at(w),tiles)){
			vec_scores.push_back(compute_score(dictionary.at(w)));
			vec_words.push_back(dictionary.at(w));
			all_words[dictionary.at(w)] = compute_score(dictionary.at(w));
		}
	}
	all_words = find_words(tiles);
	for(unsigned k{}; k<vec_scores.size(); k++){
		int low_score{};
		low_score = vec_scores.at(k);
		if(low_score > high_score){
			high_score = low_score;
		}
	}
	//high_score = *std::max_element(vec_scores.begin(),vec_scores.end());
	for(unsigned a{}; a<vec_scores.size(); a++){
		if((high_score <= vec_scores.at(a))){
			high_words[vec_words.at(a)] = vec_scores.at(a);
		}
	}
	return high_words;
}

/* Static methods */


int ScrabbleSolver::compute_score( std::string const& word ){
	int score{0};
	for(unsigned i{}; i < word.size(); i++){
		if(word.at(i) == 'a' || word.at(i) == 'e' || word.at(i) == 'i' || word.at(i) == 'l' || word.at(i) == 'n' || word.at(i) == 'o' || word.at(i) == 'r' || word.at(i) == 's' || word.at(i) == 't' || word.at(i) == 'u'){
			score += 1;
		}
		if(word.at(i) == 'd' || word.at(i) == 'g'){
			score +=2;
		}
		if(word.at(i) == 'b' || word.at(i) == 'c' || word.at(i) == 'm' || word.at(i) == 'p'){
			score +=3;
		}
		if(word.at(i) == 'f' || word.at(i) == 'h' || word.at(i) == 'v' || word.at(i) == 'w' || word.at(i) == 'y'){
			score +=4;
		}
		if(word.at(i) == 'k'){
			score +=5;
		}
		if(word.at(i) == 'j' || word.at(i) == 'x'){
			score +=8;
		}
		if(word.at(i) == 'q' || word.at(i) == 'z'){
			score +=10;
		}
	}
return score;
}

bool ScrabbleSolver::can_make_word( std::string const& word, TileSet const& tiles ){
	std::string letters {};
	for(auto elem : tiles){
		letters.push_back(elem);
	}
	for(unsigned i{}; i < word.size(); i++){
		if((tiles.find(word.at(i)) == tiles.end())){
			return false;
		}
	}
	for(unsigned b{}; b<word.size(); b++){
		int flag1 {};
		for(unsigned c{}; c<word.size(); c++){
			if(word.at(b) == word.at(c)){
				flag1++;
			}
		}
		int flag2 {};
		for(unsigned e{}; e<letters.size(); e++){
			if(word.at(b) == letters.at(e)){
				flag2++;
			}
		}
		if(flag1 > flag2){
			return false;
		}
	}
return true;
}