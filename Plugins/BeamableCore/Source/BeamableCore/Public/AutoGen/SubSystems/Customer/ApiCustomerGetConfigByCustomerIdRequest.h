
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#include "ApiCustomerGetConfigByCustomerIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiCustomerGetConfigByCustomerIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiCustomerGetConfigByCustomerIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomerGetConfigByCustomerId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiCustomerGetConfigByCustomerIdRequest* Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetConfigByCustomerIdSuccess, FBeamRequestContext, Context, UApiCustomerGetConfigByCustomerIdRequest*, Request, URealmConfigResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetConfigByCustomerIdError, FBeamRequestContext, Context, UApiCustomerGetConfigByCustomerIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiCustomerGetConfigByCustomerIdComplete, FBeamRequestContext, Context, UApiCustomerGetConfigByCustomerIdRequest*, Request);

using FApiCustomerGetConfigByCustomerIdFullResponse = FBeamFullResponse<UApiCustomerGetConfigByCustomerIdRequest*, URealmConfigResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiCustomerGetConfigByCustomerIdFullResponse, FApiCustomerGetConfigByCustomerIdFullResponse);
