
# Decima Explorer


Decima Explorer is a free and open-source program designed to allow you to unpack files from the archive structure used by games using the Decima engine. Currently files must be extracted using their ID as I am unaware of how the file names are mapped.

Early work-in-progress support for encrypted files has been added thanks to Ekey, and [Wunkolo](https://github.com/Wunkolo) for researching, implementing and documenting the decryption algorithm. Wunkolo's [implementation can be found here](https://github.com/Wunkolo/DecimaTools). Also added support for extracting a file based on its name.

This program uses [Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) for decompression. It is slightly modified for this programs purposes. Ooz is under GPL licensing.

This program also uses [Murmur3](https://github.com/PeterScott/murmur3) by [Peter Scott](https://github.com/PeterScott).

If anyone has any issue with this project's existence please feel free to reach out to me.

### To Do
 - Create GUI variant
 - Implement Repack command
 - Allow dumping of all file names
 - Choice of Recreating file path when extracting
 - Allow directory input when using 'filename' to be able to search multiple files for a hash
 - General cleanup as code is becoming sloppy in the interest of time

##  Usage

Currently Decima Explorer can only be run from the command line, files can be extracted by their ID or name;

```
DecimaExplorer.exe -extract input.bin 0 output.bin
```
In the above example the command extract is used, input.bin is the input file to extract from, 0 is the it the ID of the file to extract, and output.bin is to where the file will be saved.

```
DecimaExplorer.exe -extract input.bin filetoextract.core output.bin
```
The example above is simlar to the last however the file's name is used to chose which file to extract. Only the extract command is implemented for now.
## License
[GPL](ooz/LICENSE.md)
[Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) uses the GPL License. Everything under the Ooz directory falls under GPL licensing.

[MIT](LICENSE.md)
Everything other than the Ooz directory falls under the MIT license.