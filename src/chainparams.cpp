// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
// Copyright (c) 2024-2024 The BoldTechnologyCommerceUganda Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



/*
  ____ _____ ____ _   _  ____ 
 | __ )_   _/ ___| | | |/ ___|
 |  _ \ | || |   | | | | |  _ 
 | |_) || || |___| |_| | |_| |
 |____/ |_| \____|\___/ \____|
                              
*/


#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

#define DISABLED 0x7FFFFFFE;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Bold Technology Commerce Uganda - 2024";
    const CScript genesisOutputScript = CScript() << ParseHex("041a98becba22d29cf06719483f3acb828f7b286d1dbc34150dbd5b123bac725bf8fc0cb8e01ca292df4645abc4ac71e23510cee392b2e6cc5fcb5b824509172d1") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}



static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256S("0x00000605b45c654428fb9377c864bc81ab43d4e58292ad3cd6d8f5c158137897"))
    (1, uint256S("0x000002deb54b5d1a278a630afa6c8c2b3cb5be5d57679c7e8707b910aeec8f85"))
    (16, uint256S("0x00000805535ca2080275ad82c2583dcc8c34cd82fcdc9a543c58891ecfa2df36"))
    (49, uint256S("0x000001aa0778204e96beb0b3964d5e39205edf03d307ef8a8b0a4fee894c69c5"))
    (258, uint256S("0x7cf19211fffe676749028fd4e044a6530009fcb6772402470990a537e6764959"))
;

static const Checkpoints::CCheckpointData data =
	{ &mapCheckpoints, 1723760865, 474, 1.0000 };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x00000f7446b93653c0cc3b3abb45c96544c7efab5f68b896cad7ac3cbb9edcb2"));

static const Checkpoints::CCheckpointData dataTestnet =
	{ &mapCheckpoints, 1723740556, 0, 0 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x000004368e9f33fabebbcebfd71650d55ebeb6cf493aca0d55095fd7421107cf"));

static const Checkpoints::CCheckpointData dataRegtest =
	{ &mapCheckpoints, 1723740557, 0, 0 };


/**
  __  __           _                          _   
 |  \/  |   __ _  (_)  _ __    _ __     ___  | |_ 
 | |\/| |  / _` | | | | '_ \  | '_ \   / _ \ | __|
 | |  | | | (_| | | | | | | | | | | | |  __/ | |_ 
 |_|  |_|  \__,_| |_| |_| |_| |_| |_|  \___|  \__|
                                                  
 */


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1723740555, 486588, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000605b45c654428fb9377c864bc81ab43d4e58292ad3cd6d8f5c158137897"));
        assert(genesis.hashMerkleRoot == uint256S("0xf7300ccbf0d212b791f442c098e5a37be3e3d47810c1f2fb739199913f2d0628"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 20;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 15000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 3 * 60;
        consensus.nStakeMinDepth = 5;
        consensus.nStakeMinDepthV2 = 30;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "02985371d73cba52521aa56023a46ebe0f88b8b0ca31f07a0d29f10efc4ab9ec20";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           //{ "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 51;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 73;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 73;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 78;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 83;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 88;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 251;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("0xa93eb2021f7ca0a66c6b813ac90a30c24ca940ea7eb09c8f68d55d294b4195b3");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x09d0220056038ba1182dc96d83190b6f79fc665b46a0bd6adb12eae0515102c0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x09d0220056038ba1182dc96d83190b6f79fc665b46a0bd6adb12eae0515102c0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x695a96b7f644a54bac7cc23131fbf3018d116c91ad0ee8e17c213f6804d0abce");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x7537930792c13e121a02a68d12455acd97e68a19fd1383c4d149f6da78fb2a11");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x96b05b29cfc476e0b0f95c507519497aaf169454486649570c72d70e98af6d53");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x1dc4b8777b8bf22ef60cf9dc659f111b2a77a150344853c8fe1980030efa2d66");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        // Treasury
        consensus.nTreasuryActivationHeight = INT_MAX;
        consensus.nTreasuryPercentage = 0;
        consensus.strTreasuryAddress = "";

        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xb5;
        nDefaultPort = __PORT_MAINNET__;

        vSeeds.push_back(CDNSSeedData("seeder1", "seed01.btcugltd.com"));
        vSeeds.push_back(CDNSSeedData("seeder2", "seed02.btcugltd.com"));
        vSeeds.push_back(CDNSSeedData("seeder3", "seed03.btcugltd.com"));
        vSeeds.push_back(CDNSSeedData("seeder4", "seed04.btcugltd.com"));
        vSeeds.push_back(CDNSSeedData("seeder5", "seed05.btcugltd.com"));
        vSeeds.push_back(CDNSSeedData("seeder6", "seed06.btcugltd.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 26);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1d)(0xfc).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;



/**
  _____                _                    _   
 |_   _|   ___   ___  | |_   _ __     ___  | |_ 
   | |    / _ \ / __| | __| | '_ \   / _ \ | __|
   | |   |  __/ \__ \ | |_  | | | | |  __/ | |_ 
   |_|    \___| |___/  \__| |_| |_|  \___|  \__|
                                                
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1723740556, 1017640, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000f7446b93653c0cc3b3abb45c96544c7efab5f68b896cad7ac3cbb9edcb2"));
        assert(genesis.hashMerkleRoot == uint256S("0xf7300ccbf0d212b791f442c098e5a37be3e3d47810c1f2fb739199913f2d0628"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // BoldTechnologyCommerceUganda starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 3;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = INT_MAX * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 200;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "0267975c05193d0c79b6746ad6d2029abe55f278a3131749c49dc08131bf583478";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 51;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 101;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 201;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 301;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 501;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  =uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        // Treasury
        consensus.nTreasuryActivationHeight = INT_MAX;
        consensus.nTreasuryPercentage = 0;
        consensus.strTreasuryAddress = "";


        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xa4;
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.push_back(CDNSSeedData("tseeder", "xxxxxxx", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 128);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 194);
        // Testnet BoldTechnologyCommerceUganda BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet BoldTechnologyCommerceUganda BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet BoldTechnologyCommerceUganda BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;



/**
  ____                   _                  _   
 |  _ \    ___    __ _  | |_    ___   ___  | |_ 
 | |_) |  / _ \  / _` | | __|  / _ \ / __| | __|
 |  _ <  |  __/ | (_| | | |_  |  __/ \__ \ | |_ 
 |_| \_\  \___|  \__, |  \__|  \___| |___/  \__|
                 |___/                          
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1723740557, 180740, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000004368e9f33fabebbcebfd71650d55ebeb6cf493aca0d55095fd7421107cf"));
        assert(genesis.hashMerkleRoot == uint256S("0xf7300ccbf0d212b791f442c098e5a37be3e3d47810c1f2fb739199913f2d0628"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // BoldTechnologyCommerceUganda starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 3;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 250 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest */
        consensus.strSporkPubKey = "0387d4312ee753eabaec9b66fcd85b7bfe97de786d8bd4f43577712a803be0b100";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                    = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight               = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                     = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                  = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight        = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight  = 300;

        // Treasury
        consensus.nTreasuryActivationHeight = INT_MAX;
        consensus.nTreasuryPercentage = 0;
        consensus.strTreasuryAddress = "";


        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = __PORT_REGTEST__;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
