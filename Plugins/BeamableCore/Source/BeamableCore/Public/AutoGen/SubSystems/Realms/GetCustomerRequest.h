
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CustomerViewResponse.h"

#include "GetCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCustomerRequest* MakeGetCustomerRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomerSuccess, FBeamRequestContext, Context, UGetCustomerRequest*, Request, UCustomerViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomerError, FBeamRequestContext, Context, UGetCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCustomerComplete, FBeamRequestContext, Context, UGetCustomerRequest*, Request);

using FGetCustomerFullResponse = FBeamFullResponse<UGetCustomerRequest*, UCustomerViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCustomerFullResponse, FGetCustomerFullResponse);
