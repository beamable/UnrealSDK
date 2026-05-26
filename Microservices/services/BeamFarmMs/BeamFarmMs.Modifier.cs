using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using Beamable.Common.Api.Inventory;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using Beamable.Content;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
    // ══════════════════════════════════════════════════════════════════════════
    // MODIFIER CONTENT TYPE
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// A single property change entry within a ModifierItemContent.
    /// PropertyName must match a BeamFarmPlantPropertyType enum name:
    ///   "Corrosive", "Mutagenic", "Radioactive"
    /// Delta may be positive (increase) or negative (decrease).
    /// The final property value is clamped to [0, 10]; a result of 0 removes the property.
    /// </summary>
    [Serializable]
    public class ModifierPropertyDelta
    {
        [JsonPropertyName("PropertyName")]
        public string PropertyName;

        /// <summary>Signed change to apply to the property. Positive = increase, negative = decrease.</summary>
        [JsonPropertyName("Delta")]
        public int Delta;
    }

    /// <summary>
    /// Content type for plant modifier items (plant_modifier.*).
    ///
    /// Each modifier item is a Beamable currency — players accumulate them and spend
    /// one unit per application in the mutation lab.
    ///
    /// Each modifier defines one or more property deltas applied atomically to a plant
    /// item instance via <see cref="BeamFarmMs.MutateWithModifiers"/>.
    ///
    /// Example content IDs:
    ///   plant_modifier.corrosive_boost      — adds +3 Corrosive
    ///   plant_modifier.mutagenic_inhibitor  — adds -2 Mutagenic
    ///   plant_modifier.radioactive_surge    — adds +5 Radioactive
    ///
    /// Unreal integration:
    ///   Create matching UBeamModifierItemContent assets in the Beamable content browser.
    ///   Run `dotnet beam generate` to regenerate Blueprint nodes after editing this file.
    /// </summary>
    [Serializable]
    [ContentType("plant_modifier")]
    public class ModifierItemContent : CurrencyContent
    {
        [JsonPropertyName("DisplayName")]
        public string displayName;

        [JsonPropertyName("PropertyModifiers")]
        public List<ModifierPropertyDelta> propertyModifiers;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // MUTATE WITH MODIFIERS RESPONSE
    // ══════════════════════════════════════════════════════════════════════════

    [Serializable]
    public class MutateWithModifiersResult
    {
        public bool success;

        /// <summary>Final properties of the modified plant item after all modifiers are applied.</summary>
        public Dictionary<string, string> newProperties;

        public string message;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // MICROSERVICE IMPLEMENTATION
    // ══════════════════════════════════════════════════════════════════════════

    public partial class BeamFarmMs
    {
        /// <summary>
        /// Applies one or more modifier items to an existing plant item instance, changing
        /// its properties according to each modifier's defined deltas. Each modifier content
        /// ID in the list consumes one unit of that modifier currency — pass the same ID
        /// multiple times to apply it more than once.
        ///
        /// Property values are clamped to [0, 10]. A property reduced to 0 is removed.
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///
        ///   1. In your mutation lab widget or UBeamFarmSubsystem, call the auto-generated
        ///      BeamFarmMsMutateWithModifiers Blueprint node.
        ///   2. Pass:
        ///        plantItemContentId  → the itemplant.* content ID of the item to modify
        ///        plantItemInstanceId → the int64 instance ID from the inventory response
        ///        modifierContentIds  → array of plant_modifier.* content IDs to consume
        ///   3. On success, use MutateWithModifiersResult.newProperties to refresh your UI.
        ///      The Beamable SDK will also push an inventory update automatically.
        ///
        /// NOTE: Run `dotnet beam generate` after modifying this file to regenerate
        /// the Blueprint-callable BeamFarmMsMutateWithModifiers node.
        /// ═════════════════════════════════════════════════════════════════════
        /// </summary>
        [ClientCallable]
        public async Task<MutateWithModifiersResult> MutateWithModifiers(
            string plantItemContentId,
            long plantItemInstanceId,
            List<string> modifierContentIds)
        {
            // ── Input validation ──────────────────────────────────────────────
            if (string.IsNullOrWhiteSpace(plantItemContentId))
                return ModifyFail("plantItemContentId must not be empty.");

            if (plantItemInstanceId <= 0)
                return ModifyFail("plantItemInstanceId must be a valid positive instance ID.");

            if (modifierContentIds == null || modifierContentIds.Count == 0)
                return ModifyFail("At least one modifier content ID must be provided.");

            foreach (var id in modifierContentIds)
            {
                if (string.IsNullOrWhiteSpace(id))
                    return ModifyFail("modifierContentIds must not contain empty entries.");
            }

            // ── Load player inventory (items + currencies in one call) ─────────
            var inventory = await Services.Inventory.GetCurrent("items,currency");

            // ── Find the target plant item instance ───────────────────────────
            ItemView plantItem = null;
            if (inventory?.items != null &&
                inventory.items.TryGetValue(plantItemContentId, out var itemGroup))
            {
                plantItem = itemGroup?.FirstOrDefault(i => i.id == plantItemInstanceId);
            }

            if (plantItem == null)
                return ModifyFail(
                    $"Plant item instance {plantItemInstanceId} (contentId='{plantItemContentId}') not found in inventory.");

            // ── Count how many of each modifier are required ───────────────────
            var requiredCounts = modifierContentIds
                .GroupBy(id => id)
                .ToDictionary(g => g.Key, g => g.Count());

            // ── Verify the player owns enough modifier currency ────────────────
            foreach (var (modId, needed) in requiredCounts)
            {
                long owned = inventory.currencies != null &&
                    inventory.currencies.TryGetValue(modId, out var ownedVal) ? ownedVal : 0;

                if (owned < needed)
                    return ModifyFail(
                        $"Insufficient '{modId}': need {needed}, have {owned}.");
            }

            // ── Load each unique modifier content definition ───────────────────
            var modifierContents = new Dictionary<string, ModifierItemContent>();
            foreach (var modId in requiredCounts.Keys)
            {
                ModifierItemContent modContent;
                try
                {
                    modContent = await Services.Content.GetContent<ModifierItemContent>(
                        new ContentRef(typeof(ModifierItemContent), modId));
                }
                catch (Exception ex)
                {
                    return ModifyFail($"Failed to load modifier content '{modId}': {ex.Message}");
                }

                if (modContent == null)
                    return ModifyFail($"Modifier content '{modId}' not found. Was it unpublished?");

                modifierContents[modId] = modContent;
            }

            // ── Apply modifier deltas to current item properties ──────────────
            var newProps = plantItem.properties != null
                ? new Dictionary<string, string>(plantItem.properties)
                : new Dictionary<string, string>();

            foreach (var modId in modifierContentIds)
            {
                var modContent = modifierContents[modId];
                if (modContent.propertyModifiers == null) continue;

                foreach (var delta in modContent.propertyModifiers)
                {
                    if (string.IsNullOrWhiteSpace(delta.PropertyName)) continue;

                    newProps.TryGetValue(delta.PropertyName, out var currentStr);
                    int current = int.TryParse(currentStr, out var parsed) ? parsed : 0;
                    int updated = Math.Max(0, Math.Min(10, current + delta.Delta));

                    if (updated == 0)
                        newProps.Remove(delta.PropertyName);
                    else
                        newProps[delta.PropertyName] = updated.ToString();
                }
            }

            // ── Build inventory update: delete plant, re-add with new props,
            //    and consume modifier currencies ─────────────────────────────
            var updateBuilder = new InventoryUpdateBuilder();
            updateBuilder.DeleteItem(plantItemContentId, plantItemInstanceId);
            updateBuilder.AddItem(plantItemContentId, newProps);

            foreach (var (modId, count) in requiredCounts)
                updateBuilder.CurrencyChange(modId, -count);

            await Services.Inventory.Update(updateBuilder);

            return new MutateWithModifiersResult
            {
                success = true,
                newProperties = newProps,
                message = $"Applied {modifierContentIds.Count} modifier(s) to '{plantItemContentId}' instance {plantItemInstanceId}."
            };
        }

        private static MutateWithModifiersResult ModifyFail(string message) =>
            new MutateWithModifiersResult
            {
                success = false,
                newProperties = new Dictionary<string, string>(),
                message = message
            };
    }
}
