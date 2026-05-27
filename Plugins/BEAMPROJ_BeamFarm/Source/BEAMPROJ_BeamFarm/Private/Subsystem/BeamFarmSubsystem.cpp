// Copyright Beamable, Inc. All Rights Reserved.

#include "Subsystem/BeamFarmSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Contents/BeamPlantContent.h"
#include "Contents/BeamSeedsContent.h"
#include "BeamSeedData.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsPlantSeedRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectHarvestRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterGroundItemRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectGroundItemRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsMutateWithModifiersRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetDeliveryOrdersRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsFillDeliveryOrdersRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsDeliverOrderRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsStartResearchRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectResearchRequest.h"
#include "AutoGen/MutateWithModifiersResult.h"
#include "AutoGen/DeliveryOrderInfo.h"
#include "AutoGen/DeliveryRequirement.h"
#include "Engine/Engine.h"

UBeamBeamFarmMsApi* UBeamFarmSubsystem::GetApi()
{
	if (!BeamFarmMsApi)
	{
		BeamFarmMsApi = GEngine->GetEngineSubsystem<UBeamBeamFarmMsApi>();
	}
	return BeamFarmMsApi;
}

UBeamContentSubsystem* UBeamFarmSubsystem::GetContentSub()
{
	if (!ContentSubsystem)
	{
		ContentSubsystem = GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
	}
	return ContentSubsystem;
}

void UBeamFarmSubsystem::PlantSeed(const FString& SeedContentId, const FString& SlotId, const FOnBeamFarmCallResult& OnResult)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResult.ExecuteIfBound(false, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsPlantSeedRequest::Make(SeedContentId, SlotId, this, TMap<FString, FString>{});
	FBeamRequestContext RequestContext;

	Api->CPP_PlantSeed(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsPlantSeedFullResponse::CreateLambda(
			[OnResult](FBeamFarmMsPlantSeedFullResponse Response)
			{
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					OnResult.ExecuteIfBound(true, TEXT(""));
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("PlantSeed failed");
					OnResult.ExecuteIfBound(false, Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::CollectHarvest(const FString& SlotId, const FOnBeamFarmCallResult& OnResult)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResult.ExecuteIfBound(false, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsCollectHarvestRequest::Make(SlotId, this, TMap<FString, FString>{});
	FBeamRequestContext RequestContext;

	Api->CPP_CollectHarvest(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsCollectHarvestFullResponse::CreateLambda(
			[OnResult](FBeamFarmMsCollectHarvestFullResponse Response)
			{
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					OnResult.ExecuteIfBound(true, Response.SuccessData->HarvestedItemContentId);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("CollectHarvest failed");
					OnResult.ExecuteIfBound(false, Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::RegisterGroundItem(const FBeamFarmGroundItemParams& Params, const FOnBeamFarmCallResult& OnResult)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResult.ExecuteIfBound(false, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsRegisterGroundItemRequest::Make(
		Params.GroundItemId,
		Params.ContentId,
		Params.Quantity,
		Params.ItemType,
		this,
		{}
	);
	FBeamRequestContext RequestContext;

	Api->CPP_RegisterGroundItem(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsRegisterGroundItemFullResponse::CreateLambda(
			[OnResult, GroundItemId = Params.GroundItemId](FBeamFarmMsRegisterGroundItemFullResponse Response)
			{
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					OnResult.ExecuteIfBound(true, TEXT(""));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("RegisterGroundItem failed for '%s': %s"),
						*GroundItemId,
						Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown error"));
					OnResult.ExecuteIfBound(false, Response.State == RS_Error ? Response.ErrorData.error : TEXT("unknown error"));
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::CollectGroundItem(const FString& GroundItemId, const FOnBeamFarmCallResult& OnResult)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResult.ExecuteIfBound(false, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsCollectGroundItemRequest::Make(GroundItemId, this, {});
	FBeamRequestContext RequestContext;

	Api->CPP_CollectGroundItem(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsCollectGroundItemFullResponse::CreateLambda(
			[OnResult, GroundItemId](FBeamFarmMsCollectGroundItemFullResponse Response)
			{
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					OnResult.ExecuteIfBound(true, TEXT(""));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("CollectGroundItem failed for '%s': %s — granting locally"),
						*GroundItemId,
						Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown error"));
					// Treat server failure as local success so the player keeps the item.
					OnResult.ExecuteIfBound(true, TEXT(""));
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::MutateWithModifiers(const FString& PlantItemContentId, int64 PlantItemInstanceId, const TArray<FString>& ModifierContentIds)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnMutationFailed.Broadcast(TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsMutateWithModifiersRequest::Make(PlantItemContentId, PlantItemInstanceId, ModifierContentIds, this, {});
	FBeamRequestContext RequestContext;
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	Api->CPP_MutateWithModifiers(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsMutateWithModifiersFullResponse::CreateLambda(
			[WeakThis](FBeamFarmMsMutateWithModifiersFullResponse Response)
			{
				if (!WeakThis.IsValid()) return;
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					FBeamFarmMutationResult Result;
					Result.NewProperties = Response.SuccessData->NewProperties;
					Result.Message       = Response.SuccessData->Message;
					WeakThis->OnMutationCompleted.Broadcast(Result);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("MutateWithModifiers failed");
					WeakThis->OnMutationFailed.Broadcast(Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

TArray<FBeamPlantData> UBeamFarmSubsystem::GetAllPlants()
{
	TArray<FBeamPlantData> Result;
	UBeamContentSubsystem* ContentSub = GetContentSub();
	if (!ContentSub)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBeamFarmSubsystem::GetAllPlants - Could not get BeamContentSubsystem"));
		return Result;
	}

	TArray<FBeamContentId> PlantIds;
	ContentSub->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);

	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSub->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
		{
			Result.Add(PlantContent->PlantData);
		}
	}

	return Result;
}

bool UBeamFarmSubsystem::FindSeedData(const FString& SeedContentId, FBeamSeedData& OutData)
{
	UBeamContentSubsystem* ContentSub = GetContentSub();
	if (!ContentSub)
	{
		return false;
	}

	TArray<FBeamContentId> SeedIds;
	ContentSub->GetIdsOfContentType(UBeamSeedsContent::StaticClass(), SeedIds, true);

	for (const FBeamContentId& SeedId : SeedIds)
	{
		if (SeedId.AsString == SeedContentId)
		{
			UBeamSeedsContent* SeedContent = nullptr;
			if (ContentSub->TryGetContentOfType<UBeamSeedsContent>(SeedId, SeedContent) && SeedContent)
			{
				OutData = SeedContent->SeedData;
				return true;
			}
		}
	}
	return false;
}

void UBeamFarmSubsystem::SetSelectedCrop(const FBeamSeedData& SeedData)
{
	SelectedCrop = SeedData;
	SelectedCropContentId = TEXT("");
	SetFarmingState(EFarmingInteractionState::Planting);
}

bool UBeamFarmSubsystem::SetSelectedCropBySeedId(const FString& SeedItemContentId)
{
	FBeamSeedData SeedData;
	if (FindSeedData(SeedItemContentId, SeedData))
	{
		SelectedCrop = SeedData;
		SelectedCropContentId = SeedItemContentId;
		SetFarmingState(EFarmingInteractionState::Planting);
		return true;
	}
	return false;
}

void UBeamFarmSubsystem::ClearSelectedCrop()
{
	SelectedCrop = FBeamSeedData();
	SelectedCropContentId = TEXT("");
	SetFarmingState(EFarmingInteractionState::Idle);
}

bool UBeamFarmSubsystem::HasSelectedCrop() const
{
	return !SelectedCrop.GrowingSprite.IsNull();
}

void UBeamFarmSubsystem::SetFarmingState(EFarmingInteractionState NewState)
{
	FarmingState = NewState;
	OnFarmingStateChanged.Broadcast(NewState);
}

void UBeamFarmSubsystem::HandleSlotInteraction(const FBeamFarmInteractionRequest& Request)
{
	if (Request.SlotState == EFarmSlotState::ReadyToHarvest)
	{
		if (Request.PlantedSeed.GrowingSprite.IsNull())
		{
			return;
		}

		const FString SlotId = Request.SlotId;
		TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

		OnSlotShouldHarvest.Broadcast(SlotId);

		CollectHarvest(SlotId, FOnBeamFarmCallResult::CreateLambda(
			[WeakThis, SlotId](bool bSuccess, const FString& PayloadOrError)
			{
				if (!WeakThis.IsValid()) return;
				if (bSuccess)
				{
					WeakThis->OnItemsHarvested.Broadcast(SlotId, PayloadOrError, 1);
				}
				else
				{
					WeakThis->OnCollectFailed.Broadcast(SlotId, PayloadOrError);
				}
			}));
		return;
	}

	if (Request.SlotState == EFarmSlotState::Growing)
	{
		return;
	}

	// Empty slot — use the subsystem's own selection state.
	if (!HasSelectedCrop())
	{
		OnNoCropSelected.Broadcast();
		return;
	}

	const FString SeedContentId = SelectedCropContentId;
	const FString SlotId = Request.SlotId;

	FBeamPlantData HarvestData;
	FindPlantBySeedId(SelectedCrop.HarvestItemContentId, HarvestData);

	OnSlotShouldPlant.Broadcast(SlotId, SelectedCrop, HarvestData);

	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	PlantSeed(SeedContentId, SlotId, FOnBeamFarmCallResult::CreateLambda(
		[WeakThis, SeedContentId, SlotId](bool bSuccess, const FString& PayloadOrError)
		{
			if (!WeakThis.IsValid()) return;
			if (bSuccess)
			{
				WeakThis->OnSeedConsumed.Broadcast(SeedContentId, 1);
			}
			else
			{
				WeakThis->OnSlotShouldCancelPlant.Broadcast(SlotId);
				WeakThis->OnPlantFailed.Broadcast(SlotId, PayloadOrError);
			}
		}));
}

bool UBeamFarmSubsystem::ResolveRandomPlantData(const TArray<FBeamContentId>& PlantContentIds, FBeamPlantData& OutData, FString& OutContentId)
{
	if (PlantContentIds.IsEmpty())
	{
		return false;
	}

	UBeamContentSubsystem* ContentSub = GetContentSub();
	if (!ContentSub)
	{
		return false;
	}

	const int32 StartIdx = FMath::RandRange(0, PlantContentIds.Num() - 1);
	for (int32 Attempt = 0; Attempt < PlantContentIds.Num(); ++Attempt)
	{
		const FBeamContentId& ContentId = PlantContentIds[(StartIdx + Attempt) % PlantContentIds.Num()];
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSub->TryGetContentOfType<UBeamPlantContent>(ContentId, PlantContent) && PlantContent)
		{
			OutData = PlantContent->PlantData;
			OutContentId = ContentId.AsString;
			return true;
		}
	}
	return false;
}

bool UBeamFarmSubsystem::FindPlantBySeedId(const FString& PlantContentId, FBeamPlantData& OutData)
{
	UBeamContentSubsystem* ContentSub = GetContentSub();
	if (!ContentSub)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBeamFarmSubsystem::FindPlantBySeedId - Could not get BeamContentSubsystem"));
		return false;
	}

	TArray<FBeamContentId> PlantIds;
	ContentSub->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);

	for (const FBeamContentId& PlantId : PlantIds)
	{
		if (PlantId.AsString == PlantContentId)
		{
			UBeamPlantContent* PlantContent = nullptr;
			if (ContentSub->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
			{
				OutData = PlantContent->PlantData;
				return true;
			}
		}
	}

	return false;
}

// ─── Collectible spawner management ──────────────────────────────────────────

void UBeamFarmSubsystem::RegisterSpawner(const FBeamFarmSpawnConfig& Config)
{
	if (Config.SpawnerId.IsEmpty() || !Config.CollectibleClass)
	{
		return;
	}

	SpawnerConfigs.Add(Config.SpawnerId, Config);
	SpawnerRuntimes.Add(Config.SpawnerId, FBeamFarmSpawnerRuntime{});

	StartSpawner(Config.SpawnerId);
}

void UBeamFarmSubsystem::UnregisterSpawner(const FString& SpawnerId)
{
	StopSpawner(SpawnerId);

	if (FBeamFarmSpawnerRuntime* Runtime = SpawnerRuntimes.Find(SpawnerId))
	{
		for (const TWeakObjectPtr<ABeamFarmCollectibleActor>& Weak : Runtime->ActiveCollectibles)
		{
			if (Weak.IsValid())
			{
				Weak->Destroy();
			}
		}
	}

	SpawnerConfigs.Remove(SpawnerId);
	SpawnerRuntimes.Remove(SpawnerId);
	SpawnTimers.Remove(SpawnerId);
}

void UBeamFarmSubsystem::StartSpawner(const FString& SpawnerId)
{
	const FBeamFarmSpawnConfig* Config = SpawnerConfigs.Find(SpawnerId);
	if (!Config)
	{
		return;
	}

	if (Config->SpawnMode == EBeamFarmSpawnMode::FixedTransforms && Config->SpawnTransforms.IsEmpty())
	{
		return;
	}
	if (Config->SpawnMode == EBeamFarmSpawnMode::WeightedZones && Config->PlantContentIds.IsEmpty())
	{
		return;
	}

	UWorld* World = GetGameInstance()->GetWorld();
	if (!World)
	{
		return;
	}

	const FString CapturedId = SpawnerId;
	FTimerDelegate TimerDel;
	TimerDel.BindLambda([this, CapturedId]() { OnSpawnTimer(CapturedId); });

	FTimerHandle& Timer = SpawnTimers.FindOrAdd(SpawnerId);
	World->GetTimerManager().SetTimer(Timer, TimerDel, Config->SpawnIntervalSeconds, true, 0.f);
}

void UBeamFarmSubsystem::StopSpawner(const FString& SpawnerId)
{
	if (FTimerHandle* Timer = SpawnTimers.Find(SpawnerId))
	{
		UWorld* World = GetGameInstance()->GetWorld();
		if (World)
		{
			World->GetTimerManager().ClearTimer(*Timer);
		}
	}
}

void UBeamFarmSubsystem::OnSpawnTimer(FString SpawnerId)
{
	FBeamFarmSpawnerRuntime* Runtime = SpawnerRuntimes.Find(SpawnerId);
	if (!Runtime)
	{
		return;
	}

	Runtime->ActiveCollectibles.RemoveAll(
		[](const TWeakObjectPtr<ABeamFarmCollectibleActor>& W) { return !W.IsValid(); });

	const FBeamFarmSpawnConfig* Config = SpawnerConfigs.Find(SpawnerId);
	if (!Config || Runtime->ActiveCollectibles.Num() >= Config->MaxActiveCollectibles)
	{
		return;
	}

	SpawnCollectibleForSpawner(SpawnerId);
}

void UBeamFarmSubsystem::SpawnCollectibleForSpawner(const FString& SpawnerId)
{
	const FBeamFarmSpawnConfig* Config = SpawnerConfigs.Find(SpawnerId);
	FBeamFarmSpawnerRuntime* Runtime = SpawnerRuntimes.Find(SpawnerId);
	if (!Config || !Runtime || !Config->CollectibleClass)
	{
		return;
	}

	UWorld* World = GetGameInstance()->GetWorld();
	if (!World)
	{
		return;
	}

	FTransform SpawnT;
	FBeamFarmCollectibleInfo Info;

	if (Config->SpawnMode == EBeamFarmSpawnMode::FixedTransforms)
	{
		if (Config->SpawnTransforms.IsEmpty())
		{
			return;
		}

		const int32 SlotCount = Config->SpawnTransforms.Num();
		bool bFoundSlot = false;

		for (int32 Attempt = 0; Attempt < SlotCount; ++Attempt)
		{
			const int32 Index = (Runtime->NextSpawnIndex + Attempt) % SlotCount;
			const FTransform& Candidate = Config->SpawnTransforms[Index];

			bool bOccupied = false;
			for (const TWeakObjectPtr<ABeamFarmCollectibleActor>& Existing : Runtime->ActiveCollectibles)
			{
				if (Existing.IsValid() && FVector::Dist2D(Existing->GetActorLocation(), Candidate.GetLocation()) < 10.f)
				{
					bOccupied = true;
					break;
				}
			}

			if (!bOccupied)
			{
				SpawnT = Candidate;
				Runtime->NextSpawnIndex = (Index + 1) % SlotCount;
				bFoundSlot = true;
				break;
			}
		}
		if (!bFoundSlot)
		{
			return;
		}

		Info.ContentId = Config->SeedMaterialContentId;
		Info.Quantity  = Config->QuantityPerCollectible;
		Info.ItemType  = TEXT("RawMaterial");
		Info.SeedData  = Config->MaterialData;
	}
	else // WeightedZones
	{
		FBeamPlantData ResolvedPlant;
		FString ResolvedContentId;
		if (!ResolveRandomPlantData(Config->PlantContentIds, ResolvedPlant, ResolvedContentId))
		{
			UE_LOG(LogTemp, Warning, TEXT("UBeamFarmSubsystem: failed to resolve plant for spawner '%s'"), *SpawnerId);
			return;
		}

		FVector SpawnLocation;
		if (!TryPickSpawnPointForSpawner(SpawnerId, SpawnLocation))
		{
			return;
		}

		SpawnT = FTransform(FRotator::ZeroRotator, SpawnLocation);
		Info.ContentId  = ResolvedContentId;
		Info.Quantity   = Config->QuantityPerCollectible;
		Info.ItemType   = TEXT("PlantItem");
		Info.PlantData  = ResolvedPlant;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABeamFarmCollectibleActor* Spawned = World->SpawnActor<ABeamFarmCollectibleActor>(Config->CollectibleClass, SpawnT, Params);
	if (!Spawned)
	{
		return;
	}

	const FString GroundItemId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);
	Spawned->GroundItemId = GroundItemId;
	Spawned->SpawnerId    = SpawnerId;
	Info.Quantity = Config->QuantityPerCollectible;
	Spawned->SetItemInfo(Info);

	Spawned->OnPickedUp.AddDynamic(this, &UBeamFarmSubsystem::HandleCollectiblePickedUp);
	Runtime->ActiveCollectibles.Add(Spawned);

	FBeamFarmGroundItemParams RegParams;
	RegParams.GroundItemId = GroundItemId;
	RegParams.ContentId    = Info.ContentId;
	RegParams.Quantity     = Config->QuantityPerCollectible;
	RegParams.ItemType     = Info.ItemType;

	RegisterGroundItem(RegParams, FOnBeamFarmCallResult::CreateLambda(
		[GroundItemId](bool bSuccess, const FString& Err)
		{
			if (!bSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("RegisterGroundItem failed for '%s': %s"), *GroundItemId, *Err);
			}
		}));

	OnSpawnerCollectibleSpawned.Broadcast(SpawnerId, Spawned, SpawnT);
}

void UBeamFarmSubsystem::HandleCollectiblePickedUp(ABeamFarmCollectibleActor* Collectible, APawn* Collector)
{
	if (!Collectible)
	{
		return;
	}

	const FString SpawnerId = Collectible->SpawnerId;

	if (FBeamFarmSpawnerRuntime* Runtime = SpawnerRuntimes.Find(SpawnerId))
	{
		Runtime->ActiveCollectibles.RemoveAll(
			[Collectible](const TWeakObjectPtr<ABeamFarmCollectibleActor>& W)
			{
				return !W.IsValid() || W.Get() == Collectible;
			});
	}

	const FString GroundItemId         = Collectible->GroundItemId;
	const FBeamFarmCollectibleInfo Info = Collectible->ItemInfo;
	TWeakObjectPtr<APawn> WeakCollector(Collector);
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	if (!GroundItemId.IsEmpty())
	{
		CollectGroundItem(GroundItemId, FOnBeamFarmCallResult::CreateLambda(
			[WeakThis, SpawnerId, WeakCollector, Info](bool, const FString&)
			{
				if (!WeakThis.IsValid()) return;
				WeakThis->OnSpawnerCollectibleCollected.Broadcast(SpawnerId, WeakCollector.Get(), Info);
			}));
	}
	else
	{
		OnSpawnerCollectibleCollected.Broadcast(SpawnerId, Collector, Info);
	}
}

// ─── Delivery ────────────────────────────────────────────────────────────────

void UBeamFarmSubsystem::GetDeliveryOrders()
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnDeliveryOrdersReceived.Broadcast(TArray<FBeamDeliveryOrderInfo>{});
		return;
	}

	auto* Request = UBeamFarmMsGetDeliveryOrdersRequest::Make(this, {});
	FBeamRequestContext RequestContext;
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	Api->CPP_GetDeliveryOrders(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsGetDeliveryOrdersFullResponse::CreateLambda(
			[WeakThis](FBeamFarmMsGetDeliveryOrdersFullResponse Response)
			{
				if (!WeakThis.IsValid()) return;

				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					TArray<FBeamDeliveryOrderInfo> Orders;
					for (const UDeliveryOrderInfo* Info : Response.SuccessData->Orders)
					{
						if (!Info) continue;

						FBeamDeliveryOrderInfo Order;
						Order.OrderId                = Info->OrderId;
						Order.DisplayName            = Info->DisplayName;
						Order.RequiredItemContentId  = Info->RequiredItemContentId;
						Order.RewardCurrencyId       = Info->RewardCurrencyId;
						Order.RewardAmount           = Info->RewardAmount;

						for (const UDeliveryRequirement* Req : Info->Requirements)
						{
							if (!Req) continue;
							FBeamDeliveryRequirement Requirement;
							Requirement.PropertyName = Req->PropertyName;
							Requirement.Comparison   = Req->Comparison == TEXT("GreaterThan")
								? EBeamDeliveryComparison::BEAM_GreaterThan
								: EBeamDeliveryComparison::BEAM_LowerThan;
							Requirement.Value        = Req->Value;
							Order.Requirements.Add(Requirement);
						}

						Orders.Add(Order);
					}
					WeakThis->OnDeliveryOrdersReceived.Broadcast(Orders);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("GetDeliveryOrders failed");
					UE_LOG(LogTemp, Warning, TEXT("UBeamFarmSubsystem::GetDeliveryOrders failed: %s"), *Err);
					WeakThis->OnDeliveryOrdersReceived.Broadcast(TArray<FBeamDeliveryOrderInfo>{});
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::FillDeliveryOrders()
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		return;
	}

	auto* Request = UBeamFarmMsFillDeliveryOrdersRequest::Make(this, {});
	FBeamRequestContext RequestContext;

	Api->CPP_FillDeliveryOrders(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsFillDeliveryOrdersFullResponse::CreateLambda(
			[](FBeamFarmMsFillDeliveryOrdersFullResponse Response)
			{
				if (Response.State == RS_Success && Response.SuccessData)
				{
					UE_LOG(LogTemp, Log, TEXT("FillDeliveryOrders: added %d order(s), total %d."),
						Response.SuccessData->OrdersAdded, Response.SuccessData->TotalOrders);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("FillDeliveryOrders failed");
					UE_LOG(LogTemp, Warning, TEXT("UBeamFarmSubsystem::FillDeliveryOrders failed: %s"), *Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::DeliverOrder(const FString& OrderId, int64 ItemInstanceId)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnDeliveryFailed.Broadcast(OrderId, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsDeliverOrderRequest::Make(OrderId, ItemInstanceId, this, {});
	FBeamRequestContext RequestContext;
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	Api->CPP_DeliverOrder(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsDeliverOrderFullResponse::CreateLambda(
			[WeakThis, OrderId](FBeamFarmMsDeliverOrderFullResponse Response)
			{
				if (!WeakThis.IsValid()) return;

				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					WeakThis->OnDeliveryCompleted.Broadcast(
						Response.SuccessData->OrderId,
						Response.SuccessData->RewardCurrencyId,
						Response.SuccessData->RewardAmount);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("DeliverOrder failed");
					WeakThis->OnDeliveryFailed.Broadcast(OrderId, Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

// ─── Research ────────────────────────────────────────────────────────────────

void UBeamFarmSubsystem::StartResearch(int64 ItemInstanceId, const FString& ItemContentId, const FString& ProjectContentId)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResearchStartFailed.Broadcast(ItemInstanceId, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsStartResearchRequest::Make(ItemInstanceId, ItemContentId, ProjectContentId, this, {});
	FBeamRequestContext RequestContext;
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	Api->CPP_StartResearch(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsStartResearchFullResponse::CreateLambda(
			[WeakThis, ItemInstanceId](FBeamFarmMsStartResearchFullResponse Response)
			{
				if (!WeakThis.IsValid()) return;
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					WeakThis->OnResearchStarted.Broadcast(
						ItemInstanceId,
						Response.SuccessData->StartedAtUtcSeconds,
						Response.SuccessData->PointsSpent);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("StartResearch failed");
					WeakThis->OnResearchStartFailed.Broadcast(ItemInstanceId, Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

void UBeamFarmSubsystem::CollectResearch(int64 ItemInstanceId, const FString& ItemContentId)
{
	UBeamBeamFarmMsApi* Api = GetApi();
	if (!Api)
	{
		OnResearchCollectFailed.Broadcast(ItemInstanceId, TEXT("BeamFarmMsApi not available"));
		return;
	}

	auto* Request = UBeamFarmMsCollectResearchRequest::Make(ItemInstanceId, ItemContentId, this, {});
	FBeamRequestContext RequestContext;
	TWeakObjectPtr<UBeamFarmSubsystem> WeakThis(this);

	Api->CPP_CollectResearch(
		FUserSlot{UserSlotName},
		Request,
		FOnBeamFarmMsCollectResearchFullResponse::CreateLambda(
			[WeakThis, ItemInstanceId](FBeamFarmMsCollectResearchFullResponse Response)
			{
				if (!WeakThis.IsValid()) return;
				if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
				{
					WeakThis->OnResearchCollected.Broadcast(
						ItemInstanceId,
						Response.SuccessData->OutputContentId,
						Response.SuccessData->OutputQuantity,
						Response.SuccessData->OutputType);
				}
				else
				{
					const FString Err = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("CollectResearch failed");
					WeakThis->OnResearchCollectFailed.Broadcast(ItemInstanceId, Err);
				}
			}),
		RequestContext,
		FBeamOperationHandle(),
		this
	);
}

bool UBeamFarmSubsystem::TryPickSpawnPointForSpawner(const FString& SpawnerId, FVector& OutLocation)
{
	const FBeamFarmSpawnConfig* Config = SpawnerConfigs.Find(SpawnerId);
	const FBeamFarmSpawnerRuntime* Runtime = SpawnerRuntimes.Find(SpawnerId);
	if (!Config || !Runtime)
	{
		return false;
	}

	float TotalWeight = 0.f;
	for (const FBeamFarmSpawnZone& Zone : Config->SpawnZones)
	{
		TotalWeight += FMath::Max(Zone.Weight, 0.f);
	}

	for (int32 Attempt = 0; Attempt < Config->MaxSpawnAttempts; ++Attempt)
	{
		FVector2D Candidate;

		if (Config->SpawnZones.IsEmpty() || TotalWeight <= 0.f)
		{
			Candidate.X = FMath::RandRange(Config->BaseAreaCenter.X - Config->BaseAreaHalfExtents.X, Config->BaseAreaCenter.X + Config->BaseAreaHalfExtents.X);
			Candidate.Y = FMath::RandRange(Config->BaseAreaCenter.Y - Config->BaseAreaHalfExtents.Y, Config->BaseAreaCenter.Y + Config->BaseAreaHalfExtents.Y);
		}
		else
		{
			float Roll = FMath::FRandRange(0.f, TotalWeight);
			const FBeamFarmSpawnZone* Selected = &Config->SpawnZones.Last();
			for (const FBeamFarmSpawnZone& Zone : Config->SpawnZones)
			{
				Roll -= FMath::Max(Zone.Weight, 0.f);
				if (Roll <= 0.f)
				{
					Selected = &Zone;
					break;
				}
			}
			Candidate.X = FMath::RandRange(Selected->Center.X - Selected->HalfExtents.X, Selected->Center.X + Selected->HalfExtents.X);
			Candidate.Y = FMath::RandRange(Selected->Center.Y - Selected->HalfExtents.Y, Selected->Center.Y + Selected->HalfExtents.Y);
		}

		bool bExcluded = false;
		for (const FBeamFarmExclusionZone& Zone : Config->ExclusionZones)
		{
			if (FMath::Abs(Candidate.X - Zone.Center.X) <= Zone.HalfExtents.X &&
				FMath::Abs(Candidate.Y - Zone.Center.Y) <= Zone.HalfExtents.Y)
			{
				bExcluded = true;
				break;
			}
		}
		if (bExcluded)
		{
			continue;
		}

		const FVector CandidateWorld(Candidate.X, Candidate.Y, Config->SpawnZ);
		bool bTooClose = false;
		for (const TWeakObjectPtr<ABeamFarmCollectibleActor>& Existing : Runtime->ActiveCollectibles)
		{
			if (Existing.IsValid() && FVector::Dist2D(Existing->GetActorLocation(), CandidateWorld) < Config->MinSpawnSeparation)
			{
				bTooClose = true;
				break;
			}
		}
		if (bTooClose)
		{
			continue;
		}

		OutLocation = CandidateWorld;
		return true;
	}

	return false;
}
