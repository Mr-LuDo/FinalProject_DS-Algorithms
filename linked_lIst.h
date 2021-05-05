#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

//#include <memory>

#include "Node.h"

class LinkedList {
 public:
  class IllegalAccess{};
  class Unimplemented{};

  LinkedList() {}
  virtual ~LinkedList() {}

  virtual void PushFront(const int& data) = 0;
  virtual void PushBack(const int& data) = 0;
  virtual const Node* Back() const = 0;
  virtual const Node* Front() const = 0;
  virtual void PopBack() = 0;
  virtual void PopFront() = 0;
  virtual size_t size() const = 0;
  bool IsEmpty() const { return size() == 0; }
};

// ---------------------------------- LinkedListExtraData ---------------------------------------------------


class LinkedListExtraData : public LinkedList 
{
    public:
        LinkedListExtraData()
            : first_node_(nullptr), last_node_(nullptr), size_(0) 
        {}

        virtual ~LinkedListExtraData() override {
            while (size_) {
                //cout << "ll deleting size = " << size() << endl;
                //PrintLinkedList();
                PopFront();
            }
            //cout << "ll deleted all" << endl;
        }

        bool PushFront(const int& key, int treeID, Tree* tree) {
            if(Search(key) != nullptr) {
                //cout << "key already exist, no action were taken." << endl;
                return false;
            }
            PushFront(key);
            first_node_->treeID_ = treeID;
            first_node_->tree_ = tree;
            return true;
        }

        Node* Search(int key) {
            if(size_ == 0) 
                return nullptr;

            Node* temp_node = first_node_;
            do {
                if(temp_node->key_ == key)
                    return temp_node;
                Node* tmp = Next(temp_node);
                if(tmp == nullptr)
                    return nullptr;
                temp_node = tmp;
            }
            while(temp_node != first_node_);
            return nullptr;
        }

        void PushFront(const int& key) {
            auto new_node = new(Node)(key);
            new_node->linkedlist_ = this;

            if (size_ == 0) {
                new_node->ll_next_ = new_node;
                new_node->ll_previous_ = new_node;
                last_node_ = new_node;
                first_node_ = new_node;
            }
            else {
                new_node->ll_next_ = first_node_;
                new_node->ll_previous_ = last_node_;
                first_node_->ll_previous_ = new_node;
                last_node_->ll_next_ = new_node;
                first_node_ = new_node;
            }
            ++size_;
        }

        void PushBack(const int& key) {
            auto new_node = new(Node)(key);
            new_node->linkedlist_ = this;

            if (size_ == 0) {
                new_node->ll_next_ = new_node;
                new_node->ll_previous_ = new_node;
                last_node_ = new_node;
                first_node_ = new_node;
            }
            else {
                new_node->ll_next_ = first_node_;
                new_node->ll_previous_ = last_node_;
                first_node_->ll_previous_ = new_node;
                last_node_->ll_next_ = new_node;
                last_node_ = new_node;
            }
            ++size_;
        }

        void PushAfterThis(Node* node, int key) {
            if(node->linkedlist_ != this) 
                return;
            
            auto new_node = new(Node)(key);
            new_node->linkedlist_ = this;

            new_node->ll_next_ = node->ll_next_;
            node->ll_next_ = new_node;

            new_node->ll_previous_ = node;
            new_node->ll_next_->ll_previous_ = new_node;
            
            ++size_;
        }

        void PopFront() { PopThis(first_node_); }
        void PopBack()  { PopThis(last_node_); }

        void PopThis(Node* node) {
            if(node->linkedlist_ != this)
                return;
            if (first_node_ == last_node_) {
                first_node_ = last_node_ = nullptr;
            }
            else {
                if (node == first_node_)
                    first_node_ = Next(node);
                if (node == last_node_)
                    last_node_ = Previous(node);

                Next(node)->ll_previous_ = Previous(node);
                Previous(node)->ll_next_ = Next(node);
            }
            delete node;
            --size_;
            //cout << "deleted last node, size : " << size() << endl;
            //cout << "first_node_ : " << first_node_ << endl;
            //cout << "last_node_ : " << last_node_ << endl;
        }

        Node* Next(Node* node)      { return node->ll_next_;     }
        Node* Previous(Node* node)  { return node->ll_previous_; }
        Node* Front() const         { return first_node_; }
        Node* Back()  const         { return last_node_;  }
        size_t size() const         { return size_;       }

        void PrintLinkedList() {
            cout << endl << endl <<
                " ----------------- Linked list ----"
                "-------------" << endl << endl;
            if (size() == 0) {
                cout << "ll empty" << endl;
                return;
            }

            cout << "size_" << size_ << endl;
            cout << "first_node_" << first_node_ << endl;
            cout << "last_node_" << last_node_ << endl;

            for (auto i = first_node_; i != last_node_; i = Next(i)) {
                cout << "key_  = " << i->key_;
                cout << "  at address: " << i << endl;
            }
                cout << "key_  = " << last_node_->key_;
                cout << "  at address: " << last_node_ << endl;
        }

    private:
        Node* first_node_;
        Node* last_node_;
        size_t size_;

};



// ---------------------------------- UnidirectionalLinkedList ---------------------------------------------------

/*

template <typename T>
class UnidirectionalLinkedList : public LinkedList<T> {
 public:
  class IllegalAccess{};
  class Unimplemented{};
  class Node;

  UnidirectionalLinkedList() {}
  ~UnidirectionalLinkedList() override {}

  void PushFront(const T& data) {
    size_++;
    auto new_node = std::make_unique<ListNode>(data);
    new_node->next_ = std::move(root_->next_);
    root_->next_ = std::move(new_node);
    if (size_ == 1) last_ = root_->next_.get();
  }

  void PushBack(const T& data) override {
    if (size_ == 0) {
      PushFront(data);
      return;
    }
    size_++;
    auto new_node = std::make_unique<ListNode>(data);
    new_node->next_ = std::move(root_->next_);
    last_->next_ = std::move(new_node);
    last_ = last_->next_.get();

  }

  const T& Back() const override {
    if (last_ == nullptr) throw typename LinkedList<T>::IllegalAccess();
    return last_->value_;
  }

  const T& Front() const override {
    if (root_->next_ == nullptr) throw typename LinkedList<T>::IllegalAccess();
    return root_->next_->value_;
  }

  const void PopBack() override {
      throw typename LinkedList<T>::Unimplemented();
  }

  const void PopFront() override {
    if (!root_->next_) return;
    std::unique_ptr<ListNode> tmp = std::move(root_->next_);
    root_->next_ = std::move(tmp->next_);
    --size_;
    if (size_ == 0) {
      last_ = nullptr;
    }
  }

  size_t size() const override { return size_; }

 private:
  struct ListNode {
    ListNode(const T& value = 0) : value_(value) {}
    T value_;
    std::unique_ptr<ListNode> next_;
  };
  std::unique_ptr<ListNode> root_ = std::make_unique<ListNode>();
  ListNode* last_ = nullptr;
  size_t size_ = 0;

};


// ---------------------------------- BidirectionalLinkedList ---------------------------------------------------



template <typename T>
class BidirectionalLinkedList : public LinkedList<T> {
 public:

//   class ListNode;

  BidirectionalLinkedList() {
    root_.next_ = &root_;
    root_.prev_ = &root_;
  }
  ~BidirectionalLinkedList() override {
    ListNode *next = root_.next_;
    for (size_t i = 0; i < size_; ++i) {
      next = next->next_;
      delete next->prev_;
    }
  }

//  void PushFront(const T& data) override {
//    auto* node = new ListNode(data);
//    node->next_ = root_.next_;
//    root_.next_ = node;
//    node->prev_ = &root_;
//    node->next_->prev_ = node;
//    ++size_;
//  }

  void PushFront(const T& data) override {
    auto* node = new ListNode(data);
    node->next_ = root_.next_;
    root_.next_ = node;
    node->prev_ = &root_;
    node->next_->prev_ = node;
    ++size_;
  }

  void PushBack(const T& data) override {
    auto* node = new ListNode(data);
    node->prev_ = root_.prev_;
    root_.prev_ = node;
    node->next_ = &root_;
    node->prev_->next_ = node;
    ++size_;
  }


  const T& Front() const override {
    if (size_ == 0)  throw typename LinkedList<T>::IllegalAccess();
    return root_.next_->value_;
  }

  const T& Back() const override {
    if (size_ == 0)  throw typename LinkedList<T>::IllegalAccess();
    return root_.prev_->value_;
  }

  const void PopFront() override {
    if (size_ == 0)  throw typename LinkedList<T>::IllegalAccess();
    std::unique_ptr<ListNode> tmp(root_.next_);
    root_.next_ = tmp->next_;
    tmp->next_->prev_ = &root_;
    --size_;
  }

  const void PopBack() override {
    if (size_ == 0)  throw typename LinkedList<T>::IllegalAccess();
    std::unique_ptr<ListNode> tmp(root_.prev_);
    root_.prev_ = tmp->prev_;
    tmp->prev_->next_ = &root_;
    --size_;
  }
  size_t size() const override { return size_; }



 private:
  class ListNode {
    public:
        ListNode(const T& value = 0) : value_(value), next_(nullptr) , prev_(nullptr) {}
        T value_;
        ListNode* next_;
        ListNode* prev_;

  };

  ListNode root_;
  size_t size_ = 0;

    public:
        ListNode Next() {
            return *root_.next_;
        }
};


*/


#endif // LINKEDLIST_H
