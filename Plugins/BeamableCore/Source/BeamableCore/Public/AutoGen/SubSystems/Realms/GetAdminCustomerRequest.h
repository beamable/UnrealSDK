
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CustomerResponse.h"

#include "GetAdminCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAdminCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetAdminCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetAdminCustomerRequest* MakeGetAdminCustomerRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminCustomerSuccess, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request, UCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminCustomerError, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAdminCustomerComplete, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request);

using FGetAdminCustomerFullResponse = FBeamFullResponse<UGetAdminCustomerRequest*, UCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAdminCustomerFullResponse, FGetAdminCustomerFullResponse);
