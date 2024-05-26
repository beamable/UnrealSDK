# Unreal SDK - Intro & Mindset

At Beamable, we work to give developers visibility and autonomy over their project dependencies. As such:

- The SDK's source code is entirely available and modifiable inside your project by you.
- In case you modify the SDK's source code, we cannot guarantee that its features will work; but we trust you to know when doing so might be worth it for you.
- The SDK keeps itself as simple as possible, provides reasonable extension points and is clearly documented.
- We make public our internal documentation about how internal SDK specifics function (to the extent that they can be).
### Requirements for Beamable
Beamable has a hard-dependency on [Docker](https://www.docker.com/products/docker-desktop/). This is needed for two things:

- Building and Deploying Beamable Microservices to your realms (dev/staging/prod environments).
- Running Beamable Microservices without opening the service's project (for non-engineers that want to run microservices locally).

Beamable also has a dependency on  [.NET](https://dotnet.microsoft.com/en-us/download/dotnet/6.0). This is needed for:

- Installing the Beamable CLI (and therefore enabling the various Beamable workflows).
- Using C# Microservices.

If you don't have these installed, take this opportunity to install it while you investigate these docs further.
### Beamable CLI
Most of Beamable workflows are enabled through the Beamable CLI; our editor integrations making use of it to create Engine-specific workflows.

The SDK is tightly integrated with the CLI in some ways more than others. For example:

- [Content](../Feature Guides/Unreal SDK - Content), being designer-focused, has its own UE-familiar content editing UI so you can edit the various JSON blobs that defines your game's content. 
- [Microservices](../Feature Guides/Unreal SDK - Microservices), however, being more engineer focused, leans more directly on the CLI.

In other words: **The Beamable CLI is invisible to the user where it needs to be and explicit to users that need to work with them.**
## Where to start?

Regardless of who you are, we recommend run through the [Introduction to the SDK](../Use Guide/Unreal SDK - Intro) and [Runtime Concepts](../Use Guide/Unreal SDK - Runtime Concepts) documents. After this, it depends on what you're game is or what you are looking to do.

- If you are a game maker looking to implement simple and common back-end features, take a look at the docs for [Inventory](../Feature Guides/Unreal SDK - Inventory), for currency and items, and [Stats](../Feature Guides/Unreal SDK - Stats), for player-scoped key-value stores.
- If you are a game maker looking to implement highly specific features, browse the documentation for [Content](../Feature Guides/Unreal SDK - Content) and [Microservices](../Feature Guides/Unreal SDK - Microservices) to think about how to structure your game's data and custom data with Beamable.
- If you are looking to integrate beamable into your game through Unreal's `IOnlineSubsystem`, take a look at the [Online Subsystem Beamable](../Feature Guides/Unreal SDK - Online Subsystem).
- If you are a Beamable engineer or looking to develop a plugin that works alongside Beamable, we recommend you take a look at the [SDK Development Guide](../SDK Development Guide).

If you have any questions, feel free to contact us through one of our Customer Success channels.
