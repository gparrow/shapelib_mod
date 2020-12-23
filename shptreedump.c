/******************************************************************************
 * $Id: shptreedump.c,v 1.8 2005-01-03 22:30:13 fwarmerdam Exp $
 *
 * Project:  Shapelib
 * Purpose:  Mainline for creating and dumping an ASCII representation of
 *           a quadtree.
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
 * $Log: shptreedump.c,v $
 * Revision 1.8  2005-01-03 22:30:13  fwarmerdam
 * added support for saved quadtrees
 *
 * Revision 1.7  2002/04/10 16:59:12  warmerda
 * fixed email
 *
 * Revision 1.6  1999/11/05 14:12:05  warmerda
 * updated license terms
 *
 * Revision 1.5  1999/06/02 18:24:21  warmerda
 * added trimming code
 *
 * Revision 1.4  1999/06/02 17:56:12  warmerda
 * added quad'' subnode support for trees
 *
 * Revision 1.3  1999/05/18 19:13:13  warmerda
 * Use fabs() instead of abs().
 *
 * Revision 1.2  1999/05/18 19:11:11  warmerda
 * Added example searching capability
 *
 * Revision 1.1  1999/05/18 17:49:20  warmerda
 * New
 *
 */

#include "shapefil.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

SHP_CVSID("$Id: shptreedump.c,v 1.8 2005-01-03 22:30:13 fwarmerdam Exp $")

static void SHPTreeNodeDump( SHPTree *, SHPTreeNode *, const char *, int );
static void SHPTreeNodeSearchAndDump( SHPTree *, double *, double * );

/************************************************************************/
/*                               Usage()                                */
/************************************************************************/

static void Usage()

{
    printf( "shptreedump [-maxdepth n] [-search xmin ymin xmax ymax]\n"
            "            [-v] [-o indexfilename] [-i indexfilename]\n"
            "            shp_file\n" );
    exit( 1 );
}





/************************************************************************/
/*                           EmitCoordinate()                           */
/************************************************************************/

static void EmitCoordinate( double * padfCoord, int nDimension )

{
    const char	*pszFormat;
    
    if( fabs(padfCoord[0]) < 180 && fabs(padfCoord[1]) < 180 )
        pszFormat = "%.9f";
    else
        pszFormat = "%.2f";

    printf( pszFormat, padfCoord[0] );
    printf( "," );
    printf( pszFormat, padfCoord[1] );

    if( nDimension > 2 )
    {
        printf( "," );
        printf( pszFormat, padfCoord[2] );
    }
    if( nDimension > 3 )
    {
        printf( "," );
        printf( pszFormat, padfCoord[3] );
    }
}

/************************************************************************/
/*                             EmitShape()                              */
/************************************************************************/

static void EmitShape( SHPObject * psObject, const char * pszPrefix,
                       int nDimension )

{
    int		i;
    
    printf( "%s( Shape\n", pszPrefix );
    printf( "%s  ShapeId = %d\n", pszPrefix, psObject->nShapeId );

    printf( "%s  Min = (", pszPrefix );
    EmitCoordinate( &(psObject->dfXMin), nDimension );
    printf( ")\n" );
    
    printf( "%s  Max = (", pszPrefix );
    EmitCoordinate( &(psObject->dfXMax), nDimension );
    printf( ")\n" );

    for( i = 0; i < psObject->nVertices; i++ )
    {
        double	adfVertex[4];
        
        printf( "%s  Vertex[%d] = (", pszPrefix, i );

        adfVertex[0] = psObject->padfX[i];
        adfVertex[1] = psObject->padfY[i];
        adfVertex[2] = psObject->padfZ[i];
        adfVertex[3] = psObject->padfM[i];
        
        EmitCoordinate( adfVertex, nDimension );
        printf( ")\n" );
    }
    printf( "%s)\n", pszPrefix );
}

/************************************************************************/
/*                          SHPTreeNodeDump()                           */
/*                                                                      */
/*      Dump a tree node in a readable form.                            */
/************************************************************************/

static void SHPTreeNodeDump( SHPTree * psTree,
                             SHPTreeNode * psTreeNode,
                             const char * pszPrefix,
                             int nExpandShapes )

{
    char	szNextPrefix[150];
    int		i;

    strcpy( szNextPrefix, pszPrefix );
    if( strlen(pszPrefix) < sizeof(szNextPrefix) - 3 )
        strcat( szNextPrefix, "  " );

    printf( "%s( SHPTreeNode\n", pszPrefix );

/* -------------------------------------------------------------------- */
/*      Emit the bounds.                                                */
/* -------------------------------------------------------------------- */
    printf( "%s  Min = (", pszPrefix );
    EmitCoordinate( psTreeNode->adfBoundsMin, psTree->nDimension );
    printf( ")\n" );
    
    printf( "%s  Max = (", pszPrefix );
    EmitCoordinate( psTreeNode->adfBoundsMax, psTree->nDimension );
    printf( ")\n" );

/* -------------------------------------------------------------------- */
/*      Emit the list of shapes on this node.                           */
/* -------------------------------------------------------------------- */
    if( nExpandShapes )
    {
        printf( "%s  Shapes(%d):\n", pszPrefix, psTreeNode->nShapeCount );
        for( i = 0; i < psTreeNode->nShapeCount; i++ )
        {
            SHPObject	*psObject;

            psObject = SHPReadObject( psTree->hSHP,
                                      psTreeNode->panShapeIds[i] );
            assert( psObject != NULL );
            if( psObject != NULL )
            {
                EmitShape( psObject, szNextPrefix, psTree->nDimension );
            }

            SHPDestroyObject( psObject );
        }
    }
    else
    {
        printf( "%s  Shapes(%d): ", pszPrefix, psTreeNode->nShapeCount );
        for( i = 0; i < psTreeNode->nShapeCount; i++ )
        {
            printf( "%d ", psTreeNode->panShapeIds[i] );
        }
        printf( "\n" );
    }

/* -------------------------------------------------------------------- */
/*      Emit subnodes.                                                  */
/* -------------------------------------------------------------------- */
    for( i = 0; i < psTreeNode->nSubNodes; i++ )
    {
        if( psTreeNode->apsSubNode[i] != NULL )
            SHPTreeNodeDump( psTree, psTreeNode->apsSubNode[i],
                             szNextPrefix, nExpandShapes );
    }
    
    printf( "%s)\n", pszPrefix );

    return;
}

/************************************************************************/
/*                      SHPTreeNodeSearchAndDump()                      */
/************************************************************************/

static void SHPTreeNodeSearchAndDump( SHPTree * hTree,
                                      double *padfBoundsMin,
                                      double *padfBoundsMax )

{
    int		*panHits, nShapeCount, i;

/* -------------------------------------------------------------------- */
/*      Perform the search for likely candidates.  These are shapes     */
/*      that fall into a tree node whose bounding box intersects our    */
/*      area of interest.                                               */
/* -------------------------------------------------------------------- */
    panHits = SHPTreeFindLikelyShapes( hTree, padfBoundsMin, padfBoundsMax,
                                       &nShapeCount );

/* -------------------------------------------------------------------- */
/*      Read all of these shapes, and establish whether the shape's     */
/*      bounding box actually intersects the area of interest.  Note    */
/*      that the bounding box could intersect the area of interest,     */
/*      and the shape itself still not cross it but we don't try to     */
/*      address that here.                                              */
/* -------------------------------------------------------------------- */
    for( i = 0; i < nShapeCount; i++ )
    {
        SHPObject	*psObject;

        psObject = SHPReadObject( hTree->hSHP, panHits[i] );
        if( psObject == NULL )
            continue;
        
        if( !SHPCheckBoundsOverlap( padfBoundsMin, padfBoundsMax,
                                    &(psObject->dfXMin),
                                    &(psObject->dfXMax),
                                    hTree->nDimension ) )
        {
            printf( "Shape %d: not in area of interest, but fetched.\n",
                    panHits[i] );
        }
        else
        {
            printf( "Shape %d: appears to be in area of interest.\n",
                    panHits[i] );
        }

        SHPDestroyObject( psObject );
    }

    if( nShapeCount == 0 )
        printf( "No shapes found in search.\n" );
}