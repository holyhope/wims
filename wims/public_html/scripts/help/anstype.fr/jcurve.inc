
!goto $wims_read_parm

:general
Ce type de réponse permet à l'utilisateur de dessiner une droite, un polygone,
un rectangle ou plusieurs points dans un dessin.
<p>
La bonne réponse doit être donnée sous la forme d'une matrice (le
séparateur de lignes est le point-virgule `;'). La première ligne est
l'URL de l'image. La deuxième ligne est formée d'une condition parmi
la liste du tableau suivant. Si l'on désire analyser la réponse par des conditions,
on mettra une variable vide pour la bonne réponse et on rajoute
dans le champ <span class="tt wims_code_words">embed</span>
en seconde ligne l'URl de l'image et en troisième ligne le type de tracé comme
dans le tableau suivant (par exemple <span class="tt wims_code_words">points</span>,
<span class="tt wims_code_words">line</span> ...).
</p>
!exit
:reply
<p>
Il est recommandé d'insérer ce champ de réponse dans l'énoncé. La taille de l'image peut
être indiqué en second argument de <span class="tt wims_code_words">\embed</span> sous la forme  <span class="tt wims_code_words">L x H</span>,
par exemple <span class="tt wims_code_words">\embed{reply</span><em>n</em>, <span class="tt wims_code_words">300 x 400}</span>.
</p><p>
En général, la variable <span class="tt wims_code_variable">\reply</span><em>n</em>, où <em>n</em> est le numéro du champ de
réponse peut être utilisée dans un <span class="tt wims_code_words">\feedback</span> contient
les variables correspondant à ce qui est rentré <span class="tt">(x1,y1 ...)</span> sauf dans les cas
particuliers suivants :
</p>
<ul><li>
dans le cas de la condition <span class="tt wims_code_words">points</span>, la première ligne est la
liste des coordonnées des points cliqués en pixels, la deuxième ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> le nombre de points corrects, <span class="tt wims_code_variable">n2</span> le nombre de points manquants,
<span class="tt wims_code_variable">n3</span> le nombre de points en trop. La troisième ligne est formée de la
liste des numéros des points correctement trouvés.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">cercle</span>, la première ligne est la
liste des coordonnées des points cliqués en pixels et du rayon, la deuxième ligne
est <span class="tt wims_code_variable">n1,n2</span> avec
<span class="tt wims_code_variable">n1</span> égal à 1 si le centre est correct, à 0 sinon et
<span class="tt wims_code_variable">n2</span> égal à 1 si le rayon est correct, à 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la première ligne est la
liste des coordonnées des points cliqués en pixels et du rayon, la deuxième ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> égal à 1 si l'origine est correcte, à 0 sinon,
<span class="tt wims_code_variable">n2</span> égal à 1 si la pente est correcte, à 0 sinon,
<span class="tt wims_code_variable">n3</span> égal à 1 si le sens est correct, à 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la première ligne est la
liste des coordonnées des points cliqués en pixels et du rayon, la deuxième ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> égal à 1 si l'origine est correcte, à 0 sinon,
<span class="tt wims_code_variable">n2</span> égal à 1 si la pente est correcte, à 0 sinon,
<span class="tt wims_code_variable">n3</span> égal à 1 si le sens est correct, à 0 sinon.
</li><li>
dans le cas de la condition <span class="tt wims_code_variable">sline</span>, la première ligne est la
liste des coordonnées des points cliqués en pixels et du rayon, la deuxième ligne
est <span class="tt wims_code_variable">n1,n2,n3</span> avec
<span class="tt wims_code_variable">n1</span> égal à 1 si la pente est correcte, à 0 sinon,
</li></ul>
