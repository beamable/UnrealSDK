import {SuiParsedData} from "@mysten/sui/client";
import {DisplayFieldsResponse,MoveValue,MoveStruct} from "@mysten/sui/src/client/types/generated";

export class CreateWalletResponse {
    Address: string | undefined;
    PrivateKey: string | undefined;
    PublicKey: string | undefined;
}

export class SuiTransactionResult {
    status: string | undefined;
    digest: string | undefined;
    gasUsed: string | undefined;
    objectIds: string[] | undefined;
    error: string | undefined;
}

export interface RegularCoinMintMessage {
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletAddress: string;
    AdminCap: string;
    TreasuryCap: string;
    Amount: number;
}

export interface RegularCoinBurnMessage {
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletAddress: string;
    TreasuryCap: string;
    Amount: number;
    PlayerWalletKey: string;
}

export interface GameCoinMintMessage {
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletAddress: string;
    AdminCap: string;
    TokenPolicy: string;
    TokenPolicyCap: string;
    Store: string;
    Amount: number;
}

export interface GameCoinBurnMessage {
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletAddress: string;
    TokenPolicy: string;
    TokenPolicyCap: string;
    Store: string;
    Amount: number;
    PlayerWalletKey: string;
}

export interface CoinBalanceRequest {
    PackageId: string;
    ModuleName: string;
}

export interface RegularCoinBalanceRequest {
    PackageId: string;
    ModuleName: string;
}

export class CoinBalanceResponse {
    CoinType: string;
    Total: number;
    public constructor(coinType: string, total: number) {
        this.CoinType = coinType;
        this.Total = total;
    }
}

export interface NftMintMessage {
    ContentId: string;
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletAddress: string;
    AdminCap: string;
    NftContentItem: NftContentItem;
}

export interface SetNftOwnerMessage {
    PackageId: string;
    Module: string;
    Function: string;
    AdminCap: string;
}

export interface NftContentItem {
    Name: string;
    Url: string;
    Description: string;
    ContentId: string;
    Attributes: Attribute[]
}

export interface Attribute {
    Name: string;
    Value: string;
}

export interface NftUpdateMessage {
    ProxyId: string;
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletKey: string;
    PlayerWalletAddress: string;
    OwnerObjectId: string;
    Attributes: Attribute[]
}

export interface NftDeleteMessage {
    ProxyId: string;
    PackageId: string;
    Module: string;
    Function: string;
    PlayerWalletKey: string;
    PlayerWalletAddress: string;
    OwnerObjectId: string;
}

export class CoinToken {
    Id: string;
    Balance: number;
    public constructor(Id: string, Balance: number) {
        this.Id = Id;
        this.Balance = Balance;
    }
}

export interface PaginatedResult<T> {
    data: T[];
    hasNextPage: boolean;
    nextCursor?: string | null;
}
export interface InputParams {
    cursor?: string | null | undefined;
}

export interface CurrencyTransfer {
    PackageId: string;
    Module: string;
    PlayerWalletAddress: string;
    PlayerWalletKey: string;
    TargetWalletAddress: string;
    Amount: number;
}

export class CoinModel {
    coinObjectId: string;
    balance: number;
    public constructor(coinObjectId: string, balance: number) {
        this.coinObjectId = coinObjectId;
        this.balance = balance;
    }
}

export class SuiObject {
    ObjectId: string;
    Digest: string;
    Version: string;
    Content?: SuiParsedData | null;
    Display?: DisplayFieldsResponse | null;
    public constructor(objectId: string, digest: string, version: string, content?: SuiParsedData | null, display?: DisplayFieldsResponse | null) {
        this.ObjectId = objectId;
        this.Digest = digest;
        this.Version = version;
        this.Content = content;
        this.Display = display;
    }

    toView(): SuiViewObject {
        const viewObject = new SuiViewObject(this.ObjectId);

        switch (this.Content?.dataType) {
            case 'moveObject':
                const typeParts = this.Content?.type.split("::");
                if (typeParts.length >= 3) {
                    viewObject.Type = typeParts[1];
                } else {
                    viewObject.Type = this.Content?.type;
                }

                const contentFields = this.Content?.fields;
                if (contentFields != null) {
                    viewObject.Name = (contentFields as { [key: string]: MoveValue })["name"] as string;
                    viewObject.Description = (contentFields as { [key: string]: MoveValue })["description"] as string;
                    viewObject.Image = (contentFields as { [key: string]: MoveValue })["url"] as string;
                    viewObject.ContentId = (contentFields as { [key: string]: MoveValue })["contentId"] as string;

                    const attributes = (contentFields as { [key: string]: MoveStruct })["attributes"];
                    if (attributes != undefined) {
                        if (Array.isArray(attributes)) {
                            attributes.forEach(a => {
                                const field = a as { fields: { [key: string]: MoveValue }; type: string; };
                                if (field != undefined) {
                                    const name = field.fields["name"] as string;
                                    const value = field.fields["value"] as string;
                                    viewObject.addAttribute(name, value);
                                }
                            });
                        }
                    }
                }
        }
        return viewObject;
    }
}

export class SuiViewObject {
    ObjectId: string;
    Type: string | undefined;
    Name: string | undefined;
    Description: string | undefined;
    Image: string | undefined;
    ContentId: string | undefined;
    Attributes: Attribute[] = [];
    public constructor(objectId: string) {
        this.ObjectId = objectId;
    }

    addAttribute(name: string, value: string): void {
        const newAttribute: Attribute = { Name: name, Value: value };
        this.Attributes.push(newAttribute);
    }
}