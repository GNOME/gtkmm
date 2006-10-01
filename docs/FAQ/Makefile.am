docbook_docs = gtkmm-faq.xml

include $(top_srcdir)/docs/Makefile_web.am_fragment
gtkmm_faq_path  = $(web_path_docs)FAQ

EXTRA_DIST = README gtkmm-faq.xml html

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl

# The new XML DocBook way:
html/index.html: $(docbook_docs)
	-rm -rf html
	$(mkinstalldirs) html
	xsltproc -o html/ --catalogs $(DOCBOOK_STYLESHEET) $<

post-html: html/index.html
	rsync $(rsync_args) -r html $$USER@$(web_host):$(gtkmm_faq_path)/

doc-clean:
	-rm -rf html

all-local: html/index.html

maintainer-clean-local: doc-clean

faqdir = $(gtkmm_docdir)/FAQ/html

install-faq: html/index.html
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(faqdir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(faqdir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(faqdir)/$$f; \
	done

uninstall-faq: html/index.html
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(faqdir)/$$f"; \
	  rm -f $(DESTDIR)$(faqdir)/$$f; \
	done

all-local: html/index.html

install-data-local: install-faq

uninstall-local: uninstall-faq

maintainer-clean-local: doc-clean

.PHONY: post-html doc-clean install-faq uninstall-faq

