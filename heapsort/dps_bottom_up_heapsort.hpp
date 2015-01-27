/*
  Copyright (c) 2013, Maxim Zakharov
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _DPS_BOTTOM_UP_HEAPSORT_HPP
#define _DPS_BOTTOM_UP_HEAPSORT_HPP

#include <algorithm> // for swap()




/* 
   Modified version of BOTTOM-UP-HEAPSORT
   Ingo Wegener, BOTTOM-UP-HEAPSORT, a new variant of HEAPSORT beating, 
   on an average, QUICKSORT (if n is not very small), Theoretical Computer Science 118 (1993),
   pp. 81-98, Elsevier; n >= 16000 for median-3 version of QUICKSORT

   The idea of delayed reheap after moving the root to its place is from
   D. Levendeas, C. Zaroliagis, Heapsort using Multiple Heaps, in Proc. 2nd Panhellenic
   Student Conference on Informatics -- EUREKA. – 2008. – P. 93–104.
   It saves (n-2)/2 swaps and (n-2)/2 comparisons, for n > 3.
*/

/* Search for the special leaf. */
#define LEAF_SEARCH(m, i, j) { \
	j = i; \
	while ((j << 1) < m) { \
	    j <<= 1; \
	    if (*(begin + j - 1) < *(begin + j)) j++; \
	} \
	if ((j << 1) == m) j = m; \
    }
#define LEAF_SEARCH_CMP(m, i, j) { \
	j = i; \
	while ((j << 1) < m) {	\
	    j <<= 1; \
	    if (cmp(*(begin + j - 1), *(begin + j))) j++;	\
	} \
	if ((j << 1) == m) j = m; \
    }

/* Find the place of a[i] in the path to the special leaf. */
#define BOTTOM_UP_SEARCH(i, j) { \
	while(j > i && *(begin + i - 1) > *(begin + j - 1)) {	\
	    j >>= 1; \
	} \
    }
#define BOTTOM_UP_SEARCH_CMP(i, j) { \
        while (j > i && cmp(*(begin + j - 1), *(begin + i - 1)) ) { \
	    j >>= 1; \
	} \
    }

/* Rearrange the elements in the path. */
#define INTERCHANGE(i, j) {\
        k = *(begin + j - 1); \
	*(begin + j - 1) = *(begin + i - 1); \
	while (i < j) { \
	    j >>= 1; \
	    swap(k, begin[j - 1]); \
	} \
    }

/* Bottom-up reheap procedure. */
#define BOTTOM_UP_REHEAP(m, i) { \
	LEAF_SEARCH(m, i, j); \
	BOTTOM_UP_SEARCH(i, j); \
	INTERCHANGE(i, j); \
    }
#define BOTTOM_UP_REHEAP_CMP(m, i) { \
	LEAF_SEARCH_CMP(m, i, j); \
	BOTTOM_UP_SEARCH_CMP(i, j); \
	INTERCHANGE(i, j); \
    }




namespace std {

    template <typename Iterator>
    void bottom_up_heapsort(Iterator begin, Iterator end)
    {
	typedef typename iterator_traits<Iterator>::value_type _ValueType;
	typedef typename iterator_traits<Iterator>::difference_type _DistanceType;
	_ValueType k;
	_DistanceType i, j, l;
	_DistanceType nmemb = _DistanceType(end - begin);
        // Initial heap creation
	for (l = (nmemb >> 1); l > 0; l--) {
	    i = l;
	    BOTTOM_UP_REHEAP(nmemb, i);
	}
	// For each element of the heap, leave the largest in its final slot,
	// then recreate the heap.
	while (nmemb > 1) {
	    swap(begin[0], begin[nmemb - 1]);
	    --nmemb;
	    if (nmemb > 3) {
		l = (*(begin + 2) > *(begin + 1)) ? 2 : 1;
		swap(begin[l], begin[nmemb - 1]);
		nmemb--; l++;
		BOTTOM_UP_REHEAP(nmemb, l);
	    }
	    BOTTOM_UP_REHEAP(nmemb, 1);
	}
    }

    template <typename Iterator, typename Compare>
    void bottom_up_heapsort(Iterator begin, Iterator end, Compare cmp)
    {
	typedef typename iterator_traits<Iterator>::value_type _ValueType;
	typedef typename iterator_traits<Iterator>::difference_type _DistanceType;
	_ValueType k;
	_DistanceType i, j, l;
	_DistanceType nmemb = _DistanceType(end - begin);
        // Initial heap creation
	for (l = (nmemb >> 1); l > 0; l--) {
	    i = l;
	    BOTTOM_UP_REHEAP_CMP(nmemb, i);
	}
	// For each element of the heap, leave the largest in its final slot,
	// then recreate the heap.
	while (nmemb > 1) {
	    swap(begin[0], begin[nmemb - 1]);
	    --nmemb;
	    if (nmemb > 3) {
		if (cmp(*(begin + 1), *(begin + 2))) {
		    l = 1;
		} else {
		    l = 2;
		}
		swap(begin[l], begin[nmemb - 1]);
		nmemb--; l++;
		BOTTOM_UP_REHEAP_CMP(nmemb, l);
	    }
	    BOTTOM_UP_REHEAP_CMP(nmemb, 1);
	}
    }

} // namespace
#endif /* _DPS_BOTTOM_UP_HEAPSORT_HPP */
