/******************************************************************************
 * $Id: dbfcreate.c,v 1.7 2004-09-26 20:09:35 fwarmerdam Exp $
 *
 * Project:  Shapelib
 * Purpose:  Sample application for creating a new .dbf file.
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
 * $Log: dbfcreate.c,v $
 * Revision 1.7  2004-09-26 20:09:35  fwarmerdam
 * avoid rcsid warnings
 *
 * Revision 1.6  2002/01/15 14:36:07  warmerda
 * updated email address
 *
 * Revision 1.5  2000/07/07 13:39:45  warmerda
 * removed unused variables, and added system include files
 *
 * Revision 1.4  1999/11/05 14:12:04  warmerda
 * updated license terms
 *
 * Revision 1.3  1999/04/01 18:47:44  warmerda
 * Fixed DBFAddField() call convention.
 *
 * Revision 1.2  1995/08/04 03:17:11  warmerda
 * Added header.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "shapefil.h"

SHP_CVSID("$Id: dbfcreate.c,v 1.7 2004-09-26 20:09:35 fwarmerdam Exp $")

