
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CustomerViewResponse.h"

#include "BasicRealmsGetCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicRealmsGetCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicRealmsGetCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make BasicRealmsGetCustomer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicRealmsGetCustomerRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetCustomerSuccess, FBeamRequestContext, Context, UBasicRealmsGetCustomerRequest*, Request, UCustomerViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetCustomerError, FBeamRequestContext, Context, UBasicRealmsGetCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsGetCustomerComplete, FBeamRequestContext, Context, UBasicRealmsGetCustomerRequest*, Request);

using FBasicRealmsGetCustomerFullResponse = FBeamFullResponse<UBasicRealmsGetCustomerRequest*, UCustomerViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsGetCustomerFullResponse, FBasicRealmsGetCustomerFullResponse);
