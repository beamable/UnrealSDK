<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Inventory

## Overview
The Beamable **Inventory** Feature allows game makers to associate fungible and non-fungible content to individual players within the game.

- **Fungible** means that each instance of that content is not unique. The simplest example is a Soft/Hard Currency in a live-services game. Each coin you grant the player is not unique. In Beamable, this type of content is represented as a `UBeamCurrencyContent`.
- **Non-Fungible** means that each instance of that content is unique. The simplest example is an item in an MMORPG. Each instance of that item is unique and can have its own properties. In Beamable, this type of content is represented as a `UBeamItemContent`.

Beamable's Inventory system is built on Beamable's Content Feature. This means that content can be created, edited and published via the Content Window, then granted to players through various workflows:

- Add/Remove currencies or items to the active player during the course of gameplay. 
	- Ex. the player earns a new "Sword" inventory item based on in-game progress.
- Add inventory items to the active player via the Beamable Store. 
	- Ex. the player pays some currency to buy a new "Sword" inventory item.

## Data Concepts
Inventory manages two types of data- items and virtual currencies. One thing that both have in common is that during creation of each of them it is up to game maker to decide how they can be added to player inventory by specifying `clientPermission` field:

- When toggled, the content becomes **Client-Authoritative**. The SDK allows game-clients to add/remove that item or currency to the player inventory directly. If your game does not include networked multiplayer and can tolerate cheating, allowing the client to read and write their own currencies is the simplest option.
- If not toggled, the content becomes **Server-Authoritative**. Trying to add/remove that item or currency to the player inventory from a game-client directly results in an error. The item/currencies are still readable in the game-client. To add/remove items and currencies that are **Server-Authoritative**, do so via a Microservice and a `ClientCallable`. 

!!! note "Edit player Inventory via Portal"
    Regardlesss of the value of the `clientPermission` field it is possible to view and modify players inventory through the Portal. More info [here](https://docs.beamable.com/docs/portal-inventory).

### Virtual Currencies
Currencies are used to buy items with our [Store system](../features/stores.md) (e.g., Gold). It can also be used to symbolize the player's progress through the game, such as experience points (XP).

In Unreal SDK Currency is represented by `UBeamCurrencyContent` type. Each currency can specify a `startingAmount` that is used to pre-seed player accounts with that amount of currency.

You can [subclass this content type](../features/content.md#subclassing-content) if you want to add more information to currency that is specific to your like, such as UI related `ObjectPaths` and other references to assets that might be relevant to your game. 
### Items
The Items feature allows for the creation and management of various in-game objects, such as equipment, consumables, and resources.

In the Unreal SDK, Items are represented by the `UBeamItemContent` type. You can [subclass this content type](../features/content.md#subclassing-content) to add game-specific information to item content which is then accessible via the `UBeamContentSubsystem` and in Microservices.
#### Item State
Each item instance inside a player's inventory is represented by `FBeamItemState`. These instances have the following properties:

- **ContentId**: The Id of `UBeamItemContent` that represents the type of this item instance.
- **Properties**: A key-value store of properties of this specific item instance. You control which properties exist here.
- **InstanceId**: A unique id of item instance inside this player's inventory.

Rest of the fields:

- **CreatedAt**: when item instance was created.
- **UpdatedAt**: last edit date.
- **FederatedId**: See [Inventory Federation](../federations/federated-inventory.md) for more information about this field.

## Getting Started
To use the inventory system, you will need to first:

1. Go to the Content Window.
2. Select `item` as a type.
3. Create an item content definition.
4. Select `currency` as a type.
5. Create an currency content definition.
6. For this guide, make sure their `Client Permission` property is set to `true`.
7. Publish this content to the realm.

Now that you have items and currencies published, follow the steps below to create a BP function that adds some currencies and grants an item to the player:

1. Open your Level Blueprint (or some other BP).
2. Get the `BeamInventorySubsystem`
3. Call `BeginInventoryUpdate`. This begins building a set of changes we will submit to the Beamable backend later.
4. Call `PrepareAddCurrency` and `PrepareAddItem` selecting the currency and item types you created.
5. Call the `Commit Inventory Update` operation.

Now, call this function while a user is signed in to grant the currency/item to the player.

???+ warning "Assumptions"
    Make sure that user is logged in when you call this function. See [Runtime Concepts](runtime-concepts.md)

![unreal-inventory-operations](images/inventory-operations.png#center)

After running the above function at least once, you should be able to see the results of these calls in the Beamable portal. To do so:

- Set aside the `Gamertag/UserId` from the Unreal Engine logs.
- Click `Open Portal` in Beamable window.
- Go to `Engage->Players` and search for the player via `Gamertag/UserId`.
- Go to `Inventory` and see that the appropriate currency and items are inside the user's inventory. 

![unreal-beamable-inventory-portal](images/inventory-portal.png#center)
## Performance Guidelines

### Batching updates
In the getting started example, we make a new `FBeamInventoryUpdateCommand` and commit it right away. It is desirable, for both performance and latency reasons, to batch as many inventory changes as possible as long as it makes sense for your game's design. So, if you're game's feature allows for a "edit multiple, commit later" pattern of UX, leveraging this API is the most efficient way to go about it.
### Item Instance Properties
As with most key-value pairs for arbitrary data, try to follow the guidelines below:

- For Keys:
	- 8-20 characters are ideal (purely for human ergonomics).
	- Keeping them under a few hundred characters is best for performance.
	- Use enforce-able and recognizable patterns for your keys.
		- Bad: `ItemEnhancementName` and `ENH_Count`
		- Good: `ENHANCE_Name` and `ENHANCE_Count` OR `ItemEnhancementName` and `ItemEnhancementCount`.
	- Keeping your project organized is key.
- For Values:
	- Values should be no more than a few hundred characters long.

If you need larger complex data structures, we recommend you use [Storage Objects](microservices.md#storage-objects) instead of this key-value store. This is especially true if you do NOT need to use the data in these properties at the same time as you need the list of items; for example, a list view which then opens some sort of details view. This reduces pressure on the inventory service and can help reduce latency of inventory query requests.

