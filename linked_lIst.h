#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using std::cout;
using std::endl;

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
                PopFront();
            }
        }

        bool PushFront(const int& key, int treeID, Tree* tree) {
            if(Search(key) != nullptr) {
                return false;
            }
            PushFront(key);
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


#endif // LINKEDLIST_H
