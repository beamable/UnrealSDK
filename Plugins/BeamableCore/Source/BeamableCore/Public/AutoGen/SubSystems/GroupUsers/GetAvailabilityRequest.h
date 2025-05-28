
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamGroupType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/AvailabilityResponse.h"

#include "GetAvailabilityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailabilityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag", Category="Beam")
	FOptionalString Tag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group", Category="Beam")
	FOptionalBool bSubGroup = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailabilityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GetAvailability",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Name,_Tag,_bSubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAvailabilityRequest* Make(int64 _ObjectId, FOptionalString _Name, FOptionalString _Tag, EBeamGroupType _Type, FOptionalBool _bSubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailabilitySuccess, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request, UAvailabilityResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailabilityError, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailabilityComplete, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request);

using FGetAvailabilityFullResponse = FBeamFullResponse<UGetAvailabilityRequest*, UAvailabilityResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailabilityFullResponse, FGetAvailabilityFullResponse);
