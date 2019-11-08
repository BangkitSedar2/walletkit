//
//  BRGeneric.h
//  Core
//
//  Created by Ed Gamble on 6/19/19.
//  Copyright © 2019 Breadwinner AG. All rights reserved.
//
//  See the LICENSE file at the project root for license information.
//  See the CONTRIBUTORS file at the project root for a list of contributors.

#ifndef BRGeneric_h
#define BRGeneric_h

#include "support/BRInt.h" // UInt256
#include "support/BRSet.h" // BRSet
#include "support/BRKey.h" // BRKey
#include "support/BRArray.h"
#include "BRGenericBase.h"
#include "BRGenericClient.h"

#ifdef __cplusplus
extern "C" {
#endif

    // MARK: - Network

    extern BRGenericNetwork
    genNetworkCreate (const char * type,
                      int isMainnet);

    extern void
    genNetworkRelease (BRGenericNetwork network);

    extern const char *
    genNetworkGetType (BRGenericNetwork network);

    extern int
    genNetworkIsMainnet (BRGenericNetwork network);

    // MARK: - Account

    extern BRGenericAccount
    genAccountCreate (const char *type,
                      UInt512 seed);

    extern BRGenericAccount
    genAccountCreateWithPublicKey (const char *type,
                                   BRKey publicKey);

    extern BRGenericAccount
    genAccountCreateWithSerialization (const char *type,
                                       uint8_t *bytes,
                                       size_t   bytesCount);
    
    extern void
    genAccountRelease (BRGenericAccount account);

    extern const char *
    genAccountGetType (BRGenericAccount account);

    extern int
    genAccountHasType (BRGenericAccount account,
                       const char *type);

    extern BRGenericAddress
    genAccountGetAddress (BRGenericAccount account);

    extern uint8_t *
    genAccountGetSerialization (BRGenericAccount account, size_t *bytesCount);

    extern void
    genAccountSignTransferWithSeed (BRGenericAccount account,
                                    BRGenericTransfer transfer,
                                    UInt512 seed);

    extern void
    genAccountSignTransferWithKey (BRGenericAccount account,
                                   BRGenericTransfer transfer,
                                   BRKey *key);
    // Address

    extern BRGenericAddress
    genAddressCreate (const char *type,
                      const char *string);

    extern char *
    genAddressAsString (BRGenericAddress aid);

    extern int
    genAddressEqual (BRGenericAddress aid1,
                     BRGenericAddress aid2);

    extern void
    genAddressRelease (BRGenericAddress address);

    // Transfer

    extern void
    genTransferRelease (BRGenericTransfer transfer);

    extern BRGenericAddress
    genTransferGetSourceAddress (BRGenericTransfer transfer);

    extern BRGenericAddress
    genTransferGetTargetAddress (BRGenericTransfer transfer);

    extern UInt256
    genTransferGetAmount (BRGenericTransfer transfer);

    extern BRGenericFeeBasis
    genTransferGetFeeBasis (BRGenericTransfer transfer);

    extern BRGenericTransferDirection
    genTransferGetDirection (BRGenericTransfer transfer);

    extern BRGenericHash
    genTransferGetHash (BRGenericTransfer transfer);

    extern BRGenericTransferState
    genTransferGetState (BRGenericTransfer transfer);

    extern void
    genTransferSetState (BRGenericTransfer transfer,
                         BRGenericTransferState state);

    extern uint8_t *
    genTransferSerialize (BRGenericTransfer transfer, size_t *bytesCount);

    extern BRSetOf (BRGenericTransfer)
    genTransferSetCreate (size_t capacity);

    // MARK: - Generic Wallet

    /// Create the primary wallet.  The `account` is provided because wallet's create transfers which
    /// requires addresses that are derived from account properties.
    ///
    /// @param account The account to use for addresses derived from public keys, tyically.
    ///
    extern BRGenericWallet
    genWalletCreate (BRGenericAccount account);

    extern void
    genWalletRelease (BRGenericWallet wallet);

    extern UInt256
    genWalletGetBalance (BRGenericWallet wallet);

    extern BRGenericAddress
    genWalletGetAddress (BRGenericWallet wid);

    extern int
    genWalletHasAddress (BRGenericWallet wallet,
                         BRGenericAddress address);

    extern BRGenericFeeBasis
    genWalletGetDefaultFeeBasis (BRGenericWallet wid);

    extern void
    genWalletSetDefaultFeeBasis (BRGenericWallet wid,
                                 BRGenericFeeBasis bid);

    extern int
    genWalletHasTransfer (BRGenericWallet wallet,
                          BRGenericTransfer transfer);

    extern void
    genWalletAddTransfer (BRGenericWallet wallet,
                          BRGenericTransfer transfer);

    extern BRGenericTransfer
    genWalletCreateTransfer (BRGenericWallet wid,
                             BRGenericAddress target,
                             UInt256 amount,
                             BRGenericFeeBasis estimatedFeeBasis);

    extern BRGenericFeeBasis
    genWalletEstimateTransferFee (BRGenericWallet wid,
                                  BRGenericAddress target,
                                  UInt256 amount,
                                  UInt256 pricePerCostFactor);

    // MARK: Generic (Wallet) Manager

    extern BRGenericManager
    genManagerCreate (BRGenericClient client,
                      const char *type,
                      BRGenericNetwork network,
                      BRGenericAccount account,
                      uint64_t accountTimestamp,
                      const char *storagePath,
                      uint32_t syncPeriodInSeconds,
                      uint64_t blockHeight);

    extern void
    genManagerRelease (BRGenericManager gwm);

    extern void
    genManagerStop (BRGenericManager gwm);

    extern void
    genManagerConnect (BRGenericManager gwm);

    extern void
    genManagerDisconnect (BRGenericManager gwm);

    extern void
    genManagerSync (BRGenericManager gwm);

    #if 0
    extern BRArrayOf (BRGenericTransfer) // BRSetOf
    genManagerRestorePersistentTransfers (BRGenericManager gwm);

    extern void
    genManagerPersistTransfer (BRGenericManager gwm,
                               BRGenericTransfer  tid);
    #endif
    extern BRGenericAddress
    genManagerGetAccountAddress (BRGenericManager gwm);

    extern BRGenericWallet
    genManagerGetPrimaryWallet (BRGenericManager gwm);

    extern BRGenericAccount
    genManagerGetAccount (BRGenericManager gwm);

    extern BRGenericNetwork
    genManagerGetNetwork (BRGenericManager gwm);

    extern BRGenericClient
    genManagerGetClient (BRGenericManager gwm);

    extern BRGenericTransfer
    genManagerRecoverTransfer (BRGenericManager gwm,
                               BRGenericWallet wallet,
                               const char *hash,
                               const char *from,
                               const char *to,
                               const char *amount,
                               const char *currency,
                               const char *fee,
                               uint64_t timestamp,
                               uint64_t blockHeight);

    extern void
    genManagerWipe (BRGenericNetwork network,
                    const char *storagePath);

    extern BRArrayOf(BRGenericTransfer)
    genManagerRecoverTransfersFromRawTransaction (BRGenericManager gwm,
                                                  uint8_t *bytes,
                                                  size_t   bytesCount,
                                                  uint64_t timestamp,
                                                  uint64_t blockHeight);

    extern int
    genManagerSignTransfer (BRGenericManager gwm,
                            BRGenericWallet wid,
                            BRGenericTransfer transfer,
                            UInt512 seed);

    extern int
    genManagerSignTransferWithKey (BRGenericManager gwm,
                                   BRGenericWallet wid,
                                   BRGenericTransfer transfer,
                                   BRKey *key);

    extern void
    genManagerSubmitTransfer (BRGenericManager gwm,
                              BRGenericWallet wid,
                              BRGenericTransfer transfer);


    extern BRArrayOf(BRGenericTransfer)
    genManagerLoadTransfers (BRGenericManager gwm);

    extern void
    genManagerSaveTransfer (BRGenericManager gwm,
                            BRGenericTransfer transfer);

#endif /* BRGeneric_h */
