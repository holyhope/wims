#! /bin/sh
# Get list of new additions to the site.
# Reads the file modules/Changelog.

awk 'BEGIN {a=0}; $2=="added" {print; a++};a>='$w_llimit' {exit}' modules/Changelog

