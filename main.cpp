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
#include <chrono>

using runClock = std::chrono::high_resolution_clock;

int main(){
	auto runStart = runClock::now();

	//define origin directory and create target directory
	std::string directory = "D:/Music/Music/";
		fs::create_directory(directory + "Library/");

	//file counts
	unsigned int index = 0, moveCount = 0, skipCount = 0;

	//primary loop, iterates through origin directory and finds songs
	for(const auto& entry : fs::directory_iterator(directory)){
		std::string path = entry.path().string();
		
		//checks if path leads to a valid audio file
		std::cout << "\nChecking file " << ++index << ", '" << getFileName(path) << "': ";
		if(!goodPath(path)){
			std::cout << "invalid file type, skipping...";
			skipCount++;
			continue;
		}

		//creates and defines the song
		Song* song = new Song(directory);
			song->origin = path;
			song->getInfo();


		//attempts to move the song if it has the proper metadata
		if(song->isGood()){
			try{
				fs::rename(song->origin, song->target);
				moveCount++;
			}
			catch(const fs::filesystem_error& ex){
				std::cout << "EXCEPTION: " << ex.what();
			}
		}
		else skipCount++;

		//clears pointer for reuse
		delete song;
	}

	//output file counts
	std::cout << "\n\n     " << index << " files found...";
	std::cout << "\n     " << skipCount << " files skipped...";
	std::cout << "\n     " << moveCount << " successfully moved.\n";

	//calculate and output runtime
	auto runEnd = runClock::now();
	auto runElapsed = runEnd - runStart;
	double runTime = std::chrono::duration<double>(runElapsed).count() / 60;
		std::cout << std::fixed << std::showpoint << std::setprecision(2);
		std::cout << "     Completed in " << runTime << " minutes.\n" << std::endl;
	
    return 0;
}
