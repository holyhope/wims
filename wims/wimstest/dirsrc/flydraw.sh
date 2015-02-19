#! /bin/sh
wims_home=`pwd`;
draw_contenthfill="
new 200,200
transparent white
polygon blue,100,100,100,200,200,100
fill 50,50,blue
output wimstest/polfill.gif
"

$wims_home/src/Flydraw/flydraw <<@
$draw_contenthfill
@

exit
open hfill.gif;

draw_contenthfill="
new 200,200
transparent white
hline 100,100,blue
fill 50,50,blue
output hfill.gif
"

$wims_home/src/Flydraw/flydraw <<@
$draw_contenthfill
@
open hfill.gif;

exit

draw_contentvfill="
new 300,300
xrange -10,10
yrange -10,10
vline 0,0,black
fill -5,5, green
output vfill.gif
"

$wims_home/src/Flydraw/flydraw <<@
$draw_contentvfill
@
open vfill.gif;

draw_contenthvfill="
new 300,300
xrange -10,10
yrange -10,10
hline 0,0,black
vline 0,0,black
fill -5,5, green
output hvfill.gif
"

$wims_home/src/Flydraw/flydraw <<@
$draw_contenthvfill
@
open hvfill.gif;

draw_contentcfill="
new 300,300
xrange -10,10
yrange -10,10
hline 0,1,black
trange 0,2*pi
plot red, 2*sin(t),2*cos(t)
fill 0,0, green
output cfill.gif
"

$wims_home/src/Flydraw/flydraw <<@
$draw_contentcfill
@
open cfill.gif

exit
draw_content="
new 256,256
xrange 0,3
yrange 0,3
circle 1,1,20,blue
filltoborder 3,0,blue,red
output toto.gif"

$wims_home/src/Flydraw/flydraw <<@
$draw_content
@
open toto.gif;

draw_content1="
new 300,300
circle 100,100,20,blue
filltoborder 100,300,blue,red
output toto1.gif"

$wims_home/src/Flydraw/flydraw <<@
$draw_content1
@
open toto1.gif

draw_content2="
new 300,300
circle 100,100,20,blue
fill 300,100,blue
output toto2.gif"

$wims_home/src/Flydraw/flydraw <<@
$draw_content2
@
open toto2.gif;

exit

new 256,256
xrange 0,3
yrange 0,3
fcircle 0,0,10,blue

everything is blue

new 256,256
xrange 0,3
yrange 0,3
fcircle 0,3,10,blue

a point at the right place

new 256,256
xrange 0,3
yrange 0,3
fcircle 3,0,10,blue

