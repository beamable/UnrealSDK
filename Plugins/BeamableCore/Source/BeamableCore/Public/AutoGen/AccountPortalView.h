#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamExternalIdentity.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRoleMapping.h"

#include "AccountPortalView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAccountPortalView : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FBeamAccountId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes", Category="Beam")
	TArray<FString> Scopes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party App Associations", Category="Beam")
	TArray<FString> ThirdPartyAppAssociations = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role String", Category="Beam")
	FOptionalString RoleString = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	FOptionalArrayOfBeamExternalIdentity External = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles", Category="Beam")
	FOptionalArrayOfRoleMapping Roles = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};