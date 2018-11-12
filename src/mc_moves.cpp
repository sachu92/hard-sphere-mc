/*
 * =====================================================================================
 *
 *       Filename:  mc_moves.cpp
 *
 *    Description:  Implementation of MC Moves
 *
 *        Version:  1.0
 *        Created:  10/27/2018 04:32:36 PM
 *       Revision:  none
 *
 *         Author:  Sachin
 *   Organization:
 *
 * =====================================================================================
 */
#include "mc_moves.hpp"
#include "variables.hpp"
#include "helpers.hpp"

int moveSphere(int p)
{
    double dx, dy, dz;
    double oldx, oldy, oldz;

    dx = (udist() - 0.5) * 0.2;
    dy = (udist() - 0.5) * 0.2;
    dz = (udist() - 0.5) * 0.2;

    oldx = hsphere[p].coord[0];
    oldy = hsphere[p].coord[1];
    oldz = hsphere[p].coord[2];

    hsphere[p].coord[0] = oldx + dx;
    hsphere[p].coord[1] = oldy + dy;
    hsphere[p].coord[2] = oldz + dz;

    wrapPBC(p);

    if(collisionCheck(p))
    {
        hsphere[p].coord[0] = oldx;
        hsphere[p].coord[1] = oldy;
        hsphere[p].coord[2] = oldz;
        return 0;
    }
    return 1;
}

