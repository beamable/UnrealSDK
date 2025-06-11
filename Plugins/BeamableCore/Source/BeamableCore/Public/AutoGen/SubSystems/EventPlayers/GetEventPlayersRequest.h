
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EventPlayerView.h"

#include "GetEventPlayersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetEventPlayersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetEventPlayersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make GetEventPlayers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetEventPlayersRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventPlayersSuccess, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request, UEventPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventPlayersError, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetEventPlayersComplete, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request);

using FGetEventPlayersFullResponse = FBeamFullResponse<UGetEventPlayersRequest*, UEventPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnGetEventPlayersFullResponse, FGetEventPlayersFullResponse);
