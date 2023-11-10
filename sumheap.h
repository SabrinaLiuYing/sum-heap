#ifndef SUMHEAP_H
#define SUMHEAP_H 1

#include <memory>
#include <vector>
using namespace std;

class SumHeap {
  public:
    SumHeap(unsigned int n);
    SumHeap(unsigned int n, SumHeap *p);
 
    SumHeap *addChild(unsigned int value);
    SumHeap *getParent() const;
    size_t numChildren() const;
    SumHeap *getChild(size_t idx) const;
    unsigned int getValue() const;
    void swap(SumHeap *other);
    unsigned int getSum() const;
    bool check_parent(unsigned int value);
    bool check_swap();

  private:
    unsigned int value;
    SumHeap *parent;
    std::vector<std::unique_ptr<SumHeap>> children;
};

class InvalidValueException {};

#endif
