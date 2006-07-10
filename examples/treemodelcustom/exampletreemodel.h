//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_EXAMPLETREEMODEL_H
#define GTKMM_EXAMPLETREEMODEL_H

#include <glibmm/object.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treepath.h>

class ExampleTreeModel
  : public Glib::Object,
    public Gtk::TreeModel
{
protected:
  //Create a TreeModel with @a columns_count number of columns, each of type Glib::ustring.
  ExampleTreeModel(unsigned int columns_count = 10);
  virtual ~ExampleTreeModel();
  
public:
  static Glib::RefPtr<ExampleTreeModel> create();

  Gtk::TreeModelColumn< Glib::ustring >& get_model_column(int column);

protected:

   // Overrides:
   virtual Gtk::TreeModelFlags get_flags_vfunc() const;
   virtual int get_n_columns_vfunc() const;
   virtual GType get_column_type_vfunc(int index) const;
   virtual void get_value_vfunc(const TreeModel::iterator& iter, int column, Glib::ValueBase& value) const;
  
   bool iter_next_vfunc(const iterator& iter, iterator& iter_next) const;

   //TODO: Make sure that we make all of these const when we have made them all const in the TreeModel:
   virtual bool iter_children_vfunc(const iterator& parent, iterator& iter) const;
   virtual bool iter_has_child_vfunc(const iterator& iter) const;
   virtual int iter_n_children_vfunc(const iterator& iter) const;
   virtual int iter_n_root_children_vfunc() const;
   virtual bool iter_nth_child_vfunc(const iterator& parent, int n, iterator& iter) const;
   virtual bool iter_nth_root_child_vfunc(int n, iterator& iter) const;
   virtual bool iter_parent_vfunc(const iterator& child, iterator& iter) const;
   virtual Path get_path_vfunc(const iterator& iter) const;
   virtual bool get_iter_vfunc(const Path& path, iterator& iter) const;

   virtual bool iter_is_valid(const iterator& iter) const;

private:
   typedef std::vector< Glib::ustring> typeRow; //X columns, all of type string.
   typedef std::vector< typeRow > typeListOfRows; //Y rows.

   //This maps the GtkTreeIters to potential paths:
   //Each GlueItem might be stored in more than one GtkTreeIter,
   //but it will be deleted only once, because it is stored
   //only once in the GlueList.
   //GtkTreeIter::user_data might contain orphaned GlueList pointers,
   //but nobody will access them because GtkTreeIter::stamp will have the
   //wrong value, marking the user_data as invalid.
   class GlueItem
   {
   public:
     GlueItem(int row_number);
     int get_row_number() const;
     
   protected:
     int m_row_number;
   };

   //Allow the GlueList inner class to access the declaration of the GlueItem inner class.
   //SUN's Forte compiler complains about this.
   class GlueList;
   friend class GlueList; 
   
   class GlueList
   {
   public:
     GlueList();
     ~GlueList();

     //This is just a list of stuff to delete later:
     typedef std::list<GlueItem*> type_listOfGlue;
     type_listOfGlue m_list;
   };

   typeListOfRows::iterator get_data_row_iter_from_tree_row_iter(const iterator& iter);
   typeListOfRows::const_iterator get_data_row_iter_from_tree_row_iter(const iterator& iter) const;
   bool check_treeiter_validity(const iterator& iter) const;
   void remember_glue_item(GlueItem* item) const;

   //The data:
   typeListOfRows m_rows;

   //Column information:
   ColumnRecord m_column_record;

   typedef Gtk::TreeModelColumn<Glib::ustring> typeModelColumn;
   // Usually you would have different types for each column -
   // then you would want a vector of pointers to the model columns.
   typedef std::vector< typeModelColumn > typeListOfModelColumns;
   typeListOfModelColumns m_listModelColumns;

   int m_stamp; //When the model's stamp and the TreeIter's stamp are equal, the TreeIter is valid.
   mutable GlueList* m_pGlueList;
};

#endif //GTKMM_EXAMPLETREEMODEL_H

