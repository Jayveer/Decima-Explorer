
# Decima Explorer


Decima Explorer is a free and open-source program designed to allow you to unpack, data from the archive structures used by games using the Decima engine. It also allows you to create your own decima archive binary or repack an existing one.

Support for encrypted files has been added thanks to Ekey, and [Wunkolo](https://github.com/Wunkolo) for researching, implementing and documenting the decryption algorithm. Wunkolo's [implementation can be found here](https://github.com/Wunkolo/DecimaTools).

This program uses [Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) for decompression. It is slightly modified for this programs purposes. Ooz is under GPL licensing.

This program also uses [Murmur3](https://github.com/PeterScott/murmur3) by [Peter Scott](https://github.com/PeterScott).

If anyone has any issue with this project's existence please feel free to reach out to me.

![picture](https://github.com/Jayveer/Decima-Explorer/blob/master/gui.png?raw=true)

Decima Explorer supports both repacking and packing. Please note there are some caveats to repacking;
- You should back up an original copy the file you are repacking or you will have to redownload it if there is a problem.
- Repacking will increase the original file size based on how many files you are adding.
- Repacking can take a while as it has to insert data in the middle of the binary. 
- If the file you are repacking doesn't exist in the archive you are repacking it will not add it.
- repacking requires a version of oodle dll to be placed alongside Decima Explorer.
- If you are using this to blindly swap core files around you may not have much luck without more of an understanding on how the core files themselves work, in this case you will probably see the game fail to load in places.

### To Do
 - Clean up the code (this will always be here)

##  Usage

There are two flavours of Decima Explorer, one that can be run from the command line and one that runs as a Graphical User Interface. If the Ooz library fails to decompress a file you will need to use a version of the oodle dll. Repacking will require the oodle dll.

### GUI

With the GUI version you can select the initial data directory of the game and it will populate a file list based on the games cache prefetch. You can use the keyboard shortcut Ctrl+F to filter this list for the items you are interested in. You can select all the items with Ctrl+A or by Ctrl or shift clicking. With the items you wish to extract selected you can press the extract button and choose a directory in which to extract, when extracting multiple files with the GUI extraction will be multithreaded and should use all available cores. It is currently not possible to extract .mpk archives with the GUI.

There is also a separate GUI for packing and repacking files. I decided to separate this for now for a cleaner UX. When repacking you must first select a folder that contains the complete path for a file, this is because the directory is used when hashing. You can then select and output, if it is a bin file that already exists it will attempt to repack that file. If it is a file that doesnt exist it will pack the files into a new bin file.

### CLI

With the CLI version there are various commands that can be used, they are list, extract, pack and repack. List will dump all the strings from the game's cache prefetch. Extract can extract either with a directory as the input or by file. When extracting by file you can use the file ID to extract as well, this is useful as it doesn't require knowing the filename to extract a particular entry. This currently supports both .bin and .mpk archives. Repack can be used to repack core files to their original .bin file. A root directory should be chosen so that the path from the root directory will match the hashed file name. For example if you extract a file and keep its original filename and directory structure to C:\Files, you can repack by using C:\Files as the base path. Pack uses a base directory the same way as Repack but instread of an existing Bin as the input, it allows you to specify an output bin file to create. Packing and Repacking require oo2core_7_win64.dll to be present alongside Decima Explorer. Below are example instructions that can be used on the command line;

```
DecimaExplorer.exe -list "G:\path\to\game\data\files"
```
In the above example the list command is used to dump a text file which lists all files in the game.

```
DecimaExplorer.exe -extract input.bin 0 output.bin
```
In the above example the command extract is used, input.bin is the input file to extract from, 0 is the it the ID of the file to extract, and output.bin is to where the file will be saved.

```
DecimaExplorer.exe -extract input.mpk 0 output.bk2
```
The same command can be used on movie files.

```
DecimaExplorer.exe -extract input.bin /file/name/to/extract output.bin
```
The example above is simlar to the last however the file's name is used to chose which file to extract. Only the extract and list commands are implemented for now.

```
DecimaExplorer.exe -extract "G:\path\to\game\data\files" /file/name/to/extract output.bin
```
Here a directory is passed in as the file to extract from, this will allow the tool to search multiple files for the given file name. It is not possible to use a directory if extracting by ID.

```
DecimaExplorer.exe -extract "G:\path\to\game\data\files" /file/name/to/extract
```
It is possible to omit the output file, in this case the input filename or fileID will be used as the file name. If it is a directory, the directory structure will be created.

```
DecimaExplorer.exe -pack "G:\path\to\files\to\pack" output.bin
```
You can also create a Decima archive file, this command  will take a base directory containing multiple directories of files and output a binary archive file.

```
DecimaExplorer.exe -repack "G:\path\to\existing\archive.bin" "G:\path\to\files\to\repack"
```
You can also repack an existing decima archive file. The first argument is the binary archive file you wish to repack and the second is a base directory containing multiple directories of files.

```
DecimaExplorer.exe -swap "G:\path\to\game\data\files" "G:\path\to\swap.txt"
```
Finally there is a swap command which allows you to swap two hashes so that the game will pick up a different core file instead of the one it is pointing at. In most cases this will cause a crash but it's here if anyone finds a use for it. The swap text file will look like this;
```
file/to/swap/first -> file/to/swap/second
another/file/to/swap/first -> another/file/to/swap/second
```
the above would simple be saved as a .txt file.

## License
[GPL](ooz/LICENSE.md)
[Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) uses the GPL License. Everything under the Ooz directory falls under GPL licensing.

[MIT](LICENSE.md)
Everything other than the Ooz directory falls under the MIT license.
