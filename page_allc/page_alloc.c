#include "page_alloc.h"

/** just for debugging */
#include <assert.h>

// #define DEBUG

static unsigned int alloc_pagesize = 0;


typedef struct PageHeader
{
   struct PageHeader * nextpage;
#ifdef DEBUG
   void * cookie;
#endif
} PageHeader;

static PageHeader * alloc_firstfree = 0;

static void verify ()
{
#ifdef DEBUG
   PageHeader * cur = alloc_firstfree;
   while (cur)
   {
      assert (cur->cookie == cur);
      cur = cur->nextpage;
   }
#endif
}

/**
 * Called to initialize the library.
 * returns 0 on success. 
 *
 * Pagesize indicates the size of a page in bytes.
 */
int page_alloc_init (unsigned int pagesize)
{
   alloc_pagesize = pagesize;
   alloc_firstfree = 0;
   return 0;
}


/** Free internal resources, if any, and shutdown library */
int page_alloc_done ()
{
   alloc_pagesize = 0;
   alloc_firstfree = 0;
   return 0;
}

/**
 * Add page to top of freelist
 */
static void addPage (void * page)
{

   PageHeader * h = (PageHeader*) page;
   h->nextpage = alloc_firstfree;
#ifdef DEBUG
   h->cookie = h;
#endif
   alloc_firstfree = h;
}

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
int page_alloc_add (void * start, unsigned int count)
{
   assert (alloc_pagesize);
   assert ((((unsigned long long) start) % alloc_pagesize)==0);

   unsigned int i=0;
   char * cur = (char *) start;
   for (i=0; i<count; ++i)
   {
      addPage (cur);
      cur += alloc_pagesize;
   }
   return 0;
}

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
int page_alloc_add_done ()
{
   assert (alloc_pagesize);
   return 0;
}


/**
 * Allocate a single page. Returns pointer to page on success,
 * 0 on failure
 */
void * page_alloc_get_one ()
{
   verify();
   assert (alloc_pagesize);

   /* If no pages, return error */
   if (!alloc_firstfree)
      return alloc_firstfree;

#ifdef DEBUG
   /* check if page is not corrupted */
   assert (alloc_firstfree->cookie == alloc_firstfree);
#endif

   void * newpage = alloc_firstfree;
   alloc_firstfree = alloc_firstfree->nextpage;

   verify ();

   return newpage;
}


/**
 * Try to allocate multiple contiguous pages.
 * Returns pointer to first page on success, and sets count to number of pages
 * allocated.
 *
 * On success, count >=0; On error: count < 0 and return is NULL
 *
 * Very slow!
 */
void * page_alloc_get_multiple (int * count)
{
   verify ();

   assert (alloc_pagesize);

   if (!alloc_firstfree)
      return alloc_firstfree;

   if (*count == 1)
      return page_alloc_get_one ();

   /* Start of region we're currently trying */
   PageHeader * curhead = alloc_firstfree;

   unsigned int todo = *count;

   int bestlength = -1;
   PageHeader * curbest = 0;


   /* For each page, try to find all matching pages */
   while (curhead)
   {
      curhead = curhead->nextpage;

      todo = *count;
      int curlength = 0;

      PageHeader * regionstart = curhead;
      PageHeader * regionstop = (PageHeader*)
           (((char*)curhead) + todo*alloc_pagesize);

      /* Try to find todo pages in the [regionstart,regionstop[ */
      PageHeader * cur = alloc_firstfree;
      while (todo && cur)
      {
         if (cur >= regionstart && cur < regionstop)
         {
            --todo;
            ++curlength;
         }

         cur=cur->nextpage;
      }

      /* Check if this region is longer than the other one we had before */
      if (curlength > bestlength)
      {
         curbest = curhead;
         bestlength = curlength;
      }

      /* If we found a long enough sequence, stop search */
      if (!todo)
         break;
   }

   /* remove the best sequence */
   PageHeader * beststart = curbest;
   PageHeader * beststop = (PageHeader *)
      (((char*)curbest) + bestlength*alloc_pagesize);
   PageHeader * cur = alloc_firstfree;
   PageHeader ** prevptr = &alloc_firstfree;

   todo = bestlength;

   while (cur && todo)
   {
      if (cur >= beststart && cur < beststop)
      {
         /* remove this page */
         *prevptr = cur->nextpage;
         --todo;
      }
      else
      {
         /* keep page */
         prevptr = &cur->nextpage;
      }
      cur = cur->nextpage;
   }

   assert (!todo);

   *count=bestlength;

   verify ();

   return beststart;
}


/**
 * Free single page:
 * Returns 0 on success, <0 on error
 *
 *   Note: the page can be allocated by get_one or get_multiple
 */
int page_alloc_return_one (void * page)
{

   assert (alloc_pagesize);
   assert (!(((unsigned long long) page) % alloc_pagesize));
   assert (page);

   verify ();

#ifdef DEBUG
   /* check if page already on free list */
   PageHeader * cur = alloc_firstfree;
   while (cur)
   {
      assert (cur != page);
      cur = cur->nextpage;
   }
#endif
   addPage (page);

   verify ();

   return 0;
}


/**
 * return range of contiguous pages
 *   - Note: pages can be allocated by get_one or get_multiple
 *
 * Returns 0 on success, <0 on error
 */
int page_alloc_return_multiple (void * page, int * count)
{
   assert (alloc_pagesize);

   verify ();

   int i;
   char * cur = (char *) page;
   for (i=0; i<*count; ++i)
   {
      addPage (cur);
      cur += alloc_pagesize;
   }

   verify ();

   return 0;
}


