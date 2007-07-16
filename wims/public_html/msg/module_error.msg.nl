	    
             wims error message file, Dutch version.

Environment variable substitutions are valid (variable names start by `$').

A line starting with ':' at the FIRST column is a tag line. Text following
this line will be printed if the tag equals error type; tag line with empty
tag is valid for all error types.

Nothing before the first tag line will be printed; so put comments simply
at the beginning of the file (or after a fictive tag).


:antidated_version
 Deze module vereist minimaal versie WIMS-$module_wims_version, maar deze
 server is van versie $wims_version.
 <p>
  Dit is dus een verkeerd geinstalleerde module.

:append_syntax
  Syntax fout voor `append'.

:bad_allow
  Het veld ``allow'' in de definitie van de variable is niet geldig.

:bad_cmd
  Het commando ``$wims_error_data'' is niet geldig.  

:bad_index
  Het index nummer is niet geldig.

:bad_var_def
  Incorrecte file var.def.

:cannot_create_session_directory
  Onmogelijk een sessie directory te maken.

:cannot_create_session_number
  Onmogelijk een sessie nummer te genereren.

:comp_syntax
  Syntax fout in compare(): $wims_error_data.

:debug
  Debug output:
$debug

:defn_too_long
  Definitie string te lang.
  
:file_too_long
  De lengte van de file ``$wims_error_data'' overschrijdt de lengte limiet.
  
:for_syntax
  Syntax fout in `for'.

:getscore_syntax
  Syntax fout in `getscore'.

:illegal_cmd
  Het commando ``$wims_error_data'' is illegaal:
  U moet niet proberen om naar parent directories te gaan via de command name.
  
:illegal_fname
  De naam van de file ``$wims_error_data'' is illegaal:
  Het is verboden om files tebenaderen via parent directories.
  
:illegal_plot_cmd
  De parameter string voor gnuplot kunnen illegale strings bevatten.
  Het gebruik van een 'pipeline' in deze string (an apostrof gevolgd door `<')
  is niet toegestaan.
  
:label_not_found
  Kan het label ``$wims_error_data'' niet vinden

:mathsubst_syntax
  Syntax fout in ``mathsubst''.

:name_is_reserved
  De naam ``$wims_reserved_name'' is gereserveerd voor  intern gebruik door de server. 
  U kun dit dus niet gebruiken in U module.
  Gebruik een andere variabele naam hiervoor
  

:name_too_long
  Variabele naam te lang.

:next_without_for
  `next' zonder `for'.
  (Is er een `goto'  die springt in een  `for' loop?)

:no_double_quote
    Een dubbele aanhaling " is om beveiligings redenen niet toegstaan in de commano parameter  

  
:no_of
  Syntax fout. De syntax is: $wims_error_data ??? of ???

:not_trusted
  De module $module heeft geen rechten om private scripts of
  administratieve commando's uit te voeren.

:output_too_long
    De lengte van de html-pagina heeft de ingestelde limiet overschreden.
  Als je geen extreem lange html-pagina geschreven hebt (in dat geval opsplitsen)
  wordt dit waarschijnlijk veroorzaakt door een oneindige loop.
  
:parm_too_long
    De parameter string heeft het toegestane maximum overschreden.
  
  
:replace_syntax
  Syntax fout in `replace'.

:subst_exceeded
  Te veel substituties in een enkel string. (Is er een oneindige loop van
  substituties?

:syntax_error
  Syntax fout in het commando.

:text_bad_table
  De tabel voor text interactie is corrupt.

:too_few_columns
  De definitie van de variabele beval te weinig velden.

:too_many_gotos
  Te veel goto's (of `for' loops), deze zijn allen beperkt.
  
:too_many_ins
  Het aantal dynamische 'insertions' (instex, insplot) heeft de limiet overschreden.
  
:too_many_fors
  Het aantal  `for' loops heeft de limiet overschreden.

:too_many_variables
  Het aantal gedefinieerde variabelen in var.def heeft de limiet overschreden.

:tr_syntax
  Syntax fout voor `translate'.

:unmatched_parentheses
  Syntax fout. Unmatched parentheses.Missende haakjes

:workfile_too_long
  De module bevat een file die de ingestelde lengte limiet overschrijdt.

:zero_step
  Een `for' loop met een zero `step' kan niet worden uitgevoerd .

:timeup
 Het verwerken van Uw aanvraag wordt onderbroken, omdat de ingestelde processortijd-limiet is overschreden.

:executable
 De file $executable kan door WIMS niet worden uitgevoerd,
 omdat deze executable is.

:

</p>
Wanneer U dit bericht leest, is er een bug gecontateerd in de module `$module'.

De WIMS server heeft deze fout geregisteerd, en zal automatisch in verband met deze
bug contact opnemen met de auteur van deze module.

