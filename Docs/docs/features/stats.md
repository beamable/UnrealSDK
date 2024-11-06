<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Stats

## Overview

The Beamable SDK Stats feature allows player to track a variety of built-in and custom player stat variables with configurable visibility levels. Two main use cases are:

- **Data Store**- can hold key/value pairs associated with a particular user.
- **Targeting**-  These key/value pairs can be used by other Beamable systems for various things (Announcement Campaings, Matchmaking and others).

## Types of stats

There are two important specifiers of each stat.

First one is `visibility`, in Unreal represented by enum `EBeamStatsVisibility`, it describes who can see stat:

- `private`- Visible only to owning User and Backend.
- `public`- Visible to any User.

Second one is stat `domain`, in Unreal represented by enum `EBeamStatsDomain`, it describes if stat can be retrieved from game itself or does it require using microservices:

- `client`- Can be accessed from both the **Unreal** and **Microservices**.
- `game`- Cannot be accessed from **Unreal** directly, it can still be accessed via **Microservice** using `ClientCallable` calls.

## Getting started

In order to create first Stats commit with Blueprints we will use `BeamStatsSubsystem` created for that purpose.

???+ warning "Subsystem assumptions"
    Make sure that user is logged in. See [Runtime Concepts](../guides/runtime-concepts.md)

First there should be created a update command with `Try Create Update Command` with new stats values. Then we need to commit that stats update operation using `Commit Stats Operation` in order to send them to Beamable backend. That is it!

![unreal-beamable-stats-create](./images/stats-create-stats.png)

Then if we grab the User Id from the Unreal Engine logs, click `Open Portal` in Beamable settings, go to `Engage->Players`, find used player and go to `Stats` and search for `NewStatKey` there should be visible that it exists with correct value:

![unreal-beamable-stats-portal](./images/stats-portal.png)


## Performance Guidelines

### Batching updates

In this example there is created a new `UpdateCommand` and commited right away. In order to achieve better performance and reduce amount of calls to backend it is encouraged to create `UpdateCommand`, attach as many changes as needed and commit then instead of commiting each change separately.

### Stats keys naming

Good rule of thumb for keys is "shorter is better" and keys of 8-20 characters are ideal (purely for human ergonomics) and keeping them under a few hundred characters is best for performance.

### Stats values length

Values should be no more than a few hundred characters long. This is a performance issue: the MongoDB collection has an index on keys, so the bigger the keys are the bigger that index grows, leading to performance hits in both writing and reading. 
