!set wims_module_log=error: $error

!if $error iswordof already_exist baddocnumber not_supervisor insert_fail maxdoc toomuchsheet noexo
  !goto $error
!else
 !msg $error
 !exit
!endif

:already_exist
    Het document bestaat reeds in uw klas.
!exit

:baddocnumber
 De ingevoerde informatie komt niet overeen met een document in deze klas.
!exit

:not_supervisor
 Alleen de supervisor van deze klas mag deze actie uitvoeren.
!exit

:insert_fail
 Het is niet toegestaan deze module op te nemen.
!exit

:maxdoc
 Het maximum aantal documenten is $max_doc.
!exit

:toomuchsheet
Het maximum aantal werkbladen is ingesteld op $max_sheets. Er mag geen nieuw werkblad meer worden aangemaakt.
 !exit

:noexo
Het document bevat geen oefeningen.
!exit
