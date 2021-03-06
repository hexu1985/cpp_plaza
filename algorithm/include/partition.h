#ifndef __partition_h
#define __partition_h

#include "iter_swap.h"

template <typename BidirectionalIterator, typename UnaryPredicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, 
        UnaryPredicate pred)
{
    while (first != last) {
        while (pred(*first)) {
            ++first;
            if (first == last) return first;
        }

        do {
            --last;
            if (first == last) return first;
        } while (!pred(*last));

        _iter_swap(first, last);
        ++first;
    }
    return first;
}

#endif
