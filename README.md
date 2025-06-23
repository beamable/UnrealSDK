# Setting Up The Sui Integration Demo

Beamable provides sample projects for Unreal as part of the Unreal SDK repository. Each sample is tied to a plugin named `BEAMPROJ_<PluginName>` of a shared `BeamableUnreal` project. The sample you see in the editor is determined by which `BEAMPROJ_` plugin is enabled in the BeamableUnreal.uproject file.

This specific branch replaces the `BEAMPROJ_LiveOpsDemo` plugin with a Sui Integration Demo, The Sui integration allows you to use Sui as a wallet provider, enabling players to use their Sui wallets to interact with your game.

#### Support Disclaimer 
This sample will not be supported on future updates but you can use as a sample for your own project. The Sui integration is not a Beamable feature, but rather a custom implementation that uses the Beamable SDK to interact with the Sui blockchain. This means that you can use the Beamable SDK to build your own custom integrations with any blockchain or wallet provider.

## Preparing the Environment
1. Install Dependencies
    - NET 8.0
    - [Docker Desktop](https://www.docker.com/products/docker-desktop/)
    - [Node.js](https://nodejs.org/en/download)
2. Clone the UnrealSDK Repository
    - Clone the [UnrealSDK](https://github.com/Beamable/UnrealSDK) repository if you didn't yet.
    - Run the `prepare_repo.sh` Script. (We recommend using GitBash, but any similar shell should work)

## Select the Sample to Run

1. Use `dotnet beam unreal select-sample BEAMPROJ_LiveOpsDemo`. During this process all of the content in their `Override` folder will be copied to the `BeamamableUnreal` project replacing any previous configuration. This allow us to replace the whole "Context" in which the project will be configured, thus allowing us to have multiple samples at the same project.
2. If using Rider as IDE and already in the BeamableUnreal.sln project you can alternatively select and run the `SET BEAMPROJ - LiveOpsDemo` in the Configuration Drop Down (Top Right Corner)

## Build and Run in Editor

1. Open the generated `.sln` file in your IDE (e.g., Visual Studio, Rider...).
2. Perform a Clean build of the Editor target.
3. Run the `BeamableUnreal` Project and in the editor, go to Project Settings → Beamable Core → Beamable Environment and verify it’s set to `BeamProdEnv`.

!!! warning "Clean Up Sample Realms"
If you are using your own organization (the one you’ll use to ship your game) to test any of these samples, don’t forget to delete the test realms when you’re finished exploring!

# Copy Realm Content

1. Sign in to your account using the `dotnet beam init` command.
2. Then command `dotnet beam content replace-local --from DE_1853976001305603 --to YOUR_REALM_ID` to bring all the content from the sample to your current realm
3. Publish the content in the Content Tab (or run a `dotnet beam content publish`).

## Setting up the Project
To set up an organization and realm to run this sample, follow the steps below.

1. Go to the Beamable Portal and create a new Beamable realm called `liveops-demo-sui`
2. Compile and open the `BeamableUnreal` editor project.
3. Sign into your Beamable account and go to the `liveops-demo-sui` realm.
   1. Optionally you can hit `Apply to Build` after the realm change is done.
4. After Signin in your account, you will need to run the command `dotnet beam content replace-local --from DE_1853976001305603 --to YOUR_REALM_ID` to bring all the content from the sample to your current realm
   1. Publish the content in the Content Tab.
5. Let's Setup the Content
   1. Open the `Content` window.
   2. Ensure there's two `SuiCoins` currencies with the name `beam` and `stars`
   3. Ensure there is one `SuiGameCoins` currency with the name `gold`
   4. Ensure there is two `SuiWeaponsItems` content with the name `darksaber` and `shisui`
   5. Make sure the Items have those parameters as informed in the table below:
   
| Item      | Name      | Symbol | Image                                                                   | Description                                           | Initial Supply | Client Permission | Starting Amount | Federation - Service   | Federation - Namespace | isSet |
|-----------|-----------|--------|-------------------------------------------------------------------------|-------------------------------------------------------|----------------|-------------------|-----------------|------------------------|------------------------|-------|
| beam      | Beam      | BEAM   | https://cdn.pixabay.com/photo/2018/08/30/12/24/bitcoin-3642042_1280.png | Beam game coin                                        | 1000           | True              | 0               | SuiFederation          | SuiIdentity            | true  |
| star      | Star Coin | STR    | https://cdn.pixabay.com/photo/2016/03/31/17/33/icons-1293736_1280.png   |                                                       | 0              | True              | 0               | SuiFederation          | SuiIdentity            | true  |
| gold      | Gold      | GLD    | https://cdn.pixabay.com/photo/2013/07/12/12/55/gold-bar-146539_1280.png | In Game Gold                                          | 100            | True              | 0               | SuiFederation          | SuiIdentity            | true  |
| darksaber | DarkSaber |        | https://cdn.pixabay.com/photo/2012/04/15/20/07/light-35144_1280.png     | An ancient lightsaber created by Tarre Vizsla         |                | True              |                 | SuiFederation          | SuiIdentity            |       |
| shisui    | Shisui    |        | https://cdn.pixabay.com/photo/2019/04/05/15/01/katana-4105189_1280.png  | This sword is said to have the power to control water |                | True              |                 | SuiFederation          | SuiIdentity            |       |

5. Click `Publish` to publish those new contents to the realm.

## Running the Sample in Editor
Now you're set up to run the sample.

1. Open the Docker Desktop and Make sure it's running
2. From a terminal Open the directory `microservices/services/SuiFederation` and run `npm install`
3. Open a terminal and run `dotnet beam services run --ids SuiFederation`
4. Open the Unreal Editor
5. Go to the `Beamable -> Microservice` window. You should see the `SuiFederation` service running there.
6. Reset PIE Users to clear any existing data.
   1. Go to the `Home` window.
   2. Click on `Reset PIE Users`.
7. Open the `LiveOpsDemo` Level if it's not opened yet.
   1. You can find it inside the `BEAMPROJ_LiveOpsDemo Content`  folder.
   2. If you can't see plugin content in your content browser, you can change the settings of the UE `Content Browser` to display it.
8. Play the `LiveOpsDemo` in the Editor.

## About the Sample

- The sample project includes several important files that will help guide you through the sample flow.
  - Blueprint handles almost everything not related to SUI. We're using it primarily for **Beamable SDK** integration and UI/widget management.
  - Be sure to take a look at the **WBP_LiveOpsUI Blueprint** — it contains the core flow and logic for the sample.
  - On the C++ side, the **USuiWalletSigner** class in the **BEAMPROJ_LiveOpsDemo** is responsible for all SUI-related functionality.

- We are also using two external libraries for cryptographic operations:
  - [BLAKE2](https://github.com/BLAKE2/BLAKE2) for Blake2b hashing
  - [compact25519](https://github.com/DavyLandman/compact25519) for Ed25519 signature operations
   

## Can I use it as a Template?

This sample is not meant to be used as a template directly, however, its components are free for you to copy and use in your own project. Here's what these are:

- The LiveOpsDemoMS Microservice : located inside Microservice/LiveOpsDemoMS
- Beamable code and blueprints inside BEAMPROJ_LiveOpsDemo plugin