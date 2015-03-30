// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x77;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x07;
        vAlertPubKey = ParseHex("04988EB3D02729EF045F192E10CD9C1D74044EFC00BFD946C3294C1D9D425BA2D9B3D8E45DC1FB005A77C149371CA4929D4F99ED077E5109AB554BEF1477D96AE9");
        nDefaultPort = 17771;
        nRPCPort = 17772;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "March 10, 2015:Three Unnamed Bidders Win Latest US Marshals Bitcoin Auction";
        CTransaction txNew;
        txNew.nTime = 1425111074;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1425111074;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 177482;

        hashGenesisBlock = genesis.GetHash();



        assert(hashGenesisBlock == uint256("0xeb728e67911dd39d933ee758a1eda19eb2c4858ab1e7b1c5085859b33dd13fdf"));
        assert(genesis.hashMerkleRoot == uint256("0x4472815cca79e73c5fd7ddf9480f6915b7e5b5537203fa2867df04ab09faea58"));


        //vFixedSeeds.clear();
        //vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(28);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(88);
        base58Prefixes[SECRET_KEY] =     list_of(151);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x77)(0xB1)(0x1D);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x77)(0xAE)(0xE1);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xaf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0446C57B31F7C99691A88C8AEB029539F165DD4C5436C3D263B8A864AA8669765F25E5C4608AC73EBAD31FB662E961F863BBE81C7D2D78EF166105E3354D44CD15");
        nDefaultPort = 27771;
        nRPCPort = 27772;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 277178;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x463011b1196dfbb2a93e29b786b6ea57efe4c6140dbf73c1de5e2ef67139141f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(22);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(8);
        base58Prefixes[SECRET_KEY]     = list_of(237);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x75)(0x81)(0xC3);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x75)(0x82)(0x93);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0xde;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1425111074;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 27;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 17444;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x597795ce4800e98c991304053540636c17a9652b1dffb41615d616f252399974"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
