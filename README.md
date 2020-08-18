
# Decima Explorer


Decima Explorer is a free and open-source program designed to allow you to unpack data from the archive structures used by games using the Decima engine.

Support for encrypted files has been added thanks to Ekey, and [Wunkolo](https://github.com/Wunkolo) for researching, implementing and documenting the decryption algorithm. Wunkolo's [implementation can be found here](https://github.com/Wunkolo/DecimaTools).

This program uses [Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) for decompression. It is slightly modified for this programs purposes. Ooz is under GPL licensing.

This program also uses [Murmur3](https://github.com/PeterScott/murmur3) by [Peter Scott](https://github.com/PeterScott).

If anyone has any issue with this project's existence please feel free to reach out to me.

Now includes a GUI version, please note it has a lot less features than the command line version.

![picture](https://github.com/Jayveer/Decima-Explorer/blob/master/gui.png?raw=true)

### To Do
 - Refactor a lot of the GUI code and add error feedback
 - Research on how to inject files from custom archives
 - Clean up the code (this will always be here)

##  Usage

There are two flavours of Decima Explorer, one that can be run from the command line and one that runs as a Graphical User Interface. The GUI has less features although supports multithreaded bulk extraction.. The command line client has support for movie archive files and binary archive files. Binary archive files can be extracted by their ID or name. If extracting by name it is also possible to enter a directory to search multiple files. A list of game files can also be dumped. Movie archive files can be extracted ID or name if it is known. If the output file isn't specified it will use the 'file to extract' name along with creating its directory structure;

A repack command has been added to the Command line Interface which will currently take a root directory containing a tree structure of files and generate a Decima Archive binary file from the files. I have not found a way to make a game favour files from my archive yet so I am still researching the best way to inject or replace core files.

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
DecimaExplorer.exe -repack "G:\path\to\files\to\pack" output.bin
```
In the most recent update a repack command has been added which will take a base directory containing multiple directories of files and output a binary archive file.

If running the GUI client, select the game's data directory and a it should populate a list of files available to extract determined by the game's cache loading mechanism.

## License
[GPL](ooz/LICENSE.md)
[Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) uses the GPL License. Everything under the Ooz directory falls under GPL licensing.

[MIT](LICENSE.md)
Everything other than the Ooz directory falls under the MIT license.
