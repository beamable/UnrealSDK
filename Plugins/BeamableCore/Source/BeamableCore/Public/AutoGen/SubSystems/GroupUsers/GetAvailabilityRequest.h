
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"

#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/AvailabilityResponse.h"

#include "GetAvailabilityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailabilityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FOptionalString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag")
	FOptionalString Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	TMap<FString, FString> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group")
	FOptionalBool bSubGroup;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailabilityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Name,_Tag,_bSubGroup,Outer"))
	static UGetAvailabilityRequest* MakeGetAvailabilityRequest(int64 _ObjectId, FOptionalString _Name, FOptionalString _Tag, TMap<FString, FString> _Type, FOptionalBool _bSubGroup, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailabilitySuccess, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request, UAvailabilityResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailabilityError, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailabilityComplete, FBeamRequestContext, Context, UGetAvailabilityRequest*, Request);

using FGetAvailabilityFullResponse = FBeamFullResponse<UGetAvailabilityRequest*, UAvailabilityResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailabilityFullResponse, FGetAvailabilityFullResponse);
