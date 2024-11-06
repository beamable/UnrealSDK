
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ManifestViewStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalLongStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DeploymentDiffSummaryStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DeploymentManifestJsonDiffStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceFederationChangeStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceImageIdChangeStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "DeployablePlanStreamData.generated.h"


UCLASS()
class UDeployablePlanStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString BuiltFromRemoteChecksum = {};
	UPROPERTY()
	FString Mode = {};
	UPROPERTY()
	UManifestViewStreamData* Manifest = {};
	UPROPERTY()
	UDeploymentDiffSummaryStreamData* Diff = {};
	UPROPERTY()
	TArray<FString> ServicesToUpload = {};
	UPROPERTY()
	bool RanHealthChecks = {};
	UPROPERTY()
	int32 ChangeCount = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("builtFromRemoteChecksum"), BuiltFromRemoteChecksum);
		Serializer->WriteValue(TEXT("mode"), Mode);
		UBeamJsonUtils::SerializeUObject<UManifestViewStreamData*>("manifest", Manifest, Serializer);
		UBeamJsonUtils::SerializeUObject<UDeploymentDiffSummaryStreamData*>("diff", Diff, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("servicesToUpload"), ServicesToUpload, Serializer);
		Serializer->WriteValue(TEXT("ranHealthChecks"), RanHealthChecks);
		Serializer->WriteValue(TEXT("changeCount"), ChangeCount);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("builtFromRemoteChecksum"), BuiltFromRemoteChecksum);
		Serializer->WriteValue(TEXT("mode"), Mode);
		UBeamJsonUtils::SerializeUObject<UManifestViewStreamData*>("manifest", Manifest, Serializer);
		UBeamJsonUtils::SerializeUObject<UDeploymentDiffSummaryStreamData*>("diff", Diff, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("servicesToUpload"), ServicesToUpload, Serializer);
		Serializer->WriteValue(TEXT("ranHealthChecks"), RanHealthChecks);
		Serializer->WriteValue(TEXT("changeCount"), ChangeCount);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BuiltFromRemoteChecksum = Bag->GetStringField(TEXT("builtFromRemoteChecksum"));
		Mode = Bag->GetStringField(TEXT("mode"));
		UBeamJsonUtils::DeserializeUObject<UManifestViewStreamData*>("manifest", Bag, Manifest, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UDeploymentDiffSummaryStreamData*>("diff", Bag, Diff, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("servicesToUpload")), ServicesToUpload, OuterOwner);
		RanHealthChecks = Bag->GetBoolField(TEXT("ranHealthChecks"));
		ChangeCount = Bag->GetIntegerField(TEXT("changeCount"));	
	}
};


