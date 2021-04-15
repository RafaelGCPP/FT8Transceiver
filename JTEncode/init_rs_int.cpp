/* Initialize a RS codec
 *
 * Copyright 2002 Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 *
 * Slightly modified by Jason Milldrum NT7S, 2015 to fit into the Arduino framework
 */

#include <string.h>
#include <stdlib.h>
#include <JTEncode.h>
#include "rs_common.h"

// Not needed as we are not dynamically allocating data.
// void JTEncode::free_rs_int(void * p)
// {
//   struct rs *rs = (struct rs *)p;

//   free(rs->alpha_to);
//   free(rs->index_of);
//   free(rs->genpoly);
//   free(rs);
// }

// This function was modified for the parameters used on JTEncode constructor
//  rs_inst = (struct rs *)(intptr_t)init_rs_int(6, 0x43, 3, 1, 51, 0);
// This was done because malloc, calloc are very inneficient in microcontrollers and
// should be avoided like the plague.
// Also, all sanity checks were removed, as we know they are good. Memory in microcontrollers
// is a scarce resource.
void *JTEncode::init_rs_int(int symsize, int gfpoly, int fcr, int prim, int nroots, int pad)
{

  int i, j, sr, root, iprim;
  struct rs *rs;

  rs = &(this->rs_data);

  rs->mm = symsize;            //6
  rs->nn = (1 << symsize) - 1; //63
  rs->pad = pad;               //0

  rs->alpha_to = (this->alpha_to_data); //(data_t *)malloc(sizeof(data_t)*(rs->nn+1)); //64
  rs->index_of = (this->index_of_data); //(data_t *)malloc(sizeof(data_t)*(rs->nn+1)); //64

  /* Generate Galois field lookup tables */
  rs->index_of[0] = A_0; /* log(zero) = -inf */
  rs->alpha_to[A_0] = 0; /* alpha**-inf = 0 */
  sr = 1;
  for (i = 0; i < rs->nn; i++)
  {
    rs->index_of[sr] = i;
    rs->alpha_to[i] = sr;
    sr <<= 1;
    if (sr & (1 << symsize))
      sr ^= gfpoly;
    sr &= rs->nn;
  }

  /* Testing if field generator polynomial is not primitive was removed from here! */

  /* Form RS code generator polynomial from its roots */
  rs->genpoly = this->genpoly_data; //(data_t *)malloc(sizeof(data_t)*(nroots+1)); //52

  rs->fcr = fcr;
  rs->prim = prim;
  rs->nroots = nroots;

  /* Find prim-th root of 1, used in decoding */
  for (iprim = 1; (iprim % prim) != 0; iprim += rs->nn)
    ;
  rs->iprim = iprim / prim;

  rs->genpoly[0] = 1;
  for (i = 0, root = fcr * prim; i < nroots; i++, root += prim)
  {
    rs->genpoly[i + 1] = 1;

    /* Multiply rs->genpoly[] by  @**(root + x) */
    for (j = i; j > 0; j--)
    {
      if (rs->genpoly[j] != 0)
        rs->genpoly[j] = rs->genpoly[j - 1] ^ rs->alpha_to[modnn(rs, rs->index_of[rs->genpoly[j]] + root)];
      else
        rs->genpoly[j] = rs->genpoly[j - 1];
    }
    /* rs->genpoly[0] can never be zero */
    rs->genpoly[0] = rs->alpha_to[modnn(rs, rs->index_of[rs->genpoly[0]] + root)];
  }
  /* convert rs->genpoly[] to index form for quicker encoding */
  for (i = 0; i <= nroots; i++)
    rs->genpoly[i] = rs->index_of[rs->genpoly[i]];

done:

  return rs;
}
