A music file sorter, compiled with MSVC 14.16, using TagLib 1.12

Years ago, I moved all of my music from my ipod to my desktop. Every file ended up in a single folder, with strings of random characters as filenames.

Now, with the magic of std::filesystem and TagLib, I wrote this to rename and sort the files based on the metadata.

Ignores files which are lacking "title", "artist", or "album" tags.
