
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DeploymentManifestJsonDiffStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceFederationChangeStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceImageIdChangeStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "DeploymentDiffSummaryStreamData.generated.h"


UCLASS()
class UDeploymentDiffSummaryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UDeploymentManifestJsonDiffStreamData*> JsonChanges = {};
	UPROPERTY()
	TArray<FString> AddedServices = {};
	UPROPERTY()
	TArray<FString> RemovedServices = {};
	UPROPERTY()
	TArray<FString> DisabledServices = {};
	UPROPERTY()
	TArray<FString> EnabledServices = {};
	UPROPERTY()
	TArray<FString> AddedStorage = {};
	UPROPERTY()
	TArray<FString> RemovedStorage = {};
	UPROPERTY()
	TArray<FString> DisabledStorages = {};
	UPROPERTY()
	TArray<FString> EnabledStorages = {};
	UPROPERTY()
	TArray<UServiceFederationChangeStreamData*> AddedFederations = {};
	UPROPERTY()
	TArray<UServiceFederationChangeStreamData*> RemovedFederations = {};
	UPROPERTY()
	TArray<UServiceImageIdChangeStreamData*> ServiceImageIdChanges = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeploymentManifestJsonDiffStreamData*>(TEXT("jsonChanges"), JsonChanges, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("addedServices"), AddedServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("removedServices"), RemovedServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("disabledServices"), DisabledServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("enabledServices"), EnabledServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("addedStorage"), AddedStorage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("removedStorage"), RemovedStorage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("disabledStorages"), DisabledStorages, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("enabledStorages"), EnabledStorages, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceFederationChangeStreamData*>(TEXT("addedFederations"), AddedFederations, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceFederationChangeStreamData*>(TEXT("removedFederations"), RemovedFederations, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceImageIdChangeStreamData*>(TEXT("serviceImageIdChanges"), ServiceImageIdChanges, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeploymentManifestJsonDiffStreamData*>(TEXT("jsonChanges"), JsonChanges, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("addedServices"), AddedServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("removedServices"), RemovedServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("disabledServices"), DisabledServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("enabledServices"), EnabledServices, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("addedStorage"), AddedStorage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("removedStorage"), RemovedStorage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("disabledStorages"), DisabledStorages, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("enabledStorages"), EnabledStorages, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceFederationChangeStreamData*>(TEXT("addedFederations"), AddedFederations, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceFederationChangeStreamData*>(TEXT("removedFederations"), RemovedFederations, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceImageIdChangeStreamData*>(TEXT("serviceImageIdChanges"), ServiceImageIdChanges, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UDeploymentManifestJsonDiffStreamData*>(Bag->GetArrayField(TEXT("jsonChanges")), JsonChanges, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("addedServices")), AddedServices, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("removedServices")), RemovedServices, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("disabledServices")), DisabledServices, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("enabledServices")), EnabledServices, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("addedStorage")), AddedStorage, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("removedStorage")), RemovedStorage, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("disabledStorages")), DisabledStorages, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("enabledStorages")), EnabledStorages, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServiceFederationChangeStreamData*>(Bag->GetArrayField(TEXT("addedFederations")), AddedFederations, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServiceFederationChangeStreamData*>(Bag->GetArrayField(TEXT("removedFederations")), RemovedFederations, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServiceImageIdChangeStreamData*>(Bag->GetArrayField(TEXT("serviceImageIdChanges")), ServiceImageIdChanges, OuterOwner);	
	}
};


