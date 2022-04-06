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
#include <vector>

int main(){
	std::string directory = "D:/example/";

	unsigned int index = 0;
	unsigned int moveCount = 0;

	std::vector<std::string> toDelete;

	for(const auto& entry : fs::directory_iterator(directory)){
		std::cout << '\n' << ++index << ": ";
		std::string path = entry.path().string();
		
		if(!goodPath(path)){
			index--;
			continue;
		}

		Song* song = new Song;
			song->origin = path;
			song->getInfo();

		try{
			if(song->isGood()){
				std::cout << song->name << " is good, renaming...";
				fs::rename(song->origin, song->target);
				moveCount++;
			}
			else std::cout << song->name << " is bad :(";
		}
		catch(const fs::filesystem_error& ex){
			std::cout << "EXCEPTION: " << ex.what();
		}

		delete song;
	}

	std::cout << "\n\n" << index << " files found...\n";
	std::cout << moveCount << " successfully moved" << std::endl;

	std::cout << '\n' << std::endl;
	system("PAUSE");
	
    return 0;
}
