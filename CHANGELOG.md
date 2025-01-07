# Changelog

## [1.2.0] - Unreleased

## [1.1.0] - Unreleased

### Added
- `OnlineSubsystemBeamable` plugin now supports Frictionless Authentication and Identity Attaching 

### Changed
- Samples are now selected by running `dotnet beam unreal select-sample BEAMPROJ_Name` instead of `BeamProjOverride.txt`

### Fixed
- Fixed issue that could cause an internal engine check to fail during editor startup in very rare cases (PostObjectLoad issue).
- Fixed issue that could cause a crash when re-logging into any particular UserSlot (a cleaned up operation could be waited on; no longer possible now)
- Fixed an issue that would cause a subsystem initialized with `UBeamRuntime::ManuallyInitializeSubsystem` to not load its user's data correctly if the user signed in **after** the system was initialized. 

## [1.0.0] - 2024-12-11

### Added
- New and updated SDK install/update flow (Quick Start Docs updated to match this).
  - Handles copying the plugin files as needed.
  - Handles adding `Beam` utility code to your project's `Target.cs` file.
  - Handles adding Beamable plugins to your `uproject` file.
  
- Entirely new Microservice Window
  - Added collaborative debugging Workflow
  - Added ability to seamlessly debug In-Band Federations locally.
  - Added ability to debug Out-of-Band Federations locally via a content filter.
  - Added ability to see Microservice logs from inside the Unreal Editor.  

- Significant improvements and fixes around the Content Window and workflow.
  - `UBeamCli` updated API bindings and performance improvements (reflected in Content Window responsiveness).
  - Content objects are now displayed sorted by status (Added, Modified, Non-Modified, Removed).

- New Runtime Subsystems:
  - `UBeamAnnouncementSubsystem` added to query and receive Beamable announcement notifications.
  - `UBeamStoreSubsystem` added to enable purchasing items (for now, no IAP-support).

- New Samples:
  - Added `BEAMPROJ_LiveOpsDemo` to showcase usage of Beamable's LiveOps Platform (Stats, Inventory, Announcements).
  - Added `BEAMPROJ_DiscordDemo` to showcase usage of Beamable's Microservice to integrate with Discord for creating community management tools.
  - Added `BEAMPROJ_SteamDemo` to showcase usage of Beamable's Microservice and Identify federation to implement Steam Login.

- `UBeamInventorySubsystem` now exposes `TryGetAllCurrenciesByGamerTag` and other similar functions to query the local state of inventories other than of one of the UserSlots.

### Changed
- Updated Beamable CLI version to 3.0.1.
- Visual feedback improvements to the HathoraDemo sample project:
  - Feedback for waiting for match start.
  - Feedback for victory/defeat screen.
  - Feedback for hit-received and projectile VFX.
  
### Fixed
- Fixed documentation links pointed at incorrect .NET version (the Beamable CLI requires .NET 8 to be installed).
- Fixed issue with Microservice integration that would cause the engine to incorrectly identify the service as running or not.
- Fixed issue that would sometimes cause a login credential to be rejected by the backend.
- Fixed issue with Inventory that could cause the local state of a player's inventory to become invalid after an inventory refresh

## [1.0.0-PREVIEW] - 2024-05-28

### Added

- HathoraDemo sample demonstrating GameServer federation made with Beamable.
- New in-editor Content editing flow.
- New and up-to-date Documentation.

### Changed

- Visual feedback improvements to the HathoraDemo sample project:
  - Feedback for waiting for match start.
  - Feedback for victory/defeat screen.
  - Feedback for hit-received and projectile VFX.
