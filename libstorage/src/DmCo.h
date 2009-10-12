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


#ifndef DM_CO_H
#define DM_CO_H

#include "y2storage/PeContainer.h"
#include "y2storage/Dm.h"

namespace storage
{
class ProcPart;

class DmCo : public PeContainer
    {
    friend class Storage;

    public:
	DmCo( Storage * const s, bool detect, ProcPart& ppart );
	DmCo( const DmCo& rhs );
	virtual ~DmCo();
	static storage::CType staticType() { return storage::DM; }
	friend std::ostream& operator<< (std::ostream&, const DmCo& );
	bool equalContent( const Container& rhs ) const;
	void logDifference( const Container& d ) const;
	void updateDmMaps();

	int removeDm( const string& table );
	int removeVolume( Volume* v );
	
    protected:
	DmCo( Storage * const s, const string& File );

	void getDmData( ProcPart& ppart );
	bool findDm( unsigned num, DmIter& i );
	bool findDm( unsigned num ); 
	bool findDm( const string& dev, DmIter& i );
	bool findDm( const string& dev ); 
	void addDm( Dm* m );
	void checkDm( Dm* m );
	void updateEntry( const Dm* m );
	virtual Container* getCopy() const { return( new DmCo( *this ) ); }

	void init();

	storage::EncryptType detectEncryption( const string& device ) const;

	virtual void print( std::ostream& s ) const { s << *this; }

	int doRemove( Volume* v );

	void logData( const string& Dir );
    };

}

#endif
