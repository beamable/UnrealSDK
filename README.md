# Unreal SDK 1.0 - PREVIEW
The Beamable SDK provides functionality to integrate your game with the Beamable features. These range from Content (Remote Config) to Events to Inventory to Microservices (Beamable's unique approach to a Cloud Code Solution).

Here's a bit of our philosophy when desing the SDK so you know a bit what to expect:

- The SDK's source code is entirely available and modifiable inside your project by you.
    - In case you modify the SDK's source code, we cannot guarantee that its features will work.
    - We trust you to know when doing so might be worth it for you (VCS are your friend here).
- The SDK keeps itself as simple as possible, providing extension points and clear documented.
    - We believe that tools are either helpful **or** useless. If you find yourself working around parts of the SDK instead of using them even with MicroServices/Storages, reach out to us.
- The SDK is careful about assumptions it makes.
    - Whenever we ***have to*** make an assumption, we try to be explicit about what it means.
    - MicroServices/Storages are great ways to "just write what you want instead" when using our default services is not a good fit.

### Requirements for Beamable
Beamable currently supports **Unreal 5.3**. It'll release the official SDK 1.0 version with 5.4 support only. 

Beamable also has a dependency on  [.NET](https://dotnet.microsoft.com/en-us/download/dotnet/6.0). This is needed for:

- Installing the Beamable CLI (and therefore enabling the various Beamable workflows).
- Using C# Microservices through the CLI.

Beamable has a hard-dependency on [Docker](https://www.docker.com/products/docker-desktop/). This is needed for two things:

- Building and Deploying Beamable Microservices to your realms (dev/staging/prod environments).
- Running Beamable Microservices without opening the service's project (for non-engineers that want to run microservices locally).

If you don't have these installed, take this opportunity to install it while you investigate these docs further.
### Beamable CLI
Most of the Beamable workflows are enabled through the Beamable CLI; our editor integrations making use of it to create Engine-specific workflows.

The SDK is tightly integrated with the CLI in some ways more than others. For example:

- [Content](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Content), being designer-focused, has its own UE-familiar content editing UI so you can edit the various JSON blobs that defines your game's content.
- [Microservices](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Microservices), however, being more engineer focused, leans more directly on the CLI.

In other words: **The Beamable CLI is invisible to the user where it needs to be and explicit to users that need to work with them.**
## Where to start?

Regardless of who you are, we recommend run through the [Introduction to the SDK](https://beamable.github.io/UnrealSDK/Use%20Guide/Unreal%20SDK%20-%20Intro) and [Runtime Concepts](https://beamable.github.io/UnrealSDK/Use%20Guide/Unreal%20SDK%20-%20Runtime%20Concepts) documents. After this, it depends on what you're game is or what you are looking to do.

- If you are a game maker looking to implement simple and common back-end features, take a look at the docs for [Inventory](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Inventory), for currency and items, and [Stats](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Stats), for player-scoped key-value stores.
- If you are a game maker looking to implement highly specific features, browse the documentation for [Content](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Content) and [Microservices](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Microservices) to think about how to structure your game's data and custom data with Beamable.
- If you are looking to integrate Beamable into your game through Unreal's `IOnlineSubsystem`, take a look at the [Online Subsystem Beamable](https://beamable.github.io/UnrealSDK/Feature%20Guides/Unreal%20SDK%20-%20Online%20Subsystem).

If you have any questions, feel free to contact us through one of our Customer Success channels.


## For Beamable Developers
After cloning this repo, remember to run `init_repo.sh` and `docs_build.sh serve` such that the repo is configured correctly and you have a locally running server that serves the current branch's version of the docs. Please always run them from the root of the repo.