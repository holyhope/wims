We use "bower" to automatically download JS packages/plugins,
And then we use "Grunt" to perform special tasks (concat, minify, ...)

****************
* Installation *
****************

# Install Dependencies :
#  You need to install node, npm and git.
#  see here : http://bower.io#install-bower

# Install Bower :
  npm install -g bower

# Install Grunt :


***************************************
* Download/update Packages with Bower *
***************************************

### list all installed plugins :
  bower list

#### update Javascripts plugins via Bower :
  bower update --save

#### update Javascripts plugins for production (without devDepedencies) :
  bower update -p

#### add a new Javascript plugin via Bower :
  bower install <package> --save

## Complete documentation at Bower here :
##  http://bower.io/docs/creating-packages/


***************************
*  Make Tasks with GRUNT  *
***************************

#### Grunt HowTo (FR) :
http://www.grafikart.fr/tutoriels/grunt/grunt-introduction-470
