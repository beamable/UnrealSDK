using Beamable.Common.Api.Inventory;
using Beamable.Common.Inventory;
using Beamable.Server;
using System.Collections.Generic;
using System.Threading.Tasks;
using System;
using Beamable.Common;

namespace Beamable.LiveOpsDemoMs
{
    [Microservice("LiveOpsDemoMs")]
    public class LiveOpsDemoMs : Microservice
    {
        const string PlaySampleStatID = "my_sample_stat";
        const string SampleItemID = "items.sample_item";

        [ClientCallable]
        public async Task<bool> PrepareNewPlayer(long userID)
        {
            //Set Initial player xp to be 0
            await Services.Stats.SetProtectedPlayerStat(userID, PlaySampleStatID, "0");

            var updateBuilder = new InventoryUpdateBuilder();

            //Clear the inventory if it has any sample items
            List<InventoryObject<ItemContent>> items = await Services.Inventory.GetItems<ItemContent>();

            foreach (InventoryObject<ItemContent> item in items)
            {
                if (item.ItemContent.Id == SampleItemID)
                {
                    updateBuilder.DeleteItem(item.ItemContent.Id, item.Id);
                }
            }

            //Add 3 sample items with level 1
            Dictionary<string, string> itemProperties = new Dictionary<string, string>
            {
                 { "itemlevel", "1" }
            };

            //Add 3 instances of the sample item
            updateBuilder.AddItem(SampleItemID, itemProperties);
            updateBuilder.AddItem(SampleItemID, itemProperties);
            updateBuilder.AddItem(SampleItemID, itemProperties);

            await Services.Inventory.Update(updateBuilder);


            //Set the initial sample stat to be 1
            Dictionary<string, string> initialPlayerStats = new Dictionary<string, string>();
            initialPlayerStats.Add(PlaySampleStatID, "1");


            await Services.Stats.SetStats("client", "private", "player", userID, initialPlayerStats);


            return true;

        }

        //Increases the sample item level
        [ClientCallable]
        public async Task<bool> UpgradeItem(long userID, long itemInstaceID)
        {

            ItemContent itemRef = new ItemContent();


            List<InventoryObject<ItemContent>> items = await Services.Inventory.GetItems<ItemContent>();

            var updateBuilder = new InventoryUpdateBuilder();

            foreach (InventoryObject<ItemContent> item in items)
            {
                if (item.ItemContent.Id == SampleItemID)
                {
                    if (item.Id == itemInstaceID)
                    {
                        if (item.Properties.ContainsKey("itemlevel"))
                        {
                            int itemLevel = int.Parse(item.Properties["itemlevel"]);
                            itemLevel++;

                            item.Properties["itemlevel"] = itemLevel.ToString();

                            updateBuilder.UpdateItem(item.ItemContent.Id, item.Id, item.Properties);



                            break;
                        }

                    }
                }
            }
            await Services.Inventory.Update(updateBuilder);

            return true;
        }
        //Increases player sample stat by 1
        [ClientCallable]
        public async Task<bool> IncrementStat(long userID)
        {
            string[] returnedStatID = { PlaySampleStatID };

            Dictionary<string, string> playerStats = await Services.Stats.GetStats("client", "private", "player", userID, returnedStatID);


            int newStatValue = int.Parse(playerStats[returnedStatID[0]]);

            newStatValue++;

            playerStats[PlaySampleStatID] = newStatValue.ToString();

            await Services.Stats.SetStats("client", "private", "player", userID, playerStats);

            return true;
        }

        //Retrieves the sample stat
        [ClientCallable]
        public async Task<int> GetSamlpeStat(long userID)
        {
            string[] returnedStatID = { PlaySampleStatID };

            Dictionary<string, string> playerStats = await Services.Stats.GetStats("client", "private", "player", userID, returnedStatID);

            int statValue = int.Parse(playerStats[returnedStatID[0]]);

            return statValue;
        }
    }
}

