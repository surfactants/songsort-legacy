#pragma once

#include <algorithm>

std::string sanitize(std::string str){
	for(unsigned int i = 0; i < str.size(); i++){
		if(str.at(i) == '\\'
		|| str.at(i) == '/'
		|| str.at(i) == ':'
		|| str.at(i) == '*'
		|| str.at(i) == '?'
		|| str.at(i) == '"'
		|| str.at(i) == '<'
		|| str.at(i) == '>'
		|| str.at(i) == '|'){
			str.at(i) = '_';
		}
	}

	return str;
}

bool goodPath(std::string path){
	bool good = true;

	std::transform(path.begin(), path.end(), path.begin(), ::tolower);

	if(path.find('.') == std::string::npos
	|| (path.find(".mp3") == std::string::npos
	&& path.find(".ogg") == std::string::npos
	&& path.find(".flac") == std::string::npos
	&& path.find(".wav") == std::string::npos
	&& path.find(".aiff") == std::string::npos
	&& path.find(".mp4") == std::string::npos)){
		good = false;
	}

	return good;
}
