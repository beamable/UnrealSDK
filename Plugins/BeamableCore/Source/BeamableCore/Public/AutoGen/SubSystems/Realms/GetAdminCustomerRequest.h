
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CustomerResponse.h"

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

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetAdminCustomer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAdminCustomerRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminCustomerSuccess, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request, UCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminCustomerError, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAdminCustomerComplete, FBeamRequestContext, Context, UGetAdminCustomerRequest*, Request);

using FGetAdminCustomerFullResponse = FBeamFullResponse<UGetAdminCustomerRequest*, UCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAdminCustomerFullResponse, FGetAdminCustomerFullResponse);
