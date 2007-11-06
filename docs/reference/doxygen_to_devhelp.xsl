<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:fo="http://www.w3.org/1999/XSL/Format"
    version="1.0">

<xsl:output method="xml" version="1.0" indent="yes"/>

<xsl:param name="reference_prefix">../../../doc/gtkmm-2.4/docs/reference/html/</xsl:param>

<xsl:template match="/">
  <book title="gtkmm 2.4 library Reference Manual"
        name="gtkmm 2.4"
        link="{$reference_prefix}../../index.html">
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
  <xsl:param name="base_name"><xsl:value-of select="name"/></xsl:param>
  <xsl:param name="parent_name"><xsl:value-of select="../name"/></xsl:param>
  <xsl:param name="name"><xsl:value-of select="concat($parent_name, '::', $base_name)"/></xsl:param>
  <!-- Link is refid attribute of parent element + "#" + diff between refid of parent and own refid -->
  <xsl:param name="refid_parent"><xsl:value-of select="parent::node()/@refid"/></xsl:param>
  <xsl:param name="own_refid"><xsl:value-of select="@refid"/></xsl:param>
  <xsl:param name="offset"><xsl:value-of select="string-length($refid_parent) + 3"/></xsl:param>
  <xsl:param name="ref_diff"><xsl:value-of select="substring($own_refid, $offset)"/></xsl:param>
  <xsl:param name="link"><xsl:value-of select="$refid_parent"/>.html#<xsl:value-of select="$ref_diff"/></xsl:param>
  <function name="{$name}" link="{$reference_prefix}{$link}"/>
</xsl:template>

<xsl:template match="member" mode="as-sub">
  <xsl:param name="base_name"><xsl:value-of select="name"/></xsl:param>
  <xsl:param name="parent_name"><xsl:value-of select="../name"/></xsl:param>
  <xsl:param name="name"><xsl:value-of select="concat($parent_name, '::', $base_name)"/></xsl:param>
  <!-- Link is refid attribute of parent element + "#" + diff between refid of parent and own refid -->
  <xsl:param name="refid_parent"><xsl:value-of select="parent::node()/@refid"/></xsl:param>
  <xsl:param name="own_refid"><xsl:value-of select="@refid"/></xsl:param>
  <xsl:param name="offset"><xsl:value-of select="string-length($refid_parent) + 3"/></xsl:param>
  <xsl:param name="ref_diff"><xsl:value-of select="substring($own_refid, $offset)"/></xsl:param>
  <xsl:param name="link"><xsl:value-of select="$refid_parent"/>.html#<xsl:value-of select="$ref_diff"/></xsl:param>
  <sub name="{$name}" link="{$reference_prefix}{$link}"/>
</xsl:template>

</xsl:stylesheet>

<!-- vim:ts=2 sw=2:
-->
