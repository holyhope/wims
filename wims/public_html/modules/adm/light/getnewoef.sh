#! /bin/sh
# Get list of new OEF to the site.

grep -c . bases/site/oef/new.$w_module_language
cat bases/site/oef/new.$w_module_language 2>/dev/null | head -$w_llimit

