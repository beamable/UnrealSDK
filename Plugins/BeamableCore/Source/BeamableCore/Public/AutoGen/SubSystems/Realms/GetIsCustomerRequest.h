
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/EmptyResponse.h"

#include "GetIsCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetIsCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetIsCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetIsCustomerRequest* MakeGetIsCustomerRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetIsCustomerSuccess, FBeamRequestContext, Context, UGetIsCustomerRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetIsCustomerError, FBeamRequestContext, Context, UGetIsCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetIsCustomerComplete, FBeamRequestContext, Context, UGetIsCustomerRequest*, Request);

using FGetIsCustomerFullResponse = FBeamFullResponse<UGetIsCustomerRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetIsCustomerFullResponse, FGetIsCustomerFullResponse);
