
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/MountSiteConfigStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/MountSiteSelectorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "RemotePortalConfigurationStreamData.generated.h"


UCLASS(BlueprintType)
class URemotePortalConfigurationStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMountSiteConfigStreamData*> MountSites = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UMountSiteConfigStreamData*>(TEXT("mountSites"), MountSites, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UMountSiteConfigStreamData*>(TEXT("mountSites"), MountSites, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UMountSiteConfigStreamData*>(TEXT("mountSites"), Bag, MountSites, OuterOwner);	
	}
};


