The directory dfsg stands for: Debian Free Software Guidelines,
see <https://en.wikipedia.org/wiki/Debian_Free_Software_Guidelines>

Making a dfsg-free source package
=================================

To build an official Debian package, one needs to check thoroughly
than every source file shipped in it is distributed under a DFSG-free
license, and give proper credit to the authors inside the file
debian/copyright which will be included in the debian source package.

Non-DFSG-free licenses
----------------------

Some parts of the official source tarball for WIMS are not DFSG-free,
i.e., they may be free enough for the main concern of a random Wims
administrator, allowing him to run the server legally, but they are not
free according to the Debian Free Software Guidelines.

Examples of non-dfsg-free parts include packages including third-party
components with non-free licenses: a non-commercial clause makes a license
non-free, as well as a clause stating that the only legitimate use is for
education. More subtle non-free licenses can be the "good, not evil" license
authored by Douglas Crockford; even if it may be considered as a joke, it
entails a legal instability which is refused by Debian developers. See
<https://en.wikipedia.org/wiki/Douglas_Crockford#.22Good.2C_not_Evil.22>.

Uglified "source" code
----------------------

Also, every source file must be human-readable. For the sake of efficiency,
many javascript files are compressed or "uglified" in order to use less
bandwidth. If a javascript is compressed, minified or "uglified", it cannot
be considered as a source file any longer. If so, it must be removed from
the source package, and the source file yielding it must be included,
eventually with some way to generate the compressed file upon compilation
of the source package.

Contents of this directory
==========================

  * `README.md`: the source file for this information
  * `README.html`: this information in HTML format
  * `Makefile`:  a script for the "make" command, which strips non-dfsg
  parts, and adds eventually third-party non-obfuscated sources for
  javascript files.
