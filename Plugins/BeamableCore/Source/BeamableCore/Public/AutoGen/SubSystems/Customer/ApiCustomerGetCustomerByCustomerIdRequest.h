
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerView.h"

#include "ApiCustomerGetCustomerByCustomerIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiCustomerGetCustomerByCustomerIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiCustomerGetCustomerByCustomerIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomerGetCustomerByCustomerId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiCustomerGetCustomerByCustomerIdRequest* Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetCustomerByCustomerIdSuccess, FBeamRequestContext, Context, UApiCustomerGetCustomerByCustomerIdRequest*, Request, UCustomerActorCustomerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetCustomerByCustomerIdError, FBeamRequestContext, Context, UApiCustomerGetCustomerByCustomerIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiCustomerGetCustomerByCustomerIdComplete, FBeamRequestContext, Context, UApiCustomerGetCustomerByCustomerIdRequest*, Request);

using FApiCustomerGetCustomerByCustomerIdFullResponse = FBeamFullResponse<UApiCustomerGetCustomerByCustomerIdRequest*, UCustomerActorCustomerView*>;
DECLARE_DELEGATE_OneParam(FOnApiCustomerGetCustomerByCustomerIdFullResponse, FApiCustomerGetCustomerByCustomerIdFullResponse);
