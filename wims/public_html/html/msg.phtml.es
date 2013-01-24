
!if empty_data iswordof $wims_error
 Ha enviado una petición incompleta. Por favor, complete sus datos antes de
 enviarlos.
 !exit
!endif

!if double_reply iswordof $wims_error
 Ya ha enviado una respuesta a este problema, que ha sido analizada y 
 puntuada. Las respuestas repetidas se ignoran (¡No use el botón `Recargar' 
 de su navegador para reenviar respuestas!). 
 !exit
!endif

!if bad_data iswordof $wims_error
 Je n'ai pas pu évaluer les valeurs que vous avez soumises. Erreur de frappe?
 !exit
!endif

!if no_ldap_parameter iswordof $wims_error
 Vous devez remplir les champs marqués d'un astérisque. Consultez pour cela 
 le gestionnaire de votre annuaire ldap. 
 !exit
!endif

!if bad_class iswordof $wims_error
 Extraño, pero encuentro que su clase no es válida!
 !exit
!endif

!if bad_day iswordof $wims_error or day_dontexist iswordof $wims_error
 La fecha introducida no es válida.
!exit
!endif


!if not_supervisor iswordof $wims_error
 Lo siento, pero esta operación se reserva a los profesores registrados de una clase.
 !exit
!endif

!if nouser iswordof $wims_error or bad_user iswordof $wims_error \
  or bad_usercls iswordof $wims_error
 ¡Extraño pero el participante no parece existir!!!!
!exit
!endif

!if insert_fail iswordof $wims_error
 El software no ha podido insertar su trabajo en la base de datos. Por
 favor, compruebe sus datos.
 !exit
!endif

!if bad_pass iswordof $wims_error
 Mala contraseña: debe tener entre 4 y 16 caracteres,
 cartas y cifras solamente. ¡Y la contraseña repetida debe ser idéntica
 primero! Intente aún.
 !exit
!endif

!if bad_auth iswordof $wims_error
 Fracaso de autenticación. Vuelve a intentar.
 !exit
!endif

!if bad_login iswordof $wims_error
 Su identificador de usuario contiene caracteres ilegales. <p>
 Por favor utilice una palabra que contenga únicamente cifras o letras
 sin acentos y sin espacios entre ellas.
 </p>
 !exit
!endif

Tipo de error: $wims_error $wims_error_parm.
