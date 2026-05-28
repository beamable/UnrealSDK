using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using Beamable.Common.Api.Inventory;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
    // ══════════════════════════════════════════════════════════════════════════
    // RESEARCH ENUMS
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// What kind of reward is granted when research completes.
    /// Must match EBeamResearchOutputType in FarmTypes.h.
    /// </summary>
    public enum EResearchOutputType
    {
        /// <summary>A plant_modifier.* currency spendable in the Mutation Lab.</summary>
        PlantModifier,
        /// <summary>Any inventory item (itemplant.*, etc.).</summary>
        Item,
        /// <summary>Any Beamable currency (plant_raw_material.*, etc.).</summary>
        Currency,
    }

    // ══════════════════════════════════════════════════════════════════════════
    // PROPERTY KEY CONSTANTS
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// Item property keys written to an item instance while it is under research.
    /// Clients check for StartedAt to determine if an item is in research.
    /// Must match GetResearch*Key() helpers on UBeamFarmSubsystem.
    /// </summary>
    public static class ResearchPropertyKeys
    {
        public const string StartedAt       = "research_started_at";
        public const string DurationSecs    = "research_duration_secs";
        public const string OutputContentId = "research_output_content_id";
        public const string OutputQuantity  = "research_output_quantity";
        public const string OutputType      = "research_output_type";
    }

    // ══════════════════════════════════════════════════════════════════════════
    // PLANT DATA (nested struct inside itemplant content)
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// Mirrors FBeamPlantData in BeamPlantData.h.
    /// Must be declared so Beamable can deserialize the nested PlantData object;
    /// the microservice itself only needs the research fields, but omitting this
    /// class causes the content parse to fail for the whole object.
    /// </summary>
    [Serializable]
    public class PlantData
    {
        public string DisplayName          = string.Empty;
        public string ReadyToHarvestSprite = string.Empty;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // PLANT CONTENT TYPE (research fields only)
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// Represents the research-relevant fields of an itemplant content object.
    /// Beamable deserializes only the declared fields; all other plant fields are ignored.
    ///
    /// These fields are authored in the Beamable content browser on the itemplant entry
    /// that corresponds to the item the player wants to research.
    /// </summary>
    [Serializable]
    [ContentType("itemplant")]
    public class PlantItemContent : ItemContent
    {
        public PlantData PlantData = new PlantData();

        /// <summary>Whether this plant type can be submitted for research.</summary>
        // public bool bCanBeResearched = false;

        /// <summary>How many research_points the player must spend to start research.</summary>
        public int ResearchPointsCost = 10;

        /// <summary>How long (seconds) the research takes. Server-authoritative.</summary>
        public float ResearchDurationSeconds = 60f;

        /// <summary>
        /// What kind of reward is granted when research completes.
        /// Serialized as the enum name: "PlantModifier", "Item", or "Currency".
        /// </summary>
        public EResearchOutputType ResearchOutputType = EResearchOutputType.PlantModifier;

        /// <summary>Content ID of the reward (plant_modifier.*, itemplant.*, plant_raw_material.*, etc.).</summary>
        public string ResearchOutputContentId;

        /// <summary>How many units of ResearchOutputContentId are granted on completion.</summary>
        public int ResearchOutputQuantity = 1;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // RESULT MODELS
    // ══════════════════════════════════════════════════════════════════════════

    [Serializable]
    public class StartResearchResult
    {
        public bool   success;

        /// <summary>Server UTC timestamp (seconds) at which research started.</summary>
        public long   startedAtUtcSeconds;

        /// <summary>How many research_points were deducted.</summary>
        public int    pointsSpent;

        public string message;
    }

    [Serializable]
    public class CollectResearchResult
    {
        public bool   success;

        /// <summary>Content ID of the reward granted to the player.</summary>
        public string outputContentId;

        /// <summary>How many units were granted.</summary>
        public int    outputQuantity;

        /// <summary>Serialized ResearchOutputType name: "PlantModifier", "Item", or "Currency".</summary>
        public string outputType;

        public string message;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // MICROSERVICE IMPLEMENTATION
    // ══════════════════════════════════════════════════════════════════════════

    public partial class BeamFarmMs
    {
        // ─── Constants ────────────────────────────────────────────────────────

        /// <summary>
        /// Content ID of the research_points currency players spend to start research.
        /// Create a matching "currency.research_points" entry in the Beamable content browser.
        /// </summary>
        private const string ResearchPointsCurrencyId = "currency.research_points";

        // ──────────────────────────────────────────────────────────────────────
        // START RESEARCH
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Spends research_points and marks an item as under research by writing
        /// research state directly into the item's properties.
        ///
        /// Research parameters (cost, duration, output) are read directly from the
        /// itemplant content associated with itemContentId — no separate project content needed.
        /// The plant content must have bCanBeResearched = true.
        ///
        /// Because Beamable item properties are updated by deleting the item and re-adding
        /// it with the merged property set, the item receives a new instance ID after this call.
        /// The client should refresh its inventory to pick up the updated item.
        ///
        /// Items in research carry the following properties (see ResearchPropertyKeys):
        ///   research_started_at          — Unix timestamp (seconds)
        ///   research_duration_secs       — duration in seconds
        ///   research_output_content_id   — reward content ID
        ///   research_output_quantity     — reward quantity
        ///   research_output_type         — "PlantModifier" | "Item" | "Currency"
        ///
        /// Clients use the presence of "research_started_at" to identify items in research
        /// and hide them from other UIs (delivery, mutation lab, inventory sell screen).
        ///
        /// Validation steps (in order):
        ///   1. All arguments are non-empty / valid.
        ///   2. The item instance exists in the player's inventory.
        ///   3. The item is not already under research (no research_started_at property).
        ///   4. The plant content is valid and has bCanBeResearched = true.
        ///   5. The plant content has a valid ResearchOutputContentId and positive duration.
        ///   6. The player owns enough research_points.
        ///
        /// NOTE: Run `dotnet beam generate` after modifying this file.
        /// </summary>
        [ClientCallable]
        public async Task<StartResearchResult> StartResearch(long itemInstanceId, string itemContentId)
        {
            // ── Input validation ──────────────────────────────────────────────
            if (itemInstanceId <= 0)
                return ResearchStartFail("itemInstanceId must be a valid positive instance ID.");

            if (string.IsNullOrWhiteSpace(itemContentId))
                return ResearchStartFail("itemContentId must not be empty.");

            // ── Load inventory (items + currency in one call) ─────────────────
            var inventory = await Services.Inventory.GetCurrent("items,currency");

            // ── Find the item instance ────────────────────────────────────────
            ItemView itemInstance = null;
            if (inventory?.items != null &&
                inventory.items.TryGetValue(itemContentId, out var itemGroup))
            {
                itemInstance = itemGroup?.FirstOrDefault(i => i.id == itemInstanceId);
            }

            if (itemInstance == null)
                return ResearchStartFail(
                    $"Item instance {itemInstanceId} (contentId='{itemContentId}') not found in inventory.");

            // ── Reject if item is already under research ──────────────────────
            if (itemInstance.properties != null &&
                itemInstance.properties.ContainsKey(ResearchPropertyKeys.StartedAt))
            {
                return ResearchStartFail(
                    $"Item {itemInstanceId} is already under research. Collect it first.");
            }

            // ── Load and validate the plant content ───────────────────────────
            PlantItemContent plant;
            try
            {
                plant = await Services.Content.GetContent<PlantItemContent>(
                    new ContentRef(typeof(PlantItemContent), itemContentId));
            }
            catch (Exception ex)
            {
                return ResearchStartFail($"Failed to load plant content '{itemContentId}': {ex.Message}");
            }

            if (plant == null)
                return ResearchStartFail($"Plant content '{itemContentId}' not found. Was it unpublished?");

            // if (!plant.bCanBeResearched)
            //     return ResearchStartFail($"Plant '{itemContentId}' is not marked as researchable.");

            if (string.IsNullOrWhiteSpace(plant.ResearchOutputContentId))
                return ResearchStartFail($"Plant '{itemContentId}' has no ResearchOutputContentId configured.");

            if (plant.ResearchDurationSeconds <= 0f)
                return ResearchStartFail($"Plant '{itemContentId}' has an invalid ResearchDurationSeconds.");

            if (plant.ResearchOutputQuantity <= 0)
                return ResearchStartFail($"Plant '{itemContentId}' has an invalid ResearchOutputQuantity.");

            int cost = Math.Max(0, plant.ResearchPointsCost);

            // ── Validate research_points balance ──────────────────────────────
            if (cost > 0)
            {
                long owned = inventory.currencies != null &&
                    inventory.currencies.TryGetValue(ResearchPointsCurrencyId, out var pts) ? pts : 0L;

                if (owned < cost)
                    return ResearchStartFail(
                        $"Not enough research points: need {cost}, have {owned}.");
            }

            // ── Build new item properties (preserve existing + add research state) ──
            long   startedAt   = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
            int    durationSec = Math.Max(1, (int)Math.Ceiling(plant.ResearchDurationSeconds));
            string outputType = "";
                // string.IsNullOrWhiteSpace(plant.ResearchOutputType)
                //                     ? nameof(EResearchOutputType.PlantModifier)
                //                     : plant.ResearchOutputType;

            var newProps = itemInstance.properties != null
                ? new Dictionary<string, string>(itemInstance.properties)
                : new Dictionary<string, string>();

            newProps[ResearchPropertyKeys.StartedAt]       = startedAt.ToString();
            newProps[ResearchPropertyKeys.DurationSecs]    = durationSec.ToString();
            newProps[ResearchPropertyKeys.OutputContentId] = plant.ResearchOutputContentId;
            newProps[ResearchPropertyKeys.OutputQuantity]  = plant.ResearchOutputQuantity.ToString();
            newProps[ResearchPropertyKeys.OutputType]      = outputType;

            // ── Apply inventory update atomically ─────────────────────────────
            var updateBuilder = new InventoryUpdateBuilder();
            updateBuilder.DeleteItem(itemContentId, itemInstanceId);
            updateBuilder.AddItem(itemContentId, newProps);

            if (cost > 0)
                updateBuilder.CurrencyChange(ResearchPointsCurrencyId, -cost);

            await Services.Inventory.Update(updateBuilder);

            return new StartResearchResult
            {
                success             = true,
                startedAtUtcSeconds = startedAt,
                pointsSpent         = cost,
                message             = $"Research started on '{itemContentId}'. " +
                                      $"Ready in {durationSec}s. Spent {cost} research point(s).",
            };
        }

        // ──────────────────────────────────────────────────────────────────────
        // COLLECT RESEARCH
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Collects completed research: consumes the item (which holds the research state
        /// in its properties) and grants the configured output reward.
        ///
        /// Output dispatch by OutputType stored in item properties:
        ///   PlantModifier → CurrencyChange(outputContentId, outputQuantity)
        ///   Currency      → CurrencyChange(outputContentId, outputQuantity)
        ///   Item          → AddItem(outputContentId) × outputQuantity
        ///
        /// NOTE: Run `dotnet beam generate` after modifying this file.
        /// </summary>
        [ClientCallable]
        public async Task<CollectResearchResult> CollectResearch(long itemInstanceId, string itemContentId)
        {
            // ── Input validation ──────────────────────────────────────────────
            if (itemInstanceId <= 0)
                return ResearchCollectFail("itemInstanceId must be a valid positive instance ID.");

            if (string.IsNullOrWhiteSpace(itemContentId))
                return ResearchCollectFail("itemContentId must not be empty.");

            // ── Find the item instance ────────────────────────────────────────
            var inventory = await Services.Inventory.GetCurrent("items");

            ItemView itemInstance = null;
            if (inventory?.items != null &&
                inventory.items.TryGetValue(itemContentId, out var itemGroup))
            {
                itemInstance = itemGroup?.FirstOrDefault(i => i.id == itemInstanceId);
            }

            if (itemInstance == null)
                return ResearchCollectFail(
                    $"Item instance {itemInstanceId} (contentId='{itemContentId}') not found in inventory.");

            // ── Verify item is under research ─────────────────────────────────
            var props = itemInstance.properties ?? new Dictionary<string, string>();

            if (!props.TryGetValue(ResearchPropertyKeys.StartedAt, out var startedAtStr) ||
                !long.TryParse(startedAtStr, out long startedAt))
            {
                return ResearchCollectFail($"Item {itemInstanceId} is not under research.");
            }

            if (!props.TryGetValue(ResearchPropertyKeys.DurationSecs, out var durationStr) ||
                !int.TryParse(durationStr, out int durationSecs) || durationSecs <= 0)
            {
                return ResearchCollectFail("Corrupted research duration on item — please contact support.");
            }

            props.TryGetValue(ResearchPropertyKeys.OutputContentId, out string outputContentId);
            props.TryGetValue(ResearchPropertyKeys.OutputType, out string outputType);
            props.TryGetValue(ResearchPropertyKeys.OutputQuantity, out string outputQtyStr);

            if (string.IsNullOrEmpty(outputContentId))
                return ResearchCollectFail("No output configured for this research — please contact support.");

            int outputQuantity = int.TryParse(outputQtyStr, out var qty) ? Math.Max(1, qty) : 1;
            if (string.IsNullOrWhiteSpace(outputType))
                outputType = nameof(EResearchOutputType.PlantModifier);

            // ── Timing check (server-authoritative) ───────────────────────────
            long readyAt = startedAt + durationSecs;
            long nowUtc  = DateTimeOffset.UtcNow.ToUnixTimeSeconds();

            if (nowUtc < readyAt)
            {
                long remaining = readyAt - nowUtc;
                return ResearchCollectFail(
                    $"Research on item {itemInstanceId} is not complete yet. {remaining}s remaining.");
            }

            // ── Build update: consume item, grant output ───────────────────────
            var updateBuilder = new InventoryUpdateBuilder();
            updateBuilder.DeleteItem(itemContentId, itemInstanceId);

            if (outputType == nameof(EResearchOutputType.Item))
            {
                for (int i = 0; i < outputQuantity; i++)
                    updateBuilder.AddItem(outputContentId, new Dictionary<string, string>());
            }
            else
            {
                // PlantModifier and Currency are both Beamable currencies.
                updateBuilder.CurrencyChange(outputContentId, outputQuantity);
            }

            await Services.Inventory.Update(updateBuilder);

            return new CollectResearchResult
            {
                success         = true,
                outputContentId = outputContentId,
                outputQuantity  = outputQuantity,
                outputType      = outputType,
                message         = $"Research collected for item {itemInstanceId}. " +
                                  $"Granted {outputQuantity}× '{outputContentId}'.",
            };
        }

        // ──────────────────────────────────────────────────────────────────────
        // ERROR HELPERS
        // ──────────────────────────────────────────────────────────────────────

        private static StartResearchResult ResearchStartFail(string message) =>
            new StartResearchResult
            {
                success             = false,
                startedAtUtcSeconds = 0L,
                pointsSpent         = 0,
                message             = message,
            };

        private static CollectResearchResult ResearchCollectFail(string message) =>
            new CollectResearchResult
            {
                success         = false,
                outputContentId = string.Empty,
                outputQuantity  = 0,
                outputType      = string.Empty,
                message         = message,
            };
    }
}
