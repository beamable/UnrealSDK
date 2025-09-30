
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"

#include "ApiCustomerGetGamesByCustomerIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiCustomerGetGamesByCustomerIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiCustomerGetGamesByCustomerIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomerGetGamesByCustomerId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiCustomerGetGamesByCustomerIdRequest* Make(FString _CustomerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetGamesByCustomerIdSuccess, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdRequest*, Request, UGetGamesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetGamesByCustomerIdError, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiCustomerGetGamesByCustomerIdComplete, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdRequest*, Request);

using FApiCustomerGetGamesByCustomerIdFullResponse = FBeamFullResponse<UApiCustomerGetGamesByCustomerIdRequest*, UGetGamesResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiCustomerGetGamesByCustomerIdFullResponse, FApiCustomerGetGamesByCustomerIdFullResponse);
