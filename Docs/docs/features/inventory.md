<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Inventory

## Overview

The Beamable **Inventory** Feature allows game makers to manage owned items and currencies per player within the game.

Beamable's Inventory system is built on the Content feature. This means that content can be created and published via the Content Manager, then granted to players through various workflows:

- Add/Remove inventory items to the active player during the course of gameplay. Ex. the player earns a new "Sword" inventory item based on in-game progress
- Add inventory items to the active player via the Beamable Store. Ex. the player pays real-world currency to buy a new "Sword" inventory item

## Data Concepts

Inventory manages two types of data- items and virtual currencies. One thing that both have in common is that during creation of each of them it is up to game maker to decide how they can be added to player inventory by specifying `clientPermission` field:

- **Client-Authoritative**- If your game does not include networked multiplayer and can tolerate cheating, allowing the client to read and write their own currencies is the simplest option.
- **Server-Authoritative**- A much more secure way to handle item/currency modifications is via a Microservice. In this scenario, the client is not able to modify their currencies directly, it is handled on the server. It can still read it from Unreal.

!!! note "Edit player Inventory via Portal"
    Regardlesss of the value of the `clientPermission` field it is possible to view and modify players inventory through the Portal. More info [here](https://docs.beamable.com/docs/portal-inventory).

### Virtual Currencies

This feature is flexible enough to meet the currency needs of any game's design. Currencies are used to buy items (e.g., Gold) and to symbolize the player's progress through the game, such as experience points (XP).

The Virtual Currency system in Beamable is built on top of the Content system. Currencies are available out of the box in the Beamable SDK as a content type.

In Unreal SDK Currency is represented by `FBeamCurrencyContent` type. Besides decribed earlier `clientPermission` each Currency type contains `startingAmount` field specifying how many currency is player starting with.

### Items

The Items feature allows for the creation and management of various in-game objects, such as equipment, consumables, and resources. I

In Beamable, Items are built on the Content system and can be customized to fit the specific needs of your game. Items can be a subclass of `FBeamItemContent` and contain additional fields.

In the Unreal SDK, Items are represented by the `FBeamItemContent` type. 

#### Item State

Item State- `FBeamItemState` in Unreal SDK- is representation of the items that player has. Most important part of each one are:

- **ContentId**- id of `Item` content.
- **Properties**- map of properties of this specific item instance. 
- **InstanceId**- id of item instance.

Rest of the fields:

- **CreatedAt**- when item instance was created.
- **UpdatedAt**- last edit date.
- **FederatedId**- only if item is federated.


## Getting Started

First, make sure that you have created and published content with at least one currency and item, both of them should have `Client permission` with `true` value.

In order to create first Inventory commit with Blueprints we will use `BeamInventorySubsystem` created for that purpose.

???+ warning "Subsystem assumptions"
    Make sure that user is logged in. See [Runtime Concepts](../guides/runtime-concepts.md)

![unreal-inventory-operations](./images/inventory-operations.png)

Then if we grab the User Id from the Unreal Engine logs, click `Open Portal` in Beamable settings, go to `Engage->Players`, find used player and go to `Inventory` and search if both currency amount changed and new item is added to the inventory:

![unreal-beamable-inventory-portal](./images/inventory-portal.png)

## Federation

Items and Currencies can be attached to federated service.

## Performance Guidelines

### Batching updates

In this example there is created a new `FBeamInventoryUpdateCommand` and commited right away. In order to achieve better performance and reduce amount of calls to backend it is encouraged to create `FBeamInventoryUpdateCommand`, attach as many changes as needed and commit then instead of commiting each change separately.