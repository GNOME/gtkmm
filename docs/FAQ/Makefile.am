docbook_docs = gtkmm-faq.xml

include $(top_srcdir)/docs/Makefile_web.am_fragment
gtkmm_faq_path  = $(web_path_docs)FAQ

EXTRA_DIST = README gtkmm-faq.xml html

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl

# The new XML DocBook way:
html/index.html: $(docbook_docs)
	xsltproc -o html/ --catalogs $(DOCBOOK_STYLESHEET) $<

post-html: html/index.html
	rsync $(rsync_args) -r html $$USER@shell.sourceforge.net:$(gtkmm_faq_path)/

doc-clean:
	-rm -rf html

all-local: html/index.html

maintainer-clean-local: doc-clean

.PHONY: post-html doc-clean

