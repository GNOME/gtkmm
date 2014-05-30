/* Text Widget
 *
 * The GtkTextView widget displays a GtkTextBuffer. One GtkTextBuffer
 * can be displayed by multiple GtkTextViews. This demo has two views
 * displaying a single buffer, and shows off the widget's text
 * formatting features.
 *
 */

#include <cstdlib>
#include <gtkmm.h>
#include <gtk/gtk.h>

#include "demo-common.h"

using std::exit;

class Window_EasterEgg : public Gtk::Window
{
public:
  Window_EasterEgg();
  virtual ~Window_EasterEgg();

protected:
  virtual void recursive_attach_view(int depth, Gtk::TextView& view, Glib::RefPtr<Gtk::TextChildAnchor> refAnchor);

  //Member widgets:
  Gtk::TextView* m_pTextView;
  Gtk::ScrolledWindow m_ScrolledWindow;
};

class Example_TextView : public Gtk::Window
{
public:
  Example_TextView();
  virtual ~Example_TextView();

protected:
  virtual void create_tags(Glib::RefPtr<Gtk::TextBuffer>& refBuffer);
  virtual void insert_text(Glib::RefPtr<Gtk::TextBuffer>& refBuffer);
  virtual void attach_widgets(Gtk::TextView& text_view);
  virtual bool find_anchor(Gtk::TextBuffer::iterator& iter);

  //Signal handlers:
  virtual void on_button_clicked();


  //Member widgets
  Gtk::Paned m_VPaned;
  Gtk::TextView m_View1;
  Gtk::TextView* m_pView2;
  Gtk::ScrolledWindow m_ScrolledWindow1, m_ScrolledWindow2;

  Window_EasterEgg m_WindowEasterEgg;
};




//Called by DemoWindow;
Gtk::Window* do_textview()
{
  return new Example_TextView();
}

Example_TextView::Example_TextView()
: m_VPaned(Gtk::ORIENTATION_VERTICAL)
{
  set_default_size(450, 450);
  set_title("Text View");
  set_border_width(0);

  m_VPaned.set_border_width(5);
  add(m_VPaned);

  /* For convenience, we just use the autocreated buffer from
   * the first text view; you could also create the buffer
   * by itself with refBuffer->new(), then later create
   * a view widget.
   */
  Glib::RefPtr<Gtk::TextBuffer> refBuffer = m_View1.get_buffer();
  m_pView2 = Gtk::manage( new Gtk::TextView(refBuffer) );

  m_ScrolledWindow1.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VPaned.add1(m_ScrolledWindow1);
  m_ScrolledWindow1.add(m_View1);

  m_ScrolledWindow2.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VPaned.add2(m_ScrolledWindow2);
  m_ScrolledWindow2.add(*m_pView2);

  create_tags(refBuffer);
  insert_text(refBuffer);

  attach_widgets(m_View1);
  attach_widgets(*m_pView2);

  show_all();
}

Example_TextView::~Example_TextView()
{
}

void Example_TextView::create_tags(Glib::RefPtr<Gtk::TextBuffer>& refBuffer)
{
  /* Create a bunch of tags. Note that it's also possible to
   * create tags with Gtk::TextTag::create() then add them to the
   * tag table for the buffer, refBuffer->create_tag() is
   * just a convenience function. Also note that you don't have
   * to give tags a name.
   *
   * In any real app, another useful optimization would be to create
   * a Gtk::TextTagTable in advance, and reuse the same tag table for
   * all the buffers with the same tag set, instead of creating
   * new copies of the same tags for every buffer.
   *
   * Tags are assigned default priorities in order of addition to the
   * tag table.	 That is, tags created later that affect the same text
   * property affected by an earlier tag will override the earlier
   * tag.  You can modify tag priorities with
   * Gtk::TextTag::set_priority().
   */

  Glib::RefPtr<Gtk::TextBuffer::Tag> refTag;

  refTag = refBuffer->create_tag("heading");
  refTag->property_weight() = Pango::WEIGHT_BOLD;
  refTag->property_size() = 15 * Pango::SCALE;

  refBuffer->create_tag("italic")->property_style() = Pango::STYLE_ITALIC;
  refBuffer->create_tag("bold")->property_weight() = Pango::WEIGHT_BOLD;
  refBuffer->create_tag("big")->property_size() = 20 * Pango::SCALE;
  refBuffer->create_tag("xx-small")->property_scale() = Pango::SCALE_XX_SMALL;
  refBuffer->create_tag("x-large")->property_scale() = Pango::SCALE_X_LARGE;
  refBuffer->create_tag("monospace")->property_family() = "monospace";
  refBuffer->create_tag("blue_foreground")->property_foreground() = "blue";
  refBuffer->create_tag("red_background")->property_background() = "red";

  refBuffer->create_tag("big_gap_before_line")->property_pixels_above_lines() = 30;
  refBuffer->create_tag("big_gap_after_line")->property_pixels_below_lines() = 30;
  refBuffer->create_tag("double_spaced_line")->property_pixels_inside_wrap() = 10;
  refBuffer->create_tag("not_editable")->property_editable() = FALSE;
  refBuffer->create_tag("word_wrap")->property_wrap_mode() = Gtk::WRAP_WORD;
  refBuffer->create_tag("char_wrap")->property_wrap_mode() = Gtk::WRAP_CHAR;
  refBuffer->create_tag("no_wrap")->property_wrap_mode() = Gtk::WRAP_NONE;
  refBuffer->create_tag("center")->property_justification() = Gtk::JUSTIFY_CENTER;
  refBuffer->create_tag("right_justify")->property_justification() = Gtk::JUSTIFY_RIGHT;

  refTag = refBuffer->create_tag("wide_margins");
  refTag->property_left_margin() = 50;
  refTag->property_right_margin() = 50;

  refBuffer->create_tag("strikethrough")->property_strikethrough() = true;
  refBuffer->create_tag("underline")->property_underline() = Pango::UNDERLINE_SINGLE;
  refBuffer->create_tag("double_underline")->property_underline() = Pango::UNDERLINE_DOUBLE;

  refTag = refBuffer->create_tag("superscript");
  refTag->property_rise() = 10 * Pango::SCALE;	  /* 10 pixels */
  refTag->property_size() = 8 * Pango::SCALE;	  /* 8 points */

  refTag = refBuffer->create_tag("subscript");
  refTag->property_rise() = -10 * Pango::SCALE;   /* 10 pixels */
  refTag->property_size() = 8 * Pango::SCALE;	   /* 8 points */

  refTag = refBuffer->create_tag("rtl_quote");
  refTag->property_wrap_mode() = Gtk::WRAP_WORD;
  refTag->property_direction() = Gtk::TEXT_DIR_RTL;
  refTag->property_indent() = 30;
  refTag->property_left_margin() = 20;
  refTag->property_right_margin() = 20;
}

void Example_TextView::insert_text(Glib::RefPtr<Gtk::TextBuffer>& refBuffer)
{
  Glib::RefPtr<Gdk::Pixbuf> refPixbuf = Gdk::Pixbuf::create_from_file(demo_find_file("gtk-logo-rgb.gif"));

  if(!refPixbuf)
  {
    //TODO: This is not real error handling.
    g_printerr ("Failed to load image file gtk-logo-rgb.gif\n");
    exit (1);
  }

  Glib::RefPtr<Gdk::Pixbuf> refScaled = refPixbuf->scale_simple(32, 32, Gdk::INTERP_BILINEAR);
  refPixbuf = refScaled;

  /* get start of buffer; each insertion will revalidate the
   * iterator to point to just after the inserted text.
   */

  Gtk::TextBuffer::iterator iter = refBuffer->get_iter_at_offset(0);

  iter = refBuffer->insert(iter, "The text widget can display text with all kinds of nifty attributes. It also supports multiple views of the same buffer; this demo is showing the same buffer in two places.\n\n");
  iter = refBuffer->insert_with_tag(iter, "Font styles. ", "heading");
  iter = refBuffer->insert(iter, "For example, you can have ");
  iter = refBuffer->insert_with_tag(iter, "italic", "italic");

  iter = refBuffer->insert(iter, ", ");
  iter = refBuffer->insert_with_tag(iter, "bold", "bold");
  iter = refBuffer->insert(iter, ", or ");
  iter = refBuffer->insert_with_tag(iter, "monospace (typewriter)", "monospace");
  iter = refBuffer->insert(iter, ", or ");
  iter = refBuffer->insert_with_tag(iter, "big", "big");
  iter = refBuffer->insert(iter, " text. ");
  iter = refBuffer->insert(iter, "It's best not to hardcode specific text sizes; you can use relative sizes as with CSS, such as ");
  iter = refBuffer->insert_with_tag(iter, "xx-small", "xx-small");
  iter = refBuffer->insert(iter, " or ");
  iter = refBuffer->insert_with_tag(iter, "x-large", "x-large");
  iter = refBuffer->insert(iter, " to ensure that your program properly adapts if the user changes the default font size.\n\n");

  iter = refBuffer->insert_with_tag(iter, "Colors. ", "heading");

  iter = refBuffer->insert(iter, "Colors such as ");
  iter = refBuffer->insert_with_tag(iter, "a blue foreground", "blue_foreground");
  iter = refBuffer->insert(iter, " or ");
  iter = refBuffer->insert_with_tag(iter, "a red background", "red_background");
  iter = refBuffer->insert(iter, " or even ");

  {
    std::vector<Glib::ustring> tag_names;

    tag_names.push_back("blue_foreground");
    tag_names.push_back("red_background");
    iter = refBuffer->insert_with_tags_by_name(iter, "a blue foreground on red background", tag_names);
  }

  iter = refBuffer->insert(iter, " (select that to read it) can be used.\n\n");

  iter = refBuffer->insert_with_tag(iter, "Underline, strikethrough, and rise. ", "heading");

  iter = refBuffer->insert_with_tag(iter, "Strikethrough", "strikethrough");
  iter = refBuffer->insert(iter, ", ");
  iter = refBuffer->insert_with_tag(iter, "underline", "underline");
  iter = refBuffer->insert(iter, ", ");
  iter = refBuffer->insert_with_tag(iter, "double underline", "double_underline");
  iter = refBuffer->insert(iter, ", ");
  iter = refBuffer->insert_with_tag(iter, "superscript", "superscript");
  iter = refBuffer->insert(iter, ", and ");
  iter = refBuffer->insert_with_tag(iter, "subscript", "subscript");
  iter = refBuffer->insert(iter, " are all supported.\n\n");

  iter = refBuffer->insert_with_tag(iter, "Images. ", "heading");

  iter = refBuffer->insert(iter, "The buffer can have images in it: ");
  iter = refBuffer->insert_pixbuf(iter, refPixbuf);
  iter = refBuffer->insert_pixbuf(iter, refPixbuf);
  iter = refBuffer->insert_pixbuf(iter, refPixbuf);
  iter = refBuffer->insert(iter, " for example.\n\n");

  iter = refBuffer->insert_with_tag(iter, "Spacing. ", "heading");

  iter = refBuffer->insert(iter, "You can adjust the amount of space before each line.\n");

  {
    std::vector<Glib::ustring> tag_names;

    tag_names.push_back("big_gap_before_line");
    tag_names.push_back("wide_margins");
    iter = refBuffer->insert_with_tags_by_name(iter,
  					    "This line has a whole lot of space before it.\n", tag_names);
    iter = refBuffer->insert_with_tags_by_name(iter,
  					    "You can also adjust the amount of space after each line; this line has a whole lot of space after it.\n", tag_names);
  }

  {
    std::vector<Glib::ustring> tag_names;

    tag_names.push_back("double_spaced_line");
    tag_names.push_back("wide_margins");
    iter = refBuffer->insert_with_tags_by_name(iter,
  					    "You can also adjust the amount of space between wrapped lines; this line has extra space between each wrapped line in the same paragraph. To show off wrapping, some filler text: the quick brown fox jumped over the lazy dog. Blah blah blah blah blah blah blah blah blah.\n",
  					    tag_names);
  }

  iter = refBuffer->insert(iter, "Also note that those lines have extra-wide margins.\n\n");

  iter = refBuffer->insert_with_tag(iter, "Editability. ", "heading");

  iter = refBuffer->insert_with_tag(iter,
					    "This line is 'locked down' and can't be edited by the user - just try it! You can't delete this line.\n\n",
					    "not_editable");

  iter = refBuffer->insert_with_tag(iter, "Wrapping. ", "heading");

  iter = refBuffer->insert(iter,
			  "This line (and most of the others in this buffer) is word-wrapped, using the proper Unicode algorithm. Word wrap should work in all scripts and languages that GTK+ supports. Let's make this a long paragraph to demonstrate: blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah\n\n");

  iter = refBuffer->insert_with_tag(iter,
					    "This line has character-based wrapping, and can wrap between any two character glyphs. Let's make this a long paragraph to demonstrate: blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah\n\n",
					    "char_wrap");

  iter = refBuffer->insert_with_tag(iter,
					    "This line has all wrapping turned off, so it makes the horizontal scrollbar appear.\n\n\n",
					    "no_wrap");

  iter = refBuffer->insert_with_tag(iter, "Justification. ", "heading");

  iter = refBuffer->insert_with_tag(iter, "\nThis line has center justification.\n", "center");

  iter = refBuffer->insert_with_tag(iter, "This line has right justification.\n", "right_justify");

  iter = refBuffer->insert_with_tag(iter,
					    "\nThis line has big wide margins. Text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text.\n",
					    "wide_margins");

  iter = refBuffer->insert_with_tag(iter, "Internationalization. ", "heading");

  iter = refBuffer->insert(iter,
      "You can put all sorts of Unicode text in the buffer.\n\nGerman (Deutsch S\xC3\xBC""d) "
      "Gr\xC3\xBC\xC3\x9F Gott\nGreek (\xCE\x95\xCE\xBB\xCE\xBB\xCE\xB7\xCE\xBD\xCE\xB9\xCE\xBA"
      "\xCE\xAC) \xCE\x93\xCE\xB5\xCE\xB9\xCE\xAC \xCF\x83\xCE\xB1\xCF\x82\nHebrew\t\xD7\xA9\xD7"
      "\x9C\xD7\x95\xD7\x9D\nJapanese (\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E)\n\nThe widget "
      "properly handles bidirectional text, word wrapping, DOS/UNIX/Unicode paragraph separators, "
      "grapheme boundaries, and so on using the Pango internationalization framework.\n");

  iter = refBuffer->insert(iter, "Here's a word-wrapped quote in a right-to-left language:\n");
  iter = refBuffer->insert_with_tag(iter,
      "\xD9\x88\xD9\x82\xD8\xAF \xD8\xA8\xD8\xAF\xD8\xA3 \xD8\xAB\xD9\x84\xD8\xA7\xD8\xAB "
      "\xD9\x85\xD9\x86 \xD8\xA3\xD9\x83\xD8\xAB\xD8\xB1 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA4"
      "\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD8\xAA\xD9\x82\xD8\xAF\xD9\x85\xD8\xA7 \xD9\x81\xD9\x8A "
      "\xD8\xB4\xD8\xA8\xD9\x83\xD8\xA9 \xD8\xA7\xD9\x83\xD8\xB3\xD9\x8A\xD9\x88\xD9\x86 \xD8\xA8"
      "\xD8\xB1\xD8\xA7\xD9\x85\xD8\xAC\xD9\x87\xD8\xA7 \xD9\x83\xD9\x85\xD9\x86\xD8\xB8\xD9\x85"
      "\xD8\xA7\xD8\xAA \xD9\x84\xD8\xA7 \xD8\xAA\xD8\xB3\xD8\xB9\xD9\x89 \xD9\x84\xD9\x84\xD8\xB1"
      "\xD8\xA8\xD8\xAD\xD8\x8C \xD8\xAB\xD9\x85 \xD8\xAA\xD8\xAD\xD9\x88\xD9\x84\xD8\xAA \xD9\x81"
      "\xD9\x8A \xD8\xA7\xD9\x84\xD8\xB3\xD9\x86\xD9\x88\xD8\xA7\xD8\xAA \xD8\xA7\xD9\x84\xD8\xAE"
      "\xD9\x85\xD8\xB3 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA7\xD8\xB6\xD9\x8A\xD8\xA9 \xD8\xA5\xD9\x84"
      "\xD9\x89 \xD9\x85\xD8\xA4\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD9\x85\xD8\xA7\xD9\x84\xD9\x8A"
      "\xD8\xA9 \xD9\x85\xD9\x86\xD8\xB8\xD9\x85\xD8\xA9\xD8\x8C \xD9\x88\xD8\xA8\xD8\xA7\xD8\xAA"
      "\xD8\xAA \xD8\xAC\xD8\xB2\xD8\xA1\xD8\xA7 \xD9\x85\xD9\x86 \xD8\xA7\xD9\x84\xD9\x86\xD8\xB8"
      "\xD8\xA7\xD9\x85 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA7\xD9\x84\xD9\x8A \xD9\x81\xD9\x8A \xD8\xA8"
      "\xD9\x84\xD8\xAF\xD8\xA7\xD9\x86\xD9\x87\xD8\xA7\xD8\x8C \xD9\x88\xD9\x84\xD9\x83\xD9\x86"
      "\xD9\x87\xD8\xA7 \xD8\xAA\xD8\xAA\xD8\xAE\xD8\xB5\xD8\xB5 \xD9\x81\xD9\x8A \xD8\xAE\xD8\xAF"
      "\xD9\x85\xD8\xA9 \xD9\x82\xD8\xB7\xD8\xA7\xD8\xB9 \xD8\xA7\xD9\x84\xD9\x85\xD8\xB4\xD8\xB1"
      "\xD9\x88\xD8\xB9\xD8\xA7\xD8\xAA \xD8\xA7\xD9\x84\xD8\xB5\xD8\xBA\xD9\x8A\xD8\xB1\xD8\xA9. "
      "\xD9\x88\xD8\xA3\xD8\xAD\xD8\xAF \xD8\xA3\xD9\x83\xD8\xAB\xD8\xB1 \xD9\x87\xD8\xB0\xD9\x87 "
      "\xD8\xA7\xD9\x84\xD9\x85\xD8\xA4\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD9\x86\xD8\xAC\xD8\xA7"
      "\xD8\xAD\xD8\xA7 \xD9\x87\xD9\x88 \xC2\xBB\xD8\xA8\xD8\xA7\xD9\x86\xD9\x83\xD9\x88\xD8\xB3"
      "\xD9\x88\xD9\x84\xC2\xAB \xD9\x81\xD9\x8A \xD8\xA8\xD9\x88\xD9\x84\xD9\x8A\xD9\x81\xD9\x8A"
      "\xD8\xA7.\n\n",
      "rtl_quote");

  iter = refBuffer->insert(iter, "You can put widgets in the buffer: Here's a button: ");

  Glib::RefPtr<Gtk::TextChildAnchor> refAnchor = refBuffer->create_child_anchor(iter);
  iter = refBuffer->insert(refBuffer->end(), " and a menu: ");
  refAnchor = refBuffer->create_child_anchor(iter); //TODO: Maybe this should be a method of the Iterator.
  iter = refBuffer->insert(refBuffer->end(), " and a scale: ");
  refAnchor = refBuffer->create_child_anchor(iter);
  iter = refBuffer->insert(refBuffer->end(), " and an animation: ");
  refAnchor = refBuffer->create_child_anchor(iter);
  iter = refBuffer->insert(refBuffer->end(), " finally a text entry: ");
  refAnchor = refBuffer->create_child_anchor(iter);
  iter = refBuffer->insert(refBuffer->end(), ".\n");

  refBuffer->insert(iter, "\n\nThis demo doesn't demonstrate all the GtkTextBuffer features; it leaves out, for example: invisible/hidden text (doesn't work in GTK 2, but planned), tab stops, application-drawn areas on the sides of the widget for displaying breakpoints and such...");

  // Apply word_wrap tag to whole buffer
  Gtk::TextBuffer::iterator start, end;
  refBuffer->get_bounds(start, end);
  refBuffer->apply_tag_by_name("word_wrap", start, end);
}

bool Example_TextView::find_anchor(Gtk::TextBuffer::iterator& iter)
{
  while(++iter)
  {
    if(iter.get_child_anchor())
      return true;
  }
  return false;
}

void Example_TextView::attach_widgets(Gtk::TextView& text_view)
{
  Glib::RefPtr<Gtk::TextBuffer> refBuffer = text_view.get_buffer();
  Gtk::TextBuffer::iterator iter = refBuffer->begin();

  int i = 0;
  while(find_anchor(iter)) //previously created with create_child_anchor().
  {
    Glib::RefPtr<Gtk::TextChildAnchor> refAnchor = iter.get_child_anchor();
    Gtk::Widget* pWidget = 0;
    if (i == 0)
    {
      Gtk::Button* pButton = Gtk::manage( new Gtk::Button("Click Me") );
      pButton->signal_clicked().connect(sigc::mem_fun(*this, &Example_TextView::on_button_clicked));
      pWidget = pButton;
    }
    else if (i == 1)
    {
      Gtk::ComboBoxText* pCombo = Gtk::manage( new Gtk::ComboBoxText() );
      pCombo->append("Option 1");
      pCombo->append("Option 2");
      pCombo->append("Option 3");

      pWidget = pCombo;
    }
    else if (i == 2)
    {
      Gtk::Scale* pHScale = Gtk::manage( new Gtk::Scale(Gtk::ORIENTATION_HORIZONTAL) );
      pHScale->set_range(0, 100);
      pHScale->set_size_request(70, -1);

      pWidget = pHScale;
    }
    else if (i == 3)
      {
        pWidget = Gtk::manage( new Gtk::Image(demo_find_file("floppybuddy.gif")) );
      }
    else if (i == 4)
    {
      pWidget = Gtk::manage( new Gtk::Entry() );
    }
    else
    {
      pWidget = 0;
      g_assert_not_reached ();
    }

    if(pWidget)
    {
      text_view.add_child_at_anchor(*pWidget, refAnchor);
      pWidget->show_all();
    }

    ++i;
  }
}

void Example_TextView::on_button_clicked()
{
  m_WindowEasterEgg.show_all();
}

Window_EasterEgg::Window_EasterEgg()
{
  set_default_size(300, 400);

  Glib::RefPtr<Gtk::TextBuffer> refBuffer = Gtk::TextBuffer::create();
  Gtk::TextBuffer::iterator iter = refBuffer->end();

  iter = refBuffer->insert(iter, "This buffer is shared by a set of nested text views.\n Nested view:\n");
  Glib::RefPtr<Gtk::TextChildAnchor> refAnchor = refBuffer->create_child_anchor(iter);
  refBuffer->insert(refBuffer->end(), "\nDon't do this in real applications, please.\n");

  m_pTextView = Gtk::manage( new Gtk::TextView(refBuffer) );

  recursive_attach_view(0, *m_pTextView, refAnchor);

  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  add(m_ScrolledWindow);
  m_ScrolledWindow.add(*m_pTextView);
}

Window_EasterEgg::~Window_EasterEgg()
{
}

void Window_EasterEgg::recursive_attach_view(int depth, Gtk::TextView& view, Glib::RefPtr<Gtk::TextChildAnchor> refAnchor)
{
  if (depth > 4)
    return;

  Gtk::TextView* pChildView = Gtk::manage( new Gtk::TextView(view.get_buffer()));

  /* Event box is to add a black border around each child view */
  Gtk::EventBox* pEventBox = Gtk::manage( new Gtk::EventBox());
  Gdk::RGBA color("black");
  pEventBox->override_background_color(color);

  pChildView->set_halign(Gtk::ALIGN_CENTER);
  pChildView->set_valign(Gtk::ALIGN_CENTER);
  pChildView->set_border_width(1);

  pEventBox->add(*pChildView);

  view.add_child_at_anchor(*pEventBox, refAnchor);
  recursive_attach_view (depth + 1, *pChildView, refAnchor);
}
