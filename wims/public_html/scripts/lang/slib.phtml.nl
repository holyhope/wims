!set slib_lang_exists=yes 
!distribute lines Script bibliotheek\
Output\
Parameter\
Parameters\
Vereiste software\
Aanvraag door module\
Aavraag door OEF/Doc\
Beschikbaere scripten in slib\
Variabelen lijst van komma-gescheiden items\
default\
Het resultaat kan worden gebruikt dmv de variabele\
Alles\
into wims_name_slib,wims_name_Output,wims_name_Parameter,wims_name_Parameters,wims_name_Required_Software,\
  wims_name_call1,wims_name_call2,wims_name_listslib,wims_name_variable_list,wims_name_default,wims_name_result,wims_name_All

!set wims_name_upto=!nosubst tot en met $slpcnt, komma-gescheiden

!set wims_name_instruction=
De scripten uit deze biblitheek (slib) kunnen in modules worden gebruikt dmv het commando\ 
<span class="tt">!read</span> (of <span class="tt">!readproc</span> vanuit een phtml bestand).\
Bijvoorbeeld, de regel\
<pre>\
 !read slib/matrix/random 3, 5, 10\
</pre>\
maakt een 3&times;5 matrix met random integer coeffici&euml;nten uit interval [-10, 10].\
Het resultaat wordt opgenomen in de variabele
<span class="tt">slib_out</span>.\
Voor OEF oefeningen , documenten of forumberichten moet de functie
<span class="tt">slib()</span>.worden gebruikt<p>\
Alleen de variabelen met voorvoegsel
<span class="tt">slib_</span>\
worden gemodificeerd door deze scripten.</p>
