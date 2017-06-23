#!/bin/bash
set -e

CGI_FILE=${CGI_FILE:-./public_html/wims}
WIMS_USER=${WIMS_USER:-wims}

###########################
# Check Wims installation #
###########################
if [[ -f "$CGI_FILE" ]]
then
  echo "Wims is already installed ($CGI_FILE is present).\n"
else
  chown "$WIMS_USER": log/wims.conf
  chmod 600 log/wims.conf

  su "$WIMS_USER" \
    -c "./compile"
#      --jmol \
#      --mathjax \
#      --modules \
#      --swac

  service apache2 start

  ./bin/setwrapexec
  ./bin/apache-config
  ./bin/setwimsd

  a2enmod cgi

  service apache2 stop
fi

####################
# Start Web Server #
####################
if [[ $# -ne 0 ]]
then
  exec "$@"
fi
LOG_LEVEL=${LOG_LEVEL:-info}

apachectl -DFOREGROUND -e "${LOG_LEVEL}"
