# Announcements

## Overview

The Beamable SDK Announcement feature allows players view and receive game-wide announcements configured by the Game-Makers. A few of the main use cases are:

- **Communicating to Players** information about the game's live operations that are relevant.
- **Targeting a Subset of Players** with gifts or compensations due to things that happen over the course of your live-game services.

Announcements can be created via the [portal](https://docs.beamable.com/docs/portal-announcements).


Once created, announcements stay live during the specified date-times. While live, each player has a "view" of that announcement.
This view defines whether the player has seen that announcement or claimed any gifts contained in them.

These are exposed in the `UAnnouncementView` object which can be accessed by the `UBeamAnnouncementsSubsystem::GetAnnouncements` method.

### Claiming an Announcement's Gifts and Marking as Read

It is common to attach gifts to announcements so that players can claim them. To do so, you can use the `ClaimAnnouncementsOperation` passing in the list of announcement ids (`UAnnouncementView::Id`).

The image below shows how this can be done in blueprint.

![announcements-claiming.png](../../media/imgs/announcements-claiming.png)

Marking announcements as read can be achieved in a similar way but with the `MarkAnnouncementsReadOperation`. The image below shows how you would mark an announcement as read when a user clicks one and a popup opens displaying its details.

![announcements-mark-read.png](../../media/imgs/announcements-mark-read.png)


## Usage Guidelines
Aside from the `Id` most other `FString` fields in the announcement can be used to store whatever data you need. Common practices include:

- Passing in `TSoftObjectPath` strings to reference in-game assets.
- Passing in some custom string format such that your UI interprets it and change its behavior accordingly.
- Use `ClientDataList` to pass in key-value pairs of arbitrary string data based on your game's context.
- So on...

Our system itself and the SDK doesn't really care about the format or content of the `Title`, `Summary` or `Body` fields so feel free to use them as needed (they are merely semantic suggestions of what an announcement contains).  