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

#include "stdafx.h"
#include "sort.h"
#include <iostream>

int main(){
	std::string directory = "D:/Music/Music/";

	unsigned int index = 0;
	unsigned int moveCount = 0;

	for(const auto& entry : fs::directory_iterator(directory)){
		std::cout << '\n' << ++index << ": ";
		std::string path = entry.path().string();
		
		if(!goodPath(path)) continue;

		Song* song = new Song;
			song->origin = path;
			song->getInfo();

		try{
			if(song->isGood()){
				song->move();
				moveCount++;
			}
		}
		catch(const fs::filesystem_error& ex){
			std::cout << "EXCEPTION: " << ex.what();
		}

		delete song;
	}

	std::cout << "\n\n" << index << "files found...\n";
	std::cout << moveCount << " successfully moved\n";
	
    return 0;
}
