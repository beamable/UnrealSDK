
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPresencePutPlayerPresenceResponse.h"

#include "PutPresenceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPresenceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutPresenceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Player|Utils|Make/Break", DisplayName="Make PutPresence",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPresenceRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPresenceSuccess, FBeamRequestContext, Context, UPutPresenceRequest*, Request, UApiPlayersPresencePutPlayerPresenceResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPresenceError, FBeamRequestContext, Context, UPutPresenceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPresenceComplete, FBeamRequestContext, Context, UPutPresenceRequest*, Request);

using FPutPresenceFullResponse = FBeamFullResponse<UPutPresenceRequest*, UApiPlayersPresencePutPlayerPresenceResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutPresenceFullResponse, FPutPresenceFullResponse);
