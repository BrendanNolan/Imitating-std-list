#ifndef GUARD_LST_H
#define GUARD_LST_H

#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename T>
class Lst
{
    // BEGIN CONSTRUCTOR AND ASSIGNMENT MEMBERS
  public:
    Lst() { create(); };
    Lst(const Lst &);
    Lst &operator=(const Lst &);
    ~Lst();
    // END CONSTRUCTOR AND ASSIGNMENT MEMBERS

    // BEGIN NODE CLASS
  private:
    struct node
    {
        T data;
        node *fwd_link;
        node *bck_link;

        node() : fwd_link(0), bck_link(0) {}
        node(const T &new_data, node *new_fwd = 0, node *new_bck = 0)
            : data(new_data), fwd_link(new_fwd), bck_link(new_bck)
        {
        }
    };
    // END NODE CLASS

    // BEGIN ITERATOR CLASSES
  public:
    class iterator
    {
        // data members:
        node *ptr;

      public:
        // getter method
        node *get_ptr() const { return ptr; }
        //constructors
        iterator() : ptr(0) {}
        iterator(const iterator &other) : ptr(other.get_ptr()) {}
        iterator(node *p) : ptr(p) {}

        // operators
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        T &operator*() { return ptr->data; }
        node *operator->() const { return ptr; }
        bool operator==(const iterator &other) const
        {
            return ptr == other.get_ptr();
        }
        bool operator!=(const iterator &other) const
        {
            return !(*this == other);
        }
        iterator &operator=(const iterator &other) { ptr = other.get_ptr(); return *this; }
    };

    class const_iterator
    {
        // data members:
        const node *ptr;

      public:
        // getter method
        const node *get_ptr() const { return ptr; }
        //constructors
        const_iterator() : ptr(0) {}
        // kind-of copy constructor which takes an iterator and
        // copies it to a const_iterator
        const_iterator(const iterator &other) : ptr(other.get_ptr()) {}
        // actual copy constructor
        const_iterator(const const_iterator &other) : ptr(other.get_ptr()) {}
        const_iterator(node *p) : ptr(p) {}

        // operators
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        const T &operator*() { return ptr->data; }
        const node *operator->() const { return ptr; }
        bool operator==(const const_iterator &other) const
        {
            return ptr == other.get_ptr();
        }
        bool operator!=(const const_iterator &other) const
        {
            return !(*this == other);
        }
        const_iterator &operator=(const const_iterator &other) { ptr = other.get_ptr(); return *this; }
    };

    // END ITERATOR CLASSES
  public:
    typedef std::size_t size_type;
    // BEGIN MANAGEMENT FUNCTIONS
    void create();
    void create(const_iterator, const_iterator);
    void uncreate();
    void push_back_several(const_iterator, const_iterator);

    // END MANAGEMENT FUNCTIONS
  private:
    iterator start;
    iterator fin;
    size_type length;
    void rec_del(iterator);

  public:
    size_type size() & { return length; }
    // insert new value immediately before iterator it
    void insert(iterator, const T &);
    // erase value at it
    void erase(iterator it);
    void push_back(const T &new_data);
    void pop_back();

    iterator begin() { return start; }
    const_iterator begin() const { return start; }
    iterator end() { return fin; }
    const_iterator end() const { return fin; }
};

// Definitions of methods of the various (possibly nested) classes -------------

// Lst<T>
// management functions

template <typename T>
void Lst<T>::create()
{
    length = 0;
    fin = new node();
    start = fin;
}

template <typename T>
void Lst<T>::push_back_several(const_iterator i, const_iterator j)
{
    while (i != j)
    {
        push_back(*i);
        ++i;
    }
}

template <typename T>
void Lst<T>::create(const_iterator i, const_iterator j)
{
    create();
    push_back_several(i, j);
}

template <typename T>
void Lst<T>::uncreate()
{
    rec_del(start);
}
// constructors
template <typename T>
Lst<T>::Lst(const Lst &other)
{
    create(other.begin(), other.end());
}

// assignment operator
template <typename T>
Lst<T> &Lst<T>::operator=(const Lst &rhs)
{
    if (this != &rhs)
    {
        uncreate();
        push_back_several(rhs.begin(), rhs.end());
    }
    return *this;
}
// general methods
template <typename T>
void Lst<T>::insert(iterator it, const T &val)
{
    if (it == start)
    {
        start = new node(val, it.get_ptr(), 0);
        it->bck_link = start.get_ptr();
    }
    else
    {
        node *temp = new node(val, it.get_ptr(), it->bck_link);
        temp->fwd_link->bck_link = temp;
        temp->bck_link->fwd_link = temp;
    }
    ++length;
}

template <typename T>
void Lst<T>::push_back(const T &val)
{
    insert(fin, val);
}

template <typename T>
void Lst<T>::erase(iterator it)
{
    if (it == fin)
        throw std::domain_error("attempt to erase off-the-end iterator");
    else if (it == start)
    {
        start = it->fwd_link;
        start->bck_link = 0;

        delete it.get_ptr();
    }
    else
    {
        it->bck_link->fwd_link = it->fwd_link;
        it->fwd_link->bck_link = it->bck_link;
        delete it.get_ptr();
    }
    --length;
}

template <typename T>
void Lst<T>::pop_back()
{
    erase(fin->bck_link);
}

template <typename T>
void Lst<T>::rec_del(iterator it)
{
    if (it->fwd_link != fin.get_ptr())
        rec_del(it->fwd_link);
    erase(it);
}

// destructor
template <typename T>
Lst<T>::~Lst()
{
    uncreate();
    delete fin.get_ptr();
}

// Lst<T>::iterator
template <typename T>
typename Lst<T>::iterator &Lst<T>::iterator::operator++()
{
    ptr = ptr->fwd_link;
    return *this;
}

template <typename T>
typename Lst<T>::iterator Lst<T>::iterator::operator++(int)
{
    iterator old = *this;
    ptr = ptr->fwd_link;

    return old;
}

template <typename T>
typename Lst<T>::iterator &Lst<T>::iterator::operator--()
{
    ptr = ptr->bck_link;
    return *this;
}

template <typename T>
typename Lst<T>::iterator Lst<T>::iterator::operator--(int)
{
    iterator old = ptr;
    ptr = ptr->bck_link;

    return old;
}

// Lst<T>::const_iterator
template <typename T>
typename Lst<T>::const_iterator &Lst<T>::const_iterator::operator++()
{
    ptr = ptr->fwd_link;
    return *this;
}

template <typename T>
typename Lst<T>::const_iterator Lst<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ptr = ptr->fwd_link;

    return old;
}

template <typename T>
typename Lst<T>::const_iterator &Lst<T>::const_iterator::operator--()
{
    ptr = ptr->bck_link;
    return *this;
}

template <typename T>
typename Lst<T>::const_iterator Lst<T>::const_iterator::operator--(int)
{
    const_iterator old = ptr;
    ptr = ptr->bck_link;

    return old;
}

//------------------------------------------------------------------------------

#endif