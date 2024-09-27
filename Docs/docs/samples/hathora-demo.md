<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

This demo, created from UE's FPS Template, show-cases how you can use the **Unreal SDK**, **OnlineSubsystemBeamable** and **Beamable Microservices** to integrate with Hathora (a game server orchestration provider).

Aside from our `BeamableCore` Plugin and assets from the FPS Template, here's what the sample contains:

- **`BEAMPROJ_HathoraDemo` Unreal Plugin.**: Contains the UE implementation for the game-server and client.
- **`Microservice/HathoraDemo` Microservice**: Microservice containing code that ties Beamable's matchmaking system and Hathora's Game Server Orchestration system.
- **Pre-Built Linux Dedicated Server Binaries**: Building dedicated servers is time-consuming so... we give you a build that can be configured via Environment Variables so you can test the sample as fast as possible.
- **`OnlineSubsystemBeamable/Customer/**` Extension**: Code added to the `OnlineSubsystemBeamable` plugin to extend our implementation of `IOnlineSubsystem` interfaces with code specific to the Hathora demo.

To set up this sample you'll need a few things:

- A Beamable Account and a Realm.
- A Hathora Account.
- A downloaded build (link to git-hub action artifacts of release tag build).

To configure the sample, set the `BeamProjOverride.txt` to `BEAMPROJ_HathoraDemo`, re-generate your project files and run the `BeamableUnreal` project (it'll be configured as the `BEAMPROJ_HathoraDemo` sample).
## Setting up Beamable & Hathora
Since this sample requires several resources, we do not host it ourselves. So, in order to access the sample you'll need to configure a Beamable realm so you can use it.

1. Go to the Beamable Portal and create a new Beamable realm called `hathora-demo`.
2. Go to the Portal (`Account`) and set aside your Customer Id (CID).
3. Go to the Portal and set aside your realm's PID and Realm Secret (`Games -> YourGame -> hathora-demo`).
4. Compile and open the `BeamableUnreal` editor (it'll be configured as the `BEAMPROJ_HathoraDemo`) project.
5. Sign into your Beamable account and go to the `hathora-demo` realm.
	1. Hit `Apply to Build`.
6. Open the `Content Window` -- verify that there are two `game_types`: `solo_queue` and `training`.
	1. If you fail to see content here, close the editor and try again. There's a known issue in the UE SDK when accessing content for the first time that may cause them to not appear.
7. Hit `Publish` and wait. Go to the Portal (`Operate -> Content`) and verify that the content is there.
8. Open a bash terminal at the `BeamableUnreal` root directory.
9. Run `dotnet beam enable --with-group BEAMPROJ_HathoraDemo`
10. Make sure Docker is running and then run `dotnet beam services deploy` in that directory to get the microservices to your `hathora-demo` realm.
11. Go to the Portal (`Operate -> Microservices`) and verify that the microservices have initialized.


Now, we'll go set up a Hathora account and upload the sample dedicated server build:

1. Log into your [Hathora](https://console.hathora.dev/) account.
2. Create an App and set aside its `AppId`.
3. In the Hathora Portal, go to `Profile -> Settings`.
4. Create and set aside two dev-tokens: `game-server` and `matchmaking-server`.
5. Deploy a new version by uploading the .tar file we provided for the sample.
6. Set up the following environment variables with the values you set aside:
	1. `BEAMABLE_CUSTOMER_OVERRIDE` = `Your CustomerId (CID)`
	2. `BEAMABLE_REALM_OVERRIDE` = `Your hathora-demo Realm's PID`
	3. `BEAMABLE_REALM_SECRET` = `You hathora-demo Realm's Secret`
	4. `BEAMABLE_ENVIRONMENT_OVERRIDE` = `BeamProdEnv`
	5. `HATHORA_DEV_TOKEN` = `The game-server dev token`.
7. Make sure the `7777` UDP port is exposed.
8. Make sure that the number of rooms per processes is `1`.
9. Finish the deployment process and verify that the deployment was successful.

!!! note "Realms and Hathora"
	Hathora recommends users create one Hathora account per dev-environment. In Beamable, that is equivalent of having one Hathora account per Beamable Realm; one for **dev**, another for **staging** and yet another for **prod**. This is so you can have multiple deployments up at the same time for different purposes (the live deployment in **prod** vs a QA-testing build in **staging** and the current stable/nightly in **dev**).

Now that your Hathora account is configured to boot up our provided build, we need to configure the `hathora-demo` realm with the information it needs to correctly provision a server whenever a match is made.

1. Go to the Beamable Portal and open the Realm Config page of the `hathora-demo` realm (`Operate -> Config`).
2. Hit the `Add Config` button.
3. Set the following key-value pairs for the namespace `hathora_integration`.
	1. `app_id -> Your Hathora AppId`
	2. `dev_token -> Your matchmaking-server dev token` 

Now, you are ready to join a match through PIE.
## Playing the sample through PIE
In order to play the sample using a dedicated server in Hathora:

1. Set your `Multiplayer Options -> NetMode` to `Play as Standalone` and open the `Hathora Demo` map.
	1. If you can't find it, turn on `Cotent Browser -> Settings -> Show Plugin Content` and look inside the `BEAMPROJ_HathoraDemo` content folder.
2. Run PIE.
3. The first time you are running, type in an email/password and hit register. 
	1. In subsequent runs OR if you use the same email/password as your Beamable account, hit Login instead.
4. After you're signed in, hit the `Training` button and observe the logs. If you look at Hathora's Portal, you'll be able to see the server spinning up for you to play in. If you look at the your Microservice logs (`Operate -> Microservice -> HathoraDemo -> Logs`), you'll be able to see its communication with Hathora.
5. After a match is found --- 30 seconds later you'll connect to the actual server and see the match. 
6. Move around a while and then simply PIE.

!!! warning "Cold Starts"
	The first run of the application might time out due. If that happens, simply wait until you see a log line in the UE Log window that says "DeleteTicket" show up and simply re-join the queue.

To test this out with two players (this is max players for this sample):

1. Set your `Multiplayer Options -> NetMode` to `Play as Client` and your `Multiplayer Options -> Number of Players` to `2`.
2. Sign into different accounts in each PIE instance.
3. Hit the `Solo Queue` button instead of the `Training` one in both PIE instances.
4. Wait for a bit and both PIE instances will be matched against each other.

#### What can you do with this sample?
**This sample is NOT a template you can start your own repository from.** 

However, its Beamable code components are free for you to copy and use in your own project. Here's what these are:

- The HathoraDemo Microservice.
- Beamable code inside `BEAMPROJ_HathoraDemo` except code inside a `ThirdParty` directory.
- Content inside the `BEAMPROJ_HathoraDemo` except things inside a `ThirdParty` directory.

!!! note "Why don't we provide a client build too?"
	Because clients must be pointed at your `hathora-demo` realm. As such, you'd need to generate the build yourself, which you can do by packaging it normally for any of our supported platforms.