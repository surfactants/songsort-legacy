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

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

#include "sanitize.h"

namespace fs = std::filesystem;

////////////////////////////////////////////////////////////
// \brief Finds file name from a path
//
std::wstring getFileName(std::string path){
	while(path.find('/') != std::string::npos){
		path = path.substr(path.find('/') + 1);
	}

	return stow(path);
}

////////////////////////////////////////////////////////////
// \brief Returns the file extension
//
std::wstring getFileExtension(std::wstring filename){
	return filename.substr(filename.find('.'));
}

////////////////////////////////////////////////////////////
// \brief Extracts and holds metadata relating to a single audio file
//
struct Song{
	std::string& root;

	std::string origin;

	std::wstring title;
	std::wstring extension;
	std::wstring artist;
	std::wstring album;
	std::wstring track;

	std::wstring target;
	
	////////////////////////////////////////////////////////////
	// \brief Default constructor
	//
	Song(std::string& nroot) : root{ nroot }{}
	
	////////////////////////////////////////////////////////////
	// \brief Checks if file has the appropriate metadata for sorting
	//
	bool isGood();
	
	////////////////////////////////////////////////////////////
	// \brief Reads the file's metadata
	//
	void getInfo();
};

bool Song::isGood(){
	return !(title.empty() && artist.empty() && album.empty());
}

void Song::getInfo(){
	//create taglib objects
	TagLib::FileRef f(origin.c_str());
	TagLib::Tag* tag = f.tag();
	
	//read metadata from tag objects
	title = sanitize(tag->title());
	artist = sanitize(tag->artist());
	album = sanitize(tag->album());
	
	//checks track number and adds leading 0 if appropriate
	unsigned int nTrack = tag->track();
		if(nTrack != 0){
		if(nTrack < 10) track = '0';
		track += std::to_wstring(nTrack) + L" ";
	}

	//define and create target artist directory
	target = stow(root) + L"Library/" + artist + L"/";
		fs::create_directory(target);

		//define and create target album directory
	target += album + L"/";
		fs::create_directory(target);

	//define file target
	extension = getFileExtension(getFileName(origin));
		target += track + title + extension;
}
