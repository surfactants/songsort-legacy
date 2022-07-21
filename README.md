# songsort

A music file sorter, written using TagLib 1.12

Years ago, I moved all of my music from my ipod to my desktop. Every file ended up in a single folder, with strings of random characters as filenames.

Now, with the magic of std::filesystem and TagLib, I wrote this to rename and sort the files based on the metadata.

Ignores files lacking "title", "artist", or "album" tags.

Moves ~1k files per minute on my machine (i5-4460 @3.20GHz and 16GB RAM)
