This demo show-cases how you can use the **Unreal SDK**, **OnlineSubsystemBeamable** and **Beamable Microservices** to integrate with Hathora (a game server orchestration provider).

To set up this sample you'll need a few things:

- A Beamable Account and a Realm.
- A Hathora Account.
- A downloaded build (link to git-hub action artifacts of release tag build).

To configure the sample, set the `BeamProjOverride.txt` to `BEAMPROJ_HathoraDemo`, re-generate your project files and run the `BeamableUnreal` project (it'll be configured as the `BEAMPROJ_HathoraDemo` sample).
## Setting up Beamable & Hathora
Since this sample requires several resources, we do not host it ourselves. So, in order to access the sample you'll need to configure a Beamable realm so you can use it.

1. Go to the Beamable Portal and create a new Beamable realm called `hathora-demo`.
2. Open the `BeamableUnreal` editor (it'll be configured as the `BEAMPROJ_HathoraDemo`) project.
3. Sign into your Beamable account and go to the `hathora-demo` realm.
4. Open the `Content Window` -- verify that there are two `game_types`: `solo_queue` and `training`.
5. Hit `Publish` and wait. Go to the Portal (`Operate -> Content`) and verify that the content is there.
6. Open a bash terminal at the BeamableUnreal root directory.
7. Make sure Docker is running and then run `dotnet beam services deploy` in that directory to get the microservices to your `hathora-demo` realm.
8. Go to the Portal (`Operate -> Microservices`) and verify that the microservices have initialized.
9. Go to the Portal (`Account`) and set aside your Customer Id (CID).
10. Go to the Portal and set aside your realm's PID and Realm Secret (`Games -> YourGame -> hathora-demo`).

Now, we'll go set up a Hathora account and upload the sample dedicated server build:

1. Log into your Hathora account.
2. Create an App and set aside its `AppId`.
3. In the Hathora Portal, go to `Profile -> Settings`.
4. Create and set aside two dev-tokens: `game-server` and `matchmaking-server`.
5. Deploy a new version by uploading the .tar file we provided for the sample.
6. Set up the following environment variables with the values you set aside:
	1. `BEAMABLE_CUSTOMER_OVERRIDE -> Your CustomerId (CID)`
	2. `BEAMABLE_REALM_OVERRIDE -> Your hathora-demo Realm's PID`
	3. `BEAMABLE_REALM_SECRET -> You hathora-demo Realm's Secret`
	4. `HATHORA_DEV_TOKEN -> The game-server dev token`.
7. Make sure the `7777` UDP port is exposed.
8. Make sure that the number of rooms per processes is 1.
9. Finish the deployment process and verify that the deployment was successful.

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
3. The first time you are running, type in your email/password and hit register. 
	1. In subsequent runs, hit Login instead.
4. After you're signed in, hit the `Training` button and observe the logs. If you look at Hathora's Portal, you'll be able to see the server spinning up for you to play in. If you look at the your Microservice logs (`Operate -> Microservice -> HathoraDemo -> Logs`), you'll be able to see its communication with Hathora.
5. After a while, you'll be placed into a match by yourself. 
6. Move around a while and then simply PIE.

To test this out with two players (this is max players for this sample):

1. Set your `Multiplayer Options -> NetMode` to `Play as Standalone` and your `Multiplayer Options -> Number of Players` to `2`.
2. Sign into different accounts.
3. Hit the `Solo Queue` button instead of the Training one.
4. Wait for a bit and you'll be matched with yourself.

#### What can you do with this sample?
**This sample is NOT a template you can start your own repository from.** 

However, its Beamable code components are free for you to copy and use in your own project. Here's what these are:

- The HathoraDemo Microservice.
- Beamable code inside `BEAMPROJ_HathoraDemo` except code inside a `ThirdParty` directory.
- Content inside the `BEAMPROJ_HathoraDemo` except things inside a `ThirdParty` directory.

!!! note "Why don't we provide a client build too?"
	Because clients must be pointed at your `hathora-demo` realm. As such, you'd need to generate the build yourself, which you can simply by packaging it normally for any of our supported platforms.