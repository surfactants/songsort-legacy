A music file sorter, compiled with MSVC 14.16, using TagLib 1.12

Years ago, I moved all of my music from my ipod to my desktop. Every file ended up in a single folder, with a string of random characters as a name.

Now, with the magic of std::filesystem and TagLib, I wrote this to rename and sort the files based on the metadata.

Ignores files which are lacking "title", "artist", or "album" tags.

[Characters not appearing in the Latin-1 encoding](https://resources.avid.com/SupportFiles/attach/69906_MacRoman_Latin-1_chardiffs.htm) (such as the infinity symbol) throw an error that is likely unresolvable without a significant refactor. Such files should be edited/moved manually.
