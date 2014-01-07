/*
 4/1/2014 : adapted for wims (MathML-input , HTML-CSS and STIX only)
 7/1/2014 :replaced fonts STIX-Web by TeX (STIX-Web not working)
*/

/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/config/default.js
 *
 *  This configuration file is loaded when you load MathJax
 *  via <script src="MathJax.js?config=default"></script>
 *
 *  Use it to customize the MathJax settings.  See comments below.
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2009-2013 The MathJax Consortium
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*
 *  This file lists most, but not all, of the options that can be set for
 *  MathJax and its various components.  Some additional options are
 *  available, however, and are listed in the various links at:
 *  
 *  http://www.mathjax.org/resources/docs/?configuration.html#configuration-options-by-component
 *
 *  You can add these to the configuration object below if you 
 *  want to change them from their default values.
 */

MathJax.Hub.Config({

  //
  //  A comma-separated list of configuration files to load
  //  when MathJax starts up.  E.g., to define local macros, etc.
  //  The default directory is the MathJax/config directory.
  //  
  //  Example:    config: ["local/local.js"],
  //  Example:    config: ["local/local.js","MMLtoHTML.js"],
  //
  config: [],
  
  //
  //  A comma-separated list of CSS stylesheet files to be loaded
  //  when MathJax starts up.  The default directory is the
  //  MathJax/config directory.
  // 
  //  Example:    styleSheets: ["MathJax.css"],
  //
  styleSheets: [],
  
  //
  //  Styles to be defined dynamically at startup time.
  //  
  //  Example:
  //      styles: {
  //        ".MathJax_Preview": {
  //          color: "#888"
  //        }
  //      },
  //
  styles: {},
  
  //
  //  A comma-separated list of input and output jax to initialize at startup.
  //  Their main code is loaded only when they are actually used, so it is not
  //  inefficient to include jax that may not actually be used on the page.  These
  //  are found in the MathJax/jax directory.
  //  
  jax: ["input/MathML","output/HTML-CSS"],
  
  //
  //  A comma-separated list of extensions to load at startup.  The default
  //  directory is MathJax/extensions.
  //  
  //  Example:    extensions: ["tex2jax.js","TeX/AMSmath.js","TeX/AMSsymbols.js"],
  //
  extensions: ["mml2jax.js","MatchWebFonts.js","MathZoom.js","HTML-CSS/handle-floats.js"],
  
  //
  //  Patterns to remove from before and after math script tags.  If you are not
  //  using one of the preprocessors (e.g., tex2jax), you need to insert something
  //  extra into your HTML file in order to avoid a bug in Internet Explorer.  IE
  //  removes spaces from the DOM that it thinks are redundent, and since a SCRIPT
  //  tag usually doesn't add content to the page, if there is a space before and after
  //  a MathJax SCRIPT tag, IE will remove the first space.  When MathJax inserts
  //  the typeset mathematics, this means there will be no space before it and the
  //  preceeding text.  In order to avoid this, you should include some "guard characters"
  //  before or after the math SCRIPT tag; define the patterns you want to use below.
  //  Note that these are used as regular expressions, so you will need to quote
  //  special characters.  Furthermore, since they are javascript strings, you must
  //  quote javascript special characters as well.  So to obtain a backslash, you must
  //  use \\ (doubled for javascript).  For example, "\\[" is the pattern \[ in the
  //  regular expression.  That means that if you want an actual backslash in your
  //  guard characters, you need to use "\\\\" in order to get \\ in the regular
  //  expression, and \ in the actual text.  If both preJax and postJax are defined,
  //  both must be present in order to be  removed.
  //
  //  See also the preRemoveClass comments below.
  //  
  //  Example:
  //      preJax: "\\\\\\\\",  // makes a double backslash the preJax text
  //    or
  //      preJax:  "\\[\\[", // jax scripts must be enclosed in double brackets
  //      postJax: "\\]\\]",
  //
  preJax: null,
  postJax: null,
  
  //
  //  The CSS class for a math preview to be removed preceeding a MathJax
  //  SCRIPT tag.  If the tag just before the MathJax SCRIPT tag is of this
  //  class, its contents are removed when MathJax processes the SCRIPT
  //  tag.  This allows you to include a math preview in a form that will
  //  be displayed prior to MathJax performing its typesetting.  It also
  //  avoids the Internet Explorer space-removal bug, and can be used in
  //  place of preJax and postJax if that is more convenient.
  //  
  //  For example
  //  
  //      <span class="MathJax_Preview">[math]</span><script type="math/tex">...</script>
  //
  //  would display "[math]" in place of the math until MathJax is able to typeset it.
  //
  preRemoveClass: null,
  
  //
  //  This value controls whether the "Processing Math: nn%" message are displayed
  //  in the lower left-hand corner.  Set to "false" to prevent those messages (though
  //  file loading and other messages will still be shown).
  //
  showProcessingMessages: true,
  
  //
  //  This value controls the verbosity of the messages in the lower left-hand corner.
  //  Set it to "none" to eliminate all messages, or set it to "simple" to show
  //  "Loading..." and "Processing..." rather than showing the full file name and the
  //  percentage of the mathematics processed.
  //
  messageStyle: "normal",
  
  //
  //  These two parameters control the alignment and shifting of displayed equations.
  //  The first can be "left", "center", or "right", and determines the alignment of
  //  displayed equations.  When the alignment is not "center", the second determines
  //  an indentation from the left or right side for the displayed equations.
  //  
  displayAlign: "center",
  displayIndent: "0em",
  
  //
  //  Normally MathJax will perform its starup commands (loading of
  //  configuration, styles, jax, and so on) as soon as it can.  If you
  //  expect to be doing additional configuration on the page, however, you
  //  may want to have it wait until the page's onload hander is called.  If so,
  //  set this to "onload".
  //
  delayStartupUntil: "none",

  //
  //  Normally MathJax will typeset the mathematics on the page as soon as
  //  the page is loaded.  If you want to delay that process, in which case
  //  you will need to call MathJax.Hub.Typeset() yourself by hand, set
  //  this value to true.
  //
  skipStartupTypeset: false,
  
  //
  //  A list of element ID's that are the ones to process for mathematics
  //  when any of the Hub typesetting calls (Typeset, Process, Update, etc)
  //  are called with no element specified.  This lets you restrict the
  //  processing to particular containers rather than scanning the entire
  //  document for mathematics.  If none are supplied, the entire document
  //  is processed.
  //
  elements: [],

  //
  //  Since typesetting usually changes the vertical dimensions of the
  //  page, if the URL contains an anchor position you may no longer be
  //  positioned at the correct position on the page, so MathJax can
  //  reposition to that location after it completes its initial
  //  typesetting of the page.  This value controls whether MathJax will
  //  reposition the browser to the #hash location from the page URL after
  //  typesetting for the page.
  //  
  positionToHash: false,
  
  //
  //  These control whether to attach the MathJax contextual menu to the
  //  expressions typeset by MathJax.  Since the code for handling
  //  MathPlayer in Internet Explorer is somewhat delicate, it is
  //  controlled separately via (showMathMenuMSIE).  The latter is now
  //  deprecated in favor of the MathJax contextual menu settings for
  //  MathPlayer.
  //  
  //  These values used to be listed in the separate output jax, but
  //  have been moved to this more central location since they are shared
  //  by all output jax.
  //
  showMathMenu: true,
  showMathMenuMSIE: true,


  //
  //  The default settings for the MathJax contextual menu (overridden by
  //  the MathJax cookie when users change the menu settings).
  //  
  menuSettings: {
    zoom: "None",        //  when to do MathZoom
    CTRL: false,         //    require CTRL for MathZoom?
    ALT: false,          //    require Alt or Option?
    CMD: false,          //    require CMD?
    Shift: false,        //    require Shift?
    zscale: "200%",      //  the scaling factor for MathZoom
    font: "Auto",        //  what font HTML-CSS should use
    context: "MathJax",  //  or "Browser" for pass-through to browser menu
    mpContext: false,    //  true means pass menu events to MathPlayer in IE
    mpMouse: false,      //  true means pass mouse events to MathPlayer in IE
    texHints: true       //  include class names for TeXAtom elements
  },
  
  //
  //  The message and style for when there is a processing error handling 
  //  the mathematics (something has gone wrong with the input or output
  //  jax that prevents it from operating properly).
  //
  errorSettings: {
    message: ["[",["MathProcessingError","Math Processing Error"],"]"],
    style: {color: "#CC0000", "font-style":"italic"}  // style for message
  },

  
  //============================================================================
  //
  //  These parameters control the tex2jax preprocessor (when you have included
  //  "tex2jax.js" in the extensions list above).
  //
  tex2jax: { },
  
  //============================================================================
  //
  //  These parameters control the asciimath2jax preprocessor (when you have included
  //  "asciimath2jax.js" in the extensions list above).
  //
  asciimath2jax: { },
  
  //============================================================================
  //
  //  These parameters control the mml2jax preprocessor (when you have included
  //  "mml2jax.js" in the extensions list above).
  //
  mml2jax: {
    
    //
    //  Controls whether mml2jax inserts MathJax_Preview spans to make a
    //  preview available, and what preview to use, when it locates
    //  mathematics on the page.  The default is "mathml" which means use
    //  the <math> tag as the preview (until it is processed by MathJax).
    //  Set to "alttext", to use the  <math> tag's alttext attribute as the
    //  preview, if the tag has one.  Set to "none" to
    //  prevent the previews from being inserted (the math will simply
    //  disappear until it is typeset). Set to "altimg" to use an image
    //  described by the altimg* attributes of the <math> element.
    //  Set to an array containing the
    //  description of an HTML snippet in order to use the same preview for
    //  all equations on the page (e.g., you could have it say "[math]" or
    //  load an image).
    //  
    //  E.g.,     preview: ["[math]"],
    //  or        preview: [["img",{src: "http://myserver.com/images/mypic.jpg"}]]
    //  
    preview: "mathml"
    
  },
  
  //============================================================================
  //
  //  These parameters control the jsMath2jax preprocessor (when you have included
  //  "jsMath2jax.js" in the extensions list above).
  //
  jsMath2jax: {  },

  //============================================================================
  //
  //  These parameters control the TeX input jax.
  //
  TeX: {},

  //============================================================================
  //
  //  These parameters control the AsciiMath input jax.
  //
  AsciiMath: {  },
  
  //============================================================================
  //
  //  These parameters control the MathML input jax.
  //
  MathML: {
    //
    //  This specifies whether to use TeX spacing or MathML spacing when the
    //  HTML-CSS output jax is used.
    //
    useMathMLspacing: false
  },
  
  //============================================================================
  //
  //  These parameters control the HTML-CSS output jax.
  //
  "HTML-CSS": {
    
    //
    //  This controls the global scaling of mathematics as compared to the 
    //  surrounding text.  Values between 100 and 133 are usually good choices.
    //
    scale: 100,
    
    //
    //  Don't allow the matching of math text to surrounding text to use a scaling
    //  factor smaller than this.
    //
    minScaleAdjust: 50,
    
    //
    //  This is a list of the fonts to look for on a user's computer in
    //  preference to using MathJax's web-based fonts.  These must
    //  correspond to directories available in the  jax/output/HTML-CSS/fonts
    //  directory, where MathJax stores data about the characters available
    //  in the fonts.  Set this to ["TeX"], for example, to prevent the
    //  use of the STIX fonts, or set it to an empty list, [], if
    //  you want to force MathJax to use web-based or image fonts.
    //
    availableFonts: ["STIX"],
    
    //
    //  This is the web-based font to use when none of the fonts listed
    //  above are available on the user's computer.  Note that currently
    //  only the TeX font is available in a web-based form.  Set this to
    //  
    //      webFont: null,
    //
    //  if you want to prevent the use of web-based fonts.
    //
    webFont: ["TeX"],
    
    //
    //  This is the font to use for image fallback mode (when none of the
    //  fonts listed above are available and the browser doesn't support
    //  web-fonts via the @font-face CSS directive).  Note that currently
    //  only the TeX font is available as an image font.  Set this to
    //
    //      imageFont: null,
    //  
    //  if you want to prevent the use of image fonts (e.g., you have not
    //  installed the image fonts on your server).  In this case, only
    //  browsers that support web-based fonts will be able to view your pages
    //  without having the fonts installed on the client computer.  The browsers
    //  that support web-based fonts include: IE6 and later, Chrome, Safari3.1
    //  and above, Firefox3.5 and later, and Opera10 and later.  Note that
    //  Firefox3.0 is NOT on this list, so without image fonts, FF3.0 users
    //  will be required to to download and install either the STIX fonts or the
    //  MathJax TeX fonts.
    //
    imageFont: null ,
    
    //
    //  This is the font-family CSS value used for characters that are not
    //  in the selected font (e.g., for web-based fonts, this is where to
    //  look for characters not included in the MathJax_* fonts).  IE will
    //  stop looking after the first font that exists on the system (even
    //  if it doesn't contain the needed character), so order these carefully.
    //  
    undefinedFamily: "STIXGeneral,'Arial Unicode MS',serif",

    //
    //  This setting controls whether <mtext> elements will be typeset
    //  using the math fonts or the font of the surrounding text.  When
    //  false, the mathvariant="normal" font will be used; when true, 
    //  the font will be inherited from the surrounding paragraph.
    //  
    mtextFontInherit: true,

    //
    //  These values control how "chunky" the display of mathematical
    //  expressions will be.
    //  
    //  EqnChunk is the number of equations that will be typeset before
    //  they appear on screen.  Larger values make for less visual flicker
    //  as the equations are drawn, but also mean longer delays before the
    //  reader sees anything.
    //  
    //  EqChunkFactor is the factor by which the EqnChunk will grow after each
    //  chunk is displayed.
    //  
    //  EqChunkDelay is the time (in milliseconds) to delay between chunks
    //  (to allow the browser to respond to other user interaction).
    //  
    //  Set EqnChunk to 1, EqnChunkFactor to 1, and EqnChunkDelay to 10 to get
    //  the behavior from MathJax v1.1 and below.
    //
    EqnChunk: 50,
    EqnChunkFactor: 1.5,
    EqnChunkDelay: 100,

    //  This option indicates whether MathJax should try to correct the
    //  x-height of equations to match the size of the surrounding text.
    matchFontHeight: true,

    //
    //  These settings control automatic line breaking.  It is off by
    //  default, so only explicit line breaks are performed (via
    //  linebreak="newline" attributes on <mo> and <mspace> elements).  To
    //  perform automatic line breaking on line expressions, set
    //  'automatic' to 'true' below.  The line breaks will be applied via a
    //  penalty-based heuristic, which does well, but isn't perfect.  You
    //  might need to use linebreak="goodbreak" or linebreak="badbreak" by
    //  hand in order to get better effects.  It is also possible to modify
    //  the penalty values; contact the MathJax user's forum for details.
    //  
    linebreaks: {
      
      //
      //  This controls the automatic breaking of expressions:
      //    when false, only process linebreak="newline",
      //    when true, line breaks are inserted automatically in long expressions.
      //
      automatic: false,

      //
      //  This controls how wide the lines of mathematics can be
      //  
      //  Use an explicit width like "30em" for a fixed width.
      //  Use "container" to compute the size from the containing element.
      //  Use "nn% container" for a portion of the container.
      //  Use "nn%" for a portion of the window size.
      //  
      //  The container-based widths may be slower, and may not produce the
      //  expected results if the layout width changes due to the removal
      //  of previews or inclusion of mathematics during typesetting.
      //  
      width: "container"
    },

    //
    //  This allows you to define or modify the styles used to display
    //  various math elements created by MathJax.
    //  
    //  Example:
    //      styles: {
    //        ".MathJax .merror": {
    //          color:   "#CC0000",
    //          border:  "1px solid #CC0000"
    //        }
    //      }
    //
    styles: {},
    
    //
    //  Configuration for <maction> tooltips
    //    (see also the #MathJax_Tooltip CSS in MathJax/jax/output/HTML-CSS/config.js,
    //     which can be overriden using the styles values above).
    //
    tooltip: {
      delayPost: 600,          // milliseconds delay before tooltip is posted after mouseover
      delayClear: 600,         // milliseconds delay before tooltip is cleared after mouseout
      offsetX: 10, offsetY: 5  // pixels to offset tooltip from mouse position
    }
  },
  
  //============================================================================
  //
  //  These parameters control the NativeMML output jax.
  //
  NativeMML: { },
  
  //============================================================================
  //
  //  These parameters control the SVG output jax.
  //
  SVG: {},
  //============================================================================
  //
  //  These parameters control the contextual menus that are available on the 
  //  mathematics within the page (provided the showMathMenu value is true above).
  //
  MathMenu: {
    //
    //  This is the hover delay for the display of submenus in the
    //  contextual menu.  When the mouse is still over a submenu label for
    //  this long, the menu will appear.  (The menu also will appear if you
    //  click on the label.)  It is in milliseconds.
    //  
    delay: 150,
    
    //
    //  This is the URL for the MathJax Help menu item.
    //
    helpURL: "http://www.mathjax.org/help-v2/user/",

    //
    //  These control whether the "Math Renderer", "MathPlayer", "Font
    //  Preferences", "Contextual Menu", and "Discoverable" menu items will
    //  be displayed or not.
    //
    showRenderer: false,
    showMathPlayer: true,
    showFontMenu: false,
    showContext:  false,
    showDiscoverable: false,
    
    //
    // These are the settings for the Annotation menu. If the <math> root has
    // a <semantics> child that contains one of the following annotation
    // formats, the source will be available via the "Show Math As" menu.
    // Each format has a list of possible encodings.
    //
    semanticsAnnotations: {
      "TeX": ["TeX", "LaTeX", "application/x-tex"],
      "StarMath": ["StarMath 5.0"],
      "Maple": ["Maple"],
      "ContentMathML": ["MathML-Content", "application/mathml-content+xml"],
      "OpenMath": ["OpenMath"],
      "HTML":["HTML-Content","application/xhtml+xml"]
    },

    //
    //  These are the settings for the Show Source window.  The initial
    //  width and height will be reset after the source is shown in an
    //  attempt to make the window fit the output better.
    //
    windowSettings: {
      status: "no", toolbar: "no", locationbar: "no", menubar: "no",
      directories: "no", personalbar: "no", resizable: "yes", scrollbars: "yes",
      width: 100, height: 50
    },
    
    //
    //  This allows you to change the CSS that controls the menu
    //  appearance.  See the extensions/MathMenu.js file for details
    //  of the default settings.
    //
    styles: {}
    
  },
  
  //============================================================================
  //
  //  These parameters control the contextual menus that are available on the 
  //  mathematics within the page (provided the showMathMenu value is true above).
  //
  MathEvents: {
    //
    //  This is the time required for the mouse to be held still over a
    //  typeset equation in order for it to count as a hover (used when the
    //  zoom trigger is "Hover").  It is in milliseconds.
    //  
    hover: 500
  },

  //============================================================================
  //
  //  These parameters control the MMLorHTML configuration file.
  //  NOTE:  if you add MMLorHTML.js to the config array above,
  //  you must REMOVE the output jax from the jax array.
  //
  MMLorHTML: {}
});

MathJax.Ajax.loadComplete("[MathJax]/config/default.js");
