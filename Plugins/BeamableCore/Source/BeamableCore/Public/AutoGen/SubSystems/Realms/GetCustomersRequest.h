
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CustomersResponse.h"

#include "GetCustomersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCustomersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCustomersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCustomersRequest* MakeGetCustomersRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomersSuccess, FBeamRequestContext, Context, UGetCustomersRequest*, Request, UCustomersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCustomersError, FBeamRequestContext, Context, UGetCustomersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCustomersComplete, FBeamRequestContext, Context, UGetCustomersRequest*, Request);

using FGetCustomersFullResponse = FBeamFullResponse<UGetCustomersRequest*, UCustomersResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCustomersFullResponse, FGetCustomersFullResponse);
