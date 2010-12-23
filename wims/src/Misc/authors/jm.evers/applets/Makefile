PACKAGES   = $(shell ls -Fd *| grep /| tr -d /)
HOME_WIMS  = ../../../../..
APPLET_DIR = public_html/scripts/authors/jm.evers/applets
INSTALL_DIR = $(HOME_WIMS)/$(APPLET_DIR)
LOGFILE = $(shell pwd)/log.txt

all:
	@echo "Build date: $$(date)" > $(LOGFILE)
	@echo "+--------------------------------+"
	@echo "| Compiling applets. See log.txt |"
	@echo "+--------------------------------+"
	@for d in $(PACKAGES) ; do ( \
	  echo "============== $$d ==============" >> $(LOGFILE);  \
	  cd $$d; \
	  ant -v ;  \
	  j=`find dist -iname "*.jar" 2>/dev/null`;  \
	  if [ $$j ] ; then  \
	    echo "OK: compiled $$d/$$j" >> $(LOGFILE);  \
	  else  \
	    echo "NOK for package $$d" >> $(LOGFILE);  \
	  fi; ); \
	done

clean:
	rm -rf */dist */build log.txt *~

install:
	for d in $(PACKAGES) ; do \
	  j=`find $$d/dist -iname "*.jar" 2>/dev/null`; \
	  if [ $$j ] ; then  \
	    install -m 644 $$j  $(INSTALL_DIR); \
	  fi; \
	done

.PHONY: all clean install
