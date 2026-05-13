using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
    // ──────────────────────────────────────────────────────────────────────────
    // Request / Response types
    // ──────────────────────────────────────────────────────────────────────────

    [Serializable]
    public class MutationInput
    {
        /// <summary>Beamable content ID of the raw material currency (plant.raw.material.*).</summary>
        public string itemContentId;
        /// <summary>How many units of this material to consume.</summary>
        public int quantity;
    }

    [Serializable]
    public class MutationOutput
    {
        /// <summary>Beamable content ID of the produced crop item (itemplant.*).</summary>
        public string itemContentId;
        /// <summary>How many crop items were produced.</summary>
        public int quantity;
    }

    [Serializable]
    public class MutationResult
    {
        public bool success;
        public List<MutationOutput> outputs;
        public string message;
    }

    // ──────────────────────────────────────────────────────────────────────────
    // Mutation Lab microservice methods
    // ──────────────────────────────────────────────────────────────────────────

    public partial class BeamFarmMs
    {
        // Conversion ratio: units of raw material required to produce 1 crop item.
        private const int MaterialsPerCrop = 5;

        /// <summary>
        /// Consumes the provided raw materials from the calling player's inventory and
        /// produces mutated crop items according to the MaterialsPerCrop ratio.
        ///
        /// Raw materials are Beamable currencies (plant.raw.material.*).
        /// Produced crops are Beamable items (itemplant.*).
        ///
        /// Content ID mapping convention:
        ///   plant.raw.material.green_spore  →  itemplant.green_spore
        ///
        /// The Unreal client calls this via the auto-generated BeamFarmMsMutate Blueprint node
        /// (regenerated with `dotnet beam generate` after adding this file).
        /// </summary>
        [ClientCallable]
        public async Task<MutationResult> Mutate(List<MutationInput> inputs)
        {
            if (inputs == null || inputs.Count == 0)
            {
                return Fail("No inputs provided.");
            }

            // Validate all inputs before touching inventory.
            foreach (var input in inputs)
            {
                if (string.IsNullOrEmpty(input.itemContentId) || input.quantity <= 0)
                {
                    return Fail($"Invalid input: contentId='{input.itemContentId}' quantity={input.quantity}");
                }

                if (input.quantity < MaterialsPerCrop)
                {
                    return Fail($"Need at least {MaterialsPerCrop} units of '{input.itemContentId}' to mutate (provided {input.quantity}).");
                }
            }

            // Verify the player actually has the required currency amounts.
            var inventoryView = await Services.Inventory.GetCurrent(Context.UserId);
            foreach (var input in inputs)
            {
                var currency = inventoryView.currencies
                    .FirstOrDefault(c => c.id == input.itemContentId);
                long owned = currency?.amount ?? 0L;
                if (owned < input.quantity)
                {
                    return Fail($"Insufficient '{input.itemContentId}': need {input.quantity}, have {owned}.");
                }
            }

            // Build the inventory update: deduct materials, grant crops.
            var updateBuilder = new InventoryUpdateBuilder();
            var outputs = new List<MutationOutput>();

            foreach (var input in inputs)
            {
                // Deduct materials (negative currency delta).
                updateBuilder.CurrencyChange(input.itemContentId, -input.quantity);

                // Determine output content ID and quantity.
                string outputId = DeriveCropContentId(input.itemContentId);
                int outputQty = Math.Max(1, input.quantity / MaterialsPerCrop);

                // Grant output crop items.
                for (int i = 0; i < outputQty; i++)
                {
                    updateBuilder.AddItem(outputId, new Dictionary<string, string>());
                }

                outputs.Add(new MutationOutput { itemContentId = outputId, quantity = outputQty });
            }

            await Services.Inventory.Update(updateBuilder);

            return new MutationResult
            {
                success = true,
                outputs = outputs,
                message = $"Mutation complete! Produced {outputs.Sum(o => o.quantity)} item(s)."
            };
        }

        /// <summary>
        /// Derives the crop content ID from a raw material content ID.
        /// Convention: "plant.raw.material.green_spore" → "itemplant.green_spore"
        /// Override this logic to customise the mapping for your content structure.
        /// </summary>
        private static string DeriveCropContentId(string materialContentId)
        {
            const string prefix = "plant.raw.material.";
            if (materialContentId.StartsWith(prefix))
            {
                return "itemplant." + materialContentId.Substring(prefix.Length);
            }
            // Fallback: append to base itemplant namespace.
            return "itemplant." + materialContentId;
        }

        private static MutationResult Fail(string message) =>
            new MutationResult { success = false, outputs = new List<MutationOutput>(), message = message };
    }
}
