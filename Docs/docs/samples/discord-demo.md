# Discord Integration Sample

This demo, showcases how you can use the **Unreal SDK** and **Beamable Microservices** to integrate with Discord for community management tools.

## Introduction

Aside from our `BeamableCore` Plugin, here's what the sample contains:

- **`BEAMPROJ_DiscordDemo` Unreal Plugin.**: Contains the UE implementation for the client.
- **`Microservices/services/DiscordDemo` Microservice**: Microservice containing code that implements **IFederatedLogin** and a `DiscordBot` integration.

To set up this sample you'll need a few things:

- A Beamable Account and a Realm.
- A Discord Developer Account.

To configure the sample, run `dotnet beam unreal select-sample BEAMPROJ_DiscordDemo`.

!!! note "Assumptions"
      Instructions below assume that you already have the Discord server that you want to use for integration. If that is not the case create one first. Make sure that you have the admin access to the Discord server of choice.

## Setting Discord Application
Since this sample requires several resources, we do not host it ourselves. So, in order to access the sample we'll go set up a Discord account and setup the sample Discord bot:

1. Log into your [Discord.dev](https://discord.com/developers/applications) account.
2. Create an App. Set aside its `AppId` in a notepad for future use.
      1. Fill out General Information about your app.
      2. No need for providing any of the URLs at the bottom of the General Information page.
3. Go to App `Settings->OAuth2` and set the Redirects Url: `http://127.0.0.1`. Make sure that changes are saved.
4. Go to App `Settings->Bot`.
      1. Set a Bot username.
      2. Set as true all **Privileged Gateway Intents**, especially the **Server Members Intent**.
      3. Press the `Reset Token` button and set it aside (it will be required later on).
5. Go to App `Settings->Installation`.
      1. In `Install Link` select `Discord Provided Link`, copy and paste it into browser.
      2. In `Default Install Settings` add `bot` to the `Scopes` field and `Administrator` to the `Permissions` field
      3. Install the App into your Discord server of choice.
6. Now open the Discord application.
      1. Open `Settings->Advanced` and enable the `Developer Mode` so that we can copy various Ids by right-clicking things in the UI.
      2. Right click on the server icon and select the option `Copy server ID` and set it aside.
      3. Right click on the server icon and select `Settings->Roles`. 
      4. Create a `enabled-matchmaking` role.
      5. Right click on the role and select the option `Copy Role ID` and set it aside.
      6. Pick any text channel. Right click on the channel select the option `Copy Channel ID` and set it aside.

## Setting up Beamable

Now, you'll need to configure a Beamable realm so you can use it.

1. Go to the Beamable Portal and create a new Beamable realm called `discord-demo`.
2. On the Portal open the Realm Config page of the `discord-demo` realm (`Operate -> Config`).
3. Hit the `Add Config` button.
4. Set the following key-value pairs for the namespace `discord_integration`:
      1. `matchmaking_roles_whitelist -> Your copied Role Id, can be multiple separated by comma`
      2. `bot_token -> Your Bot Token`
      3. `guild_id -> Your Discord Server ID` 
      4. `notify_channel -> Optional- Discord channel ID that bot will notify about status changes` 
5. Open the `Plugins/BEAMPROJ_DiscordDemo/Overrides/Config/DefaultGame.ini`. 
      1. Replace the `DiscordAppId` in it with `Your App Id`.
      2. Regenerate project files.
6. Compile and open the `BeamableUnreal` editor (it'll be configured as the `BEAMPROJ_DiscordDemo`) project.

Now, you are ready to sign into a game using Discord.

## Playing the sample in Editor

In order to test the sample:

1. Open the `BeamableUnreal` in the Unreal Editor
2. Sign into your Beamable account in the `Beamable Window` and go to the `discord-demo` realm.
3. Go to the `Microservices` and run the `DiscordSampleMS` microservice.
4. Start game.
5. Press the `Sign In with Discord` button following instructions (discord will ask for permission).
6. After logging in, you should see information about being able to participate in matchmaking.
7. Adding and/or removing the role to the signed in user on Discord Server.
8. Observe the text on the UI changing to reflect your ability to participate in matchmaking.
9. Also, if `notify_channel` was specified correctly in configuration bot should inform about status change:

![discord_sample_notify.png](../media/imgs/discord_sample_notify.png)

In order to actually gate matchmaking you'll need to set up a rule in your `GameType` content that excludes people from the queue that do not have the role. This is not shown on this demo.

## Can I use it as a Template?

This sample is not meant to be used as a template directly, however, its components are free for you to copy and use in your own project. Here's what these are:

- The `DiscordDemo` Microservice.
- Beamable code inside `BEAMPROJ_DiscordDemo` except code inside a `ThirdParty` directory.
- Content inside the `BEAMPROJ_DiscordDemo` except things inside a `ThirdParty` directory.

## Why don't we provide a client build?
Because clients must be pointed at your `discord-demo` realm. As such, you'd need to generate the build yourself, which you can do by packaging it normally for any of our supported platforms.
