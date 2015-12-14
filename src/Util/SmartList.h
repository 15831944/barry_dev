////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// File Name: SmartList.h
// Description:
//	A smart list knows how to be efficient when it is small
//  and when it is big. If it is a small list, a linear list
//  is good enough. But as the number of members grow, the 
//  performance becomes a issue. When this list reaches the
//  threshold value, it uses a hash table to create an index
//  so that searches in this list can be very fast. 
//
//  This is a double linked list. When the size of the list is
//  less than eThreashold, it is just a normal double linked 
//  list. Once it reaches 
//
//	The templated object 'C' must be a subclass of OmnSeqKeyedObj.   
//
// Modification History:
// 
////////////////////////////////////////////////////////////////////////////

#ifndef Omn_Util_SmartList_h
#define Omn_Util_SmartList_h

#include "Alarm/Alarm.h"
#include "Util/OmnNew.h"
#include "Util/HashInt.h"

template <class C>
class OmnSmartList
{
private:
	enum
	{
		eInitSize = 30,
		eIncrSize = 30,
		eTooBigThreshold = 200,
		eSmallThreshold = 100
	};

	struct Elem
	{
		Elem   *prev;
		Elem   *next;
		C		content;
	};

	Elem *					mHead;
	Elem *					mTail;
	Elem *					mCrtPtr;
	Elem *					mIdle;
	Elem *					mMemory;
	C						mDefault;
	uint					mEntries;
	OmnHashInt<C, 2048>    *mIndexTable;

public:
	OmnSmartList()
	:
	mHead(0),
	mTail(0),
	mCrtPtr(0),
	mIdle(0),
	mMemory(0),
	mEntries(0),
	mIndexTable(0)
	{
	}

	~OmnSmartList() 
	{
		while (mMemory)
		{
			Elem *next = mMemory->next;
			delete [] mMemory;
			mMemory = next;
		}

		OmnDelete mIndexTable;
		mIndexTable = 0;
	}

	void	setDefaultValue(const C &c) {mDefault = c;}
    uint	entries() const {return mEntries;}

	void	append(const C &v) 
			{
				if (!mIdle)
				{
					expand();
				}

				Elem *elem = mIdle;
				mIdle = mIdle->next;

				elem->prev = mTail;
				elem->next = 0;
				if (mTail)
				{
					mTail->next = elem;
				}
				elem->content = v;
				mTail = elem;
				mEntries++;

				if (!mHead)
				{
					mHead = elem;
				}
			}

	void	clear() 
			{
				Elem *next;
				while (mHead)
				{
					mHead->content = mDefault;
					next = mHead->next;
					mHead->next = mIdle;
					mIdle = mHead;
					mHead = next;
				}

				mTail = 0;
				mEntries = 0;

				if (mIndexTable)
				{
					OmnDelete mIndexTable;
					mIndexTable = 0;
				}
			}

	C popFront() 
			{
				if (!mHead)
				{
					OmnAlarm << "popFront an empty list" << enderr;
					return mDefault;
				}

				C c = mHead->content;
				mHead->content = mDefault;
				Elem *tmp = mHead->next;
				mHead->next = mIdle;
				mIdle = mHead;
				mEntries--;
				mHead = tmp;

				if (!mHead)
				{
					mTail = 0;
				}

				// 
				// If the table is small enough, make sure the index table 
				// is removed.
				//
				if (mEntries < eSmallTheshold && mIndexTable)
				{
					OmnDelete mIndexTable;
					mIndexTable = 0;
				}

				return c;
			}

	void	reset() {mCrtPtr = mHead;}

	C crtValue() const 
			{
				if (!mCrtPtr)
				{
					OmnAlarm << "Null pointer in List::crtValue()" << enderr;
					return mDefault;
				}
							
				return mCrtPtr->content;
			}

	C &	crtValue() 
			{
				if (!mCrtPtr)
				{
					OmnAlarm << "Null pointer in List::crtValue()" << enderr;
					return mDefault;
				}
							
				return mCrtPtr->content;
			}

	void	eraseCrt() 
			{
				// 
				// It removes the element pointed to by mCrtPtr.
				// If mCrtPtr is null, it is an error. After remove,
				// mCrtPtr points to mCrtPtr->next. If mCrtPtr is the
				// last element, mTail shall be modified and new value
				// for mCrtPtr shall be null.
				//
				if (!mCrtPtr)
				{
					OmnAlarm << "Null poiner in List::eraseCrt()" << enderr;
					return;
				}

				if (mCrtPtr->prev)
				{
					mCrtPtr->prev->next = mCrtPtr->next;
				}

				if (mCrtPtr->next)
				{
					mCrtPtr->next->prev = mCrtPtr->prev;
				}

				if (mCrtPtr == mTail)
				{
					mTail = mCrtPtr->prev;
				}

				if (mCrtPtr == mHead)
				{
					mHead = mCrtPtr->next;
				}

				C obj = mCrtPtr->content;

				mEntries--;
				mCrtPtr->content = mDefault;
				Elem *tmp = mCrtPtr->next;
				mCrtPtr->next = mIdle;
				mIdle = mCrtPtr;
				mCrtPtr = tmp;

				// 
				// If the index table is not null, check whether the list
				// becomes small enough to remove the index table.
				//
				if (mEntries < eSmallThreshold && mIndexTable)
				{
					OmnDelete mIndexTable;
					mIndexTable = 0;
				}

				// 
				// If the index table is not null, need to remove the object
				// from it.
				//
				if (mIndexTable)
				{
					OmnAssert1(!obj.isNull(), "Object is null");
					mIndexTable->get(obj->getKey(), true);
				}
			}

	C next() 
			{
				if (mCrtPtr)
				{
					C rslt = mCrtPtr->content;
					mCrtPtr = mCrtPtr->next;
					return rslt;
				}
				else
				{
					//
					// mCrtPtr already points to the end of the list
					//
					OmnAlarm << "Calling next() on null mCrtPtr: " << enderr;
					return mDefault;
				}
			}

	void	insert(const C &c) 
			{
				//
				// Insert c before the current position: mCrtPtr
				//
				if (!mIdle)
				{
					//
					// The mIdle list is null. Need to expand it.
					//
					expand();

					if (!mIdle)
					{
						// 
						// Failed to expand. Raise the alarm and return.
						//
						OmnAlarm << "Failed to expand when inserting new object" << enderr;
						return;
					}
				}

				//
				// Get the first element from the idle list.
				//
				Elem *tmp = mIdle;
				tmp->content = c;
				mIdle = mIdle->next;

				if (!mHead)
				{
					// 
					// mHead is null. This is an empty list. 
					//
					mHead = tmp;
					mTail = tmp;
					mHead->next = 0;
					mHead->prev = 0;
					mEntries = 1;
				 	return;
				}

				if (!mCrtPtr)
				{
					//
					// mCrtPtr is null. Same as append
					//
					tmp->prev = mTail;
					tmp->next = 0;
					mTail->next = tmp;
					mTail = tmp;
					mEntries++;

					if (mIndexTable)
					{
						// 
						// The index table is not null. Need to insert the object.
						//
						mIndexTable->add(c->getKey(), c);
					}
					return;
				}

				if (mHead == mCrtPtr)
				{
					// 
					// Since mCrtPtr points to the first element, the new head
					// shall point to this new element. 
					//
					mHead = tmp;
				}

				tmp->prev = mCrtPtr->prev;
				if (mCrtPtr->prev)
				{
					mCrtPtr->prev->next = tmp;
				}
				tmp->next = mCrtPtr;
				mCrtPtr->prev = tmp;
				mEntries++;

				if (mIndexTable)
				{
					mIndexTable->add(c->getKey(), c);
				}
				return;
			}

	bool	hasMore() const 
			{
				return mCrtPtr != 0;
			}

	void	expand()
			{
				//
				// Create the elements first. Note that the 
				// first element is reserved for managing 
				// the memory. 
				//
				//Elem *elems = OmnNew Elem[eIncrSize];
				Elem *elems = OmnNew Elem[eIncrSize];

				elems[0].next = mMemory;
				mMemory = elems;

				Elem *prev = 0;
				for (int i=1; i<eIncrSize-1; i++)
				{
					elems[i].next = &elems[i+1];
					elems[i].prev = prev;
					prev = &elems[i];
				}

				elems[eIncrSize-1].next = 0;
				mIdle = &elems[1];
			}

	bool	isInList(const C &c) const
			{
				if (mIndexTable || mEntries >= eTooBigThreshold)
				{
					if (!mIndexTable)
					{
						// 
						// The list is big enough, but the index was not created yet.
						// It's the time to create the index now. 
						// 
						mIndexTable = OmnNew IndexType;
						Elem *ptr = mHead;
						while (ptr)
						{
							// 
							// Add the element into the index table
							//
							mIndexTable->add(ptr->content->getKey(), ptr->content);
							ptr = ptr->next;
						}
					}

					// 
					// We will use the index table to check whether the element
					// is in the list. 
					// 
					C rslt = mIndexTable->get(C->getKey());
					return !rslt.isNull();
				}
				else
				{
					// 
					// There is no index table. Linear search the list.
					//
					Elem *ptr = mHead;
					while (ptr)
					{
						if (ptr->content->getKey() == c->getKey())
						{
							return true;
						}

						ptr = ptr->next;
					}

					return false;
				}

				return false;
			}


};

#endif
