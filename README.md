
# Decima Explorer


Decima Explorer is a free and open-source program designed to allow you to unpack files from the archive structure used by games using the Decima engine. Currently files must be extracted using their ID as I am unaware of how the file names are mapped. I suspect a hashing algorithm is used for lookup but am unsure of which one.

This program uses [Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) for decompression. It is slightly modified for this programs purposes. Ooz is under GPL licensing.

If anyone has any issue with this project's existence please feel free to reach out to me.

### To Do
 - Create GUI variant
 - Implement Repack command
 - Understand how the file strings match to files

##  Usage

Currently Decima Explorer can only be run from the command line;

```
DecimaExplorer.exe -extract input.bin 0 output.bin
```
In the above example the command extract is used, input.bin is the input file to extract from, 0 is the it the ID of the file to extract, and output.bin is to where the file will be saved. Only the extract command is implemented for now.

## License
[GPL](ooz/LICENSE.md)
[Ooz](https://github.com/powzix/ooz) created by [Powzix](https://github.com/powzix) uses the GPL License. Everything under the Ooz directory falls under GPL licensing.

[MIT](LICENSE.md)
Everything other than the Ooz directory falls under the MIT license.