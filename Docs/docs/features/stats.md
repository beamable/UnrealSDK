<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Stats

## Overview

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

## Getting started

In order to create first Stats commit with Blueprints we will use `BeamStatsSubsystem` created for that purpose.

!!! note "C++ version"
    In order to achieve same effect as in this blueprint example in C++ it is possible to follow guide below. In order to achieve that replace calls to `BeamStatSubsystem` commands with the same ones with `CPP_` prefix if that version exists and use same ones if version without it does not exists. That means using `CPP_CommitStatsOperation` instead of `CommitStatsOperation`, but `TryCreateUpdateCommand` in both Blueprint and C++ version.

!!! note "Subsystem assumptions"
    Make sure that user account is created, logged in and blueprint is not performed before `OnReady` call from `UBeamRuntimeSubsystem`.

First there should be created a update command with `Try Create Update Command` with new stats values. Then we need to commit that stats update operation using `Commit Stats Operation` in order to send them to Beamable backend. That is it!

![unreal-beamable-stats-create](./images/stats-create-stats.png)

Then if we open Beamable portal, go to `Engage->Players`, find used player and go to Stats and search for `NewStatKey` there should be visible that it exists with correct value:

![unreal-beamable-stats-portal](./images/stats-portal.png)
