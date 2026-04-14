#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ChallengeSolution.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ContextInfo.h"

#include "AuthV2ExternalAuthRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAuthV2ExternalAuthRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Provider Namespace", Category="Beam")
	FOptionalBool bHasProviderNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider", Category="Beam")
	FOptionalString Provider = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FOptionalString Token = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Solution", Category="Beam")
	FOptionalAuthV2ChallengeSolution ChallengeSolution = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope", Category="Beam")
	FOptionalString Scope = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FOptionalBeamCid CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FOptionalBeamPid RealmId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Context", Category="Beam")
	FOptionalAuthV2ContextInfo Context = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};