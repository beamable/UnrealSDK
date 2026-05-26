using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common.Api.Inventory;
using Beamable.Common.Api.Stats;
using Beamable.Common.Content;
using Beamable.Server;
using UnityEngine.Serialization;

namespace Beamable.BeamFarmMs
{
    // ══════════════════════════════════════════════════════════════════════════
    // DELIVERY ENUMS
    // ══════════════════════════════════════════════════════════════════════════

    public enum DeliveryComparison
    {
        GreaterThan,
        LowerThan
    }

    // ══════════════════════════════════════════════════════════════════════════
    // DELIVERY DATA MODELS
    // ══════════════════════════════════════════════════════════════════════════

    /// <summary>
    /// A single property rule an item must satisfy to fulfil a delivery order.
    /// Stored inside DeliveryOrderContent and returned to the client inside DeliveryOrderInfo.
    ///
    /// Rules:
    ///   comparison = "GreaterThan"  →  item property value  >  value
    ///   comparison = "LowerThan"    →  item property value  &lt;  value
    ///
    /// If the item is missing the property, its effective value is 0.
    /// </summary>
    [Serializable]
    public class DeliveryRequirement
    {
        /// <summary>
        /// Name of the plant property to check.
        /// Must match one of the BeamFarmPlantPropertyType enum names:
        /// "Corrosive", "Mutagenic", "Radioactive".
        /// </summary>
        [FormerlySerializedAs("PropertyName")] public string propertyName;

        /// <summary>"GreaterThan" or "LowerThan" — matches DeliveryComparison enum names.</summary>
        [FormerlySerializedAs("Comparison")] public string comparison;

        /// <summary>Threshold value for the comparison.</summary>
        [FormerlySerializedAs("Value")] public int value;
    }

    // ──────────────────────────────────────────────────────────────────────────
    // CONTENT TYPES
    //   Create these in the Beamable Portal / Content Manager:
    //     delivery_order.*        — one entry per possible order type
    //     delivery_order_config.default — single pool configuration
    // ──────────────────────────────────────────────────────────────────────────

    /// <summary>
    /// Template for a single delivery order.
    /// Content type ID: "delivery_order"
    ///
    /// Example content IDs: "delivery_order.corrosive_demand", "delivery_order.high_energy_spore"
    ///
    /// Unreal integration:
    ///   Create matching content entries in the Beamable content browser.
    ///   The Unreal client receives the resolved data as FBeamDeliveryOrderInfo
    ///   via GetDeliveryOrders — no C++ content class is required on the client side.
    /// </summary>
    [Serializable]
    [ContentType("delivery_order")]
    public class DeliveryOrderContent : ContentObject
    {
        /// <summary>Human-readable name shown in the delivery panel UI.</summary>
        [FormerlySerializedAs("DisplayName")] public string displayName;

        /// <summary>
        /// Content ID of the plant item type the player must deliver (itemplant.*).
        /// Example: "itemplant.green_spore"
        /// </summary>
        [FormerlySerializedAs("RequiredItemContentId")] public string requiredItemContentId;

        /// <summary>
        /// Property rules the delivered item instance must all satisfy.
        /// An empty list means any instance of requiredItemContentId is accepted.
        /// </summary>
        [FormerlySerializedAs("Requirements")] public List<DeliveryRequirement> requirements;

        /// <summary>
        /// Beamable currency content ID granted as reward.
        /// Example: "currency_crystals"
        /// </summary>
        [FormerlySerializedAs("RewardCurrencyId")] public string rewardCurrencyId;

        /// <summary>Amount of rewardCurrencyId granted on successful delivery.</summary>
        [FormerlySerializedAs("RewardAmount")] public int rewardAmount;
    }

    /// <summary>
    /// Pool configuration — controls which orders can appear and how many run concurrently.
    /// Content type ID: "delivery_order_config"
    ///
    /// Publish a single entry with content ID "delivery_order_config.default".
    /// The server fetches this when filling player order slots.
    /// </summary>
    [Serializable]
    [ContentType("delivery_order_config")]
    public class DeliveryOrderPoolConfig : ContentObject
    {
        /// <summary>How many active delivery orders a player should always have available.</summary>
        [FormerlySerializedAs("MaxActiveOrders")] public int maxActiveOrders = 3;

        /// <summary>
        /// Full content IDs of all possible delivery orders to draw from.
        /// Example: ["delivery_order.corrosive_demand", "delivery_order.radioactive_harvest"]
        /// </summary>
        [FormerlySerializedAs("OrderPool")] public List<string> orderPool;
    }

    // ──────────────────────────────────────────────────────────────────────────
    // PLAYER STATE MODEL (stored in game stats)
    // ──────────────────────────────────────────────────────────────────────────

    [Serializable]
    public class ActiveDeliveryOrder
    {
        /// <summary>Content ID of the delivery_order.* assigned to this player.</summary>
        public string orderId;

        /// <summary>Unix timestamp (UTC seconds) when this order was assigned.</summary>
        public long assignedAt;
    }

    // ──────────────────────────────────────────────────────────────────────────
    // RESULT MODELS (returned to Unreal client)
    // ──────────────────────────────────────────────────────────────────────────

    /// <summary>Full order description returned to the Unreal client by GetDeliveryOrders.</summary>
    [Serializable]
    public class DeliveryOrderInfo
    {
        public string orderId;
        public string displayName;
        public string requiredItemContentId;
        public List<DeliveryRequirement> requirements;
        public string rewardCurrencyId;
        public int rewardAmount;
    }

    [Serializable]
    public class GetDeliveryOrdersResult
    {
        public bool success;
        public List<DeliveryOrderInfo> orders;
        public string message;
    }

    [Serializable]
    public class FillDeliveryOrdersResult
    {
        public bool success;
        public int ordersAdded;
        public int totalOrders;
        public string message;
    }

    [Serializable]
    public class DeliverOrderResult
    {
        public bool success;
        public string orderId;
        public string rewardCurrencyId;
        public int rewardAmount;
        public string message;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // MICROSERVICE DELIVERY IMPLEMENTATION
    // ══════════════════════════════════════════════════════════════════════════

    public partial class BeamFarmMs
    {
        // ─── Constants ────────────────────────────────────────────────────────

        /// <summary>
        /// Stat key that stores the player's active delivery order list as JSON.
        /// Value: JSON-serialised List&lt;ActiveDeliveryOrder&gt;
        /// </summary>
        private const string DeliveryActiveOrdersStatKey = "delivery_active_orders";

        /// <summary>
        /// Content ID of the singleton DeliveryOrderPoolConfig.
        /// Publish one entry in the Beamable content browser with this exact ID.
        /// </summary>
        private const string DeliveryPoolConfigContentId = "delivery_order_config.global";

        // ──────────────────────────────────────────────────────────────────────
        // GET DELIVERY ORDERS
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Returns the player's active delivery orders, auto-filling up to MaxActiveOrders
        /// if the player currently has fewer than the configured target.
        ///
        /// Call this when the delivery panel opens or when refreshing after a delivery.
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///   1. Call UBeamFarmSubsystem::GetDeliveryOrders() from Blueprint.
        ///   2. Bind to UBeamFarmSubsystem::OnDeliveryOrdersReceived.
        ///   3. In the delegate, call UBeamFarmDeliveryWidget::HandleDeliveryOrdersReceived
        ///      (wired automatically by UBeamFarmDeliveryWidget::NativeConstruct).
        /// ═════════════════════════════════════════════════════════════════════
        /// </summary>
        [ClientCallable]
        public async Task<GetDeliveryOrdersResult> GetDeliveryOrders()
        {
            // Always attempt to fill before returning so the player sees a full slate.
            await FillDeliveryOrdersInternal();

            List<ActiveDeliveryOrder> activeOrders = await LoadActiveOrders();
            if (activeOrders.Count == 0)
            {
                return new GetDeliveryOrdersResult
                {
                    success = true,
                    orders  = new List<DeliveryOrderInfo>(),
                    message = "No delivery orders available. Ensure 'delivery_order_config.default' is published."
                };
            }

            var orderInfos = new List<DeliveryOrderInfo>();
            foreach (var active in activeOrders)
            {
                try
                {
                    var content = await Services.Content.GetContent<DeliveryOrderContent>(
                        new ContentRef(typeof(DeliveryOrderContent), active.orderId));

                    if (content == null) continue;

                    orderInfos.Add(new DeliveryOrderInfo
                    {
                        orderId               = active.orderId,
                        displayName           = content.displayName ?? active.orderId,
                        requiredItemContentId = content.requiredItemContentId,
                        requirements          = content.requirements ?? new List<DeliveryRequirement>(),
                        rewardCurrencyId      = content.rewardCurrencyId,
                        rewardAmount          = content.rewardAmount
                    });
                }
                catch
                {
                    // Skip orders whose content has been unpublished; they'll be pruned on next fill.
                }
            }

            return new GetDeliveryOrdersResult
            {
                success = true,
                orders  = orderInfos,
                message = $"Loaded {orderInfos.Count} delivery order(s)."
            };
        }

        // ──────────────────────────────────────────────────────────────────────
        // FILL DELIVERY ORDERS
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Ensures the player always has MaxActiveOrders delivery orders available.
        /// Picks random, non-duplicate orders from the pool configured in
        /// "delivery_order_config.default".
        ///
        /// This is also called automatically by GetDeliveryOrders and DeliverOrder,
        /// so most clients never need to call it explicitly.
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///   Call UBeamFarmSubsystem::FillDeliveryOrders() on first login or after
        ///   a session gap to make sure the player's slate is fresh.
        /// ═════════════════════════════════════════════════════════════════════
        /// </summary>
        [ClientCallable]
        public async Task<FillDeliveryOrdersResult> FillDeliveryOrders()
        {
            int added = await FillDeliveryOrdersInternal();
            List<ActiveDeliveryOrder> after = await LoadActiveOrders();

            return new FillDeliveryOrdersResult
            {
                success     = true,
                ordersAdded = added,
                totalOrders = after.Count,
                message     = $"Added {added} order(s). Total active: {after.Count}."
            };
        }

        /// <summary>
        /// Internal fill logic. Returns the number of orders added.
        /// Safe to call multiple times; does nothing when slots are already full.
        /// </summary>
        private async Task<int> FillDeliveryOrdersInternal()
        {
            // Load pool configuration
            DeliveryOrderPoolConfig poolConfig;
            try
            {
                poolConfig = await Services.Content.GetContent<DeliveryOrderPoolConfig>(
                    new ContentRef(typeof(DeliveryOrderPoolConfig), DeliveryPoolConfigContentId));
            }
            catch
            {
                return 0; // Config not published — nothing to fill
            }

            if (poolConfig?.orderPool == null || poolConfig.orderPool.Count == 0)
                return 0;

            List<ActiveDeliveryOrder> activeOrders = await LoadActiveOrders();
            int needed = poolConfig.maxActiveOrders - activeOrders.Count;
            if (needed <= 0) return 0;

            // Build the set of order IDs that are already active
            var activeIds = new HashSet<string>(activeOrders.Select(o => o.orderId));

            // Available candidates: pool entries not currently active
            var available = poolConfig.orderPool
                .Where(id => !string.IsNullOrWhiteSpace(id) && !activeIds.Contains(id))
                .ToList();

            if (available.Count == 0) return 0;

            // Fisher-Yates shuffle for unbiased random selection
            var rng = new Random();
            for (int i = available.Count - 1; i > 0; i--)
            {
                int j = rng.Next(i + 1);
                (available[i], available[j]) = (available[j], available[i]);
            }

            int toAdd = Math.Min(needed, available.Count);
            long now  = DateTimeOffset.UtcNow.ToUnixTimeSeconds();

            for (int i = 0; i < toAdd; i++)
            {
                activeOrders.Add(new ActiveDeliveryOrder
                {
                    orderId    = available[i],
                    assignedAt = now
                });
            }

            await SaveActiveOrders(activeOrders);
            return toAdd;
        }

        // ──────────────────────────────────────────────────────────────────────
        // DELIVER ORDER
        // ──────────────────────────────────────────────────────────────────────

        /// <summary>
        /// Validates that the given item instance satisfies the order's requirements,
        /// removes the item from the player's inventory, grants the reward currency, and
        /// removes the completed order from the active list (triggering an auto-refill).
        ///
        /// Validation steps (in order):
        ///   1. orderId is in the player's active order list.
        ///   2. itemInstanceId exists in the player's inventory.
        ///   3. Item's contentId matches the order's requiredItemContentId.
        ///   4. Each DeliveryRequirement passes (GreaterThan / LowerThan on item properties).
        ///
        /// ═══ Unreal integration ═══════════════════════════════════════════
        ///   1. In UBeamFarmDeliveryWidget::ConfirmDelivery, the widget calls
        ///      UBeamFarmSubsystem::DeliverOrder(OrderId, ItemInstanceId).
        ///   2. The subsystem fires OnDeliveryCompleted or OnDeliveryFailed.
        ///   3. The widget handles both via its delegate bindings in NativeConstruct.
        ///
        /// ItemInstanceId:
        ///   Beamable item instance IDs are int64 (long). Expose them from the
        ///   Beamable inventory response in Blueprint and pass to SelectItemForDelivery.
        /// ═════════════════════════════════════════════════════════════════════
        /// </summary>
        [ClientCallable]
        public async Task<DeliverOrderResult> DeliverOrder(string orderId, long itemInstanceId)
        {
            // ── Input validation ──────────────────────────────────────────────
            if (string.IsNullOrWhiteSpace(orderId))
                return DeliverFail(orderId, "orderId must not be empty.");

            // ── Verify order is active for this player ────────────────────────
            List<ActiveDeliveryOrder> activeOrders = await LoadActiveOrders();
            if (!activeOrders.Any(o => o.orderId == orderId))
                return DeliverFail(orderId, $"Order '{orderId}' is not in your active delivery orders.");

            // ── Load order content ────────────────────────────────────────────
            DeliveryOrderContent orderContent;
            try
            {
                orderContent = await Services.Content.GetContent<DeliveryOrderContent>(
                    new ContentRef(typeof(DeliveryOrderContent), orderId));
            }
            catch (Exception ex)
            {
                return DeliverFail(orderId, $"Failed to load order content '{orderId}': {ex.Message}");
            }

            if (orderContent == null)
                return DeliverFail(orderId, $"Order content '{orderId}' not found. Was it unpublished?");

            if (string.IsNullOrWhiteSpace(orderContent.requiredItemContentId))
                return DeliverFail(orderId, $"Order '{orderId}' has no requiredItemContentId configured.");

            if (string.IsNullOrWhiteSpace(orderContent.rewardCurrencyId))
                return DeliverFail(orderId, $"Order '{orderId}' has no rewardCurrencyId configured.");

            // ── Find the item instance in the player's inventory ──────────────
            // Items are grouped by contentId: Dictionary<string, List<ItemView>>
            var inventory = await Services.Inventory.GetCurrent("items");

            ItemView itemInstance = null;
            if (inventory?.items != null &&
                inventory.items.TryGetValue(orderContent.requiredItemContentId, out var itemGroup))
            {
                itemInstance = itemGroup?.FirstOrDefault(i => i.id == itemInstanceId);
            }

            if (itemInstance == null)
                return DeliverFail(orderId,
                    $"Item instance {itemInstanceId} of type '{orderContent.requiredItemContentId}' " +
                    "not found in your inventory. Make sure you selected the correct item.");

            // ── Validate property requirements ────────────────────────────────
            if (orderContent.requirements != null)
            {
                foreach (var req in orderContent.requirements)
                {
                    if (string.IsNullOrWhiteSpace(req.propertyName)) continue;
                    
                    string propertyValue = "";
                    if (!itemInstance.properties.TryGetValue(req.propertyName, out propertyValue))
                    {
                        return DeliverFail(orderId,
                            $"Item property '{req.propertyName}' = property does exist to satisfy: " +
                            $"{req.comparison} {req.value}.");
                    }

                    int propValue = 0;
                    if (!string.IsNullOrEmpty(propertyValue))
                        int.TryParse(propertyValue, out propValue);

                    bool passes = req.comparison == nameof(DeliveryComparison.GreaterThan)
                        ? propValue > req.value
                        : propValue < req.value;

                    if (!passes)
                        return DeliverFail(orderId,
                            $"Item property '{req.propertyName}' = {propValue} does not satisfy: " +
                            $"{req.comparison} {req.value}.");
                }
            }

            // ── All checks passed — execute the delivery ──────────────────────
            // Delete item first, then grant currency in one atomic inventory update.
            var updateBuilder = new InventoryUpdateBuilder();
            updateBuilder.DeleteItem(itemInstance.contentId, itemInstanceId);
            updateBuilder.CurrencyChange(orderContent.rewardCurrencyId, orderContent.rewardAmount);
            await Services.Inventory.Update(updateBuilder);

            // ── Remove order from active list and refill ──────────────────────
            activeOrders.RemoveAll(o => o.orderId == orderId);
            await SaveActiveOrders(activeOrders);

            // Refill asynchronously so the player's slate stays at MaxActiveOrders.
            await FillDeliveryOrdersInternal();

            return new DeliverOrderResult
            {
                success          = true,
                orderId          = orderId,
                rewardCurrencyId = orderContent.rewardCurrencyId,
                rewardAmount     = orderContent.rewardAmount,
                message          = $"Delivered '{orderContent.requiredItemContentId}' for order '{orderId}'. " +
                                   $"Rewarded {orderContent.rewardAmount} of '{orderContent.rewardCurrencyId}'."
            };
        }

        // ──────────────────────────────────────────────────────────────────────
        // PLAYER STATE HELPERS
        // ──────────────────────────────────────────────────────────────────────

        private async Task<List<ActiveDeliveryOrder>> LoadActiveOrders()
        {
            string json = await GetSlotStat(DeliveryActiveOrdersStatKey);
            if (string.IsNullOrEmpty(json))
                return new List<ActiveDeliveryOrder>();

            try
            {
                return Newtonsoft.Json.JsonConvert.DeserializeObject<List<ActiveDeliveryOrder>>(json)
                    ?? new List<ActiveDeliveryOrder>();
            }
            catch
            {
                return new List<ActiveDeliveryOrder>();
            }
        }

        private async Task SaveActiveOrders(List<ActiveDeliveryOrder> orders)
        {
            string json = Newtonsoft.Json.JsonConvert.SerializeObject(orders);
            await SetSlotStat(DeliveryActiveOrdersStatKey, json);
        }

        // ──────────────────────────────────────────────────────────────────────
        // ERROR HELPERS
        // ──────────────────────────────────────────────────────────────────────

        private static DeliverOrderResult DeliverFail(string orderId, string message) =>
            new DeliverOrderResult
            {
                success          = false,
                orderId          = orderId ?? string.Empty,
                rewardCurrencyId = string.Empty,
                rewardAmount     = 0,
                message          = message
            };

        private static GetDeliveryOrdersResult GetOrdersFail(string message) =>
            new GetDeliveryOrdersResult
            {
                success = false,
                orders  = new List<DeliveryOrderInfo>(),
                message = message
            };
    }
}
