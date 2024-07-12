<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

This demo, showcases how you can use the **Unreal SDK** and **Beamable Microservices** to integrate with Discord.

Aside from our `BeamableCore` Plugin, here's what the sample contains:

- **`BEAMPROJ_DiscordDemo` Unreal Plugin.**: Contains the UE implementation for the client.
- **`Microservices/services/DiscordSampleMs` Microservice**: Microservice containing code that implements **IFederatedLogin** and DiscordBot

To set up this sample you'll need a few things:

- A Beamable Account and a Realm.
- A Discord Developer Account.

To configure the sample, set the `BeamProjOverride.txt` to `BEAMPROJ_DiscordDemo`, re-generate your project files and run the `BeamableUnreal` project (it'll be configured as the `BEAMPROJ_DiscordDemo` sample).

## Setting up Beamable & Discord Application

!!! note "Assumptions"
	Instructions below assume that you already have the Discord server that you want to use for integration. If that is not the case create one first. Make sure that you have the admin access to the Discord server of choice.

Since this sample requires several resources, we do not host it ourselves. So, in order to access the sample we'll go set up a Discord account and setup the sample Discord bot:

1. Log into your [Discord.dev](https://discord.com/developers/applications) account.
2. Create an App and set aside its `AppId`.
3. Provide general informations, there is no need for providing URLs at this moment.
4. Go to App `Settings->OAuth2` and provide Redirects url: `http://127.0.0.1`. Make sure that changes are saved.
5. Go to App `Settings->Bot` and provide a Bot username. Set as true all **Privileged Gatyeway Intents**, esspecially the **Server Members Intent**.
6. On the same page press the `Reset Token` button and set it asside (it will be required later on).
7. Go to App `Settings->Installation`, in `Install Link` select `Discord Provided Link`, copy and paste it into browser. Install it into server of choice.
8. Now open the Discord application. For our use case it would be useful to open `Settings->Advanced` and enable the `Developer Mode`.
9.  Right click on the server icon and select the option `Copy server ID` and set it asside.
10. Right click on the server icon and select `Settings->Roles`. Create the role that later on will be required for users.
11. Right click on the role and select the option `Copy Role ID` and set it aside.

Now, you'll need to configure a Beamable realm so you can use it.

1. Go to the Beamable Portal and create a new Beamable realm called `discord-demo`.
2. Go to the Portal (`Account`) and set aside your Customer Id (CID).
3. Go to the Portal and set aside your realm's PID and Realm Secret (`Games -> YourGame -> discord-demo`).
4. On the Portal open the Realm Config page of the `discord-demo` realm (`Operate -> Config`).
5. Hit the `Add Config` button.
6. Set the following key-value pairs for the namespace `discord_integration`:
   1. `matchmaking_roles_whitelist -> Your copied Role Id, can be multiple separated by comma`
   2. `bot_token -> Your Bot Token`
   3. `guild_id -> Your Discord Server ID` 
7. Compile and open the `BeamableUnreal` editor (it'll be configured as the `BEAMPROJ_DiscordDemo`) project.
8. Sign into your Beamable account and go to the `discord-demo` realm.
	1. Hit `Apply to Build`.
9.  Open a bash terminal at the `BeamableUnreal` root directory.
10. Make sure Docker is running and then run `dotnet beam services deploy` in that directory to get the microservices to your `discord-demo` realm.
11. Go to the Portal (`Operate -> Microservices`) and verify that the microservices have initialized.

Now, you are ready to sign into a game using Discord.

## Playing the sample through PIE

In order to test the sample:

- Start game
- Sign in into Discord by pressing button and following instructions.
- After logging in there should be information about being able to participate in matchmaking.
- Test it out by adding and removing selected Discord Role on Discord Server.

#### What can you do with this sample?

**This sample is NOT a template you can start your own repository from.** 

However, its Beamable code components are free for you to copy and use in your own project. Here's what these are:

- The DiscordSampleMs Microservice.
- Beamable code inside `BEAMPROJ_DiscordDemo` except code inside a `ThirdParty` directory.
- Content inside the `BEAMPROJ_DiscordDemo` except things inside a `ThirdParty` directory.

!!! note "Why don't we provide a client build?"
	Because clients must be pointed at your `discord-demo` realm. As such, you'd need to generate the build yourself, which you can do by packaging it normally for any of our supported platforms.