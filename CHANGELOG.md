# Changelog

## [1.2.0] - Unreleased

## [1.1.0] - Unreleased

### Changed
- Samples are now selected by running `dotnet beam unreal select-sample BEAMPROJ_Name` instead of `BeamProjOverride.txt`

### Fixed
- Fixed issue that could cause an internal engine check to fail during editor startup in very rare cases (PostObjectLoad issue).


## [1.0.0] - Released 

### Added

- `UBeamCli` updated API bindings and performance improvements (reflected in Content Window responsiveness).
- New and updated SDK install/update flow (Quick Start Docs updated to match this).
  - Handles copying the plugin files as needed.
  - Handles adding `Beam` utility code to your project's `Target.cs` file.
  - Handles adding Beamable plugins to your `uproject` file.
- `UBeamInventorySubsystem` now exposes `TryGetAllCurrenciesByGamerTag` and other similar functions to query the local state of inventories other than of one of the UserSlots.
- `UBeamAnnouncementSubsystem` added to query and receive Beamable announcement notifications. 
- Added `BEAMPROJ_LiveOpsDemo` to showcase usage of Beamable's LiveOps Platform (Stats, Inventory, Announcements).
- Added `BEAMPROJ_DiscordDemo` to showcase usage of Beamable's Microservice to integrate with Discord for creating community management tools.
- Added `BEAMPROJ_SteamDemo` to showcase usage of Beamable's Microservice and Identify federation to implement Steam Login.

### Changed
- Updated Beamable CLI version to 2.1.0.
- Visual feedback improvements to the HathoraDemo sample project:
  - Feedback for waiting for match start.
  - Feedback for victory/defeat screen.
  - Feedback for hit-received and projectile VFX.
  
### Fixed
- Fixed documentation links pointed at incorrect .NET version (the Beamable CLI requires .NET 8 to be installed).
- Fixed issue with Microservice integration that would cause the engine to incorrectly identify the service as running or not.
- Fixed issue that would sometimes cause a login credential to be rejected by the backend.

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
