// 
// SPUC - Signal processing using C++ - A DSP library
/*---------------------------------------------------------------------------*
 *                                   IT++			             *
 *---------------------------------------------------------------------------*
 * Copyright (c) 1995-2001 by Tony Ottosson, Thomas Eriksson, Pål Frenger,   *
 * Tobias Ringström, and Jonas Samuelsson.                                   *
 *                                                                           *
 * Permission to use, copy, modify, and distribute this software and its     *
 * documentation under the terms of the GNU General Public License is hereby *
 * granted. No representations are made about the suitability of this        *
 * software for any purpose. It is provided "as is" without expressed or     *
 * implied warranty. See the GNU General Public License for more details.    *
 *---------------------------------------------------------------------------*/

/*! 
  \file 
  \brief Implementation of binary sequence classes and functions.
  \author Tony Ottosson and Pål Frenger, Modified by Tony Kirke, Feb 1,2003

  1.3

  2001/12/03 19:37:13
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdexcept>
using namespace std;
#include <spucassert.h>
#include "sequence.h"
#include <specmat.h>
using namespace SPUC;
LFSR::LFSR(const bvec &connections)
{
    set_connections(connections);
}

LFSR::LFSR(const ivec &connections)
{
    set_connections(connections);
}

void LFSR::set_connections(const bvec &connections)
{
    short N=connections.size()-1;
    memory.set_size(N, true); // Should this be true???
    Connections=connections.right(N);
}

void LFSR::set_connections(const ivec &connections)
{
    bvec temp=oct2bin(connections);
    short N=temp.size()-1;
    memory.set_size(N, true); // Should this be true???
    Connections=temp.right(N);
}

void LFSR::set_state(const bvec &state)
{
    assert(state.length()==memory.size());
    memory=state;
}

void LFSR::set_state(const ivec &state)
{
    bvec temp=oct2bin(state,1);
    assert(temp.length()>=memory.size());
    memory=temp.right(memory.size());
}

bvec LFSR::shift(int no_shifts)
{
    assert(no_shifts>0);
    bvec temp(no_shifts);
    for (int i=0;i<no_shifts;i++) {
	temp(i)=shift();
    }
    return temp;
}

//--------------------------- class Gold -------------------------
Gold::Gold(int degree)
{
    bvec mseq1_connections, mseq2_connections;
    switch (degree) {
    case 5:
	mseq1_connections=bvec("1 0 1 0 0 1");
	mseq2_connections=bvec("1 0 1 1 1 1");
	break;
    case 7:
	mseq1_connections=bvec("1 0 0 1 0 0 0 1");
	mseq2_connections=bvec("1 1 1 1 0 0 0 1");
	break;
    case 8:
	mseq1_connections=bvec("1 1 1 0 0 1 1 1 1");
	mseq2_connections=bvec("1 1 0 0 0 0 1 1 1");
	break;
    case 9:
	mseq1_connections=bvec("1 0 0 0 1 0 0 0 0 1");
	mseq2_connections=bvec("1 0 0 1 1 0 1 0 0 1");
	break;
    default:
	it_error("This degree of Gold sequence is not available");
    }
    mseq1.set_connections(mseq1_connections);
    mseq2.set_connections(mseq2_connections);
    N=(int)round(pow(2,(double)mseq1.get_length()))-1;
}

Gold::Gold(const bvec &mseq1_connections, const bvec &mseq2_connections)
{
    assert(mseq1_connections.size()==mseq2_connections.size());
    mseq1.set_connections(mseq1_connections);
    mseq2.set_connections(mseq2_connections);
    N=(int)round(pow(2,(double)mseq1.get_length()))-1;
}

Gold::Gold(const ivec &mseq1_connections, const ivec &mseq2_connections)
{
    mseq1.set_connections(mseq1_connections);
    mseq2.set_connections(mseq2_connections);
    assert(mseq1.get_length()==mseq1.get_length());
    N=(int)round(pow(2,(double)mseq1.get_length()))-1;
}

void Gold::set_state(const bvec &state1, const bvec &state2)
{
    mseq1.set_state(state1);
    mseq2.set_state(state2);
}

void Gold::set_state(const ivec &state1, const ivec &state2)
{
    mseq1.set_state(state1);
    mseq2.set_state(state2);
}

bvec Gold::shift(int no_shifts)
{
    assert(no_shifts>0);
    bvec temp(no_shifts);
    for (int i=0;i<no_shifts;i++) {
	temp(i)=shift();
    }
    return temp;
}

bmat Gold::get_family(void)
{
    bmat codes(N+2,N);
    bvec temp=dec2bin(mseq1.get_length(),1);
    set_state(temp,temp);

    // The two m-seq.
    codes.set_row(0,mseq1.shift(N));
    codes.set_row(1,mseq2.shift(N));
    // The sum of mseq1 and all time shifts of mseq2
    for (int i=0;i<N;i++) {    
	codes.set_row( i+2,codes.get_row(0) + concat((codes.get_row(1)).right(i), (codes.get_row(1)).left(N-i)) );
    }
    return codes;
}
namespace SPUC {
smat wcdma_spreading_codes(int SF)
{
  it_assert((SF==1)||(SF==2)||(SF==4)||(SF==8)||(SF==16)||(SF==32)||(SF==64)||(SF==128)||(SF==256)||(SF==512),
	    "wcdma_spreading_codes: SF must equal 1, 2, 4, 8, 16, 32, 64, 128, 256, or 512");
  smat codes(SF,SF);
  if (SF == 1) {
    codes(0,0) = short(1);
  } else {
    int i;
    smat prev_codes(SF/2,SF/2);
    prev_codes = wcdma_spreading_codes(SF/2);
    for (i=0; i<SF/2; i++) {
      codes.set_row(2*i, concat( prev_codes.get_row(i),prev_codes.get_row(i)) );
      codes.set_row(2*i+1,concat( prev_codes.get_row(i),(-prev_codes.get_row(i))) );
    }
  }
  return codes;
}
}
