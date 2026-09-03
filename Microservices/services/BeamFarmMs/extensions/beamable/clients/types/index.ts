/**
 * ⚠️ THIS FILE IS AUTO-GENERATED. DO NOT EDIT MANUALLY.
 * All manual edits will be lost when this file is regenerated.
 */

export type Record<string, PerPlayerMatchResult> = { 
};

export type MatchResult = { 
  PerPlayerMatchResults: Record<string, PerPlayerMatchResult>; 
};

export type BeamballPlayerInfo = { 
  GamerTag: string; 
  Life: number; 
};

export type BeamballTeamInfo = { 
  TeamName: string; 
  Players: BeamballPlayerInfo[]; 
};

export type ProcessMatchResultRequestArgs = { 
  teamInfos: BeamballTeamInfo[]; 
  lobbyId: string; 
};

export type DiscordWhitelistedInfo = { 
  matchmaking_discord_whitelisted: boolean; 
};

export type SetEdgegapLocationRequestArgs = { 
  latitude: number; 
  longitude: number; 
};

export type UpgradeItemRequestArgs = { 
  gamerTag: bigint | string; 
  itemInstaceID: bigint | string; 
};

export type IncrementStatRequestArgs = { 
  gamerTag: bigint | string; 
};

export type GetSampleStatRequestArgs = { 
  gamerTag: bigint | string; 
};

export type PlantResult = { 
  success: boolean; 
  plantedAtUtcSeconds: bigint | string; 
  message: string; 
};

export type PlantSeedRequestArgs = { 
  seedContentId: string; 
  slotId: string; 
};

export type CollectResult = { 
  success: boolean; 
  harvestedItemContentId: string; 
  message: string; 
};

export type CollectHarvestRequestArgs = { 
  slotId: string; 
};

export type SlotStateEntry = { 
  slotId: string; 
  seedId: string; 
  harvestId: string; 
  plantedAt: bigint | string; 
  growSecs: number; 
};

export type GetSlotStatesResult = { 
  success: boolean; 
  slots: SlotStateEntry[]; 
  message: string; 
};

export type GetSlotStatesRequestArgs = { 
  slotIds: string[]; 
};

export type RegisterGroundItemResult = { 
  success: boolean; 
  message: string; 
};

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

export type CollectGroundItemResult = { 
  success: boolean; 
  grantedContentId: string; 
  grantedQuantity: number; 
  message: string; 
};

export type CollectGroundItemRequestArgs = { 
  groundItemId: string; 
};

export type GroundItemEntry = { 
  groundItemId: string; 
  contentId: string; 
  quantity: number; 
  itemType: string; 
  posX: number; 
  posY: number; 
  posZ: number; 
};

export type GetGroundItemsResult = { 
  success: boolean; 
  items: GroundItemEntry[]; 
  message: string; 
};

export type GetGroundItemsRequestArgs = { 
  spawnerId: string; 
};

export type DeliveryRequirement = { 
  propertyName: string; 
  comparison: string; 
  value: number; 
};

export type DeliveryOrderInfo = { 
  orderId: string; 
  displayName: string; 
  requiredItemContentId: string; 
  requirements: DeliveryRequirement[]; 
  rewardCurrencyId: string; 
  rewardAmount: number; 
};

export type GetDeliveryOrdersResult = { 
  success: boolean; 
  orders: DeliveryOrderInfo[]; 
  message: string; 
};

export type FillDeliveryOrdersResult = { 
  success: boolean; 
  ordersAdded: number; 
  totalOrders: number; 
  message: string; 
};

export type DeliverOrderResult = { 
  success: boolean; 
  orderId: string; 
  rewardCurrencyId: string; 
  rewardAmount: number; 
  message: string; 
};

export type DeliverOrderRequestArgs = { 
  orderId: string; 
  itemInstanceId: bigint | string; 
};

export type Record<string, string> = { 
};

export type MutateWithModifiersResult = { 
  success: boolean; 
  newProperties: Record<string, string>; 
  message: string; 
};

export type MutateWithModifiersRequestArgs = { 
  plantItemContentId: string; 
  plantItemInstanceId: bigint | string; 
  modifierContentIds: string[]; 
};

export type StartResearchResult = { 
  success: boolean; 
  startedAtUtcSeconds: bigint | string; 
  pointsSpent: number; 
  message: string; 
};

export type StartResearchRequestArgs = { 
  itemInstanceId: bigint | string; 
  itemContentId: string; 
};

export type CollectResearchResult = { 
  success: boolean; 
  outputContentId: string; 
  outputQuantity: number; 
  outputType: string; 
  message: string; 
};

export type CollectResearchRequestArgs = { 
  itemInstanceId: bigint | string; 
  itemContentId: string; 
};

export type GetPlayerLevelResult = { 
  success: boolean; 
  level: number; 
  totalXp: number; 
  xpForCurrentLevel: number; 
  xpIntoCurrentLevel: number; 
  message: string; 
};

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

export type PushOffer = { 
  itemId: string; 
  value: string; 
  customData: string; 
};

export type PushCampaignRequest = { 
  title: string; 
  body: string; 
  deepLink: string; 
  campaignId: string; 
  nodeId: string; 
  gamerTag: string; 
  accountId: string; 
  cidPid: string; 
  offers: PushOffer[]; 
  campaignData: string; 
};

export type SendCampaignPushToSelfRequestArgs = { 
  request: PushCampaignRequest; 
};

export type AdminSendResult = { 
  success: boolean; 
  attempted: number; 
  succeeded: number; 
  failed: number; 
  messages: string[]; 
};

export type PushOffer = { 
  itemId: string; 
  value: string; 
  customData: string; 
};

export type PushCampaignRequest = { 
  title: string; 
  body: string; 
  deepLink: string; 
  campaignId: string; 
  nodeId: string; 
  gamerTag: string; 
  accountId: string; 
  cidPid: string; 
  offers: PushOffer[]; 
  campaignData: string; 
};

export type SendCampaignPushToPlayerRequestArgs = { 
  playerId: bigint | string; 
  request: PushCampaignRequest; 
};

export type RegisteredPlayer = { 
  playerId: bigint | string; 
  deviceCount: number; 
  platforms: string[]; 
  lastUpdated: bigint | string; 
  gamePlatform: string; 
  gameDevice: string; 
};

export type RegisteredPlayerList = { 
  players: RegisteredPlayer[]; 
  message: string; 
};

export type FcmConfigStatus = { 
  configured: boolean; 
  privateKeyLoaded: boolean; 
  projectId: string; 
  clientEmail: string; 
  tokenUri: string; 
  message: string; 
};
