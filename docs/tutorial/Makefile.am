include $(top_srcdir)/docs/Makefile_web.am_fragment

gtkmm_tut_path = $(web_path_docs)tutorial

SUBDIRS = figures

DOCBOOK_PHPWEBNOTES_TRANSFORM = docbook_phpwebnotes.xsl

EXTRA_DIST = README insert_example_code.pl gtkmm-tut.xml gtkmm-tut-with-examples.xml html $(DOCBOOK_PHPWEBNOTES_TRANSFORM)

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl


# Create a DocBook source file that doesn't have the examples' comments blocks:
gtkmm-tut-with-examples.xml: gtkmm-tut.xml insert_example_code.pl
	$(PERL_PATH) $(srcdir)/insert_example_code.pl $(top_srcdir)/examples/book $< >$@

# The new XML DocBook way:
html/index.html: gtkmm-tut-with-examples.xml
	rm -rf html
	$(mkinstalldirs) html
	xsltproc -o html/ --xinclude --catalogs $(DOCBOOK_STYLESHEET) $<

# Create a version of the tutorial that has phpwebnotes code in it.
html_withcomments/index.php: gtkmm-tut-with-examples.xml $(DOCBOOK_PHPWEBNOTES_TRANSFORM)
	rm -rf html_withcomments
	xsltproc -o html_withcomments/ --xinclude --catalogs $(DOCBOOK_PHPWEBNOTES_TRANSFORM) $<

validate_original: gtkmm-tut.xml
	xmllint --xinclude --valid --noout --catalogs $<

validate: gtkmm-tut-with-examples.xml
	xmllint --xinclude --valid --noout --catalogs $<

gtkmm-tut-html.tar.gz: html/index.html
	tar cf - figures html | gzip -c --best >$@

post-html: html/index.html
	rsync $(rsync_args) figures/*.png $$USER@shell.sourceforge.net:$(gtkmm_tut_path)/figures/
	rsync $(rsync_args) -r html/ $$USER@shell.sourceforge.net:$(gtkmm_tut_path)/html/

doc-clean:
	-rm -rf html
	-rm -rf html_withcomments
	-rm -f gtkmm-tut-with-examples.xml gtkmm-tut-html.tar.gz

tutorialdir = $(gtkmm_docdir)/tutorial/html

install-tutorial: html/index.html
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(tutorialdir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(tutorialdir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(tutorialdir)/$$f; \
	done

uninstall-tutorial: html/index.html
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(tutorialdir)/$$f"; \
	  rm -f $(DESTDIR)$(tutorialdir)/$$f; \
	done

all-local: html/index.html

install-data-local: install-tutorial

uninstall-local: uninstall-tutorial

maintainer-clean-local: doc-clean

.PHONY: post-html doc-clean install-tutorial uninstall-tutorial

