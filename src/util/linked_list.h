/**
 * @file linked_list.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UTIL_LINKED_LIST_H
#define __UTIL_LINKED_LIST_H

#include <cstddef>

namespace util
{

template<typename TElement>
class LinkedList
{
public:
  class iterator;
  class const_iterator;

  friend class LinkedList::iterator;
  friend class LinkedList::const_iterator;

  LinkedList() : m_head(nullptr) {}
  LinkedList(const LinkedList& other) = delete;
  LinkedList& operator=(const LinkedList& other) = delete;

  template<typename TPushed>
  void pushFront(const TPushed& element)
  {
    ElementNode* new_node = new Node<TPushed>(element, nullptr, m_head);
    if (m_head != nullptr)
    {
      m_head->prev = new_node;
    }
    m_head = new_node;
  }

  template<typename TEmplaced, typename... TArgs>
  void emplaceFront(TArgs... args)
  {
    ElementNode* new_node = new Node<TEmplaced>(TEmplaced(args...),
                                                nullptr,
                                                m_head);
    if (m_head != nullptr)
    {
      m_head->prev = new_node;
    }
    m_head = new_node;
  }

  TElement& getFront() { return m_head->getElement(); }

  const TElement& getFront() const
  {
    return const_cast<LinkedList*>(this)->getFront();
  }

  ~LinkedList()
  {
    ElementNode* head = m_head;
    while (head != nullptr)
    {
      ElementNode* next = head->next;
      delete head;
      head = next;
    }
    m_head = nullptr;
  }

private:
  struct ElementNode
  {
    ElementNode* prev;
    ElementNode* next;

    mutable size_t observed;
    bool deleted;

    ElementNode(ElementNode* prev, ElementNode* next) :
      prev(prev), next(next), observed(0), deleted(false)
    {
    }

    virtual TElement& getElement() = 0;

    virtual ~ElementNode() = default;
  };

  template<typename TStored>
  struct Node : public ElementNode
  {
     TStored element;
     TElement& getElement() override { return element; }

     Node(const TStored& element, ElementNode* prev, ElementNode* next):
       ElementNode(prev, next), element(element)
    {
    }

    ~Node() override = default;
  };

  ElementNode* m_head;

public:
  class const_iterator
  {
  public:
    friend class LinkedList;
    friend class LinkedList::iterator;

    const_iterator(const const_iterator& other) :
      m_parent(other.m_parent),
      m_node(other.m_node)
    {
    }

    const_iterator& operator=(const const_iterator& other)
    {
      m_parent = other.m_head;
      m_node = other.m_node;
    }

    const TElement& operator*()
    {
      return const_cast<ElementNode*>(m_node)->getElement();
    }

    const TElement* operator->()
    {
      return &**this;
    }

    const_iterator& operator++()
    {
      if (m_node != nullptr)
        m_node = m_node->next;
      return *this;
    }

    const_iterator operator++(int)
    {
      const_iterator copy = *this;
      if (m_node != nullptr)
        m_node = m_node->next;
      return copy;
    }

    bool operator==(const const_iterator& other)
    {
      return m_parent == other.m_parent && m_node == other.m_node;
    }
    bool operator!=(const const_iterator& other)
    {
      return !(*this == other);
    }

    ~const_iterator()
    {
      if (m_node == nullptr)
        return;

      --m_node->observed;
      if (m_node->deleted && m_node->observed == 0)
      {
        ElementNode* node = const_cast<ElementNode*>(m_node);
        LinkedList* parent = const_cast<LinkedList*>(m_parent);

        if (node->prev == nullptr)
        {
          parent->m_head = node->next;
        }
        else
        {
          node->prev->next = node->next;
        }

        delete m_node;
      }
    }

  private:
    const_iterator(const LinkedList* parent, const ElementNode* node) :
      m_parent(parent), m_node(node)
    {
      if (m_node != nullptr)
      {
        ++m_node->observed;
      }
    }

    const LinkedList* m_parent;
    const ElementNode* m_node;

  };

  class iterator
  {
  public:
    friend class LinkedList;

    iterator(const iterator& other) :
      m_parent(other.m_parent),
      m_node(other.m_node)
    {
    }

    iterator& operator=(const iterator& other)
    {
      m_parent = other.m_head;
      m_node = other.m_node;
    }

    operator const_iterator()
    {
      return const_iterator(m_parent, m_node);
    }

    iterator& operator++()
    {
      if (m_node != nullptr)
        m_node = m_node->next;
      return *this;
    }

    iterator operator++(int)
    {
      iterator copy = *this;
      if (m_node != nullptr)
        m_node = m_node->next;
      return copy;
    }

    TElement& operator*()
    {
      return m_node->getElement();
    }

    TElement* operator->()
    {
      return &**this;
    }

    bool operator==(const iterator& other)
    {
      return m_parent == other.m_parent && m_node == other.m_node;
    }
    bool operator!=(const iterator& other)
    {
      return !(*this == other);
    }

    ~iterator()
    {
      if (m_node == nullptr)
        return;
      --m_node->observed;
      if (m_node->deleted && m_node->observed == 0)
      {
        if (m_node->prev == nullptr)
        {
          m_parent->m_head = m_node->next;
        }
        else
        {
          m_node->prev->next = m_node->next;
        }

        delete m_node;
      }
    }

  private:
    iterator(LinkedList* parent, ElementNode* node) :
      m_parent(parent), m_node(node)
    {
      if (m_node != nullptr)
      {
        ++m_node->observed;
      }
    }

    LinkedList* m_parent;
    ElementNode* m_node;
  };

  iterator begin() { return iterator(this, m_head); }
  iterator end() { return iterator(this, nullptr); }

  const_iterator begin() const { return const_iterator(this, m_head); }
  const_iterator end() const { return const_iterator(this, nullptr); }

  void erase(iterator& it)
  {
    it.m_node->deleted = true;
  }

};

} // namespace util

#endif /* linked_list.h */
