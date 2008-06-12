
<b>Error</b>.
!distribute words $wims_read_parm into w1,w2,w3,w4,w5,w6
!if $w1 iswordof antiwversion badauth badcategory badhour badlang \
	badname badtar badtype badversion badwimsversion \
	doublelang empty nochange noindex nolocalright \
	nongnu nooriginal noreply noright notallow robot \
	symlink toolong unpublishable
 !goto $w1
!else
 !default $wims_read_parm=A technical error occurred.
 $wims_read_parm
 !exit
!endif

:antiwversion
 Your module requires WIMS-$w2 to run? This server is only of version
 $wims_version. Please correct.
!exit

:badauth
 Authentification error. Access refused.
!exit

:badcategory
 !if / isin $w2
  The category <tt>$w2</tt> of your submitted module is unknown.
  !set w3=!word 3 to -1 of $wims_read_parm
  !set w0=!translate / to , in $w2
  Categories actually available in the zone <b><tt>$(w0[1])</tt></b> are:
  <p>
  <tt>$w3</tt>
  <p>
  Please write to the
  !mailurl $sysadmin publication maintainer
  if you want to add a new category.
 !else
  The zone <tt>$w2</tt> of your submitted module is unknown.
  Please report your problem to the 
  !mailurl $sysadmin publication maintainer
.
 !endif
!exit

:badhour
 This is not the time to publish a local module!
 <p>
 Please choose a period when the server is quieter. Avoid publishing
 modules during the following hours:
 <p>
 $nopublish
!exit

:badlang
 Sorry but the language <tt>$w2</tt> does not exist on WIMS yet. Somebody has
 to translate WIMS to this language before modules can be submitted.
!exit

:badname
 The module name <tt>$w2</tt> is bad: it is either too long, too short or contains
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
 The version number <tt>$w2</tt> of your module is not correctly formatted.
 Please correct.
!exit

:badwimsversion
 The wims_version declearation of your module must be an existing WIMS version
 between 3.36 and the latest release.
 This is apparently not the case. Please correct.
!exit

:doublelang
 Confusion in module language definition: the INDEX file declares
 <tt>language=$w3</tt>, while the directory has extension
 <tt>$w2</tt>. Please correct.
!exit

:empty
 Empty submission ignored.
!exit

:nochange
 The module <font color=blue><tt>$w2</tt></font>
 is not modified since the last submission.
 Submission ignored.
!exit

:noindex
 Wrong content: the INDEX file of the module seems missing or corrupt.
!exit

:nolocalright
 In order to install your module in the local space of the server,
 you should first ask the site manager to give you the right to do so.
!exit

:nongnu
 You didn't declare the copyright of the module to be GNU GPL. Submission
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
 You are not known to be the author or translator of <tt>$w2</tt>.
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

