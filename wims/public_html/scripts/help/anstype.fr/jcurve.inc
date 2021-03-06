
!goto $wims_read_parm

:general
Ce type de r�ponse permet � l'utilisateur de dessiner une droite, un polygone,
un rectangle ou plusieurs points dans un dessin.
<p>
La bonne r�ponse doit �tre donn�e sous la forme d'une matrice (le
s�parateur de lignes est le point-virgule `;'). La premi�re ligne est
l'URL de l'image. La deuxi�me ligne est form�e d'une condition parmi
la liste du tableau suivant. Si l'on d�sire analyser la r�ponse par des conditions,
on mettra une variable vide pour la bonne r�ponse et on rajoute
dans le champ <span class="tt wims_code_words">embed</span>
en seconde ligne l'URl de l'image et en troisi�me ligne le type de trac� comme
dans le tableau suivant (par exemple <span class="tt wims_code_words">points</span>,
<span class="tt wims_code_words">line</span> ...).
</p>
!exit
:reply
<p>
Il est recommand� d'ins�rer ce champ de r�ponse dans l'�nonc�. La taille de l'image peut
�tre indiqu� en second argument de <span class="tt wims_code_words">\embed</span> sous la forme  <span class="tt wims_code_words">L x H</span>,
par exemple <span class="tt wims_code_words">\embed{reply</span><em>n</em>, <span class="tt wims_code_words">300 x 400}</span>.
</p><p>
En g�n�ral, la variable <span class="tt wims_code_variable">\reply</span><em>n</em>, o� <em>n</em> est le num�ro du champ de
r�ponse peut �tre utilis�e dans un <span class="tt wims_code_words">\feedback</span> contient
les variables correspondant � ce qui est rentr� <span class="tt">(x1,y1 ...)</span> sauf dans les cas
particuliers suivants :
</p>
<ul><li>
dans le cas de la condition <span class="tt wims_code_words">points</span>, la premi�re ligne est la
liste des coordonn�es des points cliqu�s en pixels, la deuxi�me ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> le nombre de points corrects, <span class="tt wims_code_variable">n2</span> le nombre de points manquants,
<span class="tt wims_code_variable">n3</span> le nombre de points en trop. La troisi�me ligne est form�e de la
liste des num�ros des points correctement trouv�s.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">cercle</span>, la premi�re ligne est la
liste des coordonn�es des points cliqu�s en pixels et du rayon, la deuxi�me ligne
est <span class="tt wims_code_variable">n1,n2</span> avec
<span class="tt wims_code_variable">n1</span> �gal � 1 si le centre est correct, � 0 sinon et
<span class="tt wims_code_variable">n2</span> �gal � 1 si le rayon est correct, � 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la premi�re ligne est la
liste des coordonn�es des points cliqu�s en pixels et du rayon, la deuxi�me ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> �gal � 1 si l'origine est correcte, � 0 sinon,
<span class="tt wims_code_variable">n2</span> �gal � 1 si la pente est correcte, � 0 sinon,
<span class="tt wims_code_variable">n3</span> �gal � 1 si le sens est correct, � 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la premi�re ligne est la
liste des coordonn�es des points cliqu�s en pixels et du rayon, la deuxi�me ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> �gal � 1 si l'origine est correcte, � 0 sinon,
<span class="tt wims_code_variable">n2</span> �gal � 1 si la pente est correcte, � 0 sinon,
<span class="tt wims_code_variable">n3</span> �gal � 1 si le sens est correct, � 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la premi�re ligne est la
liste des coordonn�es des points cliqu�s en pixels et du rayon, la deuxi�me ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> �gal � 1 si la pente est correcte, � 0 sinon,
</li></ul>
