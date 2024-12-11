<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

This demo showcases how you can use the **Unreal SDK** and **Beamable Microservices** to integrate with Steam.

Aside from our `BeamableCore` Plugin, here's what the sample contains:

- **`BEAMPROJ_SteamDemo` Unreal Plugin.**: Contains the UE implementation for the client.
- **`Microservices/services/SteamDemo` Microservice**: Microservice containing code that implements **IFederatedLogin**

To set up this sample you'll need a few things:

- A Beamable Account and a Realm.
- A Steam Developer Account.

To configure the sample, set the `BeamProjOverride.txt` to `BEAMPROJ_SteamDemo`, re-generate your project files and run the `BeamableUnreal` project (it'll be configured as the `BEAMPROJ_SteamDemo` sample).

## Setting up Beamable & Steam Application

!!! note "Assumptions"
	Instructions below assume that you already have the Steam application created, if that is not the case create one first.

Since this sample requires several resources, we do not host it ourselves. So, in order to access the sample we'll go set up a Steam account and setup the sample:

1. Log into your [Steam](https://partner.steamgames.com/apps) developer account.
2. Go to your App and set aside its `AppId`.
3. Create a Publisher Web API key using [this tutorial](https://partner.steamgames.com/doc/webapi_overview/auth#publisher-keys). Set it aside in a notepad for future use.
4. Make sure that game is added to user that you want to use to login. To do that:
	1. Generate a Steam Key.
	2. Add it to your Steam account so you can access the game.

Now, you'll need to configure a Beamable realm so you can use it:

1. Go to the Beamable Portal and create a new Beamable realm called `steam-demo`.
2. Go to the Portal (`Account`) and set aside your Customer Id (CID).
3. Go to the Portal and set aside your realm's PID and Realm Secret (`Games -> YourGame -> steam-demo`).
4. On the Portal open the Realm Config page of the `steam-demo` realm (`Operate -> Config`).
5. Hit the `Add Config` button.
6. Set the following key-value pairs for the namespace `steam`:
   1. `appid -> Your Steam application ID`
   2. `key -> Your Steam Application Publisher Key` 
7. Compile and open the `BeamableUnreal` editor (it'll be configured as the `BEAMPROJ_SteamDemo`) project.
8. Sign into your Beamable account and go to the `steam-demo` realm.
	1. Hit `Apply to Build`.
9.  Open a bash terminal at the `BeamableUnreal` root directory.
10. Run `dotnet beam project enable --with-group BEAMPROJ_SteamDemo`
11. Run `dotnet beam project disable --without-group BEAMPROJ_SteamDemo`
12. Guarantee `Docker` is open and running.
13. Run `dotnet beam deploy plan`. 
	1. This tells you details about the services you would deploy given your project's local state.
14. Run `dotnet beam deploy release --latest-plan`. 
	1. This deploys the services outlined by the generated plan in the previous command. 
15. Go to the Portal (`Operate -> Microservices`) to verify that the microservices have initialized.
17. In `DefaultEngine.ini` set the value of `SteamDevAppId` to your Steam Application ID. For more there tutorial [here](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Online/Steam/).
18. Package the project.
19. In main folder (in the built game's folder where the executable is) create `steam_appid.txt` file with Steam Application ID as only content.

Now, you are ready to sign into a game using Steam.

## Playing the sample

!!! warninig "Starting the sample"
	Testing the Steam integration from the editor should be performed in `Standalone Game` mode. 
	![](./images/steam-demo-PIE-mode.png#center)
	Steam integration can encounter challenges when running in PIE mode. For this reason, 	Microservice needs to be deployed as local development of federation only works with PIE when not in Standalone Game mode.


In order to test the sample:

- Start game with Steam open with the account to which you added the game.
- It should automatically try to login to that account.
- You should see your "Steam" status change to playing.

#### What can you do with this sample?

!!! warning 
	This sample is NOT a template you can start your own repository from.

However, its Beamable code components are free for you to copy and use in your own project. Here's what these are:

- The `SteamDemo` Microservice.
- Beamable code inside `BEAMPROJ_SteamDemo` except code inside a `ThirdParty` directory.
- Content inside the `BEAMPROJ_SteamDemo` except things inside a `ThirdParty` directory.

!!! note "Why don't we provide a client build?"
	Because clients must be pointed at your `steam-demo` realm. As such, you'd need to generate the build yourself, which you can do by packaging it normally for any of our supported platforms.