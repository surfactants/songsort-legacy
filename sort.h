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

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

#include "sanitize.h"

namespace fs = std::filesystem;

std::wstring getFileName(std::string path){
	while(path.find('\\') != std::string::npos){
		path = path.substr(path.find('\\') + 1);
	}

	return stow(path);
}

std::wstring getFileExtension(std::wstring filename){
	return filename.substr(filename.find('.'));
}

struct Song{
	std::string& root;

	std::string origin;

	std::wstring name;
	std::wstring title;
	std::wstring extension;
	std::wstring artist;
	std::wstring album;
	std::wstring track;

	std::wstring target;

	Song(std::string& nroot) : root{ nroot }{}

	bool isGood();

	void getInfo();

	void move();
};

bool Song::isGood(){
	return (!title.empty() && !artist.empty() && !album.empty());
}

void Song::getInfo(){
	TagLib::FileRef f(origin.c_str());
	TagLib::Tag* tag1 = f.tag();

	name = getFileName(origin);
	extension = getFileExtension(name);

	title = sanitize(tag1->title());
	artist = sanitize(tag1->artist());
	album = sanitize(tag1->album());
	unsigned int tempTrack = tag1->track();
	if(tempTrack < 10) track = '0';
	track += std::to_wstring(tempTrack);

	target = stow(root) + stow("Library/") + artist + stow("/");

	fs::create_directory(target);

	target += album + stow("/");

	fs::create_directory(target);

	target += track + stow(" ") + title + extension;
}

void Song::move(){
	fs::copy_file(origin, target);
	fs::remove(origin);
}
