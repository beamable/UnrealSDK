<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

Beamable's Store feature allows the game maker to create a storefront in their application. Users can purchase items with virtual currency. 

!!! note "Unreal Project Requirements"
    Beamable does support buying listings with in game IAPs, but for Unreal SDK there is no support for it yet. It will be added in future releases.

In Unreal Stores are represented by `UBeamStoreContent` class which is subclass of `UBeamContentObject`. It does contain a list of links to `UBeamListingContent` types.
Listing type contain all the information about the offer, requirements for player, costs and benefits.
