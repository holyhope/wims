# Format:
# Line 1. type name_in_wims_conf variable_name
# Line 2. prompt
# Line 3. variable type
# Line 4. selection range; prompts
# Line 5 and up. help

:tech PATH
PATH
free

Search path for binary executables. It is safe to leave it with the default
value, unless you have a very special operating system setup.

:tech aliased_cgi
cgi to html address aliasing
choice
yes,no
Set to yes if you want internet robots to see some WIMS contents as html
pages. Helps for making the site better referenced and better known, but
you need Apache 1.3 or up to get this to work correctly.
<p>
If you have just updated Apache httpd and if you have trouble with unknown
addresses when you activate this feature,
run the script <tt>bin/apache-config</tt>.

:tech aliased_getfile
getfile address rewriting
choice
yes,no
Activating this allows you to get correct file names when downloading
wims-generated files: backup archives, student data in virtual classes, some
image files, etc. Otherwise all file downloads will default to the name
"wims.cgi" which has to be manually corrected when you save the file.
<p>
You may get into trouble downloading if your Apache httpd is not correctly
configured. In this case, say "no".

:housekeep backup_hour
Hour of daily backup
choice
-1,1,2,3,4,5,6,7,8,9,11,13,15,17,18,19,20,21,22; none,1,2,3,4,5,6,7,8,9,11,13,15,17,18,19,20,21,22
This is the hour when daily data backup will take place. Choose an hour where
the server is not busy, or pick none (-1) to disable daily backup.

:resources busyhours wims_busyhours
Busy hours of the server
free

You can list here the hours during which the server is most likely to be busy.
Some activities such as local module publication will be prohibited during 
such periods. Give a list of words composed of two digits: for example,
<p>"08 09 13 14".

:graphics default_anim_format ins_format
Format of dynamic animations*
choice
gif, mng
Graphics format for dynamic animations. There are only two possibilities:
gif or mng. You must be aware of the fact that many currently used browsers
are unable to show inline mng animations.

:graphics default_texposition
Default formula position / MathML
choice
0,1,2; low,high,MathML
TeX formulas are small graphics files that are middle-aligned with respect to
the text line. <p>
There is an ancient middle-alignment bug from the beginning days of
Netscape, which aligns the middle of the picture against the base line of
the text. This of course makes the formulas appear too low, and WIMS patches
it by raising a bit the formulas. <p>
However, recent browsers no longer carry this alignment bug. And for these
browsers, the patch makes the formulas too high with respect to text. This
parameter allows you to choose whether or not to activate the patch by
default. Note that users can define their own preferences. <p>
The parameter will also be used to activate MathML translation which is not
yet available. <p>
If you change this value, don't think of your own browser, but of those of
your average users!

:tech cgi_name
Name of the main cgi program!
free

You can change this name only if you have correctly aliased things in the
configuration file of your httpd. For example, if you have run the script
in <tt>bin/apache-config</tt>,
you may try the names <tt>index.html</tt> or <tt>wims.html</tt>.
<p>
Do not change this if you don't know what you are doing! If you make it
wrong, you will have to manually recover your config.

:class class_limit wims_class_limit
Limit of the number of virtual classes
int
0,1000

:class class_regpass wims_class_regpass
Rights to create virtual classes
free

This parameter defines your site's access right for the creation of virtual
classes. It contains 3 comma-separated fields, defining respectively the
access right for creating individual classes, class groups and institution
portals. For each field, the following definitions are possible.
<dl>
<dt><tt>all</tt><dd>Every one can create classes.
<dt><tt>deny</tt><dd>Nobody is allowed to create classes.
<dt><tt>email</tt><dd>Every one can create classes, as long as he/she submits
his/her working email address. The site will check the effectiveness of this
email address.
<dt><tt>passwd ******</tt><dd>The user must enter a password to access the
creation of classes. You can define the password as the second word
of the parameter (in replacement of `<tt>******</tt>' above), and
communicate the password to those who you allow to create classes.
<dt>Host names or IP numbers<dd>
 Only people connecting from the defined hosts will be allowed to create
classes.
$sitehelp
</dl>
Please notice that the site manager (that is, you) always has the right to
create virtual classes of any kind.

:class class_quota wims_class_quota
Disk quota for virtual classes in Meg
int
1,1000
This is the limit of disk space usage for each virtual class on the server.
If a virtual class' disk space use reaches or exceeds this number in Megabytes,
the supervisor's homepage will get locked.

:class superclass_quota wims_superclass_quota
Disk quota for portal in Meg
int
1,2000
This is the limit of disk space usage for each portal on the server.
If a portal disk space use reaches or exceeds this number in Megabytes,
the supervisor's homepage will get locked.

:class class_user_limit wims_class_user_limit
Limit of participants in each class
int
0,2000

:graphics default_ins_format ins_format
Format of dynamic graphics*
choice
gif, jpeg, png
Sorry for png advocates, but gif is the most compatible format, especially
if you can install softwares producing compressed gif files. The second
choice is jpeg. png still have some compatibility problems. <p>
Note also that animated graphics format is not affected by this setting.

:security,misc devel_modules
Access policy for modules under development
choice
open,close
If set to close, modules under development cannot be accessed without
authentication.
<p>
It is highly recommended that you choose <tt>close</tt>, in order
to avoid future problems. Module developers should be encouraged to
publish their modules into local space in order to make them usable by others.

:class examlog_limit
Limit of registered exam sessions for each participant
int
0,100
Please note that this is site-wide limitation, setups of individual classes
cannot exceed this limit. Registers of exam details may take up a lot of
disk space, so if this limit is too high, some very active classes may run
into disk quota problems.
<p>
If you set this limit to 0 or negative, no exam detail will be registered in
any virtual class.

:tech tmp_debug wims_tmp_debug
Debugging mode
choice
yes,no
Turning on debugging mode allows some basic information to be shown at the
bottom of most pages, when the query is from localhost.
At the same time, the temporary session directory
(located down tmp/sessions/) will be conserved for examination. For
development use, as well as for troubleshooting the installation.

:graphics default_insplot_font insplot_font
Font size of dynamic plot
choice
small,medium,large
This font size affects dynamic plots generated by gnuplot. Individual modules
may change this setting.

:doc doc_quota wims_class_quota
Disk quota for Documents in Meg
int
1,1000
This is the limit of disk space usage for each interactive document on the server.
If a document's disk space use reaches or exceeds this number in Megabytes,
further modification of the document will no longer be allowed.

:forum forum_limit wims_forum_limit
Limit of the number of forums
int
0,1000

:software gap_command
Command name for GAP
free

GAP is a group theoretic calculator used by WIMS. If you install it in a
directory according to its instructions, with an executable gap.sh within
usual PATH, you don't need to touch this.

:log general_log_limit
Length limit (in bytes) of main log files
int
0,102400000
Length limit of general log files (access.log, post.log, session.log).


:graphics gnuplot_format
Internal graphics format for gnuplot*
choice
gif,jpeg,png
Choose a format known to your gnuplot.
gnuplot is used for generating dynamic plottings. In
most recent distributions, gnuplot is not compiled for gif format.

:appearances home_module
Home (default) module!
free

This module is the entry point of the site. You should not change this
unless you have designed and put up your own home module.

:tech idle_time
Delay before an idle class session is killed
choice
600,1200,1800,2400,3600,5400,7200,10800,14400,18000;10 min,20 min, 30 min, 40 min, 1 hour,1.5 hours, 2 hours, 3 hours,4 hours, 5 hours
Reducing this may increase performance but slow visitors will find their
sessions expired. Usually an active
user will touch his session at least once every 10 minutes, unless he is
working on a very hard exercise (a fairly rare case). However, killing the
session of the latter will result in huge frustration. So be careful!
<p>
If exams will be carried out on your installation, please note that this
delay should exceed the time allowance of any exam sheet.

:tech idle_time2
Delay before an idle anonymous session is killed
choice
600,900,1200,1800,2400,3600,5400,7200,10800,14400,18000;10 min,15 min,20 min, 30 min, 40 min, 1 hour,1.5 hours, 2 hours, 3 hours,4 hours, 5 hours
Reducing this may increase performance but slow visitors will find their
sessions expired. Usually an active
user will touch his session at least once every 10 minutes, unless he is
working on a very hard exercise (a fairly rare case). If killing the
session of the latter will result in huge frustration, such activities
are less important when they are not in a virtual class.
<p>
This delay only applies to sessions without authentication. It cannot be
bigger than delay for class sessions.

:tech idle_time3
Delay before an idle first-created session is killed
choice
300,360,480,600,720,900,1200,1800,2400,3600,7200;5 min,6 min,8 min,10 min,12 min,15 min,20 min, 30 min, 40 min, 1 hour,2 hours, 2 hours
If one creates a session without reusing it during this amount of seconds,
the newly-created session will be removed.
<p>
This delay only applies to sessions without authentication. Creating a
session without reusing it is usually a behavior of internet robots.
<p>
This delay cannot be bigger than that for idle anonymous sessions.

:tech mail_opt
Options for !mailto command
free

Add options to the system command "mail" when using the !mailto command. See
the sytem's mail manual for details of possible options.
<p>
For example, if your system's mail command supports this, you can use 
<tt>-a "User-Agent: WIMS"</tt> to add a User-Agent header to the mail sent
out by wims. Some providers require this to accept mails.

:security manager_https
Site maintenance must use https connection*
choice
0,1;no (0),yes (1)
Whenever possible, choose https connection to increase security. An
intrusion to your server as site manager represents a great danger to your
installation!
<p>WIMS is compatible with https. All you have to do is to configure your
httpd so that it accepts https requests.

:security manager_site
Site maintenance connections must come from a site with this IP*!
free

You may put here several IP numbers. Partial numbers such as 134.59.10. are
accepted, but be aware that the more there are allowed sites, the more will be
your security risks. The most secure site is 127.0.0.1
(localhost). In any case, choose only site(s) you can trust. An
intrusion to your server as site manager represents a great danger to your
installation!
<p>
If you put a `*' to this field, the next time you will not be
able to use this online maintenance tool (and you can be sure that nobody
else will).

:software maxima_command
Command name of Maxima
free

You don't need to change this if Maxima is installed in a usual way with the
starting exercutable in PATH.

:log module_log
Log individual module informations
choice
1,0;yes (1),no (0)
Many WIMS modules define their own log informations. If you want to see
these module informations, you can activate this (see also the definition of
module log file lengths). Attention however that these
log files will end up by using up a fair amount of disk spaces, as there are
hundreds of logging modules.

:log module_log_limit
Length limit (in bytes) of module log files
int
0,102400000
Length limit of module log files. There are some secondary general log files
who also use this limit, so even if module log is set to no, this number
still makes sense.

:housekeep mu_auto
Module update method
choice
none,check,install,update,all
Method of automatic daily module update. <dl>
<dt><tt>none</tt>
   <dd>Disable automatic module update.
<dt><tt>check</tt>
   <dd>Check what should be updated, and send a mail to site manager (that
   is, you). Do not install or update anything.
<dt><tt>install</tt>
   <dd>Install new modules, but not update existing modules.
<dt><tt>update</tt>
   <dd>Update existing modules, but not install new modules. <br>
   This will let you benefit from bug fixes, as well as suffer from
   newly introduced ones.
<dt><tt>all</tt>
   <dd>Install new modules and update existing ones.
</dl>

:housekeep mu_site
Download site for module update
free

Choose a download site for module update. Known mirror sites:
<pre>
$mu_sitesw
</pre> <p>
If you choose automatic module update with very small delay (0 or 1 day),
you should set the download site to the primary mirror <tt>$(mu_sites[1])</tt>.

:housekeep mu_delay
Delay in automatic module update
choice
0,1,2,4,7,10,15,20,30,50,100
The number of days between the publication of a module and the update by
this site.
<p>
Choosing a bigger value here will allow you to reduce the risk of getting
new bugs, because the latter will hopefully be discovered and corrected during
your delay.
<p>
If you choose a very small number here (0 or 1), you should set
the download site to the primary mirror <tt>$(mu_sites[1])</tt>.
<p>
!!This feature won't work (delay=0) on Mac OS-X, due to lack of commands on
!!this platform.

:housekeep mu_zone
Zones for automatic module update
free

Limit the automatic module update to the given zones. "all" means everything.
<p>
Possible choices of zones: <dl>
<dt><tt>E</tt>
    <dd>Elementary school materials (you can fine-tune with E1 E2 E3 E4 E5 E6)
<dt><tt>H</tt>
    <dd>Middle school materials (you can fine-tune with H1 H2 H3 H4 H5 H6)
<dt><tt>U</tt>
    <dd>University teaching materials (you can fine-tune with U1 U2 U3 U4 U5)
<dt><tt>Lang</tt>
    <dd>Foreign language-learning materials
<dt><tt>tool</tt>
    <dd>Online tools and helpers.
</dl>
<p>
You can put several zones in this field, separated by white spaces.

:housekeep mu_cat
Categories for automatic module update
free

Limit the automatic module update to the given categories. "all" means everything.
<p>
Some choices of categories (non-exhaustive): <dl>
<dt><tt>math</tt> resp. <tt>physics chemistry language</tt> etc.
    <dd>Corresponding disciplines.
<dt><tt>cs</tt>
    <dd>Computer science.
</dl>
<p>
You can put several categories in this field, separated by white spaces.

!!:software mupad_command
!!Command name of MuPAD
!!free
!!
!!Refer to MuPAD installation reference for the exact location of the
!!executable. (MuPAD interface will soon be removed from WIMS.)
!!<p>
!!This command and its path must correspond exactly to where you have
!!installed MuPAD.

:log old_log_files
Number of old log files*
int
0,20
This is the number of rotated old log files. Increasing this number will give
you more historic information, while proportionally increase disk space use.

:software pari_command
Command name for PARI/GP
free

PARI/GP is a number-theoretic calculator used by many WIMS modules. If you
follow its installation procedure with binary executable within usual PATH,
you don't need to touch this.

:resources priority
Sites with connection priority
free

Connections from these sites will not be refused when server load is above
threshold. $sitehelp

:appearances page_bgcolor wims_bgcolor
Page background color
free

Background color of most WIMS pages. Use a color name or #rrggbb
hexadecimal code (see html standard for detail).

:appearances page_bgimg wims_bgimg
Page background image file
free

Background image file (tile) for most WIMS pages. You may use any valid URL.
Take also a look in the directory public_html/gifs/bg which contains
some pre-defined background files. These files can be referenced simply by
their names, without any directory prefix.
<p>
Here is the list of such directly usable background image files:
<p><tt>$bgimgs</tt>

:tech,misc rafale_level
Anti-rapidfire severity
int
0,100
Rapid-fire requests of exercises without serious attempts to resolve them
will generate errors. This is one of the anti-cheating measures of the system.
Higher severity level results in more requirements in time before new
exercises are allowed. Choosing the value of 0 or less for this severity will
disable this measure.

:appearances ref_bgcolor wims_ref_bgcolor
Table background color
free

Background color appearing in head menus and many WIMS administration
modules. Use a color name or #rrggbb hexadecimal code (see html standard for
detail).

:appearances ref_menucolor wims_ref_menucolor
Link color in menus and reference table. 
free
You can choose the color menu link  here. This is possible only
for "new themes", so not for default, column, columnb and classic themes.
Choose it according to the table background color

:appearances theme wims_theme
Presentation theme
choice
$themelist
You can choose the presentation theme here : <tt>default, classic, column, columnb</tt>
are the original themes. The theme <tt>standard</tt> allows a more configurable css style
and icon theme.

:appearances theme_icon wims_theme_icon
Icon theme
choice
$iconlist
You can choose the icon presentation theme here. This is possible only
for "new themes", so not for default, column, columnb and classic themes.


:appearances css wims_css
Style sheet
choice
$csslist
The style sheet affects almost all pages of the site.
<p>
The available stylesheet (css) files are in 
<tt>public_html/html/css/$lang</tt>. If you
want more stylesheets, you can put new css files into this directory.
<p>
If you chose css=<tt>-theme-</tt>, the stylesheet of the current theme
will be used. No stylesheet will be loaded if css=<tt>----</tt>.

:resources rlimit_cpu
Processing time allowance in seconds*
int
1,10000
If a user request needs more time than this amount to process, the
computation will be cut off and an error message will be sent back.
It is useless to increase this number too much, because in normal
circumstances few internet users will wait more than a few dozens of
seconds for a page.
<p>
This is also a very important security measure to check denial-of-service
attacks.

:appearances show_author wims_show_author
Show author names in search results
choice
yes,no
Do you want the author names to show up behind each module in the search
results?

:appearances show_stat wims_show_stat
Show site usage statistics
choice
yes,no
Log accounting must be activated before statistics can be shown.
<p>
To activate log accounting, you should run log/account.sh once every early
morning, by putting it into crontab.

:housekeep site_accounting
Activity accounting
choice
0,1; no (0), yes (1)
Enable or disable daily activity accounting. This is necessary for site
activity statistics, as well as for virtual class connection time accounting.

:misc site_description wims_site_description
Site description
free

This description text is put in the header of every page rendered by the
server. Its main purpose is to inform internet robots.
<p>
Modules will also have access to this text via the variable
$$wims_site_description.

:misc site_keywords site_keywords wims_site_keywords
Site keywords
free

This is a general keyword list which will be put to the header of every page
rendered by the server, appended by the keyword list of the module. Its main
purpose is to make the server better referenced by internet robots (hence
search engines).
<p>
Modules will also have access to this text via the variable
$$wims_site_keywords.

:appearances site_languages wims_site_languages
Supported languages*
free

Available languages: 
ca (Catalan),
cn (Chinese gb),
de (German),
en (English),
es (Spanish),
fr (French), 
it (Italian),
nl (Dutch),
si (Slovenian),
tw (Chinese gib5).

List them separated by white spaces.
<p>
The order of your listing is important: languages listed first will get
more priority.

:appearances site_manager wims_site_manager
Your email address*
free

This will be given as the email address of the site manager. It is to this 
address that visitors and users of the server will report server problems.
<p>
You must change the default value $DF_site_manager to YOUR email address, if
you don't read messages sent to $DF_site_manager.
<p>
Modules will also have access to this text via the variable
$$wims_site_manager.

:graphics texbasesize
Default TeX font size step*
choice
0,1,2,3,4,5,6,7,8,9,10
This is the defaut font size in the graphics pictures generated by TeX (that
is, mathematics formulas). This default size should be set to meet the text
font size of the browser of average visitors. The latter can change this
size to better fit their situation, but this change is not saved from one
session to another, except for virtual class users.
<p>
Don't adjust this font size only according to your own browser! Think of
others who may have different font sizes in their browsers.
<p>
Each step increases (decreases) 9% of the linear size of the font.

:resources threshold1
First load threshold
int
10,500
If the server load average (as reported by `w', `uptime' or `top') exceeds
this value times 0.01, visitors outside a virtual class will be refused
access.
<p>
The time allowance for each request will also be reduced if the server load
approaches this value.

:resources threshold2
Second load threshold
int
10,500
If the server load average (as reported by `w', `uptime' or `top') exceeds
this value times 0.01, visitors not from priority sites will be refused
access.
<p>
This value should normally be larger than the first load threshold.

:security trusted_modules
List of trusted modules
free

A trusted module may use administrative commands prohibited to usual modules.
These commands allow the module to modify or view server informations
usually hidden to the public. For security reasons, only administration
modules and modules written
by trusted authors can have access to these commands.
<p>
Administration modules (in the subdirectory adm/) and the home module are
automatically trusted. If you want to add other modules to this list, add
their addresses (the part after `module=' in the http request string) into
this field, separated by white spaces.
<p>
Avoid defining trusted modules unless you are really sure of what you are doing.

:class user_limit wims_user_limit
Limit of the total number of users in all classes
int
10,100000
Each time a new participant registration occurs, the sum of existing
participants to all the virtual classes will be computed. If this sum
exceeds the limit, registration will fail.

:resources workfile_limit
Length limit of data files
int
10000,100000000
This limit applies to many files, including script files in modules as well
as data file for participant works. So don't set it too small.

:misc usecookie wims_usecookie
Cookie for anonymous visitors
choice
yes,no
If you choose `yes', the server will send cookies to anonymous visitors,
which helps tracking the user.
<p>
Note that cookies are not mandatory: even if
the visitor disables cookies, he will still be able to work normally on WIMS.
The main difference is that cookies can help them to keep their
personal preferences longuer, and can improve server performance by
eliminating unnecessary session creations.
<p>
The use of cookies for works in virtual classes is not affected by this
parameter.

:log show_ip
Show userIP to supervisor in class logfile
choice
yes,no;yes,no
if no, supervisor cannot see IP in logfile.

