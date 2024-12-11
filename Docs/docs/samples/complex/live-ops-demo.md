<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

This demo showcases how you can use the **Unreal SDK**'s Announcements Subsystem to notify players of events while providing claimable gifts that'll end up in the player's inventory.

Aside from our `BeamableCore` Plugin, here's what the sample contains:

- **`BEAMPROJ_LiveOpsDemo` Unreal Plugin.**: Contains the UE implementation for the sample's client. The core code is inside `LiveOpsDemoMainMenu.h` and part of the implementation is done through BPs inside the folder `UI_BPs` folder of the `BEAMPROJ_LiveOpsDemo` project.
- **`Microservice/LiveOpsDemo` Microservice**: Microservice containing code that's used by the sample for various inventory and stat related things.

To set up this sample you'll need a a Beamable Account and a Realm. To configure the repo for the sample:
- Set the `BeamProjOverride.txt` to `BEAMPROJ_LiveOpsDemo`.
- Re-generate your project files.
## Setting up the Beamable Realm
To set up an organization and realm to run this sample, follow the steps below.

1. Go to the Beamable Portal and create a new Beamable realm called `liveops-demo`    
2. Compile and open the `BeamableUnreal` editor project.
3. Sign into your Beamable account and go to the `liveops-demo` realm.
	1. Hit `Apply to Build` after the realm change is done.
4. Open the `Content` window.
	1. Ensure there's an `item` content with the name `sample_item`.
	2. Ensure there are 2 `currency` contents with names `gems` and `coins`
	3. Click `Publish` to publish this new content to the realm.
5. Go back to the Beamable Portal.
	1. Choose `liveops-demo` realm from Beamable portal.
	2. Go to `Communicate->Campaigns`.
	3. Click on Create Campaign.
	4. Initialize the campaign scheduling, content, and the gifts it provides and save it.
		1. Make sure the type is `Announcement`.
		2. In the `Content` section, add a Gift that gives some amount of `coin` to the user. Optionally, you can also gift them an instance of the `sample_item` with a property called `level` set to `1`.
		3. You can leave the rest as the default.
## Running the Sample in PIE
Now you're set up to run the sample.

1. Open the Unreal editor.
2. Go to the `Microservice` window.
	1. You should see the `LiveOpsDemoMS` service there. Select it.
	2. Click `Run` and wait until you see the `Service ready for traffic` log line (and the running icon in the Microservice's card to change).
	3. After you're done with the sample, don't forget to come here and stop the service.
3. Open the `LiveOpsDemo` Level.
	1. You can find it inside the `BEAMPROJ_LiveOpsDemo Content`  folder.
	2. If you can't see plugin content in your content browser, you can change the settings of the UE `Content Browser` to display it.
4. Reset PIE Users.
5. Open PIE.

At runtime, the sample works in the following way:

1. Every time you run the demo, it will initialize the player inventory with 3 sample items that have the an item property called `level` set to `1`.    
	1. It'll also initialize a `sample_stat` with the value `1`.
2. In the announcements menu, you'll find all the announcements you configured via the portal (provided the schedule you put in makes it active). 
	1. You can click on any announcement.
	2. Doing so, shows its content and all the gifts that could be claimed through this announcement (if any).    
5. You can claim the gifts inside the announcement by clicking on the claim button.    
6. You can see each of the `sample_item` instances the player has and their level at the right portion of the screen.
	1. You should be able to upgrade the item level using the upgrade button.    
7. You can also click the button next to the `sample stat` stat to increment it.        
#### What can you do with this sample?

This sample is NOT a template you can start your own repository from.

However, its Beamable code components are free for you to copy and use in your own project. Here's what these are:

- The LiveOpsDemoMS Microservice : located inside Microservice/LiveOpsDemoMS
- Beamable code and blueprints inside BEAMPROJ_LiveOpsDemo plugin