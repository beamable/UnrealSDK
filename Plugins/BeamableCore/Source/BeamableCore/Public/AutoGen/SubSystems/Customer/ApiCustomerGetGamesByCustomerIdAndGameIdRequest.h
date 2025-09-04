
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"

#include "ApiCustomerGetGamesByCustomerIdAndGameIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiCustomerGetGamesByCustomerIdAndGameIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Id", Category="Beam")
	FString GameId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiCustomerGetGamesByCustomerIdAndGameIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomerGetGamesByCustomerIdAndGameId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiCustomerGetGamesByCustomerIdAndGameIdRequest* Make(FString _CustomerId, FString _GameId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetGamesByCustomerIdAndGameIdSuccess, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdAndGameIdRequest*, Request, UGetGamesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiCustomerGetGamesByCustomerIdAndGameIdError, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdAndGameIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiCustomerGetGamesByCustomerIdAndGameIdComplete, FBeamRequestContext, Context, UApiCustomerGetGamesByCustomerIdAndGameIdRequest*, Request);

using FApiCustomerGetGamesByCustomerIdAndGameIdFullResponse = FBeamFullResponse<UApiCustomerGetGamesByCustomerIdAndGameIdRequest*, UGetGamesResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiCustomerGetGamesByCustomerIdAndGameIdFullResponse, FApiCustomerGetGamesByCustomerIdAndGameIdFullResponse);
