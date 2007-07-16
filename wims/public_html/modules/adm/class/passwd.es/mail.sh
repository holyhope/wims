#! /bin/sh

mail -s "[WIMS] Contraseña clase virtual" $w_user_email <<@

$w_class_supervisor,

Es usted profesor de una clase virtual en WIMS, $w_class_description
de $w_class_institution, en $HTTP_HOST.

Por medio del siguiente mensaje, confirmamos una modificación de su contraseña
de profesor para esta clase virtual, solicitada por una conexión desde
$REMOTE_ADDR.

Si no fuera usted quien ha realizado esta modificación, alguien habría
robado su contraseña y probablemente no podrá volver a conectarse a su clase
a causa de este cambio de contraseña. En tal caso por favor póngase en contacto
con el administrador del sitio para que vuelva a cambiar su contraseña.

@

