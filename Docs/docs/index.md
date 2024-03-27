# Unreal SDK - Intro & Mindset

We strive to give developers visibility and autonomy over their project dependencies. As such:

- The SDK's source code is entirely available and modifiable inside your project by you.
- In case you modify the SDK's source code, we cannot guarantee that its features will work; but we trust you to know when and how it is worth it for you to take on that responsibility.
- The SDK keeps itself as simple as possible, provides reasonable extension points and is clearly documented.
- We make public our internal documentation about how internal SDK specifics function (to the extent that they can be).
### Requirements for Beamable
Beamable has a hard-dependency on [Docker](https://docs.beamable.com/docs/microservices-code#beamable--docker). This is needed for two things:

- Running Beamable Microservices without opening the service's project (for non-engineers that want to run microservices locally).
- Building and Deploying Beamable Microservices to your realms (dev/staging/prod environments).

If you don't have it installed, take this opportunity to install it while you investigate these docs further.
### Beamable CLI
The Beamable CLI is the cornerstone of our various SDKs. Most of Beamable workflows are implemented in it; our editor integrations making use of it to create Engine-specific workflows.

In Unreal, the SDK is tightly integrated with the CLI in some ways more than others. [Content](../Use Guide/Unreal SDK - Content), being designer-focused, has its own UE-familiar content editing UI so you can edit the various JSON blobs that defines your game's content. [Microservices](../Use Guide/Unreal SDK - Microservices), however, being more engineer focused, leans more directly on the CLI.

In other words: **The Beamable CLI is transparent to the user where it needs to be and explicit to users that need to work with them.**
## Where to start?

Regardless of who you are, we recommend run through the [Introduction to the SDK](../Use Guide/Unreal SDK - Intro) and [Runtime Concepts](../Use Guide/Unreal SDK - Runtime Concepts) documents. After this, it depends on what you're game is or what you are looking to do.

- If you are a game maker looking to implement simple and common back-end features, take a look at the docs for [Inventory](../Use Guide/Unreal SDK - Inventory), for currency and items, and [Stats](../Use Guide/Unreal SDK - Stats), for player-scoped key-value stores.
- If you are a game maker looking to implement highly specific features, browse the documentation for [Content](../Use Guide/Unreal SDK - Content) and [Microservices](../Use Guide/Unreal SDK - Microservices) to think about how to structure your game's data and custom data with Beamable.
- If you are looking to integrate beamable into your game through Unreal's `IOnlineSubsystem`, take a look at the [Online Subsystem Beamable](../Online Subsystem Guide).
- If you are a Beamable engineer or looking to develop a plugin that works alongside Beamable, we recommend you take a look at the [SDK Development Guide](../SDK Development Guide).

If you have any questions, feel free to contact us through one of our Customer Success channels.
