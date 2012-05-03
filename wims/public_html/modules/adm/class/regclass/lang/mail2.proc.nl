!bound adresse2 within $regpassmail default $empty
!if $adresse2=$empty or $adresse1=$empty
 wims_module_log=sendpwd error $adresse1@$adresse2
 !reset adresse1,adresse2
 !exit
!endif

sendmail=$adresse1@$adresse2
!reset adresse1,adresse2,regpass
wims_module_log=sendpwd $sendmail
!mailto $sendmail\
Hier de toegangscode voor het aanmaken van een virtuele klas of school\
op deze WIMS server.\
\
\ toegangscode: $regpasswd \
\
Als dit bericht onbekend voorkomt,\
heeft iemand anders uw emailadres ingevuld.\
Dit bericht kan worden gewist.
