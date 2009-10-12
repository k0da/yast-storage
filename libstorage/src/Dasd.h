/*
 * Copyright (c) [2004-2009] Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef DASD_H
#define DASD_H

#include "y2storage/Disk.h"

namespace storage
{

class SystemCmd;
class ProcPart;

class Dasd : public Disk
    {
    friend class Storage;
    public:
	Dasd( Storage * const s, const string& Name, unsigned long long Size );
	Dasd( const Dasd& rhs );
	virtual ~Dasd();
        int createPartition( storage::PartitionType type, long unsigned start,
	                     long unsigned len, string& device,
			     bool checkRelaxed=false );
        int removePartition( unsigned nr );
        int changePartitionId( unsigned nr, unsigned id ) { return 0; }
        int resizePartition( Partition* p, unsigned long newCyl );
	int initializeDisk( bool value );
	string fdasdText() const;
	string dasdfmtText( bool doing ) const;
	static string dasdfmtTexts( bool single, const string& devs );
	void getCommitActions( std::list<storage::commitAction*>& l ) const;
	int getToCommit( storage::CommitStage stage, std::list<Container*>& col,
			 std::list<Volume*>& vol );
	int commitChanges( storage::CommitStage stage );
	bool detectGeometry();

    protected:
	enum DasdFormat { DASDF_NONE, DASDF_LDL, DASDF_CDL };

	virtual void print( std::ostream& s ) const { s << *this; }
	virtual Container* getCopy() const { return( new Dasd( *this ) ); }
	bool detectPartitionsFdasd(ProcPart& ppart);
	bool detectPartitions( ProcPart& ppart );
	bool checkFdasdOutput( SystemCmd& Cmd, ProcPart& ppart );
	bool scanFdasdLine( const string& Line, unsigned& nr, 
	                    unsigned long& start, unsigned long& csize );
	void getGeometry( SystemCmd& cmd, unsigned long& c,
			  unsigned& h, unsigned& s );
	void redetectGeometry() {};
        int doCreate( Volume* v ) { return(doFdasd()); }
        int doRemove( Volume* v ) { return(init_disk?0:doFdasd()); }
	int doFdasd();
        int doResize( Volume* v );
        int doSetType( Volume* v ) { return 0; }
        int doCreateLabel() { return 0; }
	int doDasdfmt();
	DasdFormat fmt;

	Dasd& operator= ( const Dasd& rhs );
	friend std::ostream& operator<< (std::ostream&, const Dasd& );

    };

}

#endif
