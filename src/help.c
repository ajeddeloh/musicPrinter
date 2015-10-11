#include <stdio.h>

#include "help.h"

void print_help() 
{
    static const char help[] = 
"This is a program to print formatted music metadata. It uses libavformat to\n"
"extract the metadata, and thus will work on a large variety of files. It also\n"
"searches the steam metadata as well as the container metadata (as some \n"
"malformatted music files have their metadata in weird places)\n"
"\n"
"Still in development, some features not implemented yet.\n"
"\n"
"Usage:\n"
"$ muprint [OPTIONS] format_string filename\n"
"\n"
"The format string is similar to printf's format string. It uses % to denote\n"
"metadata chunks from the loaded file. %% is used to denote a literal %. each\n"
"metadata chunk is composed of an optional modifier character followed by a type\n"
"character. The modifier characters change the allowed characters, causing the \n"
"illegal characters to be ignored or replaced with the character specified by\n"
"the -r option. If you need more advanced replace options, use another program\n"
"like tr.\n"
"\n"
"MODIFIERS:\n"
"v - allow all printing (visible) ascii characters (as defined by isprint(3))\n"
"p - allow all characters in the POSIX.1-2008 portable filesystem character set\n"
"    (that is: all alphanumeric characters plus period (.), underscore(_) and\n"
"    hyphen (-). Does NOT enforce that the first character should not be hyphen\n"
"u - allow all characters that are valid characters in unix filenames (i.e. not\n"
"    '\0' and '/')\n"
"c - allows a custom set of characters, specified by the -c flag\n"
"\n"
"TYPES:\n"
"t - The track title\n"
"T - The track number, does not currently support padding\n"
"d - The disc number, does not currently support padding\n"
"b - The album\n"
"A - The album artist\n"
"a - The artist\n"
"e - The file's original extension\n"
"f - The original file basename (not including extension) \n"
"% - a literal %\n"
"\n"
"examples:\n"
"/media/Music/%pA/%pb/%d-%T-%t.%e would be \n"
"/media/<album artist>/<album>/<artist>/<disc>-<track>-<title>.<extension>\n"
"with all characters not in the metadata that are not in the posix portable\n"
"filesystem character set to be ignored/replaced\n"
"\n"
"OPTIONS:\n"
"-c <characters> specifies what the custom character whitelist should be. Just\n"
"    a string of characters e.g. \"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"\n"
"-s <original type><subsitition string> specifies what to replace a metadata\n"
"    element with if not found. Defaults to \"unknown\". Other metadata elements\n"
"    are valid. For example, you can replace all album artists with the artist\n"
"    using -s \"A%a\". Multiple substitutions for the same metadata type are\n"
"    allowed and the last one added will take precedence. If the substition\n"
"    string contains metadata types that are unknown it is ignored. This allows\n"
"    chains of subsitions (e.g. replace X with Y if y exists, otherwise replace\n"
"    with Z)\n"
"-r <single char> replace non-whitelisted characters with this one instead of\n"
"    deleting them\n"
"\n"
"BUILDING:\n"
"You need libavformat and libavutil. Other than that its straight up C11 with\n"
"POSIX.1-200809L extensions, so just running\n"
"$ make\n"
"should work. If you're debuging there's also \n"
"$ make debug\n"
"which turns on -g for you\n"
"\n"
"CONTACT:\n"
"andrew.jeddeloh.HATESSPAM@gmail.com\n"
"remember, I hate spam, so just remove that part.\n";
	puts(help);
}