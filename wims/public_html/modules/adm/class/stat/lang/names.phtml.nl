!set lang_exists=yes

!set classname=<b><font color=green>$wims_classname</font></b>\
 van <b><font color=green>$wims_institutionname</font></b>
 
!set months=Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec

!distribute items Exam, Sheet into name_E, name_S

!set name_title=Statistische gegevens
!distribute items Totaal,vereiste<br>punten,gewicht,moeilijkheids<br>graad,\
gemiddelde/cijfer,gemiddelde/leerling,std afwijking,tijdsduu,cijfer,\
theoretische tijdsduur,Sum,min.,min,max\
into name_totals,name_required_points,name_coeff,name_index,\
name_avg_score,name_avg_participant,name_deviation,name_duration,name_score,\
name_theoric,name_sum,name_minute,name_min,name_max

!distribute line Statistische gegevens van\
Type data\
registreerde activiteiten, niet-registreerde activiteiten, alle activiteiten\
Tel de activiteiten van de klas<br>gedeelde werkbladen met uw klas\
into name_showstat,name_data,name_typ_activities,name_shareclass

!set name_prompt=vereiste punten, gewicht,\
	moeilijkheids graad, totalen,\
	gemiddelde per score, gemiddelde per leerling,\
	minimum en maximum, standaardafwijking