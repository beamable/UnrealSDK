
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ManifestStorageEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestStorageEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CsprojPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldBeEnabledOnRemote = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamoId"), BeamoId);
		Serializer->WriteValue(TEXT("csprojPath"), CsprojPath);
		Serializer->WriteValue(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamoId"), BeamoId);
		Serializer->WriteValue(TEXT("csprojPath"), CsprojPath);
		Serializer->WriteValue(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BeamoId = Bag->GetStringField(TEXT("beamoId"));
		CsprojPath = Bag->GetStringField(TEXT("csprojPath"));
		ShouldBeEnabledOnRemote = Bag->GetBoolField(TEXT("shouldBeEnabledOnRemote"));	
	}
};


