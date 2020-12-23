/******************************************************************************
 * $Id: dbfadd.c,v 1.9 2004-09-26 20:09:35 fwarmerdam Exp $
 *
 * Project:  Shapelib
 * Purpose:  Sample application for adding a record to an existing .dbf file.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 *
 * This software is available under the following "MIT Style" license,
 * or at the option of the licensee under the LGPL (see LICENSE.LGPL).  This
 * option is discussed in more detail in shapelib.html.
 *
 * --
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 *
 * $Log: dbfadd.c,v $
 * Revision 1.9  2004-09-26 20:09:35  fwarmerdam
 * avoid rcsid warnings
 *
 * Revision 1.8  2004/01/09 16:39:49  fwarmerdam
 * include standard include files
 *
 * Revision 1.7  2002/01/15 14:36:07  warmerda
 * updated email address
 *
 * Revision 1.6  2001/05/31 18:15:40  warmerda
 * Added support for NULL fields in DBF files
 *
 * Revision 1.5  1999/11/05 14:12:04  warmerda
 * updated license terms
 *
 * Revision 1.4  1998/12/03 16:36:06  warmerda
 * Added stdlib.h and math.h to get atof() prototype.
 *
 * Revision 1.3  1995/10/21 03:13:23  warmerda
 * Use binary mode..
 *
 * Revision 1.2  1995/08/04  03:15:59  warmerda
 * Added header.
 *
 */

#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "shapefil.h"

SHP_CVSID("$Id: dbfadd.c,v 1.9 2004-09-26 20:09:35 fwarmerdam Exp $")


