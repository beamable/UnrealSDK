
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CustomerActorCustomersResponse.h"

#include "ApiCustomerGetCustomersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiCustomerGetCustomersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiCustomerGetCustomersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomerGetCustomers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiCustomerGetCustomersRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetCustomersSuccess, FBeamRequestContext, Context, UApiCustomerGetCustomersRequest*, Request, UCustomerActorCustomersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetCustomersError, FBeamRequestContext, Context, UApiCustomerGetCustomersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiCustomerGetCustomersComplete, FBeamRequestContext, Context, UApiCustomerGetCustomersRequest*, Request);

using FApiCustomerGetCustomersFullResponse = FBeamFullResponse<UApiCustomerGetCustomersRequest*, UCustomerActorCustomersResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiCustomerGetCustomersFullResponse, FApiCustomerGetCustomersFullResponse);
