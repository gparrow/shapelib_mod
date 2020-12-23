/******************************************************************************
 * $Id: shpdump.c,v 1.18 2011-07-24 03:05:14 fwarmerdam Exp $
 *
 * Project:  Shapelib
 * Purpose:  Sample application for dumping contents of a shapefile to 
 *           the terminal in human readable form.
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
 * $Log: shpdump.c,v $
 * Revision 1.18  2011-07-24 03:05:14  fwarmerdam
 * use %.15g for formatting coordiantes in shpdump
 *
 * Revision 1.17  2010-07-01 07:33:04  fwarmerdam
 * do not crash in shpdump if null object returned
 *
 * Revision 1.16  2010-07-01 07:27:13  fwarmerdam
 * white space formatting adjustments
 *
 * Revision 1.15  2006-01-26 15:07:32  fwarmerdam
 * add bMeasureIsUsed flag from Craig Bruce: Bug 1249
 *
 * Revision 1.14  2005/02/11 17:17:46  fwarmerdam
 * added panPartStart[0] validation
 *
 * Revision 1.13  2004/09/26 20:09:35  fwarmerdam
 * avoid rcsid warnings
 *
 * Revision 1.12  2004/01/27 18:05:35  fwarmerdam
 * Added the -ho (header only) switch.
 *
 * Revision 1.11  2004/01/09 16:39:49  fwarmerdam
 * include standard include files
 *
 * Revision 1.10  2002/04/10 16:59:29  warmerda
 * added -validate switch
 *
 * Revision 1.9  2002/01/15 14:36:07  warmerda
 * updated email address
 *
 * Revision 1.8  2000/07/07 13:39:45  warmerda
 * removed unused variables, and added system include files
 *
 * Revision 1.7  1999/11/05 14:12:04  warmerda
 * updated license terms
 *
 * Revision 1.6  1998/12/03 15:48:48  warmerda
 * Added report of shapefile type, and total number of shapes.
 *
 * Revision 1.5  1998/11/09 20:57:36  warmerda
 * use SHPObject.
 *
 * Revision 1.4  1995/10/21 03:14:49  warmerda
 * Changed to use binary file access.
 *
 * Revision 1.3  1995/08/23  02:25:25  warmerda
 * Added support for bounds.
 *
 * Revision 1.2  1995/08/04  03:18:11  warmerda
 * Added header.
 *
 */

#include <string.h>
#include <stdlib.h>
#include "shapefil.h"

SHP_CVSID("$Id: shpdump.c,v 1.18 2011-07-24 03:05:14 fwarmerdam Exp $")

