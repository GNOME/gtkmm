<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:m="http://www.w3.org/1998/Math/MathML">

<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl"/>
<!--
To use xml catalogs on windows with xsltproc, use:
set XML_CATALOG_FILES=c:\catalog.xml
set XML_DEBUG_CATALOG=1
-->

<!--
xsltproc command line:
xsltproc -o html/ -xinclude docbook_phpwebnotes.xsl gtkmm-tut-with-examples.xml
-->

<!-- set 'html.ext' to '.php' -->
<xsl:param name="html.ext" select="'.php'" />
<!-- need to use id's as filename to have a reference point that will stay
constant over time. Otherwise notes would show up on the wrong after a 
chapter/section has been added in the middle of the document. -->
<xsl:param name="use.id.as.filename" select="1" />

<xsl:template name="user.head.content">
  <xsl:processing-instruction name="php">
    require_once('../phpwebnotes/core/api.php');
    pwn_head();
  ?</xsl:processing-instruction>
</xsl:template>

<xsl:template name="user.footer.content">
  <hr />
  <xsl:processing-instruction name="php">
  pwn_body(basename( __FILE__ ), $PHP_SELF, isset($page_prev) ? $page_prev : "", isset($page_next) ? $page_next : "", isset($page_parent) ? $page_parent : "");
  ?</xsl:processing-instruction>
</xsl:template>

</xsl:stylesheet>
