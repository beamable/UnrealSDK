/**
 * Types for the BeamFarmMs microservice client.
 *
 * Mirrors the Beamable web-client generator output. The generated client
 * (BeamFarmMsClient.ts) exposes the whole service, so this file declares every
 * endpoint's types — push (used by this extension's UI) and gameplay (unused here,
 * but referenced by the generated client, so they must resolve). Re-run
 * `beam portal extension add-microservice PushNotifications BeamFarmMs`
 * to regenerate once the realm's portal-config endpoint is reachable.
 */

export type RegisterResult = {
  success: boolean;
  deviceCount: number;
  message: string;
};

export type RegisterDeviceTokenRequestArgs = {
  token: string;
  environment: string;
  platform: string;
};

export type UnregisterResult = {
  success: boolean;
  deviceCount: number;
  message: string;
};

export type UnregisterDeviceTokenRequestArgs = {
  token: string;
};

export type DeviceInfo = {
  token: string;
  platform: string;
  environment: string;
  updatedAt: bigint | string;
};

export type DeviceList = {
  devices: DeviceInfo[];
};

export type SendResult = {
  success: boolean;
  attempted: number;
  succeeded: number;
  failed: number;
  messages: string[];
};

export type SendPushToSelfRequestArgs = {
  title: string;
  body: string;
  deepLink: string;
};

export type AdminSendResult = {
  success: boolean;
  attempted: number;
  succeeded: number;
  failed: number;
  messages: string[];
};

export type SendPushToPlayerRequestArgs = {
  playerId: bigint | string;
  title: string;
  body: string;
  deepLink: string;
};

/** A player with at least one registered device (no token is exposed). */
export type RegisteredPlayer = {
  playerId: bigint | string;
  deviceCount: number;
  platforms: string[]; // distinct: "apns" and/or "fcm"
  lastUpdated: bigint | string; // newest device's updatedAt (unix seconds)
};

/** Roster returned by ListRegisteredPlayers. */
export type RegisteredPlayerList = {
  players: RegisteredPlayer[];
  message?: string; // set only when the roster couldn't be produced
};

/** Secret-free result of CheckFcmConfig — never carries the private key. */
export type FcmConfigStatus = {
  configured: boolean;
  privateKeyLoaded: boolean;
  projectId: string;
  clientEmail: string;
  tokenUri: string;
  message: string;
};

// ---------------------------------------------------------------------------
// Gameplay endpoints — not used by this extension's UI, but the generated
// BeamFarmMsClient exposes the whole service, so these must resolve.
// Derived from BeamFarmMs.Gameplay.cs.
// ---------------------------------------------------------------------------

// PlantSeed(string seedContentId, string slotId)
export type PlantSeedRequestArgs = {
  seedContentId: string;
  slotId: string;
};

// C# PlantResult
export type PlantResult = {
  success: boolean;
  plantedAtUtcSeconds: bigint | string;
  message: string;
};

// CollectHarvest(string slotId)
export type CollectHarvestRequestArgs = {
  slotId: string;
};

// C# CollectResult
export type CollectResult = {
  success: boolean;
  harvestedItemContentId: string;
  message: string;
};

// GetSlotStates(List<string> slotIds)
export type GetSlotStatesRequestArgs = {
  slotIds: string[];
};

// C# SlotStateEntry
export type SlotStateEntry = {
  slotId: string;
  seedId: string;
  harvestId: string;
  plantedAt: bigint | string;
  growSecs: number;
};

// C# GetSlotStatesResult
export type GetSlotStatesResult = {
  success: boolean;
  slots: SlotStateEntry[];
  message: string;
};

// RegisterGroundItem(string groundItemId, string contentId, int quantity, string itemType, float posX, float posY, float posZ, string spawnerId)
export type RegisterGroundItemRequestArgs = {
  groundItemId: string;
  contentId: string;
  quantity: number;
  itemType: string;
  posX: number;
  posY: number;
  posZ: number;
  spawnerId: string;
};

// C# RegisterGroundItemResult
export type RegisterGroundItemResult = {
  success: boolean;
  message: string;
};

// CollectGroundItem(string groundItemId)
export type CollectGroundItemRequestArgs = {
  groundItemId: string;
};

// C# CollectGroundItemResult
export type CollectGroundItemResult = {
  success: boolean;
  grantedContentId: string;
  grantedQuantity: number;
  message: string;
};

// GetGroundItems(string spawnerId)
export type GetGroundItemsRequestArgs = {
  spawnerId: string;
};

// C# GroundItemEntry
export type GroundItemEntry = {
  groundItemId: string;
  contentId: string;
  quantity: number;
  itemType: string;
  posX: number;
  posY: number;
  posZ: number;
};

// C# GetGroundItemsResult
export type GetGroundItemsResult = {
  success: boolean;
  items: GroundItemEntry[];
  message: string;
};

// C# DeliveryRequirement
export type DeliveryRequirement = {
  propertyName: string;
  comparison: string;
  value: number;
};

// C# DeliveryOrderInfo
export type DeliveryOrderInfo = {
  orderId: string;
  displayName: string;
  requiredItemContentId: string;
  requirements: DeliveryRequirement[];
  rewardCurrencyId: string;
  rewardAmount: number;
};

// C# GetDeliveryOrdersResult (GetDeliveryOrders takes no args)
export type GetDeliveryOrdersResult = {
  success: boolean;
  orders: DeliveryOrderInfo[];
  message: string;
};

// C# FillDeliveryOrdersResult (FillDeliveryOrders takes no args)
export type FillDeliveryOrdersResult = {
  success: boolean;
  ordersAdded: number;
  totalOrders: number;
  message: string;
};

// DeliverOrder(string orderId, long itemInstanceId)
export type DeliverOrderRequestArgs = {
  orderId: string;
  itemInstanceId: bigint | string;
};

// C# DeliverOrderResult
export type DeliverOrderResult = {
  success: boolean;
  orderId: string;
  rewardCurrencyId: string;
  rewardAmount: number;
  message: string;
};

// MutateWithModifiers(string plantItemContentId, long plantItemInstanceId, List<string> modifierContentIds)
export type MutateWithModifiersRequestArgs = {
  plantItemContentId: string;
  plantItemInstanceId: bigint | string;
  modifierContentIds: string[];
};

// C# MutateWithModifiersResult
export type MutateWithModifiersResult = {
  success: boolean;
  newProperties: Record<string, string>;
  message: string;
};

// StartResearch(long itemInstanceId, string itemContentId)
export type StartResearchRequestArgs = {
  itemInstanceId: bigint | string;
  itemContentId: string;
};

// C# StartResearchResult
export type StartResearchResult = {
  success: boolean;
  startedAtUtcSeconds: bigint | string;
  pointsSpent: number;
  message: string;
};

// CollectResearch(long itemInstanceId, string itemContentId)
export type CollectResearchRequestArgs = {
  itemInstanceId: bigint | string;
  itemContentId: string;
};

// C# CollectResearchResult
export type CollectResearchResult = {
  success: boolean;
  outputContentId: string;
  outputQuantity: number;
  outputType: string;
  message: string;
};

// C# GetPlayerLevelResult (GetPlayerLevel takes no args)
export type GetPlayerLevelResult = {
  success: boolean;
  level: number;
  totalXp: number;
  xpForCurrentLevel: number;
  xpIntoCurrentLevel: number;
  message: string;
};
