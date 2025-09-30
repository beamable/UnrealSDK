
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RealmsBasicCustomersResponse.h"

#include "BasicRealmsGetCustomersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicRealmsGetCustomersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicRealmsGetCustomersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make BasicRealmsGetCustomers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicRealmsGetCustomersRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetCustomersSuccess, FBeamRequestContext, Context, UBasicRealmsGetCustomersRequest*, Request, URealmsBasicCustomersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetCustomersError, FBeamRequestContext, Context, UBasicRealmsGetCustomersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsGetCustomersComplete, FBeamRequestContext, Context, UBasicRealmsGetCustomersRequest*, Request);

using FBasicRealmsGetCustomersFullResponse = FBeamFullResponse<UBasicRealmsGetCustomersRequest*, URealmsBasicCustomersResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsGetCustomersFullResponse, FBasicRealmsGetCustomersFullResponse);
