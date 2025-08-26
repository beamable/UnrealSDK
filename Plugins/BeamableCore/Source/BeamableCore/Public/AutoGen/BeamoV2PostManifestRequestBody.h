#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceReference.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageReference.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "BeamoV2PostManifestRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2PostManifestRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Auto Deploy", Category="Beam")
	FOptionalBool bAutoDeploy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments", Category="Beam")
	FOptionalString Comments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest", Category="Beam")
	FOptionalArrayOfBeamoV2ServiceReference Manifest = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage References", Category="Beam")
	FOptionalArrayOfBeamoV2ServiceStorageReference StorageReferences = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};