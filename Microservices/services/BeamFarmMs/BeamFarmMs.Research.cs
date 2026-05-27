using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using Beamable.Common.Api.Inventory;
using Beamable.Common.Content;
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
    public enum ResearchOutputType
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
    /// Clients check for ResearchStartedAt to determine if an item is in research.
    /// Must match GetResearch*PropertyKey() helpers on UBeamFarmSubsystem.
    /// </summary>
    public static class ResearchPropertyKeys
    {
        public const string ProjectId      = "research_project_id";
        public const string StartedAt      = "research_started_at";
        public const string DurationSecs   = "research_duration_secs";
        public const string OutputContentId = "research_output_content_id";
        public const string OutputQuantity  = "research_output_quantity";
        public const string OutputType      = "research_output_type";
    }

    // ══════════════════════════════════════════════════════════════════════════
    // RESEARCH CONTENT TYPE
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// Template that defines a researchable item, its research_points cost, and its reward.
    /// Content type ID: "research_project"
    ///
    /// Examples:
    ///   research_project.wheat_analysis  — consumes itemplant.wheat (costs 5 pts), grants 4× plant_raw_material.wheat_seed
    ///   research_project.ancient_spore   — consumes itemplant.ancient (costs 20 pts), grants 1× plant_modifier.spore_boost
    ///   research_project.rare_specimen   — consumes itemplant.rare (costs 30 pts), grants 1× itemplant.rare_evolved
    ///
    /// Publish entries in the Beamable content browser. Run `dotnet beam generate`
    /// after modifying this file to regenerate Blueprint-callable nodes.
    /// </summary>
    [Serializable]
    [ContentType("research_project")]
    public class ResearchProjectContent : ContentObject
    {
        /// <summary>Content ID of the plant item that must be in-research for this project (itemplant.*).</summary>
        [JsonPropertyName("InputItemContentId")]
        public string InputItemContentId;

        /// <summary>How many research_points the player must spend to start this research.</summary>
        [JsonPropertyName("ResearchPointsCost")]
        public int ResearchPointsCost = 10;

        /// <summary>How long (seconds) the research takes. Server-authoritative.</summary>
        [JsonPropertyName("ResearchDurationSeconds")]
        public float ResearchDurationSeconds = 60f;

        /// <summary>
        /// What kind of reward is granted when research completes.
        /// Serialized as the enum name: "PlantModifier", "Item", or "Currency".
        /// </summary>
        [JsonPropertyName("OutputType")]
        public string OutputType = nameof(ResearchOutputType.PlantModifier);

        /// <summary>Content ID of the reward (plant_modifier.*, itemplant.*, plant_raw_material.*, etc.).</summary>
        [JsonPropertyName("OutputContentId")]
        public string OutputContentId;

        /// <summary>How many units of OutputContentId are granted on completion.</summary>
        [JsonPropertyName("OutputQuantity")]
        public int OutputQuantity = 1;

        /// <summary>Human-readable name shown in the Research Lab UI.</summary>
        [JsonPropertyName("DisplayName")]
        public string DisplayName;

        /// <summary>Flavour text shown when inspecting this project in the Research Lab UI.</summary>
        [JsonPropertyName("Description")]
        public string Description;
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
        /// Create a matching "research_points.default" entry in the Beamable content browser.
        /// </summary>
        private const string ResearchPointsCurrencyId = "research_points.default";

        // ──────────────────────────────────────────────────────────────────────
        // START RESEARCH
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Spends research_points and marks an item as under research by writing
        /// research state directly into the item's properties.
        ///
        /// Because Beamable item properties are updated by deleting the item and re-adding
        /// it with the merged property set, the item receives a new instance ID after this call.
        /// The client should refresh its inventory to pick up the updated item.
        ///
        /// Items in research carry the following properties (see ResearchPropertyKeys):
        ///   research_project_id      — which project was started
        ///   research_started_at      — Unix timestamp (seconds)
        ///   research_duration_secs   — duration in seconds
        ///   research_output_content_id — reward content ID
        ///   research_output_quantity   — reward quantity
        ///   research_output_type       — "PlantModifier" | "Item" | "Currency"
        ///
        /// Clients use the presence of "research_started_at" to identify items in research
        /// and hide them from other UIs (delivery, mutation lab, inventory sell screen).
        ///
        /// Validation steps (in order):
        ///   1. All arguments are non-empty / valid.
        ///   2. The item instance exists in the player's inventory.
        ///   3. The item's contentId matches the project's InputItemContentId.
        ///   4. The item is not already under research (no research_started_at property).
        ///   5. The project content is valid, has an OutputContentId, and a positive cost.
        ///   6. The player owns enough research_points.
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///   Call UBeamFarmSubsystem::StartResearch(ItemInstanceId, ItemContentId, ProjectContentId).
        ///   Bind to OnResearchStarted / OnResearchStartFailed.
        ///   On success, refresh inventory — the item has a new instance ID.
        ///
        /// NOTE: Run `dotnet beam generate` after modifying this file.
        /// ═════════════════════════════════════════════════════════════════════
        /// </summary>
        [ClientCallable]
        public async Task<StartResearchResult> StartResearch(
            long   itemInstanceId,
            string itemContentId,
            string projectContentId)
        {
            // ── Input validation ──────────────────────────────────────────────
            if (itemInstanceId <= 0)
                return ResearchStartFail("itemInstanceId must be a valid positive instance ID.");

            if (string.IsNullOrWhiteSpace(itemContentId))
                return ResearchStartFail("itemContentId must not be empty.");

            if (string.IsNullOrWhiteSpace(projectContentId))
                return ResearchStartFail("projectContentId must not be empty.");

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

            // ── Load and validate the research project content ────────────────
            ResearchProjectContent project;
            try
            {
                project = await Services.Content.GetContent<ResearchProjectContent>(
                    new ContentRef(typeof(ResearchProjectContent), projectContentId));
            }
            catch (Exception ex)
            {
                return ResearchStartFail($"Failed to load research project '{projectContentId}': {ex.Message}");
            }

            if (project == null)
                return ResearchStartFail($"Research project '{projectContentId}' not found. Was it unpublished?");

            if (string.IsNullOrWhiteSpace(project.InputItemContentId))
                return ResearchStartFail($"Research project '{projectContentId}' has no InputItemContentId configured.");

            if (string.IsNullOrWhiteSpace(project.OutputContentId))
                return ResearchStartFail($"Research project '{projectContentId}' has no OutputContentId configured.");

            if (project.ResearchDurationSeconds <= 0f)
                return ResearchStartFail($"Research project '{projectContentId}' has an invalid ResearchDurationSeconds.");

            if (project.OutputQuantity <= 0)
                return ResearchStartFail($"Research project '{projectContentId}' has an invalid OutputQuantity.");

            int cost = Math.Max(0, project.ResearchPointsCost);

            // ── Validate item matches project input ───────────────────────────
            if (itemInstance.contentId != project.InputItemContentId)
                return ResearchStartFail(
                    $"Item '{itemContentId}' does not match project's required input '{project.InputItemContentId}'.");

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
            int    durationSec = Math.Max(1, (int)Math.Ceiling(project.ResearchDurationSeconds));
            string outputType  = string.IsNullOrWhiteSpace(project.OutputType)
                                    ? nameof(ResearchOutputType.PlantModifier)
                                    : project.OutputType;

            var newProps = itemInstance.properties != null
                ? new Dictionary<string, string>(itemInstance.properties)
                : new Dictionary<string, string>();

            newProps[ResearchPropertyKeys.ProjectId]       = projectContentId;
            newProps[ResearchPropertyKeys.StartedAt]       = startedAt.ToString();
            newProps[ResearchPropertyKeys.DurationSecs]    = durationSec.ToString();
            newProps[ResearchPropertyKeys.OutputContentId] = project.OutputContentId;
            newProps[ResearchPropertyKeys.OutputQuantity]  = project.OutputQuantity.ToString();
            newProps[ResearchPropertyKeys.OutputType]      = outputType;

            // ── Apply inventory update atomically ─────────────────────────────
            // Delete old instance, re-add with research properties, deduct research_points.
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
                message             = $"Research started on '{itemContentId}' using project '{projectContentId}'. " +
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
        /// Validation steps (in order):
        ///   1. The item instance exists in the player's inventory.
        ///   2. The item has the research_started_at property (is actually in research).
        ///   3. The research duration has fully elapsed (server clock — cannot be spoofed).
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///   Call UBeamFarmSubsystem::CollectResearch(ItemInstanceId, ItemContentId).
        ///   Get the instance ID from inventory — items with research_started_at property
        ///   are in research. Use UBeamFarmSubsystem::GetResearchStartedAtPropertyKey()
        ///   in Blueprint to filter.
        ///   Bind to OnResearchCollected / OnResearchCollectFailed.
        ///
        /// NOTE: Run `dotnet beam generate` after modifying this file.
        /// ═════════════════════════════════════════════════════════════════════
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
                return ResearchCollectFail(
                    $"Item {itemInstanceId} is not under research.");
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
                outputType = nameof(ResearchOutputType.PlantModifier);

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

            if (outputType == nameof(ResearchOutputType.Item))
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
