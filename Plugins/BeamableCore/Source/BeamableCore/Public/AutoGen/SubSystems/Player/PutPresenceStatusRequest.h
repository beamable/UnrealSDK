
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SetPresenceStatusRequestBody.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#include "PutPresenceStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPresenceStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USetPresenceStatusRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutPresenceStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Player|Utils|Make/Break", DisplayName="Make PutPresenceStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Status,_Description,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPresenceStatusRequest* Make(FString _PlayerId, FOptionalPresenceStatus _Status, FOptionalString _Description, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPresenceStatusSuccess, FBeamRequestContext, Context, UPutPresenceStatusRequest*, Request, UOnlineStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPresenceStatusError, FBeamRequestContext, Context, UPutPresenceStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPresenceStatusComplete, FBeamRequestContext, Context, UPutPresenceStatusRequest*, Request);

using FPutPresenceStatusFullResponse = FBeamFullResponse<UPutPresenceStatusRequest*, UOnlineStatus*>;
DECLARE_DELEGATE_OneParam(FOnPutPresenceStatusFullResponse, FPutPresenceStatusFullResponse);
