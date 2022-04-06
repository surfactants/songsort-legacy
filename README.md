A music file sorter, compiled with MSVC 14.16, using TagLib 1.12

The purpose of this program is to solve a problem I have been avoiding for a long time: years ago, I moved all of my music from my ipod to my desktop. Every file ended up in a single folder, with a string of random characters as a name.

Now, with the magic of std::filesystem and TagLib, I wrote this to rename and sort the files based on the metadata.
