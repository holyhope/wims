#!/usr/bin/perl

use URI::Escape;
print uri_escape($ENV{'wims_exec_parm'});