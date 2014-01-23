// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 LottoCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     1, uint256("0xb906af5b944449626faf9fc478373ce932f36cd8066916806946b5a38461cfe0"))
            ( 10000, uint256("0xa6e4605497a28503fb20bb728ba8fbbcb38cfce33e6bd31d51fb2547fb6ba5d7"))
            ( 30000, uint256("0xea421a7670439d56b20d3b490e2dabf17ed056189d04d30631562a58bb3957ec"))
            ( 50000, uint256("0x8fe4c45e8d6ef6c045860127cb1c32d2ac6eda7cd88e22408b2b92093493ee0e"))
            ( 70000, uint256("0x7d1af02b1528463ed4787c13c1325da56070660415e61c2692c7ba51e5e88578"))
            (100000, uint256("0x300f159b6abc21e3c487e0a3382036f31a45aab1593da59dfb2a4b42a4079cbf"))
            (120000, uint256("0x30299d1383d6e11f9c5d41e2886c9df1b5464426e1f2844bbaea9d3ba31b2e6d"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

		
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
