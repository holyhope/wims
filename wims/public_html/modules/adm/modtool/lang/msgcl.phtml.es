
<span class="wims_warning">$wims_name_Error</span>.
!distribute words $wims_read_parm into w1,w2,w3,w4,w5,w6
!if $w1 iswordof antiwversion badauth badauthhost badcategory badhour badlang \
	badname badtar badtype badversion badwimsversion \
	doublelang empty nochange noindex nolocalright \
	nongnu nooriginal noreply noright noright_translate notallow robot \
	symlink toolong unpublishable please-update-module-version lengthlimit \
	mirror_exists domain_keyword
 !goto $w1
!else
 !default $wims_read_parm=A technical error occurred.
 $wims_read_parm
 !exit
!endif

:mirror_exists
 Un module de m�me nom existe d�j� sur un autre serveur miroir. Si vous en �tes l'auteur,
 vous devez le publier sur l'autre serveur ou demander au serveur de publication de
 transf�rer vos droits. Si vous n'en �tes pas l'auteur, veuillez changer le nom de votre module.
!exit

:antiwversion
 Your module requires WIMS-$w2 to run? This server is only of version
 $wims_version. Please correct.
!exit

:badauth
 Authentification error. Access refused.
!exit

:badauthhost
Authentification error. You have no right to publish with this IP number. Access refused.
!exit

:badcategory
 !if / isin $w2
  The category <span class="tt wims_code_words">$w2</span> of your submitted module is unknown.
  !set w3=!word 3 to -1 of $wims_read_parm
  !set w0=!translate / to , in $w2
  Categories actually available in the zone <span class="tt wims_code_words">$(w0[1])</span> are:
  <pre>
  $w3
  </pre>
  Please write to the
  !mailurl $sysadmin publication maintainer
  if you want to add a new category.
 !else
  The zone <span class="tt wims_code_words">$w2</span> of your submitted module is unknown.
  Please report your problem to the
  !mailurl $sysadmin publication maintainer
.
 !endif
!exit

:badhour
 This is not the time to publish a local module!

 Please choose a period when the server is quieter. Avoid publishing
 modules during the following hours:
 <br class="spacer" />
 $nopublish
!exit

:badlang
 Sorry but the language <span class="tt wims_code_words">$w2</span> does not exist on WIMS yet. Somebody has
 to translate WIMS to this language before modules can be submitted.
!exit

:badname
 The module name <span class="tt wims_fname">$w2</span> is bad: it is either too long, too short or contains
 illegal characters.
!exit

:badtar
 Error detected in the transmission. Please verify your manoeuvre or try again.
!exit

:badtype
 Wrong submission type:
 !if $w2=new
  your module is not new.
 !else
  you cannot modify a non-existing module.
 !endif
 Have you put a wrong address to this module?
!exit

:badversion
 The version number <span class="tt wims_code_words">$w2</span> of your module is not correctly formatted.
 Please correct.
!exit

:badwimsversion
 The wims_version declearation of your module must be an existing WIMS version
 between 3.36 and the latest release.
 This is apparently not the case. Please correct.
!exit

:doublelang
 Confusion in module language definition: the INDEX file declares
 <span class="tt wims_code_words">language=$w3</span>, while the directory has extension
 <span class="tt wims_code_words">$w2</span>. Please correct.
!exit

:empty
 Empty submission ignored.
!exit

:lengthlimit
  La taille du module d�passe la limite permise. Aussi, ce module ne peut �tre install�
  par cette interface. Vous pouvez vous adresser directement au centre de publication
  !mailurl $sysadmin $centralhost
  afin qu'une installation manuelle soit faite.
!exit

:nochange
 The module <span class="tt wims_fname">$w2</span>
 is not modified since the last submission.
 Submission ignored.
!exit

:noindex
 Wrong content: the INDEX file of the module seems missing or corrupt.
!exit

:nolocalright
 In order to install your module in the local space of the server,
 you should first ask the webmaster to give you the right to do so.
!exit

:nongnu
 You did not declare the copyright of the module to be GNU GPL. Submission
 refused.
!exit

:nooriginal
 The publication center cannot find the original module from which
 this module is translated.
 Have you put a wrong address to this module?
!exit

:noreply
 Connection error trying to contact the publication center $centralhost.
!exit

:noright
 You are not known to be the author or translator of <span class="tt wims_fname">$w2</span>.
 You can send a
 !href cmd=reply&jobreq=backup backup archive
 of your modification to the author
 !set au=!line 2 of $wims_read_parm
 !distribute items $au into w3,w4
 <a href="mailto:$w4?subject=Your WIMS module $w2">$w3</a>
 who knows how to publish it.
!exit

:notallow
 You cannot make new publications in $D1/$D2. Try to publish
 under development version, or find somebody having the rights to publish
 it for you!
!exit

:please-update-module-version
You must increase the module version when you update it. You should also write which modifications
have been done in the file NEWS.
!exit
:robot
 Robot access detected: internal technical error, please report.
!exit

:symlink
 Symbolic links are not allowed in new modules. If you have an old version
 OEF module, you can translate it into new version that does not contain
 symbolic links.
!exit

:toolong
 Sorry but your module is too big for automatic submission. You can send it
 manually to the maintainer of the distribution. Thanks!
!exit

:unpublishable
 This module does not have a publishable address. It must first be
 !href cmd=reply&jobreq=move&modreq=$mod renamed
 or
 !href cmd=reply&jobreq=copy&original=devel/$auth_login/$mod duplicated
 if you want to publish it.
!exit

:domain_keyword
 The fields <span class="wims_label">$wims_name_Domain</span> or
 <span class="wims_label">$wims_name_Keywords</span> have not been filled.
 Thanks to modify
!href cmd=reply&jobreq=index $wims_name_properties
 of the module $mod and read the helps.
!exit
