#ifndef PAGE_ALLOC_H
#define PAGE_ALLOC_H

/**
 * How this page allocator will be used:
 *
 *   1) call page_alloc_init ()
 *   2) Add a number of memory regions by repeatedly calling
 *      page_alloc_add
 *   3) call page_alloc_add_done ()
 *
 *   4) allocate pages & free pages
 *
 */

/**
 * Called to initialize the library.
 * returns 0 on success. 
 *
 * Pagesize indicates the size of a page in bytes.
 */
int page_alloc_init (unsigned int pagesize);


/** Free internal resources, if any, and shutdown library */
int page_alloc_done ();

/**
 * Add a memory region to be managed by this allocator.
 * The start address will be aligned to the page size,
 * and count is the number of pages.
 *
 * Returns 0 if success, <0 if error.
 *
 * Note: The page allocator will need to store its internal bookkeeping
 * data somewhere. This has to be within the regions added by 
 * page_alloc_add(). Global variables can be used as well,
 * but their use should be limited whenever possible.
 */
int page_alloc_add (void * start, unsigned int count);

/**
 * Called when all memory regions have been added.
 *
 * After this call returns, no more memory regions will be added
 * (using page_alloc_add), and no calls to get_one or get_multiple
 * will be made before page_alloc_add_done () has been called.
 *
 * This function can only be called once.
 *
 */
int page_alloc_add_done ();


/**
 * Allocate a single page. Returns pointer to page on success,
 * 0 on failure
 */
void * page_alloc_get_one ();

/**
 * Try to allocate multiple contiguous pages.
 * Returns pointer to first page on success, and sets count to number of pages
 * allocated.
 *
 * On success, count >=0; On error: count < 0 and return is NULL
 */
void * page_alloc_get_multiple (int * count);


/**
 * Free single page:
 * Returns 0 on success, <0 on error
 *
 *   Note: the page can be allocated by get_one or get_multiple
 */
int page_alloc_return_one (void * page);


/**
 * return range of contiguous pages
 *   - Note: pages can be allocated by get_one or get_multiple
 *
 * Returns 0 on success, <0 on error
 */
int page_alloc_return_multiple (void * page, int * count);


#endif
