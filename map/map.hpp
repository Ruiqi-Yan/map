/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
        class Key,
        class T,
        class Compare = std::less<Key>
> class map {
 public:
  /**
   * the internal type of data.
   * it should have a default constructor, a copy constructor.
   * You can use sjtu::map as value_type by typedef.
   */
  typedef pair<const Key, T> value_type;
  /**
   * see BidirectionalIterator at CppReference for help.
   *
   * if there is anything wrong throw invalid_iterator.
   *     like it = map.begin(); --it;
   *       or it = map.end(); ++end();
   */
  class node
  {
    friend map<Key,T,Compare>;
   private:
    value_type data;
    node *left;
    node *right;
    int height;
    node *next;
    node *previous;

   public:
    node(const value_type &Data,int h=1,
         node *l= nullptr,
         node *r= nullptr):data(std::move(Data)),height(h),left(l),right(r){};

    ~node()=default;
  };

  class const_iterator;
  class iterator {
    friend map<Key,T,Compare>;
    friend const_iterator;
   private:
    /**
     * TODO add data members
     *   just add whatever you want.
     */
    node *pointer;
    map<Key,T,Compare> *p_map;

   public:
    iterator(node *p1= nullptr,map<Key,T,Compare> *p2= nullptr) {
      // TODO
      pointer=p1;
      p_map=p2;
    }

    iterator(const iterator &other) {
      // TODO
      pointer=other.pointer;
      p_map=other.p_map;
    }

    /**
     * TODO iter++
     */
    iterator operator++(int)
    {
      if(!pointer || !pointer->next || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      iterator it(pointer,p_map);
      pointer=pointer->next;
      return it;
    }

    /**
     * TODO ++iter
     */
    iterator & operator++()
    {
      if(!pointer || !pointer->next || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      pointer=pointer->next;
      return *this;
    }

    /**
     * TODO iter--
     */
    iterator operator--(int)
    {
      if(!pointer || !pointer->previous
         || pointer==p_map->head
         || pointer==p_map->head->next
         || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      iterator it(pointer,p_map);
      pointer= pointer->previous;
      return it;
    }

    /**
     * TODO --iter
     */
    iterator & operator--()
    {
      if(!pointer || !pointer->previous
         || pointer==p_map->head
         || pointer==p_map->head->next)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      pointer=pointer->previous;
      return *this;
    }

    /**
     * a operator to check whether two iterators are same (pointing to the same memory).
     */
    value_type & operator*() const
    {
      return pointer->data;
    }
    bool operator==(const iterator &rhs) const
    {
      return pointer==rhs.pointer;
    }
    bool operator==(const const_iterator &rhs) const
    {
      return pointer==rhs.pointer;
    }

    /**
     * some other operator for iterator.
     */
    bool operator!=(const iterator &rhs) const
    {
      return pointer!=rhs.pointer;
    }
    bool operator!=(const const_iterator &rhs) const
    {
      return pointer!=rhs.pointer;
    }

    /**
     * for the support of it->first.
     * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
     */
    value_type* operator->() const noexcept
    {
      return &(pointer->data);
    }
  };

  class const_iterator {
    // it should have similar member method as iterator.
    //  and it should be able to construct from an iterator.
   private:
    // data members.
    const node *pointer;
    const map<Key,T,Compare> *p_map;
    friend iterator;

   public:
    const_iterator(const node *p1= nullptr,const map<Key,T,Compare> *p2= nullptr) {
      // TODO
      pointer=p1;
      p_map=p2;
    }

    const_iterator(const const_iterator &other) {
      // TODO
      pointer=other.pointer;
      p_map=other.p_map;
    }

    const_iterator(const iterator &other) {
      // TODO
      pointer=other.pointer;
      p_map=other.p_map;
    }

    // And other methods in iterator.
    // And other methods in iterator.
    // And other methods in iterator.
    /**
     * TODO iter++
     */
    const_iterator operator++(int)
    {
      if(!pointer || !pointer->next || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      const_iterator it(pointer,p_map);
      pointer=pointer->next;
      return it;
    }

    /**
     * TODO ++iter
     */
    const_iterator & operator++()
    {
      if(!pointer || !pointer->next || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      pointer=pointer->next;
      return *this;
    }

    /**
     * TODO iter--
     */
    const_iterator operator--(int)
    {
      if(!pointer || !pointer->previous
         || pointer==p_map->head
         || pointer==p_map->head->next
         || pointer==p_map->tail)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      const_iterator it(pointer,p_map);
      pointer=pointer->previous;
      return it;
    }

    /**
     * TODO --iter
     */
    const_iterator & operator--()
    {
      if(!pointer || !pointer->previous
         || pointer==p_map->head
         || pointer==p_map->head->next)
      {
        invalid_iterator invalid_iterator;
        throw invalid_iterator;
      }
      pointer=pointer->previous;
      return *this;
    }

    /**
     * a operator to check whether two iterators are same (pointing to the same memory).
     */
    const value_type & operator*() const
    {
      return pointer->data;
    }
    bool operator==(const iterator &rhs) const
    {
      return pointer==rhs.pointer;
    }
    bool operator==(const const_iterator &rhs) const
    {
      return pointer==rhs.pointer;
    }

    /**
     * some other operator for iterator.
     */
    bool operator!=(const iterator &rhs) const
    {
      return pointer!=rhs.pointer;
    }
    bool operator!=(const const_iterator &rhs) const
    {
      return pointer!=rhs.pointer;
    }

    /**
     * for the support of it->first.
     * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
     */
    const value_type* operator->() const noexcept
    {
      return &(pointer->data);
    }
  };

 private:
  node *root;
  node *head;
  node *tail;
  int number;

 public:
  int height(node *p)
  {
    if(p) {return p->height;}
    return 0;
  }

  int max(int a,int b)
  {
    if(a>b) {return a;}
    return b;
  }
  /**
   * TODO two constructors
   */
  map():number(0),root(nullptr)
  {
    void *p= operator new(sizeof(node));
    head=static_cast<node*>(p);
    p= operator new(sizeof(node));
    tail=static_cast<node*>(p);
    head->previous= nullptr;
    head->next=tail;
    tail->previous=head;
    tail->next= nullptr;
  }

  void copy(node * &p,const node *other)
  {
    if(!other->left && !other->right) { return;}
    if(other->left)
    {
      p->left=new node(other->left->data,other->left->height);
      p->previous->next=p->left;
      p->left->previous=p->previous;
      p->left->next=p;
      p->previous=p->left;
      copy(p->left,other->left);
    }
    if(other->right)
    {
      p->right=new node(other->right->data,other->right->height);
      p->next->previous=p->right;
      p->right->previous=p;
      p->right->next=p->next;
      p->next=p->right;
      copy(p->right,other->right);
    }
  }

  map(const map &other):root(nullptr)
  {
    void *p= operator new(sizeof(node));
    head=static_cast<node*>(p);
    p= operator new(sizeof(node));
    tail=static_cast<node*>(p);
    head->previous= nullptr;
    head->next=tail;
    tail->previous=head;
    tail->next= nullptr;
    number=other.number;
    if(number)
    {
      root=new node(other.root->data,other.root->height);
      root->previous=head;
      root->next=tail;
      head->next=root;
      tail->previous=root;
      copy(root,other.root);
    }
  }

  /**
   * TODO assignment operator
   */
  map & operator=(const map &other)
  {
    if(this==&other) {return *this;}
    if(number)
    {
      node *p1=head->next;
      node *p2;
      for(int i=1;i<=number;++i)
      {
        p2=p1->next;
        delete p1;
        p1=p2;
      }
    }
    root= nullptr;
    head->previous= nullptr;
    head->next=tail;
    tail->previous=head;
    tail->next= nullptr;
    number=other.number;
    if(number)
    {
      root=new node(other.root->data,other.root->height);
      root->previous=head;
      root->next=tail;
      head->next=root;
      tail->previous=root;
      copy(root,other.root);
    }
    return *this;
  }

  /**
   * TODO Destructors
   */
  ~map()
  {
    if(number)
    {
      node *p1=head->next;
      node *p2;
      for(int i=1;i<=number;++i)
      {
        p2=p1->next;
        delete p1;
        p1=p2;
      }
    }
    operator delete(head);
    operator delete(tail);
  }

  /**
   * TODO
   * access specified element with bounds checking
   * Returns a reference to the mapped value of the element with key equivalent to key.
   * If no such element exists, an exception of type `index_out_of_bound'
   */
  T & at(const Key &key)
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else {return p->data.second;}
    }
    index_out_of_bound index_out_of_bound;
    throw index_out_of_bound;
  }

  const T & at(const Key &key) const
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else {return p->data.second;}
    }
    index_out_of_bound index_out_of_bound;
    throw index_out_of_bound;
  }

  /**
   * TODO
   * access specified element
   * Returns a reference to the value that is mapped to a key equivalent to key,
   *   performing an insertion if such key does not already exist.
   */
  T & operator[](const Key &key)
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else {return p->data.second;}
    }
    value_type tmp(key,T());
    return insert(tmp).first->second;
  }

  /**
   * behave like at() throw index_out_of_bound if such key does not exist.
   */
  const T & operator[](const Key &key) const
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else {return p->data.second;}
    }
    index_out_of_bound index_out_of_bound;
    throw index_out_of_bound;
  }

  /**
   * return a iterator to the beginning
   */
  iterator begin()
  {
    iterator it(head->next,this);
    return it;
  }
  const_iterator cbegin() const
  {
    const_iterator it(head->next,this);
    return it;
  }

  /**
   * return a iterator to the end
   * in fact, it returns past-the-end.
   */
  iterator end()
  {
    iterator it(tail,this);
    return it;
  }
  const_iterator cend() const
  {
    const_iterator it(tail,this);
    return it;
  }

  /**
   * checks whether the container is empty
   * return true if empty, otherwise false.
   */
  bool empty() const {
    return number==0;
  }

  /**
   * returns the number of elements.
   */
  size_t size() const {
    return number;
  }

  /**
   * clears the contents
   */
  void clear()
  {
    if(number)
    {
      node *p1=head->next;
      node *p2;
      for(int i=1;i<=number;++i)
      {
        p2=p1->next;
        delete p1;
        p1=p2;
      }
    }
    root= nullptr;
    head->previous= nullptr;
    head->next=tail;
    tail->previous=head;
    tail->next= nullptr;
    number=0;
  }

  /**
   * insert an element.
   * return a pair, the first of the pair is
   *   the iterator to the new element (or the element that prevented the insertion),
   *   the second one is true if insert successfully, or false.
   */
  void LL(node * &t)
  {
    node *tmp=t->left;
    t->left=tmp->right;
    tmp->right=t;
    t->height=max(height(t->left), height(t->right))+1;
    tmp->height=max(height(tmp->left), height(t))+1;
    t=tmp;
  }

  void RR(node * &t)
  {
    node *tmp=t->right;
    t->right=tmp->left;
    tmp->left=t;
    t->height=max(height(t->right), height(t->left))+1;
    tmp->height=max(height(t->right), height(t))+1;
    t=tmp;
  }

  void LR(node * &t)
  {
    RR(t->left);
    LL(t);
  }

  void RL(node * &t)
  {
    LL(t->right);
    RR(t);
  }

  pair<iterator, bool> insert_l(const value_type &value,node * &t,node *parent)
  {
    if(t== nullptr)
    {
      t=new node(value,1);
      t->next=parent;
      t->previous=parent->previous;
      t->previous->next=t;
      parent->previous=t;
      ++number;
      t->height=max(height(t->left), height(t->right))+1;
      iterator it(t,this);
      pair<iterator, bool> result(it, true);
      return result;
    }
    else
    {
      Compare compare;
      if(compare(t->data.first,value.first))
      {
        pair<iterator, bool> result=insert_r(value,t->right,t);
        if(height(t->right)-height(t->left)==2)
        {
          if(compare(value.first,t->right->data.first)) {RL(t);}
          else {RR(t);}
        }
        t->height=max(height(t->left), height(t->right))+1;
        return result;
      }
      else if(compare(value.first,t->data.first))
      {
        pair<iterator, bool> result=insert_l(value,t->left,t);
        if(height(t->left)-height(t->right)==2)
        {
          if(compare(value.first,t->left->data.first)) {LL(t);}
          else {LR(t);}
        }
        t->height=max(height(t->left), height(t->right))+1;
        return result;
      }
      else
      {
        iterator it(t,this);
        pair<iterator, bool> result(it, false);
        return result;
      }
    }
  }

  pair<iterator, bool> insert_r(const value_type &value,node * &t,node * parent)
  {
    if(t== nullptr)
    {
      t=new node(value,1);
      t->next=parent->next;
      t->previous=parent;
      t->next->previous=t;
      parent->next=t;
      ++number;
      t->height=max(height(t->left), height(t->right))+1;
      iterator it(t,this);
      pair<iterator, bool> result(it, true);
      return result;
    }
    else
    {
      Compare compare;
      if(compare(t->data.first,value.first))
      {
        pair<iterator, bool> result=insert_r(value,t->right,t);
        if(height(t->right)-height(t->left)==2)
        {
          if(compare(value.first,t->right->data.first)) {RL(t);}
          else {RR(t);}
        }
        t->height=max(height(t->left), height(t->right))+1;
        return result;
      }
      else if(compare(value.first,t->data.first))
      {
        pair<iterator, bool> result=insert_l(value,t->left,t);
        if(height(t->left)-height(t->right)==2)
        {
          if(compare(value.first,t->left->data.first)) {LL(t);}
          else {LR(t);}
        }
        t->height=max(height(t->left), height(t->right))+1;
        return result;
      }
      else
      {
        iterator it(t,this);
        pair<iterator, bool> result(it, false);
        return result;
      }
    }
  }

  pair<iterator, bool> insert(const value_type &value)
  {
    if(number)
    {
      Compare compare;
      if(compare(root->data.first,value.first))
      {
        pair<iterator, bool> result=insert_r(value,root->right,root);
        root->height=max(height(root->left), height(root->right))+1;
        return result;
      }
      else if(compare(value.first,root->data.first))
      {
        pair<iterator, bool> result=insert_l(value,root->left,root);
        root->height=max(height(root->left), height(root->right))+1;
        return result;
      }
      else
      {
        iterator it(root,this);
        pair<iterator, bool> result(it, false);
        return result;
      }
    }
    else
    {
      root=new node(value,1);
      head->next=root;
      root->previous= head;
      root->next=tail;
      tail->previous=root;
      ++number;
      iterator it(root,this);
      pair<iterator, bool> result(it, true);
      return result;
    }
  }

  /**
   * erase the element at pos.
   *
   * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
   */
  bool adjust(node * &t,int type)
  {
    if(type)
    {
      if(height(t->left)- height(t->right)==1) {return true;}
      if(height(t->right) - height(t->left)==0)
      {
        --t->height;
        return false;
      }
      if(height(t->left->right)> height(t->left->left))
      {
        LR(t);
        return false;
      }
      LL(t);
      if(height(t->left) - height(t->right)==0) {return false;}
      else {return true;}
    }

    else
    {
      if(height(t->right)- height(t->left)==1) {return true;}
      if(height(t->right)- height(t->left)==0)
      {
        --t->height;
        return false;
      }
      if(height(t->right->left)> height(t->right->right))
      {
        RL(t);
        return false;
      }
      RR(t);
      if(height(t->right) - height(t->left)==0) {return false;}
      else {return true;}
    }
  }

  bool erase(const Key &key,node * &t)
  {
    if(!t) {return true;}
    Compare compare;
    if(compare(key,t->data.first))
    {
      if(erase(key,t->left)) {return true;}
      return adjust(t,0);
    }
    else if(compare(t->data.first,key))
    {
      if(erase(key,t->right)) {return true;}
      return adjust(t,1);
    }
    else
    {
      if(!t->left || !t->right)
      {
        node *tmp=t;
        if(t->left) {t=t->left;}
        else {t=t->right;}
        tmp->left= nullptr;
        tmp->right= nullptr;
        delete tmp;
        return false;
      }
      else
      {
        node *tmp1=t->right;
        while (tmp1->left) {tmp1=tmp1->left;}
        node *tmp2=t;
        t=new node(tmp1->data,tmp2->height,tmp2->left,tmp2->right);
        tmp2->previous->next=t;
        tmp2->next->previous=t;
        t->next=tmp2->next;
        t->previous=tmp2->previous;
        tmp2->left= nullptr;
        tmp2->right= nullptr;
        delete tmp2;
        if(erase(tmp1->data.first,t->right)) {return true;}
        return adjust(t,1);
      }
    }
  }

  void erase(iterator pos)
  {
    if(pos==end() || pos.p_map!=this)
    {
      invalid_iterator invalid_iterator;
      throw invalid_iterator;
    }
    else if (number == 0)
    {
      container_is_empty container_is_empty;
      throw container_is_empty;
    }
    else
    {
      --number;
      erase(pos->first,root);
    }
  }

  /**
   * Returns the number of elements with key
   *   that compares equivalent to the specified argument,
   *   which is either 1 or 0
   *     since this container does not allow duplicates.
   * The default method of check the equivalence is !(a < b || b > a)
   */
  size_t count(const Key &key) const
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else {return 1;}
    }
    return 0;
  }

  /**
   * Finds an element with key equivalent to key.
   * key value of the element to search for.
   * Iterator to an element with key equivalent to key.
   *   If no such element is found, past-the-end (see end()) iterator is returned.
   */
  iterator find(const Key &key)
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else
      {
        iterator it(p,this);
        return it;
      }
    }
    return end();
  }

  const_iterator find(const Key &key) const
  {
    node *p=root;
    Compare compare;
    while (p)
    {
      if(compare(p->data.first,key)) {p=p->right;}
      else if(compare(key,p->data.first)) {p=p->left;}
      else
      {
        const_iterator it(p,this);
        return it;
      }
    }
    return cend();
  }
};

}

#endif