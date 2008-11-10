<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:fo="http://www.w3.org/1999/XSL/Format"
    version="1.0">

<xsl:output method="xml" version="1.0" indent="yes"/>

<xsl:param name="reference_prefix">../../../doc/gtkmm-2.4/docs/reference/html/</xsl:param>

<xsl:template match="/">
  <book title="gtkmm 2.4 library Reference Manual"
        name="gtkmm 2.4"
        link="{$reference_prefix}index.html">
  <chapters>
    <sub name="Classes" link="{$reference_prefix}classes.html">
      <xsl:apply-templates select="doxygenindex/compound[@kind='class']">
        <xsl:sort select="."/>
      </xsl:apply-templates>
    </sub>
    <sub name="Namespaces" link="{$reference_prefix}namespaces.html">
      <xsl:apply-templates select="doxygenindex/compound[@kind='namespace']">
        <xsl:sort select="."/>
      </xsl:apply-templates>
    </sub>
  </chapters>

  <functions>
    <!-- @todo: maybe select only the real functions, ie those with kind=="function"? -->
    <xsl:apply-templates select="doxygenindex/compound/member" mode="as-function"/>
  </functions>
  </book>
</xsl:template>

<xsl:template match="compound">
  <xsl:param name="name"><xsl:value-of select="name"/></xsl:param>
  <xsl:param name="link"><xsl:value-of select="@refid"/>.html</xsl:param>
  <sub name="{$name}" link="{$reference_prefix}{$link}">
  <xsl:apply-templates select="member" mode="as-sub">
    <xsl:sort select="."/>
  </xsl:apply-templates>
  </sub>
</xsl:template>

<xsl:template match="member" mode="as-function">
  <!--
  <function name="atk_set_value" link="atk-atkvalue.html#ATK-SET-VALUE"/>
  -->
  <xsl:variable name="fqn">
    <xsl:call-template name="get-fully-qualified-name" />
  </xsl:variable>
  <xsl:variable name="link">
    <xsl:call-template name="get-member-link" />
  </xsl:variable>
  <function name="{$fqn}" link="{$reference_prefix}{$link}"/>
</xsl:template>

<xsl:template match="member" mode="as-sub">
  <xsl:variable name="fqn">
    <xsl:call-template name="get-fully-qualified-name" />
  </xsl:variable>
  <xsl:variable name="link">
    <xsl:call-template name="get-member-link" />
  </xsl:variable>
  <sub name="{$fqn}" link="{$reference_prefix}{$link}"/>
</xsl:template>


<!-- get a url link for the current member node.
  The source xml looks like this:
  <compound refid="classGtk_1_1AboutDialog" kind="class"><name>Gtk::AboutDialog</name>
    <member refid="classGtk_1_1AboutDialog_1ad14950354fa1d9e7d02e951bd0f232e" kind="typedef"><name>SlotActivateLink</name></member>

  The URL for the member function is obtained by adding '.html' to the refid of
  the parent node.  The in-page anchor id is the portion of the child's refid
  that is different than the parent's refid, but without the leading '_1'
  So, in the example above, the url would be:
    classGtk_1_1AboutDialog.html#ad14950354fa1d9e7d02e951bd0f232e
-->
<xsl:template name="get-member-link">
  <xsl:variable name="offset">
    <xsl:value-of select="string-length(../@refid) + 3"/>
  </xsl:variable>
  <xsl:value-of select="concat(../@refid, '.html#', substring(@refid, $offset))"/>
</xsl:template>

<!-- Get the fully qualified name for the current class member node -->
<xsl:template name="get-fully-qualified-name">
  <xsl:value-of select="concat(../name, '::', name)"/>
</xsl:template>

</xsl:stylesheet>

<!-- vim:ts=2 sw=2:
-->
