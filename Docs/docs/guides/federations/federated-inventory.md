```csharp
// id here is the UserId that the IFederatedLogin returns
Promise<FederatedInventoryProxyState> GetInventoryState(string id);  

// id here is the UserId that the IFederatedLogin returns
// Only federated content shows up here
// transaction: idempotent-guarantee string (when present, should only apply)
// This is usually just a passalong string to Stripe or wherever you're storing the inventory information. If not supported, StorageObjects can handle providing this guarantee.
Promise<FederatedInventoryProxyState> StartInventoryTransaction(  
    string id,  
    string transaction,  
    Dictionary<string, long> currencies,  
    List<FederatedItemCreateRequest> newItems,  
    List<FederatedItemDeleteRequest> deleteItems,  
    List<FederatedItemUpdateRequest> updateItems);
```