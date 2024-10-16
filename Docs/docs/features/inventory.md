<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Inventory

## Overview

The Beamable **Inventory** Feature allows game makers to manage owned items per player within the game.

Beamable's Inventory system is built on the Content feature. This means that content can be created and published via the Content Manager, then granted to players through various workflows:

- Add/Remove inventory items to the active player during the course of gameplay. Ex. the player earns a new "Sword" inventory item based on in-game progress
- Add inventory items to the active player via the Beamable Store. Ex. the player pays real-world currency to buy a new "Sword" inventory item

## Data Concepts

Inventory manages two types of data- items and virtual currencies. One thing that both have in common is that during creation of each of them it is up to game maker to decide how they can be added to player inventory by specifying `Write self` property:

- **Client-Authoritative**- If your game does not include networked multiplayer and can tolerate cheating, allowing the client to read/write their own currencies is the simplest option.
- **Server-Authoritative**- A much more secure way to handle item/currency modifications is via a Microservice. In this scenario, the client is not able to modify their currencies directly, it is handled on the server.

!!! note "Edit player Inventory via Portal"
    Regardlesss of the value of the `Write self` property it is possible to view and modify players inventory through the Portal. More info [here](https://docs.beamable.com/docs/portal-inventory).