#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include "Node.h"


class LinkedList {
 public:
//  class IllegalAccess{};
//  class Unimplemented{};

  LinkedList() {}
  virtual ~LinkedList() {}

  virtual void PushFront(const int& data) = 0;
  virtual void PushBack(const int& data) = 0;
  virtual const int& Back() const = 0;
  virtual const int& Front() const = 0;
  virtual const void PopBack() = 0;
  virtual const void PopFront() = 0;
  virtual size_t size() const = 0;
  bool IsEmpty() const { return size() == 0; }
};

// ---------------------------------- LinkedListExtraData ---------------------------------------------------


class LinkedListExtraData : public LinkedList {
    public:
        LinkedListExtraData()
            : first_node_(nullptr), last_node_(nullptr), size_(0) {}
        virtual ~LinkedListExtraData() override {}

        bool PushFrontfruit(const int& fruitID, int treeID) {
            if(Search(fruitID) != nullptr) {
                cout << "fruit already exist, no action were taken." << endl;
                return false;
            }
            PushFront(fruitID);
            first_node_->treeID_ = treeID;
            return true;
        }

        Node* Search(int fruitID) {
            if(size_ == 0) return nullptr;
            Node* temp_node = first_node_;
            do {
//                cout << "searching, temp node = " << temp_node << " fisrt node = " << first_node_ << endl;
                if(temp_node->fruitID_ == fruitID)
                    return temp_node;
//                cout << "next" << endl;
                Node* tmp = Next(temp_node);
                if(tmp == nullptr)
                    return nullptr;
                temp_node = tmp;
            }
            while(temp_node != first_node_);
            return nullptr;
        }

        void PushFront(const int& fruitID) {
            auto new_node = new(Node)(fruitID);
            new_node->ll_source_ = this;
            new_node->ll_next_ = first_node_;
            new_node->ll_previous_ = last_node_;

            if(!size_) last_node_ = new_node;
            else {
                first_node_->ll_previous_ = new_node;
                last_node_->ll_next_ = new_node;
            }

            first_node_ = new_node;
            ++size_;
        }

        void PushBack(const int& fruitID) {
            auto new_node = new(Node)(fruitID);
            new_node->ll_source_ = this;
            new_node->ll_next_ = first_node_;
            new_node->ll_previous_ = last_node_;

            if(!size_) first_node_ = new_node;
            else {
                last_node_->ll_next_ = new_node;
                first_node_->ll_previous_ = new_node;
            }

            last_node_ = new_node;
            ++size_;
        }

        void PushAfterThis(Node* node, int fruitID) {
            if(node->ll_source_ != this) return;
            auto new_node = new(Node)(fruitID);
            new_node->ll_source_ = this;

            new_node->ll_next_ = node->ll_next_;
            node->ll_next_ = new_node;

            new_node->ll_previous_ = node;
            new_node->ll_next_->ll_previous_ = new_node;
            ++size_;

            return;
        }

        const int& Front() const    { return first_node_->fruitID_; }
        const int& Back()  const    { return last_node_->fruitID_; }
        const void PopBack() {}         // not really needed for now
        const void PopFront() {}        // not really needed for now

        const void PopThis(Node* node) {
            if(node->ll_source_ != this) return;
            node->ll_next_->ll_previous_ = node->ll_previous_;
            node->ll_previous_->ll_next_ = node->ll_next_;
            delete node;
            --size_;
            return;
        }

        Node* Next(Node* node) {
            return node->ll_next_;
        }
        Node* Previous(Node* node) {
            return node->ll_previous_;
        }

        size_t size() const { return size_; }

//    private:
        Node* first_node_;
        Node* last_node_;
        size_t size_;
};




//
//// ---------------------------------- LinkedListExtraData ---------------------------------------------------
//template <typename Type>
//class LinkedListExtraData;
//
//class Node {
//    public:
//        Node(int data) :
//             data_(data), source_(nullptr),/* first_(nullptr), last_(nullptr),*/
//             next_(nullptr), previous_(nullptr)
//             {}
//
//
//        int data_;
//        LinkedListExtraData<int>* source_;
////        std::unique_ptr<Node> first_ ;
////        std::unique_ptr<Node> last_;
//        std::unique_ptr<Node> next_;
//        std::unique_ptr<Node> previous_;
//
//};
//
//
//template <typename Type>
//class LinkedListExtraData : public LinkedList<Type> {
//    public:
//        LinkedListExtraData() : first_node_(nullptr), last_node_(nullptr), size_(0) {}
//        virtual ~LinkedListExtraData() override {}
//
//        void PushFront(const Type& data) {
//            auto new_node = std::make_unique<Node>(data);
//            new_node->source_ = this;
//            new_node->next_ = std::move(first_node_);
//            first_node_ = std::move(new_node);
//            ++size_;
//        }
//
//        void PushBack(const Type& data) {}
//        const Type& Back() const {}
//        const Type& Front() const {}
//        const void PopBack() {}
//        const void PopFront() {}
//        size_t size() const { return size_; }
//
////    private:
//        std::unique_ptr<Node> first_node_;
//        std::unique_ptr<Node> last_node_;
//        size_t size_;
//};
//
//
//


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