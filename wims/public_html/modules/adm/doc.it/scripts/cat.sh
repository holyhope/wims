#!/bin/sh

sed 's/\&/\&amp;/g;s/</\&lt;/g;' <$wims_exec_parm

