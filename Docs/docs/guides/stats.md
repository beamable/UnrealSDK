<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Unreal SDK - Stats

The Beamable SDK Stats feature allows player to track a variety of built-in and custom player stat variables with configurable visibility levels. Two main use cases are:
- Data Store- a simple place to read/write info about player
- Targeting- Stats can be the vector for player segmentation (Ex. A/B testing, targeted offer, focused message campaign, announcement for subset of player-base)

## Types of stats

There are two important specifiers of each stat.

First one is `visibility`, in Unreal represented by enum `EBeamStatsVisibility`, it describes who can see stat:
- `private`- this one is visible to owning Player and Backend. 
- `public`- Public client stats can be retrieved by anyone who knows ID of the user.


Second one is stat `domain`, in Unreal represented by enum `EBeamStatsDomain`, it describes if stat can be retrieved from game itself or does it require using microservices:
- `client`- this one can be accessed from both the game and microservices.
- `game`- this one cannot be accessed from Unreal directly, it can still be accessed and/or updated from microservice.
