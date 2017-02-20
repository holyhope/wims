# This file allows one to make the Wims source tarball comply
# to the DFSG

TRUNK =    $(abspath $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))/../..)

WIMSHOME = $(TRUNK)/wims

IS_SVN   = $(shell if [ -d "$(TRUNK)/.svn" ]; then echo true; else echo false; fi)

all:
ifeq ($(IS_SVN), false)
	$(MAKE) deletions
else
	@echo "ERROR"
	@echo "You should never use this Makefile inside a SVN repository."
endif

deletions: removeUseless deleteBinaries

removeUseless:
	find $(WIMSHOME) -name "*.bak" -o -name .DS_Store | xargs rm -f

deleteBinaries:
	# sourceless precompiled ELF files
	rm -f $(WIMSHOME)/bin/true
	rm -f $(WIMSHOME)/bin/false
	#### java binary files
	find $(WIMSHOME) -name "*.jar" | xargs rm -f
	#### flash binaries
	rm -f $(WIMSHOME)/public_html/flash/*.swf
	#### uglyfied javascript libraries
	for d in jquery jsxgraph ; do \
	    rm -rf $(WIMSHOME)/public_html/scripts/js/$d; \
	done
	#### uglyfied javascript files
	# Joke Evers' jqmath
	for f in jqmath.js ; do \
	   rm -f $(WIMSHOME)/public_html/scripts/authors/jm.evers/js/$f; \
	done
	# asciimathml which is provided by a debian package
	rm -f $(WIMSHOME)/public_html/scripts/js/ASCIIMathML.js \
	  $(WIMSHOME)/public_html/scripts/js/LaTeXMathML.js
	# mootools which is provided by a debian package
	rm -f $(WIMSHOME)/public_html/scripts/js/editor/scripts_1/mootools.js
	## uglified third party libraries which should be got from their
	## official repositories
	rm -rf $(WIMSHOME)/public_html/scripts/js/bower_components/jquery.mb.extruder
	rm -rf $(WIMSHOME)/public_html/scripts/js/bower_components/what-input
	### delete symbols which will be generated during
	### the post-installation
	rm  -f $(WIMSHOME)/public_html/gifs/symbols/20/*.gif
	############## remove edit-area's uglified javascript
	rm -f $(WIMSHOME)/public_html/scripts/js/edit_area/*full*

downloads:
	## jquery.mb.extruder version 2.6.0
	dest=$(WIMSHOME)/public_html/scripts/js/bower_components/; \
	  cd $${dest}; \
	  wget https://github.com/pupunzi/jquery.mb.extruder/archive/2.6.0.zip; \
	  unzip 2.6.0.zip; rm 2.6.0.zip
	## what-input version 3.0.0
	dest=$(WIMSHOME)/public_html/scripts/js/bower_components/; \
	  cd $${dest}; \
	  wget https://github.com/ten1seven/what-input/archive/v3.0.0.zip; \
	  unzip v3.0.0.zip; rm v3.0.0.zip


.PHONY: all deletions removeUseless deleteBinaries
