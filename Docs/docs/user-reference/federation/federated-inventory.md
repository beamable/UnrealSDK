# Federated Inventory
Federated Inventory allows you to integrate with other 3rd Party inventory systems such as Steam's Inventory or Web3 wallets. Because of this intended usage, all `FederatedInventory` implementations are also [Federated Login](federated-login.md) implementations.

Here's how this works at a high-level:

- Take a `UBeamItemContent` or `UBeamCurrencyContent` whose `federation` field has a valid [Federation Id](federation.md#federation-id).
- Whenever a the inventory is fetched, if that content object is within its scope, the Beamable backend will invoke the `GetInventoryState` call with the user's 3rd Party  `UserId` as its parameter.
- Whenever an inventory update is committed, any currencies or items involved that are federated are bundled up and passed into `StartInventoryTransaction`.

Here's some more detail:

```csharp
// The "id" parameter is the UserId that the IFederatedLogin.Authenticate generates
// All this function really does is add instances of items and currencies to the 
// response and forward it along.
Promise<FederatedInventoryProxyState> GetInventoryState(string id);  

// The "id" parameter is the UserId that the IFederatedLogin.Authenticate generates
//
// The "transaction" parameter is an optional string provided by the caller.
// You are expected to provide an idempotency guarantee that every given 
// transaction string value is only processed once.
// In most cases, this is just a passalong to Web3 wallet or wherever you're 
// keeping the inventory information. If that's not supported by your 3rd Party, 
// you can leverage StorageObjects to provide this guarantee.
Promise<FederatedInventoryProxyState> StartInventoryTransaction(  
    string id,  
    string transaction,  
    Dictionary<string, long> currencies,  
    List<FederatedItemCreateRequest> newItems,  
    List<FederatedItemDeleteRequest> deleteItems,  
    List<FederatedItemUpdateRequest> updateItems);
```

!!! note "Support in SDK"
	Support for this federation in the SDK's `UBeamInventorySubsystem` is coming soon.