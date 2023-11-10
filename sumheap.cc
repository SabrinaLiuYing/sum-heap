#include "sumheap.h"

SumHeap::SumHeap(unsigned int n) : value(n), parent(nullptr), children() {}

SumHeap::SumHeap(unsigned int n, SumHeap* p) : value(n), parent(p), children() {}

SumHeap* SumHeap::addChild(unsigned int value) {
    if (this->getSum() + value < this->getValue() && check_parent(value)) {
        this->children.emplace_back(std::make_unique<SumHeap>(value, this));
        return children.back().get();
    }
    else {
        return nullptr;
    }
}

SumHeap* SumHeap::getParent() const {
    return parent;
}

size_t SumHeap::numChildren() const {
    return children.size();
}

SumHeap* SumHeap::getChild(size_t idx) const {
    return children[idx].get();
}

unsigned int SumHeap::getValue() const {
    return value;
}
void SumHeap::swap(SumHeap* other) {
    /*size_t left_idx, right_idx;
    for (left_idx = 0; left_idx < this->getParent()->numChildren(); left_idx++){
        if (this->getParent()->getChild(left_idx) == this) {
            break;
        }
    }
    for (right_idx = 0; right_idx < other->getParent()->numChildren(); left_idx++){
        if (other->getParent()->getChild(right_idx) == other) {
            break;
        }
    }*/

    size_t left_idx, right_idx;

    for (left_idx = 0; left_idx < this->getParent()->numChildren(); left_idx++)
    {
        if (this->getParent()->getChild(left_idx) == this)
            break;
    }

	for (right_idx = 0; right_idx < other->getParent()->numChildren(); right_idx++)
	{
		if (other->getParent()->getChild(right_idx) == other)
			break;
	}

    this->getParent()->children[left_idx].swap(other->getParent()->children[right_idx]);
    std::swap(this->parent, other->parent);
    if (!check_swap() || !other->check_swap()) {
        this->getParent()->children[right_idx].swap(other->getParent()->children[left_idx]);
        std::swap(this->parent, other->parent);
        throw InvalidValueException();
    }
}

unsigned int SumHeap::getSum() const {
    int result = 0;
    for (const auto& child : children) {
        result += child->getSum() + child->getValue();
    }
    return result;
}

bool SumHeap::check_parent(unsigned int value) {
    if (getParent() == nullptr) {
        return true;
    }
    else if (getParent()->getSum() + value < getParent()->getValue()) {
        return getParent()->check_parent(value);
    }
    else {
        return false;
    }
}

bool SumHeap::check_swap() {
    if (getParent() == nullptr) {
        return true;
    }
    else if (getParent()->getSum() < getParent()->getValue()) {
        return getParent()->check_swap();
    }
    else {
        return false;
    }
}