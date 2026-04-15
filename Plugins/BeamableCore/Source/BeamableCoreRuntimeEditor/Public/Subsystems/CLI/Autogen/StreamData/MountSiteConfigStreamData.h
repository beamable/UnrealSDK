
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/MountSiteSelectorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "MountSiteConfigStreamData.generated.h"


UCLASS(BlueprintType)
class UMountSiteConfigStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMountSiteSelectorStreamData*> Selectors = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> NavContext = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
		UBeamJsonUtils::SerializeArray<UMountSiteSelectorStreamData*>(TEXT("selectors"), Selectors, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("navContext"), NavContext, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
		UBeamJsonUtils::SerializeArray<UMountSiteSelectorStreamData*>(TEXT("selectors"), Selectors, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("navContext"), NavContext, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("path"), Bag, Path);
		UBeamJsonUtils::DeserializeArray<UMountSiteSelectorStreamData*>(TEXT("selectors"), Bag, Selectors, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("navContext"), Bag, NavContext, OuterOwner);	
	}
};


