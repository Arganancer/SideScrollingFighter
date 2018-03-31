#include "score_model.h"
#include <string>
#include <fstream>
#include <algorithm>

int score_model::nb_score_;
std::vector<std::string> score_model::array_score_;
std::vector<std::string> score_model::sorted_array_score_;
std::string score_model::file_name_;
std::string score_model::temp_file_name_;
std::vector<std::pair<std::string, std::string>> score_model::pair_vector_;
std::string score_model::current_search_;

bool score_model::init()
{
	file_name_ = "Data\\score.txt";
	temp_file_name_ = "Data\\score_temp.txt";
	current_search_ = " ";
	return true;
}

std::vector<std::pair<std::string, std::string>> score_model::get_high_score()
{
	nb_score_ = 0;
	std::ifstream ifs(file_name_);
	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			array_score_.push_back(line);
			nb_score_++;
		}
		sort_vector();
	}
	return line_to_pair_vector();
}


std::vector<std::pair<std::string, std::string>> score_model::get_my_high_score(std::string username)
{
	nb_score_ = 0;
	std::ifstream ifs(file_name_);
	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			size_t pos = line.find('|');
			std::string str = line.substr(pos + 1);
			if (str == username)
			{
				array_score_.push_back(line);
				nb_score_++;
			}
		}
		sort_vector();
	}
	return line_to_pair_vector();
}

void score_model::sort_vector()
{
	for (int i = 0; i < nb_score_; i++)
	{
		for (int j = 0; j < nb_score_; j++)
		{
			size_t pos = array_score_[i].find('|');
			std::string str = array_score_[i].substr(0, pos);
			size_t pos2 = array_score_[j].find('|');
			std::string str2 = array_score_[j].substr(0, pos2);

			int int1 = std::stoi(str);
			int int2 = std::stoi(str2);

			if (int1 > int2)
			{
				std::string temp = array_score_[i];
				array_score_[i] = array_score_[j];
				array_score_[j] = temp;
				sorted_array_score_ = array_score_;
			}
		}
	}
}

bool score_model::save_new_score(std::string username, std::string score)
{
	const std::string temp_sf_to_std = score+"|"+username+"\n";
	std::ofstream output_file(file_name_, std::ios_base::app | std::ios_base::out);
	output_file << temp_sf_to_std;
	return true;
}

int score_model::get_nb_score()
{
	return nb_score_;
}

bool score_model::delete_account_score(std::string username)
{
	std::ifstream ifs(file_name_);
	std::ofstream fileout(temp_file_name_);
	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			size_t pos = line.find('|');
			std::string str = line.substr(pos + 1);
			if (str != username)
			{
				line += "\n";
				fileout << line;
			}
		}
		ifs.close();
		fileout.close();
		if(std::remove(file_name_.c_str()) == 0)
		{
			std::rename(temp_file_name_.c_str(), file_name_.c_str());
			return true;
		}
		else
		{
			std::remove(temp_file_name_.c_str());
			return false;
		}
	}
}

std::vector<std::pair<std::string, std::string>> score_model::line_to_pair_vector()
{
	for(int i=0; i<sorted_array_score_.size(); i++)
	{
		size_t pos = sorted_array_score_[i].find('|');
		std::string str = sorted_array_score_[i].substr(pos + 1);
		std::string str2 = sorted_array_score_[i].substr(0, pos);

		pair_vector_.push_back(std::make_pair(str2,str));
	}
	return pair_vector_;
}


std::string score_model::get_current_search()
{
	return current_search_;
}


void score_model::set_current_search(std::string search)
{
	current_search_ = search;
}
