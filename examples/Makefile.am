example_dirs =		\
book			\
arrow			\
base			\
calendar		\
cellrenderercustom	\
dnd			\
exception		\
filesel			\
fixed			\
gdk			\
idle			\
markup			\
rulers			\
statusbar		\
stock			\
thread			\
tictactoe		\
window

# deprecated = clist ctree list text tree pixmap
# TODO:
# broken = input - uses std:: stuff that isn't the same with all versions of gcc. Doesn't seem to correspond to a GTK+ example anway.
#              layout - uses deprecated draw_string. demonstrates double-buffering which might not be useful anymore.
#              selection - It's still in C, and I have no idea what it's supposed to demonstrate, even when I run the C version in GTK+. murrayc.
#              thread
# mystery = drawingarea - need to put its scribble example somewhere appropriate.

SUBDIRS = $(example_dirs)
EXTRA_DIST = README Makefile.am_fragment

#Web upload:
include $(top_srcdir)/docs/Makefile_web.am_fragment

web_path = $(web_path_gtkmm2)examples

#rsync --cvs-exclude ignores *.o and anything in .cvsignore and some more:
rsync_options = -vzr --rsh ssh --cvs-exclude --delete-excluded --exclude=.libs --exclude=.deps --exclude=core --exclude=.cvsignore --exclude=a.out --exclude=Makefile --exclude=Makefile.in

post-html:
	rsync $(rsync_options) $(example_dirs) $$USER@shell.sourceforge.net:$(web_path)

.PHONY: post-html

