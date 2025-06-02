import { getFullnodeUrl, SuiClient, GetOwnedObjectsParams, PaginatedObjectsResponse, SuiObjectRef} from '@mysten/sui/client';
import { verifyPersonalMessageSignature } from '@mysten/sui/verify';
import { fromHEX, fromB64 } from '@mysten/sui/utils';
import { Ed25519Keypair } from '@mysten/sui/keypairs/ed25519';
import { bech32 } from 'bech32';
import { Transaction } from '@mysten/sui/transactions';
import {
    CreateWalletResponse,
    NftMintMessage,
    RegularCoinMintMessage,
    SuiTransactionResult,
    CoinBalanceResponse,
    CoinBalanceRequest,
    SuiObject,
    RegularCoinBurnMessage,
    GameCoinMintMessage,
    GameCoinBurnMessage,
    RegularCoinBalanceRequest,
    NftUpdateMessage,
    SetNftOwnerMessage, CoinToken, NftDeleteMessage, CurrencyTransfer, CoinModel
} from './models';
import { retrievePaginatedData,calculateTotalCost,stringToNumber } from "./utils";
import {MoveValue} from "@mysten/sui/src/client/types/generated";
import { SUI_CLOCK_OBJECT_ID } from '@mysten/sui/utils';
import { bcs } from "@mysten/sui/bcs";

type Callback<T> = (error: any, result: T | null) => void;
type Environment = 'mainnet' | 'testnet' | 'devnet' | 'localnet';
const SUI_PRIVATE_KEY_PREFIX = 'suiprivkey';
let suiClientInstance: SuiClient | null = null;

function getSuiClientInstance(environment: Environment): SuiClient {
    if (!suiClientInstance) {
        suiClientInstance = new SuiClient({url: getFullnodeUrl(environment)});
    }
    return suiClientInstance;
}

function decodeSuiPrivateKey(value: string) {
    if (value.startsWith("0x")) {
        return fromHEX(value);
    }
    if (value.startsWith(SUI_PRIVATE_KEY_PREFIX)) {
        const { prefix, words } = bech32.decode(value);
        const extendedSecretKey = new Uint8Array(bech32.fromWords(words));
        return extendedSecretKey.slice(1);
    }
    if (!value.startsWith(SUI_PRIVATE_KEY_PREFIX) && value.length == 60) {
        const pk_with_prefix = SUI_PRIVATE_KEY_PREFIX + value;
        const { prefix, words } = bech32.decode(pk_with_prefix);
        const extendedSecretKey = new Uint8Array(bech32.fromWords(words));
        return extendedSecretKey.slice(1);
    }
    if (!value.startsWith(SUI_PRIVATE_KEY_PREFIX) && value.length == 44) {
        return fromB64(value);
    }
    throw new Error('invalid private key value');
}
async function createWallet(callback: Callback<string>) {
    let error = null;
    const keys= new CreateWalletResponse();
    try {
        const keypair = new Ed25519Keypair();
        keys.PrivateKey = keypair.getSecretKey();
        keys.Address = keypair.toSuiAddress();
        keys.PublicKey = Buffer.from(keypair.getPublicKey().toRawBytes()).toString('base64');
    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(keys));
}
async function importWallet(callback: Callback<string>, privateKey: string) {
    let error = null;
    const keys= new CreateWalletResponse();
    try {
        const decoded = decodeSuiPrivateKey(privateKey);
        const keypair = Ed25519Keypair.fromSecretKey(decoded);
        keys.PrivateKey = keypair.getSecretKey();
        keys.Address = keypair.toSuiAddress();
        keys.PublicKey = Buffer.from(keypair.getPublicKey().toRawBytes()).toString('base64');
    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(keys));
}
async function verifySignature(callback: Callback<boolean>, token: string, challenge: string, solution: string) {
    let isValid = false;
    let error = null;
    try {
        const messageEncoded = new TextEncoder().encode(challenge);
        const verificationPublicKey = await verifyPersonalMessageSignature(messageEncoded, solution);
        if (verificationPublicKey.toSuiAddress() === token) {
            isValid = true;
        }
    } catch (ex) {
        if (ex instanceof Error && ex.message === `Signature is not valid for the provided message`) {
            isValid = false;
        } else if (ex instanceof Error && ex.message.startsWith('Unsupported signature scheme')) {
            isValid = false;
        } else {
            isValid = false;
            error = ex;
        }
    }
    callback(error, isValid);
}
async function mintRegularCoin(callback: Callback<string>, item: string, realmKey: string, environment: Environment) {
    let error = null;
    const result = new SuiTransactionResult();
    try {
        const mintRequests: RegularCoinMintMessage[] = JSON.parse(item);
        const keypair = Ed25519Keypair.fromSecretKey(realmKey);
        const txb = new Transaction();

        mintRequests.forEach((coinItem) => {
            const coinTarget: `${string}::${string}::${string}` = `${coinItem.PackageId}::${coinItem.Module}::${coinItem.Function}`;
            txb.moveCall({
                target: coinTarget,
                arguments: [
                    txb.object(coinItem.AdminCap),
                    txb.object(coinItem.TreasuryCap),
                    txb.pure.u64(coinItem.Amount),
                    txb.pure.address(coinItem.PlayerWalletAddress)
                ]});
        });

        const suiClient = getSuiClientInstance(environment);
        const response = await suiClient.signAndExecuteTransaction({
            signer: keypair,
            transaction: txb,
            options: {
                showEffects: true
            }
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function getBalance(callback: Callback<string>, address: string, item: string, environment: Environment) {
    let error = null;
    let coinBalanceResponse = new CoinBalanceResponse("",0);
    try {
        const suiClient = getSuiClientInstance(environment);
        const request: CoinBalanceRequest = JSON.parse(item);
        const coinType = `${request.PackageId}::${request.ModuleName.toLowerCase()}::${request.ModuleName.toUpperCase()}`;
        const coinBalance = await suiClient.getBalance({
            owner: address,
            coinType: coinType
        });
        coinBalanceResponse.CoinType = coinType;
        coinBalanceResponse.Total = parseInt(coinBalance.totalBalance ?? "0", 10) || 0;

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(coinBalanceResponse));
}
async function mintNfts(callback: Callback<string>, item: string, realmKey: string, environment: Environment) {
    let error = null;
    const result = new SuiTransactionResult();
    try {
        const mintRequests: NftMintMessage[] = JSON.parse(item);
        const keypair = Ed25519Keypair.fromSecretKey(realmKey);
        const txb = new Transaction();

        mintRequests.forEach((item) => {
            const target: `${string}::${string}::${string}` = `${item.PackageId}::${item.Module}::${item.Function}`;
            txb.moveCall({
                target: target,
                arguments: [
                    txb.object(item.AdminCap),
                    txb.pure.address(item.PlayerWalletAddress),
                    txb.pure.string(item.NftContentItem.Name),
                    txb.pure.string(item.NftContentItem.Description),
                    txb.pure.string(item.NftContentItem.Url),
                    txb.pure.string(item.NftContentItem.ContentId),
                    txb.pure.vector("string", item.NftContentItem.Attributes.map(attribute => attribute.Name)),
                    txb.pure.vector("string", item.NftContentItem.Attributes.map(attribute => attribute.Value))


                ]});
        });

        const suiClient = getSuiClientInstance(environment);
        const response = await suiClient.signAndExecuteTransaction({
            signer: keypair,
            transaction: txb,
            options: {
                showEffects: true
            }
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function setNftContractOwner(callback: Callback<string>, item: string, realmKey: string, environment: Environment) {
    let error = null;
    const result = new SuiTransactionResult();
    try {
        const request: SetNftOwnerMessage = JSON.parse(item);
        const keypair = Ed25519Keypair.fromSecretKey(realmKey);
        const txb = new Transaction();

        const target: `${string}::${string}::${string}` = `${request.PackageId}::${request.Module}::${request.Function}`;
        txb.moveCall({
            target: target,
            arguments: [
                txb.object(request.AdminCap),
                txb.pure.vector("u8", keypair.getPublicKey().toRawBytes())
            ]});

        const suiClient = getSuiClientInstance(environment);
        const response = await suiClient.signAndExecuteTransaction({
            signer: keypair,
            transaction: txb,
            options: {
                showEffects: true
            }
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function getOwnedObjects(callback: Callback<string>, address: string, packageId: string, environment: Environment) {
    let error = null;
    const objects: SuiObject[] = [];
    try {
        const suiClient = new SuiClient({url: getFullnodeUrl(environment)});

        const inputParams: GetOwnedObjectsParams = {
            owner: address,
            cursor: null,
            options: {
                showType: true,
                showContent: true,
                showDisplay: true
            },
            filter: {
                Package: packageId
            }
        };
        const handleData = async (input: GetOwnedObjectsParams) => {
            return await suiClient.getOwnedObjects(input);
        };

        const results = await retrievePaginatedData<GetOwnedObjectsParams, PaginatedObjectsResponse>(handleData, inputParams);

        results.forEach(result => {
            result.data.forEach(element => {
                if (element.data != undefined)  {
                    const suiObject = new SuiObject(
                        element.data.objectId,
                        element.data.digest,
                        element.data.version,
                        element.data.content,
                        element.data.display
                    );
                    objects.push(suiObject);
                }
            });
        })

    } catch (ex) {
        error = ex;
    }

    callback(error, JSON.stringify(objects.map(object => object.toView())));
}
async function getGameCoinBalance(callback: Callback<string>, address: string, item: string, environment: Environment) {
    let error = null;
    let coinBalanceResponse = new CoinBalanceResponse("",0);
    const objects: SuiObject[] = [];
    try {
        const suiClient = new SuiClient({url: getFullnodeUrl(environment)});
        const request: RegularCoinBalanceRequest = JSON.parse(item);
        const coinType = `0x2::token::Token<${request.PackageId}::${request.ModuleName.toLowerCase()}::${request.ModuleName.toUpperCase()}>`;
        coinBalanceResponse.CoinType = coinType;
        const inputParams: GetOwnedObjectsParams = {
            owner: address,
            cursor: null,
            options: {
                showType: true,
                showContent: true,
                showDisplay: false
            },
            filter: {
                StructType: coinType
            }
        };
        const handleData = async (input: GetOwnedObjectsParams) => {
            return await suiClient.getOwnedObjects(input);
        };

        const results = await retrievePaginatedData<GetOwnedObjectsParams, PaginatedObjectsResponse>(handleData, inputParams);

        results.forEach(result => {
            result.data.forEach(element => {
                if (element.data != undefined)  {
                    const suiObject = new SuiObject(
                        element.data.objectId,
                        element.data.digest,
                        element.data.version,
                        element.data.content,
                        null // NO display
                    );
                    objects.push(suiObject);
                }
            });
        })

        let totalAmount = 0;
        objects.forEach(obj => {
            switch (obj.Content?.dataType) {
                case 'moveObject':
                    const contentFields = obj.Content?.fields;
                    if (contentFields != null) {
                        const balanceStr = (contentFields as { [key: string]: MoveValue })["balance"] as string;
                        const balance = stringToNumber(balanceStr);
                        totalAmount += balance;
                    }
            }
        });
        coinBalanceResponse.Total = totalAmount;

    } catch (ex) {
        error = ex;
    }

    callback(error, JSON.stringify(coinBalanceResponse));
}
async function burnRegularCoin(callback: Callback<string>, request: string, realmKey: string, environment: Environment) {
    let error = null;
    const burnRequests: RegularCoinBurnMessage[] = JSON.parse(request);
    let result = new SuiTransactionResult();
    try {
        const suiClient = getSuiClientInstance(environment);
        const gameKeypair = Ed25519Keypair.fromSecretKey(realmKey);
        const playerKeypair = Ed25519Keypair.fromSecretKey(burnRequests[0].PlayerWalletKey);
        const playerWallet = burnRequests[0].PlayerWalletAddress;
        const gameWallet = gameKeypair.toSuiAddress();
        const txb = new Transaction();

        for (const coinItem of burnRequests) {
            const coins = await suiClient.getCoins({
                owner: coinItem.PlayerWalletAddress,
                coinType: `${coinItem.PackageId}::${coinItem.Module.toLowerCase()}::${coinItem.Module.toUpperCase()}`
            });

            // Sort coins by balance (descending)
            const sortedCoins = coins.data.sort((a, b) => Number(b.balance) - Number(a.balance));

            // Select coins whose total balance matches the amount to burn
            let totalBalance = 0;
            const selectedCoins = [];
            for (const coin of sortedCoins) {
                if (totalBalance >= coinItem.Amount) break;
                selectedCoins.push(coin);
                totalBalance += Number(coin.balance);
            }

            let remainingAmount = coinItem.Amount;
            const coinsToBurn = [];
            for (const coin of selectedCoins) {
                const coinBalance = Number(coin.balance);
                if (coinBalance <= remainingAmount) {
                    // Use the entire coin
                    coinsToBurn.push(coin.coinObjectId);
                    remainingAmount -= coinBalance;
                } else {
                    // Split the coin to get the exact amount needed
                    const splitCoin = txb.splitCoins(txb.object(coin.coinObjectId), [txb.pure.u64(remainingAmount)]);
                    coinsToBurn.push(splitCoin);
                    remainingAmount = 0;
                }
                if (remainingAmount === 0) break;
            }
            const coinTarget: `${string}::${string}::${string}` = `${coinItem.PackageId}::${coinItem.Module}::${coinItem.Function}`;
            for (const coinId of coinsToBurn) {
                txb.moveCall({
                    target: coinTarget,
                    arguments: [
                        txb.object(coinItem.TreasuryCap),
                        txb.object(coinId),
                    ],
                });
            }
        }

        let payment: SuiObjectRef[] = [];
        const coins = await suiClient.getCoins({ owner: gameWallet, limit: 1 });
        if (coins.data.length > 0) {
            payment = coins.data.map((coin) => ({
                objectId: coin.coinObjectId,
                version: coin.version,
                digest: coin.digest,
            }));
        } else {
            throw new Error(`Can't find gas coins from sponsor ${gameWallet}.`);
        }

        const kindBytes = await txb.build({ onlyTransactionKind: true, client: suiClient });
        const sponsoredTxb = Transaction.fromKind(kindBytes);
        sponsoredTxb.setSender(playerWallet);
        sponsoredTxb.setGasOwner(gameWallet);
        sponsoredTxb.setGasPayment(payment);
        const sponsoredBytes = await sponsoredTxb.build({ client: suiClient });
        const developerSignature = await gameKeypair!.signTransaction(sponsoredBytes);
        const playerSignature = await playerKeypair!.signTransaction(sponsoredBytes);

        const response = await suiClient.executeTransactionBlock({
            transactionBlock: sponsoredBytes,
            signature: [developerSignature.signature, playerSignature.signature],
            options: {
                showEffects: true,
                showEvents: true,
                showObjectChanges: true,
            },
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function mintGameCoin(callback: Callback<string>, item: string, realmKey: string, environment: Environment) {
    let error = null;
    const result = new SuiTransactionResult();
    try {
        const mintRequests: GameCoinMintMessage[] = JSON.parse(item);
        const keypair = Ed25519Keypair.fromSecretKey(realmKey);
        const txb = new Transaction();

        mintRequests.forEach((coinItem) => {
            const coinTarget: `${string}::${string}::${string}` = `${coinItem.PackageId}::${coinItem.Module}::${coinItem.Function}`;
            txb.moveCall({
                target: coinTarget,
                arguments: [
                    txb.object(coinItem.AdminCap),
                    txb.object(coinItem.Store),
                    txb.pure.u64(coinItem.Amount),
                    txb.pure.address(coinItem.PlayerWalletAddress)
                ]});
        });

        const suiClient = getSuiClientInstance(environment);
        const response = await suiClient.signAndExecuteTransaction({
            signer: keypair,
            transaction: txb,
            options: {
                showEffects: true
            }
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function burnGameCoin(callback: Callback<string>, request: string, realmKey: string, environment: Environment) {
    let error = null;
    const burnRequests: GameCoinBurnMessage[] = JSON.parse(request);
    let result = new SuiTransactionResult();
    const coinTokens: CoinToken[] = [];

    try {
        const suiClient = getSuiClientInstance(environment);
        const gameKeypair = Ed25519Keypair.fromSecretKey(realmKey);
        const playerKeypair = Ed25519Keypair.fromSecretKey(burnRequests[0].PlayerWalletKey);
        const playerWallet = burnRequests[0].PlayerWalletAddress;
        const gameWallet = gameKeypair.toSuiAddress();
        const txb = new Transaction();

        for (const tokenItem of burnRequests) {
            const objects: SuiObject[] = [];

            const coinType = `0x2::token::Token<${tokenItem.PackageId}::${tokenItem.Module.toLowerCase()}::${tokenItem.Module.toUpperCase()}>`;
            const inputParams: GetOwnedObjectsParams = {
                owner: playerWallet,
                cursor: null,
                options: {
                    showType: true,
                    showContent: true,
                    showDisplay: false
                },
                filter: {
                    StructType: coinType
                }
            };
            const handleData = async (input: GetOwnedObjectsParams) => {
                return await suiClient.getOwnedObjects(input);
            };

            const results = await retrievePaginatedData<GetOwnedObjectsParams, PaginatedObjectsResponse>(handleData, inputParams);

            results.forEach(result => {
                result.data.forEach(element => {
                    if (element.data != undefined)  {
                        const suiObject = new SuiObject(
                            element.data.objectId,
                            element.data.digest,
                            element.data.version,
                            element.data.content,
                            null // NO display
                        );
                        objects.push(suiObject);
                    }
                });
            });
            objects.forEach(obj => {
                switch (obj.Content?.dataType) {
                    case 'moveObject':
                        const contentFields = obj.Content?.fields;
                        if (contentFields != null) {
                            const balanceStr = (contentFields as { [key: string]: MoveValue })["balance"] as string;
                            const balance = stringToNumber(balanceStr);
                            const idValue = (contentFields as { [key: string]: MoveValue })["id"] as { id: string };
                            const idStr = idValue.id;
                            coinTokens.push(new CoinToken(idStr, balance));
                        }
                }
            });

            const sortedCoins = coinTokens.sort((a, b) => a.Balance - b.Balance);

            // Select coins whose total balance matches the amount to burn
            let totalBalance = 0;
            const selectedCoins = [];
            for (const coin of sortedCoins) {
                if (totalBalance >= tokenItem.Amount) break;
                selectedCoins.push(coin);
                totalBalance += Number(coin.Balance);
            }

            let remainingAmount = tokenItem.Amount;
            for (const coin of selectedCoins) {
                const coinBalance = Number(coin.Balance);
                if (coinBalance <= remainingAmount) {
                    // Use the entire coin
                    const coinTarget: `${string}::${string}::${string}` = `${tokenItem.PackageId}::${tokenItem.Module}::${tokenItem.Function}`;
                    txb.moveCall({
                        target: coinTarget,
                        arguments: [
                            txb.object(coin.Id),
                            txb.object(tokenItem.Store),
                        ],
                    });
                    remainingAmount -= coinBalance;
                } else {
                    // Split the coin to get the exact amount needed
                    const coinTarget: `${string}::${string}::${string}` = `${tokenItem.PackageId}::${tokenItem.Module}::splitBurn`;
                    txb.moveCall({
                        target: coinTarget,
                        arguments: [
                            txb.object(coin.Id),
                            txb.object(tokenItem.Store),
                            txb.pure.u64(remainingAmount)
                        ],
                    });
                    remainingAmount = 0;
                }
                if (remainingAmount === 0) break;
            }
        }

        let payment: SuiObjectRef[] = [];
        const coins = await suiClient.getCoins({ owner: gameWallet, limit: 1 });
        if (coins.data.length > 0) {
            payment = coins.data.map((coin) => ({
                objectId: coin.coinObjectId,
                version: coin.version,
                digest: coin.digest,
            }));
        } else {
            throw new Error(`Can't find gas coins from sponsor ${gameWallet}.`);
        }

        const kindBytes = await txb.build({ onlyTransactionKind: true, client: suiClient });
        const sponsoredTxb = Transaction.fromKind(kindBytes);
        sponsoredTxb.setSender(playerWallet);
        sponsoredTxb.setGasOwner(gameWallet);
        sponsoredTxb.setGasPayment(payment);
        const sponsoredBytes = await sponsoredTxb.build({ client: suiClient });
        const developerSignature = await gameKeypair!.signTransaction(sponsoredBytes);
        const playerSignature = await playerKeypair!.signTransaction(sponsoredBytes);

        const response = await suiClient.executeTransactionBlock({
            transactionBlock: sponsoredBytes,
            signature: [developerSignature.signature, playerSignature.signature],
            options: {
                showEffects: true,
                showEvents: true,
                showObjectChanges: true,
            },
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function updateNft(callback: Callback<string>, request: string, realmKey: string, environment: Environment) {
    let error = null;
    const updateRequests: NftUpdateMessage[] = JSON.parse(request);
    let result = new SuiTransactionResult();
    try {
        const suiClient = getSuiClientInstance(environment);
        const gameKeypair = Ed25519Keypair.fromSecretKey(realmKey);
        const playerKeypair = Ed25519Keypair.fromSecretKey(updateRequests[0].PlayerWalletKey);
        const gameWallet = gameKeypair.toSuiAddress();
        const txb = new Transaction();
        const currentTime = Date.now();

        for (const request of updateRequests) {
            for (const attribute of request.Attributes) {
                const nftIdBytes = bcs.Address.serialize(request.ProxyId).toBytes();
                const nameBytes = bcs.string().serialize(attribute.Name).toBytes();
                const valueBytes = bcs.string().serialize(attribute.Value).toBytes();
                const timestampBytes = bcs.u64().serialize(currentTime).toBytes();

                // Combine all serialized bytes into a single Uint8Array
                const messageBytes = new Uint8Array([
                    ...nftIdBytes,
                    ...nameBytes,
                    ...valueBytes,
                    ...timestampBytes,
                ]);

                const signature = await gameKeypair.sign(messageBytes);
                const coinTarget: `${string}::${string}::${string}` = `${request.PackageId}::${request.Module}::${request.Function}`;
                txb.moveCall({
                    target: coinTarget,
                    arguments: [
                        txb.object(request.ProxyId),
                        txb.object(request.OwnerObjectId),
                        txb.object(SUI_CLOCK_OBJECT_ID),
                        txb.pure.vector("u8", signature),
                        txb.pure.u64(currentTime),
                        txb.pure.string(attribute.Name),
                        txb.pure.string(attribute.Value),
                    ],
                });
            }
        }

        let payment: SuiObjectRef[] = [];
        const coins = await suiClient.getCoins({ owner: gameWallet, limit: 1 });
        if (coins.data.length > 0) {
            payment = coins.data.map((coin) => ({
                objectId: coin.coinObjectId,
                version: coin.version,
                digest: coin.digest,
            }));
        } else {
            throw new Error(`Can't find gas coins from sponsor ${gameWallet}.`);
        }

        const kindBytes = await txb.build({ onlyTransactionKind: true, client: suiClient });
        const sponsoredTxb = Transaction.fromKind(kindBytes);
        sponsoredTxb.setSender(playerKeypair.toSuiAddress());
        sponsoredTxb.setGasOwner(gameWallet);
        sponsoredTxb.setGasPayment(payment);
        const sponsoredBytes = await sponsoredTxb.build({ client: suiClient });
        const developerSignature = await gameKeypair!.signTransaction(sponsoredBytes);
        const playerSignature = await playerKeypair!.signTransaction(sponsoredBytes);

        const response = await suiClient.executeTransactionBlock({
            transactionBlock: sponsoredBytes,
            signature: [developerSignature.signature, playerSignature.signature],
            options: {
                showEffects: true,
                showEvents: true,
                showObjectChanges: true,
            },
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function burnNft(callback: Callback<string>, request: string, realmKey: string, environment: Environment) {
    let error = null;
    const deleteRequests: NftDeleteMessage[] = JSON.parse(request);
    let result = new SuiTransactionResult();
    try {
        const suiClient = getSuiClientInstance(environment);
        const gameKeypair = Ed25519Keypair.fromSecretKey(realmKey);
        const playerKeypair = Ed25519Keypair.fromSecretKey(deleteRequests[0].PlayerWalletKey);
        const gameWallet = gameKeypair.toSuiAddress();
        const txb = new Transaction();
        const currentTime = Date.now();

        for (const request of deleteRequests) {
            const nftIdBytes = bcs.Address.serialize(request.ProxyId).toBytes();
            const timestampBytes = bcs.u64().serialize(currentTime).toBytes();

            // Combine all serialized bytes into a single Uint8Array
            const messageBytes = new Uint8Array([
                ...nftIdBytes,
                ...timestampBytes,
            ]);

            const signature = await gameKeypair.sign(messageBytes);
            const coinTarget: `${string}::${string}::${string}` = `${request.PackageId}::${request.Module}::${request.Function}`;
            txb.moveCall({
                target: coinTarget,
                arguments: [
                    txb.object(request.ProxyId),
                    txb.object(request.OwnerObjectId),
                    txb.object(SUI_CLOCK_OBJECT_ID),
                    txb.pure.vector("u8", signature),
                    txb.pure.u64(currentTime),
                ],
            });
        }

        let payment: SuiObjectRef[] = [];
        const coins = await suiClient.getCoins({ owner: gameWallet, limit: 1 });
        if (coins.data.length > 0) {
            payment = coins.data.map((coin) => ({
                objectId: coin.coinObjectId,
                version: coin.version,
                digest: coin.digest,
            }));
        } else {
            throw new Error(`Can't find gas coins from sponsor ${gameWallet}.`);
        }

        const kindBytes = await txb.build({ onlyTransactionKind: true, client: suiClient });
        const sponsoredTxb = Transaction.fromKind(kindBytes);
        sponsoredTxb.setSender(playerKeypair.toSuiAddress());
        sponsoredTxb.setGasOwner(gameWallet);
        sponsoredTxb.setGasPayment(payment);
        const sponsoredBytes = await sponsoredTxb.build({ client: suiClient });
        const developerSignature = await gameKeypair!.signTransaction(sponsoredBytes);
        const playerSignature = await playerKeypair!.signTransaction(sponsoredBytes);

        const response = await suiClient.executeTransactionBlock({
            transactionBlock: sponsoredBytes,
            signature: [developerSignature.signature, playerSignature.signature],
            options: {
                showEffects: true,
                showEvents: true,
                showObjectChanges: true,
            },
        });

        if (response.effects != null) {
            result.status = response.effects.status.status;
            result.gasUsed = calculateTotalCost(response.effects.gasUsed);
            result.digest = response.effects.transactionDigest;
            result.objectIds = response.effects.created?.map(o => o.reference.objectId);
            result.error = response.effects.status.error;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}
async function objectExists(callback: Callback<string>, itemId: string, environment: Environment) {
    let error = null;
    let result = true;
    try {
        const suiClient = getSuiClientInstance(environment);
        const objectResult = await suiClient.getObject({
            id: itemId,
        });

        if (objectResult.error !== undefined && objectResult.error !== null) {
            result = false;
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}

async function getTargetCoins(owner: string, packageId: string, coin: string, target: number, suiClient: SuiClient) {
    const coinsFromClient: CoinModel[] = [];
    let coins_resp;
    let cursor = null;
    let targetFound = false;
    let sum = 0;
    do {
        coins_resp = await suiClient.getCoins({
            coinType: `${packageId}::${coin.toLowerCase()}::${coin.toUpperCase()}`,
            owner : owner,
            cursor: cursor,
            limit : 10
        });
        for (const coin of coins_resp.data) {
            coinsFromClient.push(new CoinModel(coin.coinObjectId, Number(coin.balance)))
            sum += Number(coin.balance);
        }

        if (sum >= target) {
            targetFound = true;
            break;
        }
        cursor = coins_resp?.nextCursor;
    } while (coins_resp.hasNextPage);

    if (!targetFound) {
        return [];
    }
    // Sort the array in ascending order based on the balance
    coinsFromClient.sort((a, b) => a.balance - b.balance);

    // Reduce sorted array to include only coins needed for transaction
    let accumulatedBalance = 0;
    return coinsFromClient.reduce((acc: CoinModel[], coin: CoinModel) => {
        if (accumulatedBalance < target) {
            acc.push(coin);
            accumulatedBalance += coin.balance;
        }
        return acc;
    }, []);
}

async function withdrawCurrency(callback: Callback<string>, request: string, developerKey: string, environment: Environment) {
    let error = null;
    const result = new SuiTransactionResult();
    try {
        const suiClient = getSuiClientInstance(environment);
        const currencyTransfer: CurrencyTransfer = JSON.parse(request);
        const playerKeypair = Ed25519Keypair.fromSecretKey(decodeSuiPrivateKey(currencyTransfer.PlayerWalletKey));
        const developerKeypair = Ed25519Keypair.fromSecretKey(decodeSuiPrivateKey(developerKey));
        const developerWallet = developerKeypair.toSuiAddress();
        const sourceWallet = playerKeypair.toSuiAddress();

        if (currencyTransfer != null) {
            currencyTransfer.Amount = Math.abs(currencyTransfer.Amount);
            const targetCoins= await getTargetCoins(sourceWallet, currencyTransfer.PackageId, currencyTransfer.Module, currencyTransfer.Amount, suiClient);
            if (!Array.isArray(targetCoins) || (Array.isArray(targetCoins) && targetCoins.length === 0)) {
                throw new Error(`Can't find target amount (${currencyTransfer.Amount}) of coins from address ${sourceWallet}.`);
            }
            const tx = new Transaction();

            if (targetCoins.length === 1) {
                const coin = targetCoins[0];
                if (coin.balance === currencyTransfer.Amount) {
                    tx.transferObjects([tx.object(coin.coinObjectId)], tx.pure.address(currencyTransfer.TargetWalletAddress));
                } else if (coin.balance > currencyTransfer.Amount) {
                    const [targetCoin] = tx.splitCoins(tx.object(coin.coinObjectId), [tx.pure.u64(currencyTransfer.Amount)]);
                    tx.transferObjects([targetCoin], tx.pure.address(currencyTransfer.TargetWalletAddress));
                }
            } else if (targetCoins.length > 1) {
                const totalBalance = targetCoins.reduce((sum, coin) => sum + coin.balance, 0);
                if (totalBalance === currencyTransfer.Amount) {
                    const coinsToTransfer = targetCoins.map(coin => tx.object(coin.coinObjectId));
                    tx.transferObjects(coinsToTransfer, tx.pure.address(currencyTransfer.TargetWalletAddress));
                } else {
                    targetCoins.sort((a, b) => a.balance - b.balance);
                    const balanceExceptLargest = targetCoins.slice(0, -1).reduce((sum, coin) => sum + coin.balance, 0);
                    const [targetCoinFromLargest] = tx.splitCoins(tx.object(targetCoins[targetCoins.length - 1].coinObjectId), [tx.pure.u64(currencyTransfer.Amount - balanceExceptLargest)]);
                    tx.transferObjects([targetCoinFromLargest], tx.pure.address(currencyTransfer.TargetWalletAddress));
                    const remainingCoinsToTransfer = targetCoins.slice(0, -1).map(coin => tx.object(coin.coinObjectId));
                    tx.transferObjects(remainingCoinsToTransfer, tx.pure.address(currencyTransfer.TargetWalletAddress));
                }
            }

            let payment: SuiObjectRef[] = [];
            const coins = await suiClient.getCoins({ owner: developerWallet, limit: 1 });
            if (coins.data.length > 0) {
                payment = coins.data.map((coin) => ({
                    objectId: coin.coinObjectId,
                    version: coin.version,
                    digest: coin.digest,
                }));
            } else {
                throw new Error(`Can't find gas coins from sponsor ${developerWallet}.`);
            }

            const kindBytes = await tx.build({ onlyTransactionKind: true, client: suiClient });
            const sponsoredTxb = Transaction.fromKind(kindBytes);
            sponsoredTxb.setSender(playerKeypair.toSuiAddress());
            sponsoredTxb.setGasOwner(developerWallet);
            sponsoredTxb.setGasPayment(payment);
            const sponsoredBytes = await sponsoredTxb.build({ client: suiClient });
            const developerSignature = await developerKeypair!.signTransaction(sponsoredBytes);
            const playerSignature = await playerKeypair!.signTransaction(sponsoredBytes);

            const response = await suiClient.executeTransactionBlock({
                transactionBlock: sponsoredBytes,
                signature: [developerSignature.signature, playerSignature.signature],
                options: {
                    showEffects: true,
                    showEvents: true,
                    showObjectChanges: true,
                },
            });

            if (response.effects != null) {
                result.status = response.effects.status.status;
                result.gasUsed = calculateTotalCost(response.effects.gasUsed);
                result.digest = response.effects.transactionDigest;
                result.objectIds = response.effects.created?.map(o => o.reference.objectId);
                result.error = response.effects.status.error;
            }

        } else {
            throw new Error(`Can't deserialize CurrencyTransfer object.`);
        }

    } catch (ex) {
        error = ex;
    }
    callback(error, JSON.stringify(result));
}

module.exports = {
    createWallet,
    importWallet,
    verifySignature,
    mintRegularCoin,
    getBalance,
    mintNfts,
    getOwnedObjects,
    burnRegularCoin,
    mintGameCoin,
    burnGameCoin,
    getGameCoinBalance,
    setNftContractOwner,
    updateNft,
    objectExists,
    burnNft,
    withdrawCurrency
};