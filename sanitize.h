////////////////////////////////////////////////////////////
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <taglib/tstring.h>

std::wstring sanitize(TagLib::String str){
	for(unsigned int i = 0; i < str.size(); i++){
		if(str[i] == '\\'
		|| str[i] == '/'
		|| str[i] == ':'
		|| str[i] == '*'
		|| str[i] == '?'
		|| str[i] == '"'
		|| str[i] == '<'
		|| str[i] == '>'
		|| str[i] == '|'){
			str[i] = '-';
		}
	}

	return str.toWString();
}

bool goodPath(std::string path){
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);

	return !(path.find('.') == std::string::npos
	|| (path.find(".mp3") == std::string::npos
	&& path.find(".m4a") == std::string::npos
	&& path.find(".ogg") == std::string::npos
	&& path.find(".flac") == std::string::npos
	&& path.find(".wav") == std::string::npos
	&& path.find(".aiff") == std::string::npos
	&& path.find(".mp4") == std::string::npos));
}

std::wstring stow(std::string str){
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}
