/**
 * ⚠️ THIS FILE IS AUTO-GENERATED. DO NOT EDIT MANUALLY.
 * All manual edits will be lost when this file is regenerated.
 */

import { BeamMicroServiceClient, type BeamBase } from '@beamable/sdk';
import type * as Types from './types';

declare module '@beamable/sdk' {
  interface BeamBase {
    /**
     * Access the BeamFarmMs microservice.
     * @remarks Before accessing this property, register it first via the `use` method.
     * @example
     * ```ts
     * // client-side:
     * beam.use(BeamFarmMsClient);
     * beam.beamFarmMsClient.serviceName;
     * // server-side:
     * beamServer.use(BeamFarmMsClient);
     * beamServer.beamFarmMsClient.serviceName;
     * ```
     */
    beamFarmMsClient: BeamFarmMsClient;
  }
}

export class BeamFarmMsClient extends BeamMicroServiceClient {
  readonly federationIds = {
    google: "google",
    gamecenter: "gamecenter"
  } as const;
  
  constructor(
    beam: BeamBase
  ) {
    super(beam);
  }
  
  get serviceName(): string {
    return "BeamFarmMs";
  }
  
  async plantSeed(params: Types.PlantSeedRequestArgs): Promise<Types.PlantResult> {
    return this.request({
      endpoint: "PlantSeed",
      payload: params,
      withAuth: true
    });
  }
  
  async collectHarvest(params: Types.CollectHarvestRequestArgs): Promise<Types.CollectResult> {
    return this.request({
      endpoint: "CollectHarvest",
      payload: params,
      withAuth: true
    });
  }
  
  async getSlotStates(params: Types.GetSlotStatesRequestArgs): Promise<Types.GetSlotStatesResult> {
    return this.request({
      endpoint: "GetSlotStates",
      payload: params,
      withAuth: true
    });
  }
  
  async registerGroundItem(params: Types.RegisterGroundItemRequestArgs): Promise<Types.RegisterGroundItemResult> {
    return this.request({
      endpoint: "RegisterGroundItem",
      payload: params,
      withAuth: true
    });
  }
  
  async collectGroundItem(params: Types.CollectGroundItemRequestArgs): Promise<Types.CollectGroundItemResult> {
    return this.request({
      endpoint: "CollectGroundItem",
      payload: params,
      withAuth: true
    });
  }
  
  async getGroundItems(params: Types.GetGroundItemsRequestArgs): Promise<Types.GetGroundItemsResult> {
    return this.request({
      endpoint: "GetGroundItems",
      payload: params,
      withAuth: true
    });
  }
  
  async getDeliveryOrders(): Promise<Types.GetDeliveryOrdersResult> {
    return this.request({
      endpoint: "GetDeliveryOrders",
      withAuth: true
    });
  }
  
  async fillDeliveryOrders(): Promise<Types.FillDeliveryOrdersResult> {
    return this.request({
      endpoint: "FillDeliveryOrders",
      withAuth: true
    });
  }
  
  async deliverOrder(params: Types.DeliverOrderRequestArgs): Promise<Types.DeliverOrderResult> {
    return this.request({
      endpoint: "DeliverOrder",
      payload: params,
      withAuth: true
    });
  }
  
  async mutateWithModifiers(params: Types.MutateWithModifiersRequestArgs): Promise<Types.MutateWithModifiersResult> {
    return this.request({
      endpoint: "MutateWithModifiers",
      payload: params,
      withAuth: true
    });
  }
  
  async startResearch(params: Types.StartResearchRequestArgs): Promise<Types.StartResearchResult> {
    return this.request({
      endpoint: "StartResearch",
      payload: params,
      withAuth: true
    });
  }
  
  async collectResearch(params: Types.CollectResearchRequestArgs): Promise<Types.CollectResearchResult> {
    return this.request({
      endpoint: "CollectResearch",
      payload: params,
      withAuth: true
    });
  }
  
  async getPlayerLevel(): Promise<Types.GetPlayerLevelResult> {
    return this.request({
      endpoint: "GetPlayerLevel",
      withAuth: true
    });
  }
  
  async registerDeviceToken(params: Types.RegisterDeviceTokenRequestArgs): Promise<Types.RegisterResult> {
    return this.request({
      endpoint: "RegisterDeviceToken",
      payload: params,
      withAuth: true
    });
  }
  
  async unregisterDeviceToken(params: Types.UnregisterDeviceTokenRequestArgs): Promise<Types.UnregisterResult> {
    return this.request({
      endpoint: "UnregisterDeviceToken",
      payload: params,
      withAuth: true
    });
  }
  
  async listMyDevices(): Promise<Types.DeviceList> {
    return this.request({
      endpoint: "ListMyDevices",
      withAuth: true
    });
  }
  
  async sendPushToSelf(params: Types.SendPushToSelfRequestArgs): Promise<Types.SendResult> {
    return this.request({
      endpoint: "SendPushToSelf",
      payload: params,
      withAuth: true
    });
  }
  
  async sendPushToPlayer(params: Types.SendPushToPlayerRequestArgs): Promise<Types.AdminSendResult> {
    return this.request({
      endpoint: "SendPushToPlayer",
      payload: params,
      withAuth: true
    });
  }
  
  async listRegisteredPlayers(): Promise<Types.RegisteredPlayerList> {
    return this.request({
      endpoint: "ListRegisteredPlayers",
      withAuth: true
    });
  }
  
  async checkFcmConfig(): Promise<Types.FcmConfigStatus> {
    return this.request({
      endpoint: "CheckFcmConfig",
      withAuth: true
    });
  }
}
