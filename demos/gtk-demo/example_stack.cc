/* Stack
 *
 * Gtk::Stack is a container that shows a single child at a time,
 * with nice transitions when the visible child changes.
 *
 * Gtk::StackSwitcher adds buttons to control which child is visible.
 */

#include "gtkmm.h"

class Example_Stack : public Gtk::Window
{
public:
  Example_Stack();
  virtual ~Example_Stack();

protected:

  // Containers
  Gtk::Grid m_grid;
  Gtk::Stack m_stack;

  // Widgets
  Gtk::StackSwitcher m_stack_switcher;
  Gtk::Image m_image;
  Gtk::CheckButton m_check_button;
  Gtk::Spinner m_spinner;

private:
};

//Called by DemoWindow;
Gtk::Window* do_stack()
{
  return new Example_Stack();
}

Example_Stack::Example_Stack()
{
  // Window properties
  set_title("Stack");

  // Build stack
  m_stack.add(m_image, "page1", "Page 1");
  m_stack.add(m_check_button, "page2", "Page 2");
  m_stack.add(m_spinner, "page3");

  // Page 1
  m_image.set_from_icon_name("gtk3-demo", Gtk::ICON_SIZE_DIALOG);

  // Page 2
  m_check_button.set_label("Page 2");
  m_check_button.set_halign(Gtk::ALIGN_CENTER);

  // Page 3
  m_stack.child_property_icon_name(m_spinner) = "face-laugh-symbolic";
  m_spinner.property_active() = true;

  // Stack transition
  m_stack.set_transition_type(Gtk::STACK_TRANSITION_TYPE_CROSSFADE);

  // Layout
  m_stack_switcher.set_stack(m_stack);
  m_grid.attach(m_stack_switcher, 0, 0, 1, 1);
  m_grid.attach(m_stack, 0, 1, 1, 1);
  add(m_grid);

  show_all_children();
}

Example_Stack::~Example_Stack()
{
}
