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

#include <filesystem>

#include <stdio.h>
#include <taglib/tag_c.h>

#include "sanitize.h"

namespace fs = std::filesystem;

std::string getFileName(std::string path){
	while(path.find('\\') != std::string::npos){
		path = path.substr(path.find('\\') + 1);
	}

	return path;
}

std::string getFileExtension(std::string filename){
	return filename.substr(filename.find('.'));
}

struct Song{
	std::string origin;

	std::string name;
	std::string title;
	std::string extension;
	std::string artist;
	std::string album;
	std::string track;
	std::string target;

	bool isGood();

	void getInfo();

	void move();
};

bool Song::isGood(){
	return (artist != "" && album != "");
}

void Song::getInfo(){
	//ID3_Tag tag(origin.c_str());
	name = getFileName(origin);
	extension = getFileExtension(name);
	

	TagLib_File* file = NULL;
	TagLib_Tag* tag = NULL;

	const TagLib_AudioProperties* properties;

	file = taglib_file_new(origin.c_str());

	tag = taglib_file_tag(file);
	properties = taglib_file_audioproperties(file);

	title = sanitize(taglib_tag_title(tag));
	artist = sanitize(taglib_tag_artist(tag));
	album = sanitize(taglib_tag_album(tag));
	track = std::to_string(taglib_tag_track(tag));

	target = "D:/Library/" + artist + '/';

	fs::create_directory(target);

	target += album + "/";

	fs::create_directory(target);

	target += track + " " + title + extension;
}

void Song::move(){
	fs::copy_file(origin, target);
}
