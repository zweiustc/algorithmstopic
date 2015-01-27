#include "page_alloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <assert.h>

/* How many pages we will add to our test */
#define PAGECOUNT 100
#define LOOPS 10
typedef struct memregion{
    void *mem;
    unsigned int size;
}memregion;

static MEM[PAGECOUNT];

static void * marker (void * ptr)
{
   return ptr;
}
int  allocate_memory(unsigned int pagesize)
{
    struct memregion mem[PAGECOUNT];
    unsigned int i , j, ret;

    for (i = 0, j = PAGECOUNT; j > 0; j = j - page_cnt, i++) {
         page_cnt = random() % PAGECOUNT;
         ret = posix_memalign (&region[regions], pagesize, pagesize * page_cnt);
         if (ret) {
             printf("failed to allocate memory\n");
             return 1;
         }
         mem[i].size = page_cnt;
         page_alloc_add(mem[i].mem, page_cnt);
    }
   
}
void doTest (unsigned int pagesize)
{
   /* TODO: add error checking */

   unsigned int todo = PAGECOUNT;
   unsigned int i;


   page_alloc_init (pagesize);

   /* PHASE 1: allocate memory regions and add to page allocator */

   /* Keep track of pages so we can free them after test */
   struct mem 
   unsigned int regions = 0;

      todo -= pagecount;

      ++regions;
   }

   printf ("Allocated %u pages (size %u) in %u regions\n", PAGECOUNT,
         pagesize, regions);

   page_alloc_add_done ();

   /* PHASE 2: Test page_alloc functionality */

   
   /* all pages allocated */
   void * pages[PAGECOUNT];
   /* Number of valid pages in array */
   unsigned int pagecount = 0;

   unsigned int operations = 10000;
   unsigned int allocs = 0;
   unsigned int frees = 0;
   for (i=0; i<operations; ++i)
   {
      if (random () % 3)
      {
         /* slightly more likely (try out of memory situation) */
         /* allocate a page */
         void * newpage = page_alloc_get_one ();
         if (opt_verbose)
            printf ("pages=%u (before alloc), alloc=%p, pagesize=%u\n",
                  pagecount, newpage, pagesize);

         /* must be out of memory  if failure */
         if ((pagecount == PAGECOUNT) && (newpage != 0))
         {
            printf ("Error in alloc!\n");
            exit (1);
         }

         if (newpage)
         {
            // check alignment
            if (((intptr_t) newpage) % pagesize)
            {
               printf ("Alignment error (%p)!\n", newpage);
               exit (1);
            }
            
            // check it is within a region
            unsigned int j = 0;
            while (j<regions)
            {
               if ((newpage >= region[j]) &&
                  ((char*)newpage < (((char*)region[j])+(regionsize[j]*pagesize))))
                  break;
               ++j;
            }
            if (j >= regions)
            {
               printf ("Invalid page returned!\n");
               exit (1);
            }

            /* Check if we already got this page */
            for (j=0; j<pagecount; ++j)
            {
               if (pages[j] != newpage)
                  continue;
               printf ("Error: double page returned! (%p, %u)\n",
                     newpage, j);
               exit (1);
            }

            pages[pagecount] = newpage;
            ++pagecount;

            /* mark page */
            int p;
            void * c = marker (newpage);
            for (p=0; p<(pagesize/sizeof (void*)); ++p)
            {
               ((void **) newpage)[p] = c;
            }
         }

         ++allocs;
      }
      else
      {
         /* free a random page */
         if (pagecount)
         {
            unsigned int pagenum = random () % pagecount;
            void * thispage = pages[pagenum];
            if (opt_verbose)
            {
               printf ("pages=%u, freeing page %p (%u)\n", pagecount,
                     thispage, pagenum);
            }


            // check marker

            void * c = marker (thispage);
            int p;
            for (p=0; p<(pagesize/sizeof (void *)); ++p)
            {
               assert (((void **)thispage)[p]==c);
               if (((void **)thispage)[p]==c)
                  continue;
               printf ("Page contents corrupted!\n");
               exit (1);
            }

            if (page_alloc_return_one (thispage))
            {
               printf ("Error freeing page!\n");
               exit (1);
            }
            if (pagenum + 1 != pagecount)
            {
               pages[pagenum]=pages[pagecount-1];
               pages[pagecount-1] = 0;
            }
            --pagecount;
            ++frees;
         }
      }
   }

   printf ("Did %u allocations, %u frees, %u still allocated\n", allocs,
         frees, pagecount);

   /* release all remaining pages */
   for (i=0; i<pagecount; ++i)
   {
      if (page_alloc_return_one (pages[i]))
      {
         printf ("Error during cleanup\n");
      }
   }

   printf ("Released all pages\n");

   /* PHASE 3: All done; Cleanup */
   page_alloc_done ();

   /* Free all memory */
   for (i=0; i<regions; ++i)
      free (region[i]);
}

int main (int argc, char ** args)
{
   int i;
   for (i=0; i<LOOPS; ++i)
   {
      struct timeval tv;
      gettimeofday (&tv, 0);
      srandom ((unsigned int) tv.tv_usec);

      printf ("=== %u/%u ===\n", (i+1), LOOPS);
      doTest (4096);
      doTest (8192);
      doTest (4194304);
   }

   printf ("All OK!\n");
   return 0;
}
